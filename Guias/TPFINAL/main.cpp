//Para compilar: g++ -o main main.cpp -O0 -lm -lpthread -lX11 -lfftw3

#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions.h"
#include <cstdlib>
#include <complex>
#include <string>
#include <cmath>
#include <cassert>

#if 1
    #include "segm_marc.h"
#else
    #include "segm_cris.h"
#endif

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
CImgList<double> decouplingLR(CImg<double> img, double option_gl, double option_gh) {

    const unsigned int VAR_BLUR_MEDIAN = 7;
    const unsigned int TAMANHO_F_PROMEDIADO = 5;

    // FILTRO BILATERAL

    CImg<double> luminancia(img.get_blur_bilateral(option_gl,option_gh, -33, 32, true));
    CImg<double> reflactancia(img.width(), img.height(),1,1);

    luminancia.normalize(1, 2);
    img.normalize(1, 2);

    cimg_forXY(reflactancia, i, j){
        reflactancia(i,j) = img(i,j) / luminancia(i,j);
    }

    reflactancia.blur_median(VAR_BLUR_MEDIAN);

    CImg<double> f_promediado(TAMANHO_F_PROMEDIADO, TAMANHO_F_PROMEDIADO, 1, 1, 1);
    
    reflactancia.convolve(f_promediado);
    reflactancia /= (pow(TAMANHO_F_PROMEDIADO, 2));

    luminancia.normalize(0, 255);
    reflactancia.normalize(0, 255);

    return (luminancia, reflactancia);

}

///Dadas dos imagenes de intensidad una de dia y una de noche, las desacopla en Luminancia y Reflactancia
/// y luego obtiene el cociente Lday/Lnight
CImg<double> ratioDayNightBG(
    CImg<double> daytime, CImg<double> nighttime, double option_gl, double option_gh){

    CImgList<double> LRday(decouplingLR(daytime, option_gl, option_gh));
    CImgList<double> LRnight(decouplingLR(nighttime, option_gl, option_gh));

    CImg<double> ratio(daytime.width(), daytime.height());

    LRday[0].normalize(1,2);
    LRnight[0].normalize(1,2);

    (LRday, LRnight).display("LRday, LRnight", 0);

    cimg_forXY(daytime, x, y){
        ratio(x,y) = LRday[0](x,y) / LRnight[0](x,y);
    }

    return ratio;
}

///Recibimos la imagen de intensidad a mejorar y el ratio calculado anteriormente
/// Devolvemos la imagen mejorada
CImg<double> denighting(CImg<double> base, CImg<double> ratio,
                        double option_gl, double option_gh){

    CImgList<double> LRbase(decouplingLR(base, option_gl, option_gh));

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

///Funcion principal que hace todo
void nighttimeEnhacement(
    const char* images_file,
    double psi,
    double option_gl,
    double option_gh,
    double alfa_int,
    double alfa_hue,
    double pendiente_saturacion,
    unsigned int tamanho_prom_hue,
    double option_fs,
    double option_fss,
    double option_useg,
    int option_pseg,
    bool aplicar_laplaciano) {

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

    /// EMPEZAMOS DESDE ACA EL TRABAJO, ANTES ERA GESTION DE ARCHIVOS

    CImg<double> daytime_bg((carpetaInResultado + day_file).c_str());
    CImg<double> nighttime_bg((carpetaInResultado + night_file).c_str());

    daytime_bg.RGBtoHSI();
    nighttime_bg.RGBtoHSI();

    // Con un 3 esta bueno aparentemente
    nighttime_bg = correccionPsi(nighttime_bg, psi);

    CImg<double> ratio(ratioDayNightBG(daytime_bg.get_channel(2),
                                       nighttime_bg.get_channel(2),
                                       option_gl, option_gh));

    //Nesecito que este en RGB para segmentar
    nighttime_bg.HSItoRGB();

    unsigned int contador = 1;

    CImg<double> daytime_bg_hue(daytime_bg.get_channel(0));
    CImg<double> daytime_bg_saturation(daytime_bg.get_channel(1));

    CImg<double> promediado(tamanho_prom_hue, tamanho_prom_hue, 1, 1, 1);

    // Vamos recorriendo cada path en el archivo y analizando la imagen
    while(!f.eof()) {

        f >> image_file;

        CImg<double> image((carpetaInResultado + image_file).c_str());
        CImg<double> original(image);

        //SEGMENTAMOS | ENVIAR IMAGENES EN FORMATO RGB
        CImg<bool> mascara_seg(image.width(),image.height(), 1, 1, 0);

        //Si alfa_int = 0 NO segmentamos, si es distinto de 0 SI segmentamos
        if (alfa_int) {
            mascara_seg = segmentar(image, nighttime_bg, daytime_bg, contador, option_pseg, option_useg);
        }

        /// DEFINIMOS EL LAPLACIANO DEL GAUSSIANO
        CImg<double> LoG(5, 5, 1, 1, 0);

        LoG(0, 2) = -1;
        LoG(1, 1) = -1; LoG(1, 2) = -2; LoG(1, 3) = -1;
        LoG(2, 0) = -1; LoG(2, 1) = -2; LoG(2, 2) = 16; LoG(2, 3) = -2; LoG(2, 4) = -1; 
        LoG(3, 1) = -1; LoG(3, 2) = -2; LoG(3, 3) = -1;
        LoG(4, 2) = -1;

        CImg<bool> mascara_LoG(mascara_seg.get_convolve(LoG).get_threshold(0.5));
        /// Y OBTENEMOS SU MASCARA FINAL

        // TRABAJAMOS CON LA IMAGEN
        image.RGBtoHSI();
        image = correccionPsi(image, psi);

        CImg<double> hue(image.get_channel(0));
        CImg<double> saturation(image.get_channel(1));
        CImg<double> intensity_night(image.get_channel(2));

        CImg<double> intensidad(denighting(intensity_night, ratio, option_gl, option_gh));
        
        cimg_forXY(mascara_seg, x, y){

            if (mascara_LoG(x, y) == 1 && aplicar_laplaciano) {
                hue(x, y) = 120;
                saturation(x, y) = 0;
                intensidad(x, y) = 1;

            } else {

                /// Voy a trabajar a parte con la parte segmentada, y la sin segmentar
                if (mascara_seg(x, y)) { // movimiento (solo cambio intensidad)
                    
                    intensidad(x, y) = 
                        intensity_night(x, y) * alfa_int + intensidad(x,y) * (1.0 - alfa_int);

                    if (alfa_int != 1){
                        saturation(x,y) = saturation(x,y) * option_fss;
                    }

                } else { // background estatico

                    hue(x, y) = daytime_bg_hue(x, y) * alfa_hue + hue(x,y) * (1.0 - alfa_hue);

                    //%% Si alfa_int = 0 como el paper
                    if (alfa_int != 0) {

                        double satur =
                            intensity_night(x, y) * option_fs + 
                            daytime_bg_saturation(x, y) * (1.0 - option_fs);
                        
                        // Nos quedamos con la menor saturacion (no inventamos saturacion)
                        saturation(x, y) = (satur > saturation(x, y)) ? saturation(x, y) : satur;

                    } else {
                        saturation(x,y) = saturation(x,y) * option_fs;
                    }
                }

            }
        }

        image = join_channels(hue, saturation, intensidad);
        image.HSItoRGB();

        image.save(str_resultado.c_str(), contador);

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
    f_stats << "Gl: " << option_gl << endl;
    f_stats << "Gh: " << option_gh << endl;
    f_stats << "Valor alfa de Intensidad: " << alfa_int << endl;
    f_stats << "Valor alfa de Hue: " << alfa_hue << endl;
    f_stats << "Pendiente saturacion: " << pendiente_saturacion << endl;
    f_stats << "Option_FS: " << option_fs << endl;
    f_stats << "Option_FSS: " << option_fss << endl;

    f_stats.close();

}

int main(int argc, char *argv[]){

    const char* _day_filename = cimg_option("-dayf","img_in/prueba.jpg", "Imagen de entrada");
    const char* _night_filename = cimg_option("-nightf","img_in/prueba.jpg", "Imagen de entrada");
    const char* _images_filename = cimg_option("-imagesf","images.txt", "Imagen de entrada");
    const double _psi = cimg_option("-psi", -1.0, "Factor de correccion psi");

    const double _fs = cimg_option("-fs", 0.15, "Factor que maneja la saturacion del fondo de la imagen");
    const double _fss = cimg_option("-fss", 0.2, "Factor que maneja la saturacion de la parte segmentada de la imagen");

    const double _gl = cimg_option("-gl", 0.6, "Gamma Low");
    const double _gh = cimg_option("-gh", 25.0, "Gamma High");
    const double _ps = cimg_option("-ps", 1.0, "Pendiente transf. lineal a saturacion");
    const unsigned int _tam_hue = cimg_option("-tph", 15, "Tamanho de matriz Promedio en Hue");

    const double _umbralSegmentacion = cimg_option("-useg", 0.25, "Umbral de segmentacion");
    const int _promediadoSegmentacion = cimg_option("-pseg", 7, "Tamanio del filtro para suavizar en segmentacion");

    const double _alfaint = cimg_option("-alfaint", 0.0, "Factor que maneja la intensidad de la parte segmentada");
    const double _alfahue = cimg_option("-alfahue", 0.0, "Factor que maneja el tono del fondo de la imagen");

    const bool _aplicar_laplaciano = cimg_option("-LoG", false, "Aplica o no el laplaciano");

    nighttimeEnhacement(
        _images_filename,
        _psi,
        _gl,
        _gh,
        _alfaint,
        _alfahue,
        _ps,
        _tam_hue,
        _fs,
        _fss,
        _umbralSegmentacion,
        _promediadoSegmentacion,
        _aplicar_laplaciano);

///  Para ejecutarlo exactamente segun el paper:
//    -alfaint 0     (indica que usamos la intensidad de la imagen denightiada)
//    -alfahue 0    (indica que usamos el tono de la imagen denightiada)
//    -fs 0.15 (factor que reduce la saturacion)

///   Para ejecutarlo con nuestras modificaciones (segmentacion y color de dia):
//    -alfaint 1    (indica que usamos la intensidad de la imagen original en la parte segmentada)
//    -alfahue 1   (indica que usamos el tono de la imagen de dia en las partes fijas)
//    -fs 0   (factor que maneja la saturacion de las partes fijas (fondo) )
//    -fss 0.2(factor que reduce la saturacion de la parte segmentada)


///    Para ejecutarlo interpolando los dos casos anteriores:
//    -alfaint 0.3   (indica que usamos un promedio ponderado para la intensidad de la parte segmentada)
//    -alfahue 1    (indica que usamos un promedio entre img denightiada e img de dia| es mejor ponerlo a 1 y usar el de dia)
//    -fs 0.15 (factor que reduce la saturacion de la imagen del fondo)
//    -fss 0.2 (factor que reduce la saturacion de la parte segmentada)

    return 0;
}
