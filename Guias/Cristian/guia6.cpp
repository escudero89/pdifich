/// LINEA DE COMANDO A USAR (se agrega una bandera -lfftw3)
// g++ -o guia5.bin guia5.cpp -O0 -lm -lpthread -lX11 -lfftw3
#include <cassert>
#include <cmath>
#include <complex>
#include <ctime>
#include <iostream>

#include "../../CImg-1.5.4/CImg.h"
#include "PDI_functions.h"
#include "funciones.h"

using namespace cimg_library;

/// EJERCICIO 6 GUIA 1, con varianzas de gaussiano, uniforme e impulsivo
void guia6_eje1(const char * filename, double var_g, double var_u, double var_i) {

    CImg<double> base(filename);
    //base.quantize(pow(2, 8)); // para hacerla en escala de grises bien bien

    CImg<double> b_ga(base.get_noise(var_g, 0));
    CImg<double> b_un(base.get_noise(var_u, 1));
    CImg<double> b_im(base.get_noise(var_i, 2));

    (base, b_ga, b_un, b_im).display("Base, Gaussiano, Uniforme, Impulsivo");

    b_ga.get_histogram(256, 0, 255).display_graph("Gaussiano", 3);
    b_un.get_histogram(256, 0, 255).display_graph("Uniforme", 3);
    b_im.get_histogram(256, 0, 255).display_graph("Impulsivo", 3);

}

int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/grises.jpg", "Image");

    const double opt_1 = cimg_option("-g", 1.0, "Gaussian");
    const double opt_2 = cimg_option("-u", 1.0, "Uniforme");
    const double opt_3 = cimg_option("-m", 1.0, "Impulsivo");

    guia6_eje1(filename, opt_1, opt_2, opt_3);

    return 0;
}
