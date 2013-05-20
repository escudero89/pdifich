//Para compilar: g++ -o guia5 guia5.cpp -O0 -lm -lpthread -lX11 -lfftw3 && ./guia5

#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions.h"
#include <cstdlib>
#include <complex>
#include <string>
#include <cmath>
#include <cassert>

#define EPSILON 0.1

using namespace cimg_library;
using namespace std;

/// Le paso 3 imagenes distintas (con un canal cada una), y me retorna una imagen combinada de estas
CImg<double> join_channels(CImg<double> canal_1, CImg<double> canal_2 = CImg<double>(), CImg<double> canal_3 = CImg<double>()) {

	CImg<double> base(canal_1);

	if (!canal_2.is_empty()) {
		base.append(canal_2, 'c');

		if (!canal_3.is_empty()) {
			base.append(canal_3, 'c');
		}
	}

	return base;
}

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

    if (psi != 1 && psi > 0) {
        cimg_forXY(img, x, y){
            img(x, y, 2) = ( 255 * log((img(x, y, 2)/255) * (psi -1) + 1) ) / log(psi);
        }
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

    LRday[0].normalize(1,2);
    LRnight[0].normalize(1,2);
    (LRday, LRnight).display();

    cimg_forXY(daytime, x, y){
        //Obtenemos el ratio
        ratio(x,y) = LRday[0](x,y) / LRnight[0](x,y);
    }

    return ratio;
}

///Recibimos la imagen de intensidad a mejorar y el ratio calculado anteriormente
/// Devolvemos la imagen mejorada
CImg<double> denighting(CImg<double> base, CImg<double> ratio,
                        int option_fc, double option_gl, double option_gh, double option_c){

    CImgList<double> LRbase(decouplingLR(base, option_fc, option_gl, option_gh, option_c));

    CImg<double> f_promediado(7,7,1,1,1);
    LRbase[0].convolve(f_promediado);

    //Normalizamos entre 1 y 2 para que no moleste la division por cero
    LRbase[0].normalize(1,2);
    LRbase[1].normalize(1,2);

    cimg_forXY(LRbase[0],x,y){
        //En este paso hacemos el producto entre la reflactancia de la imagen a mejorar
        //y la luminancia obtenida al multiplicar el ratio por la luminancia de la base
        //f(x,y) = Ldenight(x,y) * R(x,y)
        base(x,y) = (LRbase[0](x,y) * ratio(x,y)) * LRbase[1](x,y);

    }

    //Volvemos al rango original entre 0 y 255
    base.normalize(0,255);

    return base;
}

///Funcion principal que hace todo
void nighttimeEnhacement(  
    const char* images_file, 
    double psi,
    int option_fc,
    double option_gl,
    double option_gh, 
    double option_c,
    double pendiente_saturacion) {

    /// Abrimos y trabajamos imagen por imagen
    ifstream f(images_file);
    string image_file;

    // Si no pudo abrirlo, problema vieja
    assert(f.is_open());

    string day_file;
    string night_file;

    // Primeras dos filas: daytime_background y nighttime_background
    f >> day_file;
    f >> night_file;

    CImg<double> daytime_bg(day_file.c_str());
    CImg<double> nighttime_bg(night_file.c_str());

    nighttime_bg = correccionPsi(nighttime_bg, psi);

    daytime_bg.RGBtoHSI();
    nighttime_bg.RGBtoHSI();

    CImg<double> ratio(ratioDayNightBG(daytime_bg.get_channel(2),
                                       nighttime_bg.get_channel(2),
                                       option_fc, option_gl, option_gh, option_c));


    unsigned int contador = 1;

    // Vamos recorriendo cada path en el archivo y analizando la imagen
    while(!f.eof()) {

        f >> image_file;

        CImg<double> image(image_file.c_str());
        CImg<double> original(image);
        // para comparar
        //image.save("temp/r.png", contador);

        image = correccionPsi(image, psi);

        image.RGBtoHSI();
        CImg<double> intensidad(denighting(image.get_channel(2),
                                           ratio,
                                           option_fc, option_gl, option_gh, option_c ));

        CImg<double> promediado(13, 13, 1, 1, 1);
        CImg<double> hue(image.get_channel(0).get_convolve(promediado).get_normalize(0, 359));
        CImg<double> saturation(image.get_channel(1).get_convolve(promediado).get_normalize(0, 1));

		// Simplemente aplico un filtro lineal en la saturacion
		cimg_forXY(saturation, x, y) {
            double val = saturation(x, y) * pendiente_saturacion;
			saturation(x, y) = (val > 1) ? 1 : val; // evitamos que se vaya a la bosta
		}

        intensidad.normalize(0, 1);
        image = join_channels(hue, saturation, intensidad);
        image.HSItoRGB();

        image.save("img_out/resultado.png", contador);

        //(original, image).display("MARCOUSOSUCOUSOU", 0);
        //(original.get_RGBtoHSI().get_channel(2), intensidad).display("MARCOUSOSUCOUSOU", 0);
        //(image.get_RGBtoHSI().get_channel(0), image.get_RGBtoHSI().get_channel(1)).display("MARCOUSOSUCOUSOU", 0);

        contador++;
    }

    f.close();

}

int main(int argc, char *argv[]){
    const char* _day_filename = cimg_option("-dayf","img_in/prueba.jpg", "Imagen de entrada");
    const char* _night_filename = cimg_option("-nightf","img_in/prueba.jpg", "Imagen de entrada");
    const char* _images_filename = cimg_option("-imagesf","images.txt", "Imagen de entrada");
    const double _psi = cimg_option("-psi", 3.0, "Factor de correccion psi");

    const int _fc = cimg_option("-fc", 150, "Frecuencia de Corte");
    const double _gl = cimg_option("-gl", 1.0, "Gamma Low");
    const double _gh = cimg_option("-gh", 0.0, "Gamma High");
    const double _c = cimg_option("-c", 1.0, "Offset");
    const double _ps = cimg_option("-ps", 1.0, "Pendiente transf. lineal a saturacion");

    nighttimeEnhacement(_images_filename, _psi, _fc, _gl, _gh, _c, _ps);

    return 0;
}
