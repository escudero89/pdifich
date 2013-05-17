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
#define EVITAR_PIXEL -123.321
#define PI 3.14159265359
using namespace cimg_library;

/// Convoluciona con ambos filtros gx y gy y devuelve una imagen binaria con los bordes
// Sacando un umbral como 4to parametro
CImg<bool> border_detection(
    CImg<double> base, 
    const char * file_gx, 
    const char * file_gy, 
    unsigned int threshold = 128) {

    CImg<double> filter_gx = cimg_ce::get_filter_from_file<double>(file_gx);
    CImg<double> filter_gy;

    CImg<double> resultado(base.get_convolve(filter_gx).get_abs());

    // Si le paso un filter_gy, lo uso, sino no
    if (strlen(file_gy) > 2) {
        filter_gy = cimg_ce::get_filter_from_file<double>(file_gy);
        resultado = resultado + base.get_convolve(filter_gy).get_abs();
    }

    CImg<bool> resultado_bin(resultado.get_threshold(threshold));

    return resultado_bin;
}

/// EJERCICIO 1
void guia7_eje1(
    const char * filename, 
    const char * file_gx, 
    const char * file_gy,
    const unsigned int umbral,
    const double gaussian_var) {

    CImg<double> base(filename);
    base = cimg_ce::transform_to_grayscale(base);

    // Si le pasamos varianza positiva, le ponemos ruido gaussiano
    if (gaussian_var >= 0) {
        base.noise(gaussian_var, 0);
    }

    (border_detection(base, file_gx, file_gy)).display();
}

int main (int argc, char* argv[]) {

    const char* _filename = cimg_option("-i", "../../img/estanbul.tif", "Imagen");
    const char* _file_gx = cimg_option("-gx", "filtros/roberts_gx.txt", "Filtro G_x");
    const char* _file_gy = cimg_option("-gy", "filtros/roberts_gy.txt", "Filtro G_y");

    const unsigned int _umbral = cimg_option("-umbral", 128, "Umbral para binarizacion");
    
    const double _gaussian_var = cimg_option("-gvar", -1, "Varianza gaussian");

    guia7_eje1(_filename, _file_gx, _file_gy, _umbral, _gaussian_var);

    return 0;
}