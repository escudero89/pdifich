#include <iostream>
#include "../../../CImg-1.5.4/CImg.h"

using namespace cimg_library;
using namespace std;


CImg<unsigned char> cuadrado_circulo(unsigned int tamanio = 256,
                                      unsigned int radio = 80){


    CImg<unsigned char> imagen(tamanio,tamanio,1,1,0);
    int center = tamanio / 2;

    cimg_forXY(imagen,x,y){
        if( pow(x - center, 2) + pow(y - center, 2) <= pow(radio,2) ){
            imagen(x,y) = 255;
        }
    }

    imagen.display();
    return imagen;
}

int main(){
    /* EJERCICIO 1

    CImg<unsigned int> mi_imagen1(256,256,1,1,0);

    cimg_forXY(mi_imagen1,x,y){
        mi_imagen1(x,y) = x;
    }

    mi_imagen1.display("256 x 256");

    */

    /* EJERCICIO 2

    CImg<unsigned int> mi_imagen2(200,200,1,1,0);
    cimg_forXY(mi_imagen2,x,y){
        mi_imagen2(x,y) = x;
    }

    CImgDisplay ventana1(mi_imagen2,"Sin Normalizar",0),
                ventana2(mi_imagen2,"Normalizada",1);

    while(!ventana1.is_closed() && !ventana2.is_closed()){}

    */

    /*EJERCICIO 3

    CImg<unsigned int> mi_imagen2(600,600,1,1,0);
    cimg_forXY(mi_imagen2,x,y){
        mi_imagen2(x,y) = x % 2;
    }

    CImgDisplay ventana1(mi_imagen2,"Sin Normalizar",0),
                ventana2(mi_imagen2,"Normalizada",1);

    while(!ventana1.is_closed() && !ventana2.is_closed()){}

    */

    /* EJERCICIO 4 */
    cuadrado_circulo();

    return 0;
}
