#include <iostream>
#include "../../../CImg-1.5.4/CImg.h"
#include <vector>

using namespace cimg_library;
using namespace std;

CImg<unsigned char> mediosTonos_10(CImg<unsigned char> imagen){

    //Cuantizamos la imagen de entrada en 10 niveles de grises [0 - 9]
    imagen.quantize(10,0);
    //imagen.display();

    //Creamos imagen a rellenar (vacia)
    CImg<unsigned char>  imagen_bw(imagen.width() * 3, imagen.height() * 3, 1, 1),
                fila(imagen.width(),3,1,1,0);

    //Creamos vector de imagenes
    CImgList<unsigned char> puntillado(0,3,3,1,1);

    //Definimos los puntillados y los guardamos en el vector
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,0,0,0,0,0,0,0,0,0));
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,0,255,0,0,0,0,0,0,0));
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,0,255,0,0,0,0,0,0,255));
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,255,255,0,0,0,0,0,0,255));
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,255,255,0,0,0,0,255,0,255));
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,255,255,255,0,0,0,255,0,255));
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,255,255,255,0,0,255,255,0,255));
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,255,255,255,0,0,255,255,255,255));
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,255,255,255,255,0,255,255,255,255));
    puntillado.push_back(CImg<unsigned char>(3,3,1,1,255,255,255,255,255,255,255,255,255));

    //Mostramos el puntillado
    //puntillado.display();

    imagen_bw.clear();
    //Mapeamos cada bit
    for(int j = 0; j < imagen.height(); j++){

        fila.clear();

        for(int i = 0; i < imagen.width(); i++){

            fila.append(puntillado[imagen(i,j)], 'x');
        }

        imagen_bw.append(fila,'y');
    }

    //(imagen_bw,imagen).display();

    return imagen_bw;
}

int main(){

   //CImg<unsigned char> imagen("../../../img/cameraman.tif");

    ///PRUEBA CON DEGRADE
    CImg<unsigned int> mi_imagen1(256,256,1,1,0);
    cimg_forXY(mi_imagen1,x,y){mi_imagen1(x,y) = x;}
    (mi_imagen1, mediosTonos_10(mi_imagen1)).display();

    ///PRUEBA CON HUANGX.JPG
    CImg<unsigned char> imagen1("../../../img/Huang1.jpg");
    CImg<unsigned char> imagen2("../../../img/Huang2.jpg");
    CImg<unsigned char> imagen3("../../../img/Huang3.jpg");

    (imagen1, mediosTonos_10(imagen1)).display();
    mediosTonos_10(imagen1).save("Huang1.bmp");
    (imagen2, mediosTonos_10(imagen2)).display();
    mediosTonos_10(imagen2).save("Huang2.bmp");
    (imagen3, mediosTonos_10(imagen3)).display();
    mediosTonos_10(imagen3).save("Huang3.bmp");

    return 0;
}
