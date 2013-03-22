#include <iostream>
#include "../../../CImg-1.5.4/CImg.h"

using namespace cimg_library;
using namespace std;


int main(){

    CImg<unsigned char> imagen_1("../../../img/cameraman.tif"),
                        imagen_2(256,256,1,3,0);

    unsigned char white[] = {255, 255, 255};
    int cord_x, cord_y;
    CImgDisplay ventana_1(imagen_1, "Imagen de muestra", 0),
                ventana_2(imagen_2, "Perfil de intensidad");

     //Bucle hasta cerrar la ventana
    while(!ventana_1.is_closed() && !ventana_2.is_closed()){
        ventana_1.wait(); //Esperamos evento
        if(ventana_1.button()){
            //Capturamos coordenadas del mouse
            cord_x = ventana_1.mouse_x();
            cord_y = ventana_1.mouse_y();

            //Mostramos intensidad en punto
            cout<<"Intensidad en ("<<cord_x<<","<<cord_y<<"): "
            <<int(imagen_1(cord_x,cord_y))<<endl;

            //Dibujamos perfil de intensidad de la fila
            imagen_2.fill(0).draw_graph(imagen_1.get_row(cord_y), white);
            imagen_2.display(ventana_2);
        }
    }
    return 0;
}
