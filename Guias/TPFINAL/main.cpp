//Para compilar: g++ -o guia5 guia5.cpp -O0 -lm -lpthread -lX11 -lfftw3 && ./guia5

#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions.h"
#include "../Cristian/funciones.h"
#include <cstdlib>
#include <complex>
#include <string>
#include <cmath>


using namespace cimg_library;
using namespace std;


/// Genera el filtro H(u, v) para filtrado homomorfico
CImgList<> get_H_homomorphic(
    CImg<double> base,
    unsigned int cutoff_frecuency,
    double gamma_l = 0.5,
    double gamma_h = 2.0,
    double c = 1.0) {

    CImg<double> H(base.width(), base.height()),
        D_matriz(cimg_ce::get_D_matriz(base));

    cimg_forXY(H, u, v) {
        double factor = 1 - exp(-c * pow(D_matriz(u, v), 2) / pow(cutoff_frecuency, 2));

        H(u, v) = (gamma_h - gamma_l) * factor + gamma_l;
    }

    // Y lo deshifteamos
    H.shift(-H.width()/2, -H.height()/2, 0, 0, 2);

    // La parte imaginaria es cero
    return (H, H.get_fill(0));
}

/// Aplica un filtro haciendo filtrado homomorfico
CImg<double> get_image_homomorphic(CImg<double> base, CImgList<> H) {

    // Una imagen f(x, y) = i(x, y) * r(x, y), por lo que aplicamos log para separarlos
    CImg<double>
        base_normalizada(base.get_normalize(1, 100)),
        logarithm(cimg_ce::get_log(base_normalizada)),
        filtrado;

    (base_normalizada, base_normalizada.get_equalize(256)).display("Imagen Original, Imagen Ecualizada");
    CImgDisplay hist_wdw;
    base_normalizada.get_normalize(0, 255).get_histogram(256, 0, 255).display_graph(hist_wdw, 3);
    base_normalizada.get_normalize(0, 255).get_equalize(256).get_histogram(256, 0, 255).display_graph(hist_wdw, 3);

    // Ahora los tengo separado teoricamente, aplico fourier (esta dentro de la funcion)
    // Y aplico el filtro S(u, v) = H(u, v) * F_i(u,v) + H(u,v) * F_r(u,v)
    filtrado = get_img_from_filter(logarithm, H);
    filtrado.normalize(0, 1);

    // Ahora tengo que volver a como era antes, aplicando exp
    filtrado.exp();

    return filtrado.get_normalize(0, 255);
}


/// Aplicamos la correccion Psi para expandir oscuros y contraer claros (mejora contraste)
// Trabajamos la imagen de entrada en el modelo HSI para modificar solo el canal I
CImg<double> correccionPsi(CImg<double> img, double psi = 3){

    cimg_forXY(img, x, y){
        img(x, y, 2) = ( 255 * log((img(x, y, 2)/255) * (psi -1) + 1) ) / log(psi);
    }

    return img;

}

/// Separa componente de luminancia de componente de reflactancia
// Solo debe venir la componente de intensidad de la imagen
CImgList<double> decouplingLR(
    CImg<double> img, int option_fc, double option_gl, double option_gh, double option_c){

    CImgList<double> f_luminancia(get_H_homomorphic(base, option_fc, option_gl, option_gh, option_c));
    CImgList<double> f_reflactancia(get_H_homomorphic(base, option_fc, option_gh, option_gl, option_c));

    CImg<double> luminancia(get_image_homomorphic(base, f_luminancia).get_normalize(0, 255));
    CImg<double> reflactancia(get_image_homomorphic(base, f_reflactancia).get_normalize(0, 255));

    return (luminancia, reflactancia);

}

int main(int argc, char *argv[]){
    const char* filename = cimg_option("-i","img/prueba.jpg", "Imagen de entrada");
    const double psi = cimg_option("-psi", 3.0, "Factor de correccion psi");

    const int fc = cimg_option("-fc", 150, "Frecuencia de Corte");
    const double gl = cimg_option("-gl", 1.0, "Gamma Low");
    const double gh = cimg_option("-gh", 0.0, "Gamma High");
    const double c = cimg_option("-c", 0.0, "Offset");

    CImg<double> base(filename);
    base.RGBtoHSI();

    CImg<double> corregida(correccionPsi(base, psi));


    (base, corregida, decouplingLR(corregida.get_channel(2))).display();

    return 0;
}
