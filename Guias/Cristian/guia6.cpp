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
    double retorno = 1;
    double mn = ventana.width() * ventana.height();
    cimg_forXY(ventana, s, t) {
        // Le multiplicamos para hacer la productoria
        retorno *= ventana(s, t);
    }

    // Si me da negativo, no le pongo la raiz, sino que le asigno 0
    retorno = (retorno < 0) ? 0 : pow(retorno, 1 / mn);

    return retorno;
}

/// Aplico la media contra-armonica a una ventana que me pasan con orden Q, y retorno el valor del punto x,y
double apply_contraharmonic_mean(CImg<double> ventana, double Q) {
    double numerador = 0;
    double denominador = 0;

    cimg_forXY(ventana, s, t) {
        numerador += pow(ventana(s, t), Q + 1);
        denominador += pow(ventana(s, t), Q);
    }

    // Evitamos dividir por cero
    numerador /= (denominador != 0) ? denominador : 1;

    return numerador;
}

/// Filtros de ordenamiento: mediana
double apply_median(CImg<double> ventana) {
    // Los ordeno
    ventana.sort();

    // retorno el que este en el medio
    return ventana(ventana.width() / 2, ventana.height() / 2);
}

/// Filtro del punto medio
double apply_midpoint(CImg<double> ventana) {
    // Obtengo el valor maximo y el minimo de la ventana
    double max = ventana.max();
    double min = ventana.min();

    return 0.5 * (max + min);
}

/// Filtro de media-alfa recortado (el d es la mitad de la formula 5.3-11 p246)
double apply_alpha_trimmed_mean(CImg<double> ventana, unsigned int d = 2) {

    unsigned int m = ventana.width();
    unsigned int n = ventana.height();
    int factor = m * n - 2 * d;

    double coeff = 1.0 / factor;
    double sumatoria = 0;

    // Lo ordeno 
    ventana.sort();

    // Pero en la sumatoria solo considero los que estan dentro de la ventana mn - d
    for (unsigned int k = d; k < (m * n - d); k++) {
        // El modulo me da la columna, la division la fila
        unsigned int columna = k % m;
        unsigned int fila = floor(k / n);

        sumatoria += ventana(columna, fila);
    }
 //   ventana.get_sort().display("derp", 0);
  //  std::cout << sumatoria << " * " << coeff << " = " << sumatoria * coeff << endl;

    double retorno = coeff * sumatoria;

    // Si el valor del factor es 0 o menor, retorno el pixel original sin procesar
    if (factor <= 0) {
        retorno = ventana(m / 2, n / 2);
    }

    return retorno;
}

/// Aplico el filtro de la media geometrica a una imagen base, usando una ventana S de MxN
// Tipo_filtro : g [Geometrica], c [Contra-armonica], m [mediana], p [midpoint], a [alpha-trimmed]
CImg<double> apply_mean(
    CImg<double> base,
    unsigned char tipo_filtro = 'g',
    double factor = 0,
    int m = 3,
    int n = 3) {

    // Mi ventana
    CImg<double> S;

    // Para determinar el tamanho de las ventanas
    int step_x = m / 2;
    int step_y = n / 2;

    // Recorro la base y voy tomando ventanas
    cimg_forXY(base, x, y) {

        double pixel_procesado;

        // Esto es para evitar que se me vaya del rango
        int x0 = (x - step_x < 0) ? 0 : x - step_x;
        int y0 = (y - step_y < 0) ? 0 : y - step_y;
        int x1 = (x + step_x >= base.width()) ? base.width() - 1 : x + step_x;
        int y1 = (y + step_y >= base.height()) ? base.height() - 1 : y + step_y;

        // Obtengo la ventana S
        S = base.get_crop(x0, y0, x1, y1);

        // Aplico el filtro media geometrica
        if (tipo_filtro == 'g') {
            pixel_procesado = apply_geometric_mean(S);
        // Contra-armonica
        } else if (tipo_filtro == 'c') {
            pixel_procesado = apply_contraharmonic_mean(S, factor);
        // Mediana
        } else if (tipo_filtro == 'm') {
            pixel_procesado = apply_median(S);
        // Midpoint
        } else if (tipo_filtro == 'p') {
            pixel_procesado = apply_midpoint(S);
        // Media Alpha Recortada
        } else if (tipo_filtro == 'a') {
            pixel_procesado = apply_alpha_trimmed_mean(S, factor);
        }

        base(x, y) = pixel_procesado;

    }

    return base;

}

/// EJERCICIO 2 y 3
void guia6_eje2(
    const char * filename,
    double var_gaussian,
    double var_uniform,
    double var_impulsivo,
    double Q,
    unsigned int d) {

    CImg<double> base(filename);
    CImg<double> ruidosa(base);

    const double NO_APLICAR_RUIDO = -1.1;

    // Le contamino con ruido gaussiano e impulsivo
    // Si vale -1.1, no aplico el ruido
    if (var_gaussian != NO_APLICAR_RUIDO) {
        ruidosa.noise(var_gaussian, 0);
    }
    if (var_uniform != NO_APLICAR_RUIDO) {
        ruidosa.noise(var_uniform, 1);
    }
    if (var_impulsivo != NO_APLICAR_RUIDO) {
        ruidosa.noise(var_impulsivo, 2);
    }

    CImg<double> media_geom(apply_mean(ruidosa, 'g'));
    CImg<double> media_cohm(apply_mean(ruidosa, 'c', Q));
    CImg<double> ord_median(apply_mean(ruidosa, 'm'));
    CImg<double> ord_midpnt(apply_mean(ruidosa, 'p'));
    CImg<double> ord_alphtr(apply_mean(ruidosa, 'a', d));

    std::cout << "ECM media_geom : " << base.MSE(media_geom) << endl;
    std::cout << "ECM media_cohm : " << base.MSE(media_cohm) << endl;
    std::cout << "ECM ord_median : " << base.MSE(ord_median) << endl;
    std::cout << "ECM ord_midpnt : " << base.MSE(ord_midpnt) << endl;
    std::cout << "ECM ord_alphtr : " << base.MSE(ord_alphtr) << endl;

    (ruidosa, media_geom, media_cohm, ord_median, ord_midpnt, ord_alphtr)
        .display("Base con ruido impulsivo/gaussiano, geometrica, contra-armonica, mediana, midpoint, alpha-trimmed", 0);

    // Conclusiones: el ruido sal y pimienta me jode todo, excepto el median y alphtr
}

int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/sangre.jpg", "Image");

    const double opt_1 = cimg_option("-g", 1.0, "Gaussian");
    const double opt_2 = cimg_option("-u", 1.0, "Uniforme");
    const double opt_3 = cimg_option("-m", 1.0, "Impulsivo");
    
    const double opt_4 = cimg_option("-q", 1.0, "Orden");
    const double opt_5 = cimg_option("-d", 2.0, "Distancia para el alpha-trimmed");
    
    //guia6_eje1(filename, opt_1, opt_2, opt_3);
    guia6_eje2(filename, opt_1, opt_2, opt_3, opt_4, opt_5);

    return 0;
}
