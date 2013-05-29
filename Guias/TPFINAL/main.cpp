//Para compilar: g++ -o tp main.cpp -O0 -lm -lpthread -lX11 -lfftw3

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
// Recibe imagen HSI
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

#if 0 // Homomorfico
    CImgList<double> f_luminancia(get_H_homomorphic(img, option_fc, option_gl, option_gh, option_c));
    CImgList<double> f_reflactancia(get_H_homomorphic(img, option_fc, option_gh, option_gl, option_c));

    CImg<double> luminancia(get_image_homomorphic(img, f_luminancia).get_normalize(0, 255));
    CImg<double> reflactancia(get_image_homomorphic(img, f_reflactancia).get_normalize(0, 255));
#endif

#if 1 //Bilateral
    CImg<double> luminancia(img.get_blur_bilateral(option_gl,option_gh,-33,32, true));
    CImg<double> reflactancia(img.width(), img.height(),1,1);

    luminancia.normalize(1,2);
    img.normalize(1,2);

    cimg_forXY(reflactancia, i, j){
        reflactancia(i,j) = img(i,j) / luminancia(i,j);
    }

    luminancia.normalize(0, 255);
    reflactancia.normalize(0, 255);

#endif



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
    (LRday, LRnight).display("LRday, LRnight", 0);

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

    //CImg<double> f_promediado(7,7,1,1,1);
    //LRbase[0].convolve(f_promediado);

    //Normalizamos entre 1 y 2 para que no moleste la division por cero
    LRbase[0].normalize(1,2);
    LRbase[1].normalize(1,2);

    cimg_forXY(LRbase[0],x,y){
        //En este paso hacemos el producto entre la reflactancia de la imagen a mejorar
        //y la luminancia obtenida al multiplicar el ratio por la luminancia de la base
        //f(x,y) = Ldenight(x,y) * R(x,y)
        base(x,y) = (LRbase[0](x,y) * ratio(x,y)) * LRbase[1](x,y);

    }

    //Volvemos al rango entre 0 y 1 (ya que es intensidad en double en HSI)
    base.normalize(0, 1);

    return base;
}


///FUNCION SEGMENTAR:
///     INPUT:
///         img1: Imagen de entrada 1 (canal de INTENSIDAD)
///         img2: Imagen de entrada 2 (canal de INTENSIDAD)
///         tam_suavizado: tamanio de mascara utilizado para suavizar la diferencia de imagenes
///         umbral_segmentacion: umbral que define que parte pasa y que parte no en la segmentacion

///     OUTPUT:
///         Mascara booleana con la imagen segmentada
CImg<bool> segmentar(CImg<double> img1, CImg<double> img2,
                      unsigned int tam_suavizado = 15,
                      double umbral_segmentacion=0.2){

 //Creamos una imagen con el valor absoluto de la diferencia de
 //las dos imagenes de entrada.
     CImg<double> diferencia(abs(img1 - img2));

 //Suavizamos la imagen para quitar imperfecciones y dejar los valores
 //de la resta mas uniformes
     CImg<double> filtro_suavizado(tam_suavizado, tam_suavizado, 1, 1, 1);
     diferencia.convolve(filtro_suavizado).normalize(0,1);

 //Aplicamos umbralizacion
     CImg<bool> mascara(img1.width(), img1.height(), 1, 1);
     cimg_forXY(mascara, x, y){
          //(media - desvio * umbral_segmentacion)
         mascara(x,y) = (diferencia(x,y) > umbral_segmentacion) ? 1 : 0;
     }

//      SEGUNDO SUAVIZADO, OPCIONAL
//        (mascara, mascara.convolve(filtro_suavizado)
//                               .normalize(0,1))
//                               .display("Diferencia | Diferencia suavizada");
//        desvio = sqrt(diferencia.variance_mean(0, media));
//        cimg_forXY(mascara, x, y){
//             //(media - desvio * umbral_segmentacion)
//            mascara(x,y) = (mascara(x,y) > media + desvio * umbral_segmentacion) ? true : false;
//        }
//
//        (diferencia, mascara).display();

     return mascara;

}


///Funcion principal que hace todo
void nighttimeEnhacement(
    const char* images_file,
    double psi,
    int option_fc,
    double option_gl,
    double option_gh,
    double option_c,
    double pendiente_saturacion,
    unsigned int tamanho_prom_hue,
    double option_fs) {

    string nombreFile = string(images_file).substr(0, string(images_file).find(".txt"));

    string carpetaIn = "CasosPrueba/";
    string carpetaOut = "Resultados/";

    string carpetaInResultado = carpetaIn + nombreFile + "/";
    string carpetaOutResultado = carpetaOut + nombreFile + "/";

    cout << "Tomando casos de prueba desde: " << carpetaInResultado << endl;
    cout << "Retornando resultados en: " << carpetaOutResultado << endl;

    string str_resultado = carpetaOutResultado + "resultado.png";

    /// Abrimos y trabajamos imagen por imagen
    ifstream f(string(carpetaIn + images_file).c_str());
    string image_file;

    string day_file;
    string night_file;

    // Si no pudo abrirlo, problema vieja
    assert(f.is_open());

    // Primeras dos filas: daytime_background y nighttime_background
    f >> day_file;
    f >> night_file;

    CImg<double> daytime_bg((carpetaInResultado + day_file).c_str());
    CImg<double> nighttime_bg((carpetaInResultado + night_file).c_str());

    daytime_bg.RGBtoHSI();
    nighttime_bg.RGBtoHSI();

    // Con un 3 esta bueno aparentemente
    nighttime_bg = correccionPsi(nighttime_bg, psi);

    CImg<double> ratio(ratioDayNightBG(daytime_bg.get_channel(2),
                                       nighttime_bg.get_channel(2),
                                       option_fc, option_gl, option_gh, option_c));


    unsigned int contador = 1;

    CImg<double> daytime_bg_hue(daytime_bg.get_channel(0));
    CImg<double> daytime_bg_saturation(daytime_bg.get_channel(1));

    CImg<double> promediado(tamanho_prom_hue, tamanho_prom_hue, 1, 1, 1);

    // Vamos recorriendo cada path en el archivo y analizando la imagen
    while(!f.eof()) {

        f >> image_file;

        CImg<double> image((carpetaInResultado + image_file).c_str());
        CImg<double> original(image);

        // TRABAJAMOS CON LA IMAGEN
        image.RGBtoHSI();
        image = correccionPsi(image, psi);

        CImg<double> hue(image.get_channel(0)/*.get_convolve(promediado).get_normalize(0, 359)*/);
        CImg<double> saturation(image.get_channel(1) /*image.get_channel(1)*/);
        CImg<double> intensity_night(image.get_channel(2));



        CImg<double> intensidad(denighting(intensity_night,
                                           ratio,
                                           option_fc, option_gl, option_gh, option_c ));

        CImg<bool> mascara_seg(segmentar(intensity_night,
                                         nighttime_bg.get_channel(2)));
        cimg_forXY(mascara_seg, x, y){

            /// Voy a trabajar a parte con la parte segmentada, y la sin segmentar
            if (mascara_seg(x, y)) { // movimiento (solo cambio intensidad)
                intensidad(x, y) = intensity_night(x, y);

            } else { // background estatico
                hue(x, y) = daytime_bg_hue(x, y);

                double satur = intensity_night(x, y) * option_fs + daytime_bg_saturation(x, y) * (1.0 - option_fs);
                
                // Nos quedamos con la menor saturacion (no inventamos saturacion)
                saturation(x, y) = (satur > saturation(x, y)) ? saturation(x, y) : satur;

                // No hay cambios en la intensidad                
            }

            /*
            hue(x, y) = daytime_bg_hue(x, y) * (1 - mascara_seg(x, y)) + hue(x,y) * mascara_seg(x,y);

            double val = intensidad(x,y) * (1.0 - mascara_seg(x,y)) + intensity_night(x,y) * mascara_seg(x,y) ;
            intensidad(x,y) = (val > 1) ? 1 : val;

            double satur = intensity_night(x, y) * option_fs + saturation(x, y) * (1.0 - option_fs);
            satur = (mascara_seg(x, y) == 1) ? saturation(x, y) : satur;

            // Nos quedamos con la menor saturacion (no inventamos saturacion)
            saturation(x, y) = (satur > saturation(x, y)) ? saturation(x, y) : satur;
            */
        }

		// Hacemos una transformacion lineal sobre la saturacion para disminuirla.
		// Para hacer la transformacion nos basamos en informacion de intensidad
		// de la imagen a procesar. Si la intensidad es muy baja, la saturacion tambien
		// debe serlo. De esta manera atenuamos los falsos colores que se generan
		// a causa de la poca informacion de color de la imagen de noche.
        /*saturation.display();
        cimg_forXY(saturation, x, y) {
            double intensity_n = (intensity_night(x, y) < option_fs) ? intensity_night(x, y) / option_fs : 1;
            double val = intensity_n * pendiente_saturacion;
            saturation(x, y) = (val > 1) ? 1 : val; // evitamos que se vaya a la bosta
        }
        (intensity_night, saturation).display();*/

        /// Hago una interpolacion entre la intensidad de noche y la saturacion de noche
        //saturation = intensity_night * option_fs + saturation * (1.0 - option_fs);

        image = join_channels(hue, saturation, intensidad);
        image.HSItoRGB();

        image.save(str_resultado.c_str(), contador);

        //(original, image).display("MARCOUSOSUCOUSOU", 0);
        //(original.get_RGBtoHSI().get_channel(2), intensidad).display("MARCOUSOSUCOUSOU", 0);
        //(image.get_RGBtoHSI().get_channel(0), image.get_RGBtoHSI().get_channel(1)).display("MARCOUSOSUCOUSOU", 0);

        cout << "Imagen procesada: " << image_file;
        cout << "\tImagen salida: " << "resultado_" << contador << ".png" << endl;

        contador++;
    }

    f.close();

    /// ACA GUARDO LOS PARAMETROS

    ofstream f_stats(string(carpetaOutResultado + "stats.txt").c_str());

    assert(f_stats.is_open());

    f_stats << "Nombre del archivo base: " << images_file << endl;
    f_stats << "Psi: " << psi << endl;
    f_stats << "Frecuencia de corte: " << option_fc << endl;
    f_stats << "Gl: " << option_gl << endl;
    f_stats << "Gh: " << option_gh << endl;
    f_stats << "C: " << option_c << endl;
    f_stats << "Pendiente saturacion: " << pendiente_saturacion << endl;

    f_stats.close();

}

int main(int argc, char *argv[]){
    const char* _day_filename = cimg_option("-dayf","img_in/prueba.jpg", "Imagen de entrada");
    const char* _night_filename = cimg_option("-nightf","img_in/prueba.jpg", "Imagen de entrada");
    const char* _images_filename = cimg_option("-imagesf","images.txt", "Imagen de entrada");
    const double _psi = cimg_option("-psi", -1.0, "Factor de correccion psi");

    const double _fs = cimg_option("-fs", 0.9, "Factor de Saturacion en la pendiente");

    const int _fc = cimg_option("-fc", 150, "Frecuencia de Corte");
    const double _gl = cimg_option("-gl", 1.0, "Gamma Low");
    const double _gh = cimg_option("-gh", 0.0, "Gamma High");
    const double _c = cimg_option("-c", 1.0, "Offset");
    const double _ps = cimg_option("-ps", 1.0, "Pendiente transf. lineal a saturacion");

    const unsigned int _tam_hue = cimg_option("-tph", 15, "Tamanho de matriz Promedio en Hue");

    nighttimeEnhacement(_images_filename, _psi, _fc, _gl, _gh, _c, _ps, _tam_hue, _fs);

    return 0;
}
