#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions.h"
#include <vector>
#include <cstdlib>
#include <string>

using namespace cimg_library;
using namespace std;

CImg<unsigned char> normalizar(CImg<float> imagen_entrada,int min_in = 0,
                                                        int max_in = 0,
                                                        int min_out= 0,
                                                        int max_out= 255){

    CImg<unsigned char> imagen_salida(imagen_entrada.width(),
                                      imagen_entrada.height(),
                                      1,1);

    if(min_in == 0 and max_in == 0){
        //Obtenemos valores maximos y minimos de la imagen para realizar el mapeo
        min_in = imagen_entrada.min_max( max_in );
    }

    //Realizamos mapeo lineal en rango [min_in max_in] => [min_out max_out]
    cimg_forXY(imagen_entrada,i,j){

        imagen_salida(i,j) = (unsigned char)(((imagen_entrada(i,j) - min_in) * (max_out - min_out))
                                    /
                        (max_in - min_in) + min_out);
    }

    return imagen_salida;
}



int main(int argc, char *argv[]){

#if 0     ///          /// EJERCICIO 1 ///          ///

    const char* filename = cimg_option("-i", "../../img/cameraman.tif", "Input Image File");

    CImg<double>img(filename);

    //Transformada directa y obtencion de las partes real e imaginaria
    CImgList<>TDF_img = img.get_FFT();
    CImg<double>TDF_real=TDF_img[0];
    CImg<double>TDF_imaginaria=TDF_img[1];

    CImgList<>TDF_nueva(TDF_img);
    TDF nueva[0]=TDF_real;
    TDF nueva[1]=TDF_imaginaria;

    //Transformada inversa y obtencion de la parte real
    CImg<double>img_nueva=TDF_nueva.get FFT(true)[0];




#endif     ///          /// FIN E1 ///          ///


    return 0;
}
