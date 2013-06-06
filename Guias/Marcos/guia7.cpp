//Para compilar: g++ -o guia5 guia5.cpp -O0 -lm -lpthread -lX11 -lfftw3 && ./guia5

#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions.h"
#include "misFuncionesPDI.h"
#include <cstdlib>
#include <complex>
#include <vector>
#include <algorithm>
#include <string>


using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]){
#if 0 ///EJERCICIO 1
    ///Parametros de consola
    const char* filename = cimg_option("-i", "../../img/cameraman.tif", "Input Image File");
    const string tipo = cimg_option("-tipo", "sobel", "| sobel | prewitt | roberts|");
    const string orientacion = cimg_option("-orientacion", "Gx", "|Gx: Gradiente en X| Gy: Gradiente en Y| magnitud: Magnitud del gradiente|");
    const double umbral = cimg_option("-umbral", -1.0, "Umbral");
    const bool binarizar = cimg_option("-binarizar", 1, "Si es 1, binariza la imagen, si es 0 no");

    CImg<double> imagen1(filename);
    imagen1.channel(0);
    CImg<double> imagen2(bordes(imagen1, tipo, orientacion, umbral, !binarizar));
    CImg<double> imagen3(bordes(imagen1, tipo, orientacion, umbral, binarizar));

    (imagen1, imagen2, imagen3).display("Imagen original y con deteccion de bordes sin binarizar y binarizada");
    (imagen1.normalize(0,1),
     imagen2.normalize(0,1),
     imagen3.normalize(0,1)).display("Imagen original y con deteccion de bordes sin binarizar y binarizada");

#endif

#if 0 ///EJERCICIO 2
///Parametros de consola
    const char* filename = cimg_option("-i", "../../img/hand.tif", "Input Image File");
    const string tipo = cimg_option("-tipo", "sobel", "| sobel | prewitt | roberts|");
    const string orientacion = cimg_option("-orientacion", "Gx", "|Gx: Gradiente en X| Gy: Gradiente en Y| magnitud: Magnitud del gradiente|");
    const double umbral = cimg_option("-umbral", -1.0, "Umbral");
    const bool binarizar = cimg_option("-binarizar", 1, "Si es 1, binariza la imagen, si es 0 no");
    double x1 = cimg_option("-x1", 0.0, "Coordenada x1");
    double y1 = cimg_option("-y1", 0.0, "Coordenada y1");
    double x2 = cimg_option("-x2", 0.0, "Coordenada x2");
    double y2 = cimg_option("-y2", 0.0, "Coordenada y2");
    int separacion = cimg_option("-sep", 5, "separacion entre maximos");
    int cant_maximos = cimg_option("-cantMax", 5, "cantidad de  maximos");

//    CImg<unsigned char> img1(500,500,1,1,0);
//    const unsigned char color[] = { 255,255,255 };
//    while(x1 != -1 ){
//        img1.draw_line(x1,y1,x2,y2,color);
//        (img1, my_hough(img1, false, 0, 250, 10, 100)).display();
//        cout<<"Ingrese Coordenadas de la recta: "<<endl;
//        cin >> x1;
//        cin >> y1;
//        cin >> x2;
//        cin >> y2;
//    }

    CImg<double> img2(filename);
    img2.channel(0);

    img2 = bordes(img2, tipo, orientacion, umbral, binarizar);
    (img2, hough(img2)).display("Imagen de bordes y su tansformada");

    (hough(img2), my_hough(img2, false, x1, y1, x2, y2)).display("Transformada comun y la que detecta angulos y rhoes");

    CImg<int> transformada( my_hough(img2, false, x1, y1, x2, y2) );

    transformada = n_maximos(transformada, cant_maximos, separacion);
    transformada.display();

    (img2, hough(transformada, true) ).display("Imagen de bordes y deteccion");

    img2 = img2 * 0.7;
    CImg<double> asdf(hough(transformada, true));
    (img2 + asdf.normalize(0,1)).display();





#endif


#if 0 ///EJERCICIO 3
///Parametros de consola
    const char* filename = cimg_option("-i", "../../img/bone.tif", "Input Image File");
    int cord_x = cimg_option("-x", 0, "semilla cordenada x");
    int cord_y = cimg_option("-y", 0, "semilla cordenada y");
    int delta = cimg_option("-delta", 10, "delta para considerarlo como parte de la region");
    int etiqueta = cimg_option("-et", 256, "etiqueta para la region");


    srand(time(NULL));

    CImg<unsigned char> img(filename);
    img.channel(0);

    cord_x = rand() % (img.width() - 1);
    cord_y = rand() % (img.height() - 1);

    (img, region_growing(img, cord_x, cord_y, delta, etiqueta)).display();


#endif

#if 1 ///EJERCICIO 4
///Parametros de consola
    const char* filename = cimg_option("-i", "../../img/rosas.jpg", "Input Image File");
    double delta = cimg_option("-delta", 0.5, "delta para considerarlo como parte de la region");
    int masc_x = cimg_option("-mx", 9, "delta para considerarlo como parte de la region");
    int masc_y = cimg_option("-my", 9, "delta para considerarlo como parte de la region");
    int separacion = cimg_option("-sep", 11, "delta para considerarlo como parte de la region");

    CImg<double> img(filename);
    CImg<double> color(1,1,3);


    CImg<double> mascara(color_slicing(img, 1.0, 0.0, 0.0, delta));
    CImg<double> f_suavizado(5,5,1,1,1);
    mascara.convolve(f_suavizado);
    mascara.normalize(0,1);

    cimg_forXY(mascara,x,y){

        mascara(x,y) = (mascara(x,y) > 0.5) ? 1 : 0;

    }

    CImg<int> componentes(label_cc(mascara, 1, 2));
    (img, mascara, componentes).display();

    vector<int> V(unique_element_image(componentes));

    dibujar_circulos_centrales(mascara,img,masc_x,masc_y,V.size()-1,separacion);





#endif

return 0;
}
