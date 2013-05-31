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
 
    (vector, new_vector).display();
}

/// Implementa la compresion RLC sin perdidas (supongo primer valor 0)
CImg<int> RLC_compresion(CImg<double> base, double umbral = 128, bool BIT_INICIO = false) {

    CImg<bool> umbralizada(base.get_threshold(umbral));
    CImg<int> vector_c;

    unsigned int contador = 0;
    bool bit_actual = BIT_INICIO;

    cimg_forXY(umbralizada, x, y) {
        // Si cambiamos de bit o es el ultimo elemento
        if (umbralizada(x, y) != bit_actual || (x == base.width() - 1 && y == base.height() - 1)) { 
            bit_actual = !bit_actual;

            vector_c.resize(vector_c.width() + 1, -100, -100, -100, 0);
            vector_c(vector_c.width() - 1, 0) = contador;                

            contador = 1;

        } else { 
            contador++;
        }

    }
    // Le sumo un elemento mas al final, que fue el que no conte en el for
    vector_c(vector_c.width() - 1, 0) += 1;

    // La suma de los valores en el vector_c han de ser igual a la cant elementos en base
    assert(vector_c.sum() == (base.width() * base.height()));

    // Tasa de compresiones
    double n1 = base.width() * base.height();
    double n2 = vector_c.width() * 8 * 2 - 1; // El * 2 - 1 es para contar los espacios

    std::cout << "Tasa de compresion estimada: CR = n_original / n_comprimida\n";
    std::cout << "Original (codificada 1 bit):\tCR = " << n1 / n2 * 100.0 << "%\n";
    std::cout << "Original (codificada 8 bits):\tCR = " << ( n1 * 8.0 ) / n2 * 100.0 << "%\n";

    // Agregamos la cabecera: vector_c_final = [bit inicial, M, N, vector_c]
    CImg<int> vector_c_final(3, 1);
    vector_c_final(0, 0) = BIT_INICIO;
    vector_c_final(1, 0) = base.width();
    vector_c_final(2, 0) = base.height();

    vector_c_final.append(vector_c, 'x'); // appendamos el vector_c

    // Y lo guardamos
    (umbralizada * 255).save("resultados/g8e2_original.bmp");
    cimg_ce::image_to_text<double>(vector_c_final, "resultados/g8e2_comprimido.rlc");

    return vector_c;

}

/// Implementa la descompresion RLC (devuelve una imagen binaria)
CImg<bool> RLC_descompresion(const char * filename) {

    // Abrimos el codigo rlc
    CImg<int> vector_c(cimg_ce::image_to_text<int>(filename));

    // En la primera columna tengo el valor binario que comienza, luego columnas y filas
    CImg<bool> restaurada(vector_c(1, 0), vector_c(2, 0));

    bool bit_actual = vector_c(0, 0);

    unsigned int kStartCantBits = 3; // Aca comienza la cantidad de bits en cada imagen
    unsigned int kContador = 0;
    
    cimg_forXY(restaurada, x, y) {
        if (kContador < vector_c(kStartCantBits, 0)) {
            kContador++;
        } else {
            kStartCantBits++;
            kContador = 1;
            bit_actual = !bit_actual;
        }

        restaurada(x, y) = bit_actual;
    }

    return restaurada;
}

/// EJERCICIO 2
void guia8_eje2(const char * filename, const double UMBRAL = 128, const bool BIT_INICIO = false) {

    CImg<double> base(filename);

    RLC_compresion(base, UMBRAL, BIT_INICIO);
    CImg<double> descomprimido = RLC_descompresion("resultados/g8e2_comprimido.rlc");

    (base.get_threshold(UMBRAL) * 255, descomprimido * 255)
        .display("Original / Descomprimida RLC", 0);

    // El archivo rlc para "cuadro.png" es de 1.011 bytes
    // El archivo bmp de "cuadro.png" umbralizado es de 196.662 bytes
    // El CR estimado para 8 bits es 13110.5 %
    // El CR calculado es: CR = 196.662 / 1.011 ~= 19452.2 %
    // La diferencia relativa entre ambos es de menos del 1%.

    // Para "huang1.jpg" el CR_estimado = 1753.06% [8 bits] (buena compresion)
    // Para "huang3.jpg" el CR_estimado = 357.81% [8 bits] (buena compresion, pero menor, debido al detalle)
    // Para una imagen (256x256) con R_impulsivo (con varianza 300), CR_estimado = 100 %
        // La compresion sigue estando, pero es menor, y del solo 10 % si se codifica con 1 bit

    // Aun asi, esto demuestra que el metodo es bastante bueno comprimiendo solo imagenes binarias,
    // y que su CR es completamente variable

}

int main (int argc, char* argv[]) {

    srand(time(0));

    const char* _filename = cimg_option("-i", "../../img/estanbul.tif", "Imagen");
   
    //guia8_eje1(_filename);
    guia8_eje2(_filename);

    return 0;
}