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

/// EJERCICIO 1, con varianzas de gaussiano, uniforme e impulsivo
void guia6_eje1(const char * filename, double var_g, double var_u, double var_i) {

    CImg<double> base(filename);
    //base.quantize(pow(2, 8)); // para hacerla en escala de grises bien bien

    CImg<double> b_ga(base.get_noise(var_g, 0));
    CImg<double> b_un(base.get_noise(var_u, 1));
    CImg<double> b_im(base.get_noise(var_i, 2));

    (base, b_ga, b_un, b_im).display("Base, Gaussiano, Uniforme, Impulsivo", 0);

    b_ga.get_histogram(256, 0, 255).display_graph("Gaussiano", 3);
    b_un.get_histogram(256, 0, 255).display_graph("Uniforme", 3);
    b_im.get_histogram(256, 0, 255).display_graph("Impulsivo", 3);

}

// Obtengo la ventana mxn de una imagen parado en el pixel x,y
CImg<double> get_ventana(
    CImg<double> base,
    unsigned int x,
    unsigned int y,
    unsigned int m,
    unsigned int n) {

}

/// Aplico la media geometrica a una ventana que me pasan, y retorno el valor del punto x,y
double apply_geometric_mean(CImg<double> ventana) {
    double retorno = 0;
    double mn = ventana.width() * ventana.height();

    cimg_forXY(ventana, s, t) {
        // Si es 0, le asignamos el primer elemento, sino el anterior
        retorno = (retorno == 0) ? 1 : retorno;

        // Le multiplicamos para hacer la productoria
        retorno *= ventana(s, t);
    }

    return pow(retorno, 1 / mn);
}

/// Aplico la media contra-armonica a una ventana que me pasan con orden Q, y retorno el valor del punto x,y
double apply_contraharmonic_mean(CImg<double> ventana, double Q) {
    double numerador = 0;
    double denominador = 0;

    cimg_forXY(ventana, s, t) {
        numerador += pow(ventana(s, t), Q + 1);
        denominador += pow(ventana(s, t), Q);
    }

    return numerador/denominador;
}

/// Aplico el filtro de la media geometrica a una imagen base, usando una ventana S de MxN
// Tipo_filtro : m [Media Geometrica], c [Contra-armonica]
CImg<double> apply_mean(
    CImg<double> base,
    unsigned char tipo_filtro = 'm',
    unsigned int m = 3,
    unsigned int n = 3,
    double Q = 0) {

    CImg<double> S;

    // Recorro la base y voy tomando ventanas
    cimg_forXY(base, x, y) {

        double pixel_procesado;

        // Esto es para evitar que se me vaya del rango
        int x0 = (x - m < 0) ? 0 : x - m;
        int y0 = (y - n < 0) ? 0 : y - n;
        int x1 = (x + m > base.width()) ? base.width() : x + m;
        int y1 = (y + n > base.height()) ? base.height() : y + n;

        // Obtengo la ventana S
        S = base.get_crop(x0, y0, x1, y1);

        // Aplico el filtro media geometrica
        if (tipo_filtro == 'm') {
            pixel_procesado = apply_geometric_mean(S);
        // Contra-armonica
        } else if (tipo_filtro == 'c') {
            pixel_procesado = apply_contraharmonic_mean(S, Q);
        }

        base(x, y) = pixel_procesado;

    }

    return base;

}

/// EJERCICIO 2
void guia6_eje2(const char * filename, double var_gaussian, double var_impulsivo, double Q) {

    CImg<double> base(filename);
    CImg<double> ruidosa(base);

    // Le contamino con ruido gaussiano e impulsivo
    ruidosa.noise(var_gaussian, 0);
    ruidosa.noise(var_impulsivo, 2);

    CImg<double> media_geom(apply_mean(ruidosa, 'm'));
    CImg<double> media_cohm(apply_mean(ruidosa, 'c', Q));

    std::cout << "ECM media_geom : " << base.MSE(media_geom) << endl;
    std::cout << "ECM media_cohm : " << base.MSE(media_cohm) << endl;

    (ruidosa, media_geom, media_cohm)
        .display("Base con ruido impulsivo y gaussiano, media geometrica, media contra-armonica", 0);

}

int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/sangre.jpg", "Image");

    const double opt_1 = cimg_option("-g", 1.0, "Gaussian");
    const double opt_2 = cimg_option("-u", 1.0, "Uniforme");
    const double opt_3 = cimg_option("-m", 1.0, "Impulsivo");

    //guia6_eje1(filename, opt_1, opt_2, opt_3);
    guia6_eje2(filename, opt_1, opt_3, opt_2);

    return 0;
}
