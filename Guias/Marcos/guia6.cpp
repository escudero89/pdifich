//Para compilar: g++ -o guia5 guia5.cpp -O0 -lm -lpthread -lX11 -lfftw3 && ./guia5

#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions.h"
#include <cstdlib>
#include <complex>
#include <string>
#include "misFuncionesPDI.h"


using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]){


#if 0 ///EJERCICIO 1
    const char* filename = cimg_option("-i", "../../img/grises.jpg", "Input Image File");
    const int varianza_ruido = cimg_option("-vr", 30, "Varianza del ruido [0 255]");
    const int tipo_ruido = cimg_option("-tr", 0, "Tipo de ruido: | 0 gausseano | 1 uniforme | 2 sal y pimienta | etc");


    CImg<unsigned char> imagen(filename);
    imagen.channel(0);

    imagen.display();
    imagen.get_histogram(256, 0, 255).display_graph(0,3);

    //El segundo argumento define el tipo de ruido
    //
    imagen.noise(varianza_ruido , tipo_ruido);
    imagen.normalize(0, 255);

    imagen.display();
    imagen.get_histogram(256, 0, 255).display_graph(0,3);
#endif

#if 0 ///EJERCICIO 2

    const char* filename = cimg_option("-i", "../../img/grises.jpg", "Input Image File");
    const double varianza_ruido = cimg_option("-vr", 0.1, "Varianza del ruido [0 255]");
    const int tipo_ruido = cimg_option("-tr", 0, "Tipo de ruido: | 0 gausseano | 1 uniforme | 2 sal y pimienta | etc");
    const int Q = cimg_option("-Q", 0, "Valor de Q para filtrado media CONTRA ARMONICA");
    CImg<double> imagen(filename);
    imagen.channel(0);
    imagen.normalize(0, 1);

    CImg<double> imagen_con_ruido_1(imagen.get_noise(varianza_ruido, tipo_ruido));
    imagen_con_ruido_1.normalize(0, 1);
    imagen_con_ruido_1.display("Imagen con Ruido");

    //FILTRO MEDIA GEOMETRICA
    CImg<double> imagen_filtrada_1(filtrar_mediaGeometrica(imagen_con_ruido_1, 3, 3));
    imagen_filtrada_1.display("Imagen filtrada con filtro Media Geometrica");

    cout<<"MSE img original e img con ruido: "
        <<imagen.MSE(imagen_con_ruido_1)<<endl
        <<"MSE img filtrada e img con ruido: "
        <<imagen.MSE(imagen_filtrada_1)<<endl;

    //FILTRO MEDIA CONTRA ARMONICA
    CImg<double> imagen_filtrada_2(filtrar_mediaContraArmonica(imagen_con_ruido_1, Q, 3, 3));
    imagen_filtrada_2.display("Imagen filtrada con filtro Media Contra armonica");

    cout<<"MSE img original e img con ruido: "
        <<imagen.MSE(imagen_con_ruido_1)<<endl
        <<"MSE img filtrada e img con ruido: "
        <<imagen.MSE(imagen_filtrada_2)<<endl;


#endif


#if 0 ///EJERCICIO 3

    const char* filename = cimg_option("-i", "../../img/cameraman.tif", "Input Image File");
    const double varianza_ruido = cimg_option("-vr", 0.1, "Varianza del ruido [0 255]");
    const int tipo_ruido = cimg_option("-tr", 0, "Tipo de ruido: | 0 gausseano | 1 uniforme | 2 sal y pimienta | etc");
    const int alfa = cimg_option("-alfa", 0, "Valor de alfa para filtrado MEDIA ALFA RECORTADO");
    CImg<double> imagen(filename);
    imagen.channel(0);
    imagen.normalize(0, 1);

    //DOBLE CONTAMINACION DE RUIDO
    CImg<double> imagen_con_ruido_1(imagen.get_noise(varianza_ruido, tipo_ruido));
    imagen_con_ruido_1.noise(0.6, 2);

    imagen_con_ruido_1.normalize(0, 1);
    imagen_con_ruido_1.display("Imagen con Ruido");

    //FILTRO MEDIA GEOMETRICA
    CImg<double> imagen_filtrada_1(filtrar_puntoMedio(imagen_con_ruido_1, 3, 3));
    imagen_filtrada_1.display("Imagen filtrada con filtro de Punto Medio");

    cout<<"MSE img original e img con ruido: "
        <<imagen.MSE(imagen_con_ruido_1)<<endl
        <<"MSE img filtrada e img con ruido: "
        <<imagen.MSE(imagen_filtrada_1)<<endl;

    //FILTRO MEDIA CONTRA ARMONICA
    CImg<double> imagen_filtrada_2(filtrar_mediasAlfaRecortado(imagen_con_ruido_1, alfa, 3, 3));
    imagen_filtrada_2.display("Imagen filtrada con filtro Alfa medias recortado");

    cout<<"MSE img original e img con ruido: "
        <<imagen.MSE(imagen_con_ruido_1)<<endl
        <<"MSE img filtrada e img con ruido: "
        <<imagen.MSE(imagen_filtrada_2)<<endl;


#endif


#if 0 ///EJERCICIO 4

    const char* filename = cimg_option("-i", "../../img/img_degradada.tif", "Input Image File");
    const string tipo_filtro = cimg_option("-tipoFiltro", "g", "Tipo de filtro: |g gauss|bwx bw de orden x| i ideal|");
    const double frec_corte = cimg_option("-fCorte", 30.0, "Frecuencia de corte del filtro");
    const bool mostrar = cimg_option("-mostrar", 1, "Mostrar procedimiento intermedio de filtrado");
    const int origen_x = cimg_option("-origen_x", 70, "Cordenada x de origen del filtro");
    const int origen_y = cimg_option("-origen_y", 90, "Cordenada y de origen del filtro");

    CImg<double> imagen(filename);
    imagen.channel(0);

    (magn_tdf(imagen, true),
    magn_tdf(imagen, false)).display("Magnitud de fourier centrada y sin centrar");

    filtrar_frecuencia( imagen,
                       (1 - get_filtro(imagen,frec_corte, tipo_filtro, 10, 0, false)) +
                       (1 - get_filtro(imagen,frec_corte, tipo_filtro, 0, 20, false)) +
                       (1 - get_filtro(imagen,frec_corte, tipo_filtro, 40, 40, false) - 2),
                        mostrar);





#endif

#if 1 ///EJERCICIO 5
    const char* filename = cimg_option("-i", "../../img/img_degradada.tif", "Input Image File");
    const string tipo_filtro = cimg_option("-tipoFiltro", "g", "Tipo de filtro: |g gauss|bwx bw de orden x| i ideal|");
    const double frec_corte = cimg_option("-fCorte", 30.0, "Frecuencia de corte del filtro");
    const bool mostrar = cimg_option("-mostrar", 1, "Mostrar procedimiento intermedio de filtrado");
    const int origen_x = cimg_option("-origen_x", 70, "Cordenada x de origen del filtro");
    const int origen_y = cimg_option("-origen_y", 90, "Cordenada y de origen del filtro");

    CImg<double> imagen(filename);
    imagen.channel(0);


#endif
return 0;
}
