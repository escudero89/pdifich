#include <cassert>
#include <cmath>
#include <complex>
#include <ctime>
#include <iostream>
#include <cstring>

#include "../../CImg-1.5.4/CImg.h"
#include "PDI_functions.h"
#include "funciones.h"

#define EPSILON 0.00001
#define PI 3.14159265359
using namespace cimg_library;

/// Voy a suponer que el tamanho de espuma h se considera segun la altura h + altura de la cerveza.



int main (int argc, char* argv[]) {

    srand(time(0));

    const char* _filename = cimg_option("-i", "../../img/estanbul.tif", "Imagen");
   
    //guia8_eje1(_filename);
    guia8_eje2(_filename);

    return 0;
}