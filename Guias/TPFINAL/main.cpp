//Para compilar: g++ -o guia5 guia5.cpp -O0 -lm -lpthread -lX11 -lfftw3 && ./guia5

#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions.h"
#include <cstdlib>
#include <complex>
#include <string>
#include <cmath>
#include <cassert>

using namespace cimg_library;
using namespace std;

/// Retorno una convolucion de una imagen con un filtro trabajando en el espectro de frec
CImg<double> get_img_from_filter(CImg<double> base, CImgList<double> filtro) {

    // Obtengo la transformada y su magnitud/fase
    CImgList<double> fft = base.get_FFT();

    // Multiplico por el filtro
    cimg_forXY(fft[0], u, v) {
        complex<double>
            part1(fft[0](u, v), fft[1](u, v)),
            part2(filtro[0](u, v), filtro[1](u, v)),
            resultado = part1 * part2;

        fft[0](u, v) = real(resultado);
        fft[1](u, v) = imag(resultado);
    }

    CImg<double> resultado = fft.get_FFT(true)[0];

    return resultado;
}


/// Obtengo la distancia al punto (x, y) desde cada puntos de una matriz
CImg<double> get_D_matriz(CImg<double> base, int x = -1, int y = -1) {

    CImg<double> D_matriz(base.width(), base.height());

    // Si no especificamos el punto (-1, -1), toma el centro de la matriz
    if (x == -1 && y == -1) {
        x = D_matriz.width() / 2;
        y = D_matriz.height() / 2;
    }

    cimg_forXY(D_matriz, u, v) {
        D_matriz(u, v) = pow(pow(u - x, 2) + pow(v - y, 2), 0.5);
    }

    return D_matriz;
}

/// Genera el filtro H(u, v) para filtrado homomorfico
CImgList<> get_H_homomorphic(
    CImg<double> base,
    unsigned int cutoff_frecuency,
    double gamma_l = 0.5,
    double gamma_h = 2.0,
    double c = 1.0) {

    CImg<double> H(base.width(), base.height()),
        D_matriz(get_D_matriz(base));

    cimg_forXY(H, u, v) {
        double factor = 1 - exp(-c * pow(D_matriz(u, v), 2) / pow(cutoff_frecuency, 2));

        H(u, v) = (gamma_h - gamma_l) * factor + gamma_l;
    }

    // Y lo deshifteamos
    H.shift(-H.width()/2, -H.height()/2, 0, 0, 2);

    // La parte imaginaria es cero
    return (H, H.get_fill(0));
}

/// Aplica un filtro haciendo filtrado homomorfico
CImg<double> get_image_homomorphic(CImg<double> base, CImgList<> H) {

    // Una imagen f(x, y) = i(x, y) * r(x, y), por lo que aplicamos log para separarlos
    CImg<double>
        base_normalizada(base.get_normalize(1, 100)),
        logarithm(base_normalizada.get_log()),
        filtrado;

    // Ahora los tengo separado teoricamente, aplico fourier (esta dentro de la funcion)
    // Y aplico el filtro S(u, v) = H(u, v) * F_i(u,v) + H(u,v) * F_r(u,v)
    filtrado = get_img_from_filter(logarithm, H);
    filtrado.normalize(0, 1);

    // Ahora tengo que volver a como era antes, aplicando exp
    filtrado.exp();

    return filtrado.get_normalize(0, 255);
}


/// Aplicamos la correccion Psi para expandir oscuros y contraer claros (mejora contraste)
// Trabajamos la imagen de entrada en el modelo HSI para modificar solo el canal I
CImg<double> correccionPsi(CImg<double> img, double psi = 3){

    cimg_forXY(img, x, y){
        img(x, y, 2) = ( 255 * log((img(x, y, 2)/255) * (psi -1) + 1) ) / log(psi);
    }

    return img;

}

/// Separa componente de luminancia de componente de reflactancia
// Solo debe venir la componente de intensidad de la imagen
CImgList<double> decouplingLR(
    CImg<double> img, int option_fc, double option_gl, double option_gh, double option_c){

    CImgList<double> f_luminancia(get_H_homomorphic(img, option_fc, option_gl, option_gh, option_c));
    CImgList<double> f_reflactancia(get_H_homomorphic(img, option_fc, option_gh, option_gl, option_c));

    CImg<double> luminancia(get_image_homomorphic(img, f_luminancia).get_normalize(0, 255));
    CImg<double> reflactancia(get_image_homomorphic(img, f_reflactancia).get_normalize(0, 255));

    return (luminancia, reflactancia);

}

///Dadas dos imagenes de intensidad una de dia y una de noche, las desacopla en Luminancia y Reflactancia
/// y luego obtiene el cociente Lday/Lnight
CImg<double> ratioDayNightBG(CImg<double> daytime, CImg<double> nighttime,
                             int option_fc, double option_gl, double option_gh, double option_c){

    CImgList<double> LRday(decouplingLR(daytime, option_fc, option_gl, option_gh, option_c));
    CImgList<double> LRnight(decouplingLR(nighttime, option_fc, option_gl, option_gh, option_c));
    CImg<double> ratio(daytime.width(), daytime.height());

    cimg_forXY(daytime, x, y){
        ratio(x,y) = LRday[0](x,y) / LRnight[0](x,y);
    }

    return ratio;
}

///Recibimos la imagen de intensidad a mejorar y el ratio calculado anteriormente
/// Devolvemos la imagen mejorada
CImg<double> denighting(CImg<double> base, CImg<double> ratio,
                        int option_fc, double option_gl, double option_gh, double option_c){

    CImgList<double> LRbase(decouplingLR(base, option_fc, option_gl, option_gh, option_c));

    cimg_forXY(LRbase[0],x,y){
        //En este paso hacemos el producto entre la reflactancia de la imagen a mejorar
        //y la luminancia obtenida al multiplicar el ratio por la luminancia de la base
        //f(x,y) = Ldenight(x,y) * R(x,y)
        base(x,y) = (LRbase[0](x,y) * ratio(x,y)) * LRbase[1](x,y);

    }

    return base;
}

///Funcion principal que hace todo
void nighttimeEnhacement(   const char* day_file,
                            const char* night_file,
                            const char* images_file,
                            int option_fc, double option_gl,
                            double option_gh, double option_c) {

    CImg<double> daytime_bg(day_file);
    CImg<double> nighttime_bg(night_file);

    daytime_bg.RGBtoHSI();
    nighttime_bg.RGBtoHSI();

    CImg<double> ratio(ratioDayNightBG(daytime_bg.get_channel(2),
                                       nighttime_bg.get_channel(2),
                                       option_fc, option_gl, option_gh, option_c));

    /// Abrimos y trabajamos imagen por imagen
    ifstream f(images_file);
    string image_file;

    // Si no pudo abrirlo, problema vieja
    assert(f.is_open());

    unsigned int contador = 1;

    // Vamos recorriendo cada path en el archivo y analizando la imagen
    while(!f.eof()) {

        f >> image_file;

        CImg<double> image(image_file.c_str());
        CImg<double> procesado(denighting(image, ratio, option_fc, option_gl, option_gh, option_c ));

        procesado.get_shared_channel(2).normalize(0, 1);
        procesado.HSItoRGB();
        procesado.save("img_out/resultado.png", contador);

        contador++;
    }

    f.close();

}

int main(int argc, char *argv[]){
    const char* day_filename = cimg_option("-dayf","img_in/prueba.jpg", "Imagen de entrada");
    const char* night_filename = cimg_option("-nightf","img_in/prueba.jpg", "Imagen de entrada");
    const char* images_filename = cimg_option("-imagesf","images.txt", "Imagen de entrada");
    const double psi = cimg_option("-psi", 3.0, "Factor de correccion psi");

    const int fc = cimg_option("-fc", 150, "Frecuencia de Corte");
    const double gl = cimg_option("-gl", 1.0, "Gamma Low");
    const double gh = cimg_option("-gh", 0.0, "Gamma High");
    const double c = cimg_option("-c", 1.0, "Offset");

    nighttimeEnhacement(day_filename, night_filename, images_filename, fc, gl, gh, c);

 /*
    CImg<double> corregida(correccionPsi(base, psi));
    CImg<double> couplingImage(corregida);
    CImgList<double> LR(decouplingLR(corregida.get_channel(2), fc, gl, gh, c));

    cimg_forXY(LR[0], x, y){
        couplingImage(x,y,2) = LR[0](x,y) * LR[1](x,y);
    }
    couplingImage.get_shared_channel(2).normalize(0, 1);

    (couplingImage.get_channel(2),corregida.get_channel(2))
        .display();

    (base.get_HSItoRGB(),
     corregida.get_HSItoRGB(),
     LR, couplingImage.get_HSItoRGB()).display();
*/
    return 0;
}
