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

//g++ -o template template.cpp -O0 -lm -lpthread -lX11 -lfftw3


/// SUBLIME TEXT

int main (int argc, char* argv[]) {

    srand(time(0));

    const char* _filename = cimg_option("-i", "training/???", "Imagen");
   

    return 0;
}