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

/// Ejercicio 1
void guia8_eje1(const char * filename) {

    CImg<unsigned char> base(filename);
    // Lo convierto a niveles de gris
    base = cimg_ce::transform_to_grayscale(base);

    base.quantize(8);

    CImg<unsigned char> vector(base.get_histogram(8, 0, 255));

    base.display("Base", 0);
    vector.display_graph("Histograma", 3);

    // Agrego una fila debajo del vector, ascendente (y fila arriba, u fila abajo)
    CImg<double> new_vector(vector.width(), 2);

    // Obtengo la suma del vector para las probabilidades
    double sum = vector.sum();

    cimg_forX(vector, x) {
        new_vector(x, 0) = vector(x) / sum;
    }
    
    // Ordeno el vector de forma descendente
    vector.sort(false, 'x');

    cimg_forX(vector, x) {
        cimg_forX(new_vector, i) {
            // Para comparar
            if (abs(double(vector(x)) / sum - new_vector(i, 0)) < EPSILON) {
                new_vector(i, 1) = x; // le asigno el indice
                break;
            }
        }
    }

    /// El valor final para estambul.tif es:
    // a_6 | 10     (0.213)
    // a_5 | 11     (0.211)
    // a_7 | 000    (0.150)
    // a_3 | 001    (0.140)
    // a_1 | 011    (0.131)
    // a_2 | 0100   (0.093)
    // a_4 | 01010  (0.062)
    // a_0 | 01011  (0.000)
 | 0
    (vector, new_vector).display();
}

int main (int argc, char* argv[]) {

    srand(time(0));

    const char* _filename = cimg_option("-i", "../../img/estanbul.tif", "Imagen");
   
    guia8_eje1(_filename);

    return 0;
}