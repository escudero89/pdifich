#include <iostream>
#include "../../../CImg-1.5.4/CImg.h"

using namespace cimg_library;
using namespace std;


int main(){

    CImg<unsigned char> imagen_1("../../../img/rmn.jpg"),
                        imagen_2,
                        imagen_3,
                        imagen_4,
                        imagen_5,
                        imagen_6;


    imagen_2 = imagen_1.get_resize_halfXY().get_resize_doubleXY();
    imagen_3 = imagen_2.get_resize_halfXY().get_resize_doubleXY();
    imagen_4 = imagen_3.get_resize_halfXY().get_resize_doubleXY();
    imagen_5 = imagen_4.get_resize_halfXY().get_resize_doubleXY();
    imagen_6 = imagen_5.get_resize_halfXY().get_resize_doubleXY();

    CImgList<unsigned char> lista(imagen_1,
                                  imagen_2,
                                  imagen_3,
                                  imagen_4,
                                  imagen_5,
                                  imagen_6);

	CImgDisplay ventana(lista, "Submuestreo", 0);

	while (!ventana.is_closed() && !ventana.is_keyQ()) { }








    return 0;
}
