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

#define EPSILON 0.00001
#define PI 3.14159265359

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

    // Evitamos dividir por cero (definir un epsilon? @fern17 ain't nobody got time fo dat)
    if (!(abs(denominador) < EPSILON )) {
        numerador /= denominador;
    } else {
        numerador = 0; // o dividir por infinito, que es cero
    }

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
    CImg<double> procesada(base);
    CImg<double> S;

    // Para determinar el tamanho de las ventanas
    int step_x = m / 2;
    int step_y = n / 2;

    // Recorro la base y voy tomando ventanas (recorro por espectro tambien)
    cimg_forXYC(base, x, y, c) {

        double pixel_procesado;

        // Esto es para evitar que se me vaya del rango
        int x0 = (x - step_x < 0) ? 0 : x - step_x;
        int y0 = (y - step_y < 0) ? 0 : y - step_y;
        int x1 = (x + step_x >= base.width()) ? base.width() - 1 : x + step_x;
        int y1 = (y + step_y >= base.height()) ? base.height() - 1 : y + step_y;

        // Obtengo la ventana S (en cada canal)
        S = base.get_crop(x0, y0, 0, c, x1, y1, 0, c);

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

        procesada(x, y, c) = pixel_procesado;

    }

    return procesada;

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

    // Para poder normalizar la salida
    CImgList<double> coleccion((ruidosa, media_geom, media_cohm, ord_median, ord_midpnt, ord_alphtr));
    CImgDisplay ventana(coleccion, "Base con ruido impulsivo/gaussiano, geometrica, contra-armonica, mediana, midpoint, alpha-trimmed", 0);

    while (!ventana.is_closed() && !ventana.is_keyQ() ) {};

    coleccion.display("Displayed", 0);

    // Conclusiones: el ruido sal y pimienta me jode todo, excepto el median y alphtr
    /// Ante ruido gaussiano varianza=20 || impulsivo var=10 || ambos [grises.jpg (sangre.jpg)]

    // ECM media_geom : 97.843 (120.56) || 264.815 (331.562) || 6918.96 (7324.09)
    // ECM media_cohm : 105.652 (140.371) || 972.399 (260.08) || 2582.82 (782.567)
    // ECM ord_median : 79.9874 (140.299) || 23.3535 (67.7683) || 137.89 (182.15)
    // ECM ord_midpnt : 136.547 (185.093) || 2447.99 (1066.42) || 3554.6 (1835.38)
    // ECM ord_alphtr : 74.2385 (119.036) || 48.8281 (86.6234) || 169.474 (189.853)

    /// En promedio el que mejor se comporto fue el de mediana, seguido por el alfa_trimmed
    /// Ante la aparicion del impulsivo, se mueren los de no-ordenamiento y el midpoint
}

/// Devuelve un filtro notch rechazabanda (o pasabanda), donde W es el ancho de la banda rechazada.
CImgList<double> notch_filter(CImg<double> base, double D0, double W, bool is_passband = false) {

    CImg<double> D = cimg_ce::get_D_matriz(base);
    CImg<double> H(base.width(), base.height());

    cimg_forXY(H, u, v) {
        H(u, v) = (D(u, v) >= (D0 - W/2.0) && D(u, v) <= (D0 + W/2.0)) ? is_passband : !is_passband;
    }

    // Y desshifteo porque asi es la vida
    H.shift(-H.width()/2, -H.height()/2, 0, 0, 2);

    return (H, H.get_fill(0));
}

/// Devuelve un filtro notch ad hoc, del tamanho de la base (u0 y v0 distancia desde el centro)
CImgList<double> notch_filter(CImg<double> base, double D0, int u0, int v0, bool is_passband = false) {

    CImg<double> D1 = cimg_ce::get_D_matriz(base, -1, -1, -u0, -v0);
    CImg<double> D2 = cimg_ce::get_D_matriz(base, -1, -1, u0, v0);

    CImg<double> H(base.width(), base.height());

    cimg_forXY(H, u, v) {
        // Si esta dentro del radio D0 (cutoff frequency), es 1, sino 0
        H(u, v) = ( D1(u, v) <= D0 || D2(u, v) <= D0) ? is_passband : !is_passband;
    }

    // Y desshifteo porque asi es la vida
    H.shift(-H.width()/2, -H.height()/2, 0, 0, 2);

    // La componente imaginaria es 0
    return (H, H.get_fill(0));
}

/// EJERCICIO 4
void guia6_eje4(
    const char * filename = "../../img/img_degradada.tif",
    const char * filename_original = "../../img/img.tif",
    unsigned int D0 = 20,  // Cutoff frecuency
    unsigned int x0 = 199, // Puntos donde estan los focos del ruido
    unsigned int y0 = 219) {

    CImg<double> base(filename);
    CImg<double> original(filename_original);
    CImg<double> restaurada;
    CImg<double> restaurada_adhoc;
    CImg<double> solo_ruido;

    (base, magn_tdf(base)).display("Base y Magnitud, para inspeccionar", 0);

    int distancia_al_centro_x = x0 - floor(base.width() / 2.0);
    int distancia_al_centro_y = y0 - floor(base.height() / 2.0);

    // Esto es para aplicar un rechazabanda normal, la distancia al foco seria mi frecuencia de corte
    double distancia_al_foco = pow(pow(distancia_al_centro_x, 2) + pow(distancia_al_centro_y, 2), 0.5);

    // Y mi D0 seria mi "ancho" de la banda a rechazar
    CImgList<double> nf(notch_filter(base, distancia_al_foco, D0));

    // Por analisis, veo que esta el ruido en los puntos (58;38) .. (199; 219) [ptos intermedios esquinas]
    CImgList<double> nf1(notch_filter(base, D0, distancia_al_centro_x, distancia_al_centro_y));
    CImgList<double> nf2(notch_filter(base, D0, distancia_al_centro_x, -distancia_al_centro_y));
    
    CImgList<double> nf1p(notch_filter(base, D0, distancia_al_centro_x, distancia_al_centro_y, true));
    CImgList<double> nf2p(notch_filter(base, D0, distancia_al_centro_x, -distancia_al_centro_y, true));

    // Esto es para unir los filtros ad hoc que tengo en uno solo
    CImgList<double> nf12(cimg_ce::fusion_complex_images(nf1, nf2, true));
    CImgList<double> nf12p(cimg_ce::fusion_complex_images(nf1p, nf2p));

    // Aplico el filtro notch para eliminar los puntos de foco de mi ruido
    restaurada = cimg_ce::get_img_from_filter(base, nf);
    restaurada_adhoc = cimg_ce::get_img_from_filter(base, nf12);
    solo_ruido = cimg_ce::get_img_from_filter(base, nf12p);

    // Ahora mostramos ambas
    std::cout << "MSE original vs restaurada: " << original.MSE(restaurada) << std::endl;
    std::cout << "MSE original vs restaurada_adhoc: " << original.MSE(restaurada_adhoc) << std::endl;

    (original, restaurada, restaurada_adhoc, solo_ruido)
        .display("Original, Restaurada, Restaurada Ad Hoc y Solo Ruido (desde ad hoc)", 0);

    // Cualitativamente la imagen ha mejorado mucho, pero cuantitativamente (MSE) todavia hay
    // una gran "diferencia" en valores pixel a pixel
    // La restaurada ad hoc me da un poco menos de MSE, pero hasta ahi no mas (6042 vs 6065)
}

/// Filtro de degradacion uniforme por movimiento
CImgList<double> uniform_linear_motion(CImg<double> base, double T, double a, double b) {

    CImgList<double> H(2, base.width(), base.height());

    complex<double> j(0, 1);

    cimg_forXY(H[0], u, v) {
        double factor = PI * (u * a + v * b);

        complex<double> retorno = 0;
        
        // Para que directamente el sin me de 0 y todo el retorno sea 0
        if (!(abs(sin(factor)) < EPSILON)) {
            // Tambien debo tener precaucion si es pi/2 o cercano (el sin=1 y exp es =1)
            if (abs(cos(factor)) < EPSILON) {
                retorno = T / factor;
            } else {
                retorno = T / factor * sin(factor) * exp(-j * factor);
            }
        }

        H[0](u, v) = real(retorno);
        H[1](u, v) = imag(retorno);
        //std::cout << factor << " # " << real(retorno) << " + j" << imag(retorno);
        //getchar();
    }

    // Y desshifteo porque asi es la vida
    H[0].shift(-H[0].width()/2, -H[0].height()/2, 0, 0, 2);
    H[1].shift(-H[1].width()/2, -H[1].height()/2, 0, 0, 2);

    return H;
}


/// Filtro de Wiener Generalizado, al que le paso un H
CImgList<double> wiener_generalized(CImgList<double> H, double alfa, double K) {

    CImgList<double> wiener(2, H[0].width(), H[0].height());

    CImgList<double> magnitud_phase(cimg_ce::get_magnitude_phase(H));

    CImgList<double> H_conjugado(H);
    
    // Invierto la componente imaginaria para hacer el conjugado (que en teoria deberia dar 0 si es real)
    cimg_forXY(H_conjugado[0], u, v) {
        H_conjugado[1](u, v) = -H_conjugado[1](u, v);
    }

    CImgList<double> magnitud_phase_conjugado(cimg_ce::get_magnitude_phase(H_conjugado));

    // Ahora voy aplicando la formula 5.8-2
    cimg_forXY(wiener[0], u, v) {

        complex<double> factor1 = H_conjugado(u, v) / pow(magnitud_phase[0](u, v), 2);
        complex<double> factor2 = H_conjugado(u, v) / pow(magnitud_phase[0](u, v), 2) + K;

        complex<double> resultado = pow(factor1, alfa) * pow(factor2, 1 - alfa);

        wiener[0](u, v) = real(resultado);
        wiener[1](u, v) = imag(resultado);
    }

    // Y desshifteo porque asi es la vida
    H[0].shift(-H[0].width()/2, -H[0].height()/2, 0, 0, 2);
    H[1].shift(-H[1].width()/2, -H[1].height()/2, 0, 0, 2);

    return wiener;

}

/// EJERCICIO 5
void guia6_eje5(
    const char * filename,
    const double K,
    const double a,
    const double b) {

    CImg<double> base(filename);
    
    CImgList<double> H(uniform_linear_motion(base, K, a, b));
    //CImgList<double> wiener(wiener_generalized(H, 1, 1));

    (base, cimg_ce::get_img_from_filter(base, H)/*, cimg_ce::get_img_from_filter(base, wiener)*/)
        .display("Derp", 0);
}

int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/huang3_movida.tif", "Image");
    const char* filename_original = cimg_option("-o", "../../img/huang3.jpg", "Image");

    const double opt_1 = cimg_option("-g", 1.0, "Gaussian");
    const double opt_2 = cimg_option("-u", 1.0, "Uniforme");
    const double opt_3 = cimg_option("-m", 1.0, "Impulsivo");
    
    const double opt_4 = cimg_option("-q", 1.0, "Orden");
    const double opt_5 = cimg_option("-d", 2.0, "Distancia para el alpha-trimmed");
    
    const unsigned int opt_6 = cimg_option("-c", 10, "CutOff Frequency");
    const unsigned int opt_7 = cimg_option("-x", 199, "Punto x0");
    const unsigned int opt_8 = cimg_option("-y", 219, "Punto y0");

    //guia6_eje1(filename, opt_1, opt_2, opt_3);
    //guia6_eje2(filename, opt_1, opt_2, opt_3, opt_4, opt_5);
    //guia6_eje4(filename, filename_original, opt_6, opt_7, opt_8);
    guia6_eje5(filename, opt_1, opt_2, opt_3);

    return 0;
}
