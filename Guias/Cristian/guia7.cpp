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

/// Extrae los x maximos picos de la transformada de Hough
CImg<double> get_maxs_from_hough(CImg<double> Hough, unsigned int cantidad_picos = 1) {

    CImg<double> retorno(Hough);

    double max_umbral = 0;

    for (unsigned int kMaxs = 0 ; kMaxs < cantidad_picos ; kMaxs++) {
        unsigned int x = 0;
        unsigned int y = 0;
        const double zero = 0;

        max_umbral = Hough.max();
        Hough.max() = zero;
        std::cout << "Max-umbral: " << max_umbral << std::endl;
/*
        while (y < Hough.height()) {
            // Cada vez que encuentro un maximo
            if (Hough(x, y) == Hough.max()) {
                retorno(x, y) = Hough(x, y);
                Hough.max(0.0);
                break;
            }
            
            // Esto es a motivos de ir avanzando
            x++;
            if (x >= Hough.width()) {
                x = 0;
                y++;
            }
        }
        */
    }
retorno.get_threshold(max_umbral).display();
    return retorno.get_threshold(max_umbral);
}

/// Le mandamos una transformada de Hough, y recorta solo en el angulo y rho que le pedimos
// El angulo se lo pasas en grados [-90..90], y el rho se escala por la imagen, su rango es [-1.4142, 1.4142]
CImg<double> slice_hough(
    CImg<double> Hough, 
    double angulo, 
    double rho,
    int ang_tol = 0, 
    int rho_tol = 0,
    bool just_max = false) {

    // Obtenemos la columna (le sumo 90 para hacer el rango [0..180])
    double col_hough = (angulo + 90) / 180 * Hough.width(); 

    // Y ahora la fila (las operaciones de adelante es para escalar entre 0 y 1)
    double row_hough = (rho + sqrt(2)) * sqrt(2) / 4 * Hough.height();

    // Guardo el maximo pico
    double max_pico = 0;
    double x_max_pico = 0;
    double y_max_pico = 0;

    CImg<double> auxiliar(Hough.width(), Hough.height(), 1, 1, 0);

    for (int i = -rho_tol ; i <= rho_tol ; i++) {
        for (int j = -ang_tol ; j <= ang_tol ; j++) {
            // Evitamos que se nos salga de los limites
            if (col_hough + i < Hough.width() && col_hough + i >= 0 &&
                row_hough + j < Hough.height()&& row_hough + j >= 0) {

                x_max_pico = col_hough + i;
                y_max_pico = row_hough + j;

                // Si solo es el max, sacamos el max, sino todos
                if (just_max) {
                    if (Hough(col_hough + i, row_hough + j) > max_pico) {
                        max_pico = Hough(x_max_pico, y_max_pico);
                    }
                } else {
                    auxiliar(x_max_pico, y_max_pico) = Hough(x_max_pico, y_max_pico);
                }
            }
        }
    }

    if (just_max) {
        auxiliar(x_max_pico, y_max_pico) = Hough(x_max_pico, y_max_pico);
    } else { // Aplico un umbral asi no me devuelve  todooo
        auxiliar.threshold(0.3 * auxiliar.mean() + 0.7 * auxiliar.max());
    }

    return auxiliar;
}

/// EJERCICIO 2 (el inciso uno fue experimental)
void guia7_eje2(
    const char * filename, 
    double angulo, 
    double rho, 
    int ang_tol, 
    int rho_tol,
    unsigned char umbral,
    unsigned int max_picos) {

    CImg<double> base(filename);
    // Al trabajar con imagenes reales, primero debemos pasarle un PA suma cero
    const char filter_name [] = "filtros/laplaciano2.txt";

    CImg<double> filtro(cimg_ce::get_filter_from_file<double>(filter_name));
    CImg<double> pa(base.get_convolve(filtro));

    // Ahora la umbralizamos
    CImg<bool> umb(pa.abs().get_threshold(umbral));

    CImg<double> Hough(hough(umb));

    CImg<double> Sliced(slice_hough(Hough, angulo, rho, ang_tol, rho_tol));

    (base, pa, umb, Hough).display("Base, PA, Umbralizada, Hough", 0);
    (base, Sliced, hough(Sliced, true) + base / 2).display("Eje 2", 0);
    (base, hough(get_maxs_from_hough(Hough, max_picos), true) + base / 2).display("Eje2", 0);
}

int main (int argc, char* argv[]) {

    const char* _filename = cimg_option("-i", "../../img/estanbul.tif", "Imagen");
    const char* _file_gx = cimg_option("-gx", "filtros/roberts_gx.txt", "Filtro G_x");
    const char* _file_gy = cimg_option("-gy", "filtros/roberts_gy.txt", "Filtro G_y");

    const unsigned int _umbral = cimg_option("-umbral", 128, "Umbral para binarizacion");
    
    const double _gaussian_var = cimg_option("-gvar", -1, "Varianza gaussian");

    const double _rho = cimg_option("-rho", 0.0, "Rho de la transformada Hough");
    const double _ang = cimg_option("-ang", 0.0, "Angulo de la transformada Hough");
    const int _rho_tol = cimg_option("-rht", 0, "Tolerancia para elegir rho");
    const int _ang_tol = cimg_option("-ant", 0, "Tolerancia para elegir el angulo");

    const unsigned int _ints = cimg_option("-ints", 25, "Valor unsigned int multipleuso");

    //guia7_eje1(_filename, _file_gx, _file_gy, _umbral, _gaussian_var);
    guia7_eje2(_filename, _ang, _rho, _rho_tol, _ang_tol, _umbral, _ints);

    return 0;
}