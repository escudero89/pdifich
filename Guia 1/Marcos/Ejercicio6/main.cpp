#include <iostream>
#include "../../../CImg-1.5.4/CImg.h"

using namespace cimg_library;
using namespace std;


int main(){

    CImg<unsigned char> imagen("../../../img/huang2.jpg");
    CImgList<unsigned char> lista(imagen);

    for(int i = 7; i>=0; i--){
        lista.push_back(imagen.get_quantize(pow(2,i),1));
    }

    CImgDisplay ventana(lista, "Cuantizaciones sucesivas", 1);

	while (!ventana.is_closed() && !ventana.is_keyQ()) { }

    return 0;
}
