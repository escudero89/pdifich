/// LINEA DE COMANDO A USAR (se agrega una bandera -lfftw3)
// g++ -o guia5.bin guia5.cpp -O0 -lm -lpthread -lX11 -lfftw3
#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>

#include "../../CImg-1.5.4/CImg.h"
#include "PDI_functions.h"
#include "funciones.h"

using namespace cimg_library;

/// Dibuja una recta en una posicion pos, horizontal o vertical
CImg<bool> art_draw_line(CImg<bool> base, unsigned int pos = 0, bool horizontal = false) {

    unsigned int 
        x0 = (horizontal) ? 0 : pos,
        x1 = (horizontal) ? base.width() : x0,

        y0 = (!horizontal) ? 0 : pos,
        y1 = (!horizontal) ? base.height() : y0;

    unsigned char color[] = {1};

    // Dibujamos la recta
    base.draw_line(x0, y0, x1, y1, color);

    return base;
}

/// Dibujamos un rectangulo/triangulo o circulo en una base binaria. REVISAR PUNTOS QUE LE PASO
CImg<bool> art_draw_centered(
    CImg<bool> base, char fig, unsigned int pts_x [], unsigned int pts_y[]) {

    unsigned char color[] = {1};

    // Si queremos un rectangulo (o cuadrado), le pasamos [x0, x1] y [y0, y1]
    if (fig == 'r') {
        base.draw_rectangle(pts_x[0], pts_y[0], pts_x[1], pts_y[1], color);

    // Si queremos un triangulo, le pasamos [x0, x1, x2] y [y0, y1, y2]
    } else if (fig == 't') {
        base.draw_triangle(pts_x[0], pts_y[0], pts_x[1], pts_y[1], pts_x[2], pts_y[2], color);

    // Un circulo, le pasamos [x0, radio] y [y0 , 0]
    } else if (fig == 'c') {
        base.draw_circle(pts_x[0], pts_y[0], pts_x[1], color);

    } else {
        std::cout << "[art_draw_centered] :: No se eligio una figura\n"; assert(0);
    }

    return base;
}

/// EJERCICIO 1 del [1 ~ 3]
void guia5_eje1_part1() {

    // En los patrones (patrones/activacion):
    // 1 => B ; 2 => A ; 3 => D ; 4 => C

    unsigned int 
        width = 512, 
        height = 512,

        line_hor = 64, // posicion y = ?? de la linea horizontal
        line_ver = 64, // posicion x = ?? de la linea vertical

        quad_pts_x [] = { 192, 320 }, // pts para un cuadrado central
        quad_pts_y [] = { 192, 320 },

        cir_pts_x [] = { 256, 40 }, // pts para un circ de radio [x0, radio]
        cir_pts_y [] = { 256, 0 };

    CImg<bool> inciso(width, height),
        prueba_uno(inciso),
        prueba_dos(inciso),
        prueba_tres(inciso);

    /// ESTA IMAGEN ES UN CUADRADO CENTRADO Y DOS RECTAS HACIENDO UNA CRUZ EN LA ESQUINA
    // Lo relleno con ceros
    prueba_uno.fill(0);

    prueba_uno = art_draw_line(prueba_uno, line_hor, true);
    prueba_uno = art_draw_line(prueba_uno, line_ver, false);

    // Cuadrado central
    prueba_dos = art_draw_centered(prueba_uno, 'r', quad_pts_x, quad_pts_y);

    // Circulo central que reemplaza al cuadrado y las lineas
    prueba_tres = art_draw_centered(inciso, 'c', cir_pts_x, cir_pts_y);

    // Voy a tener una "+"" copada en el centro, 
    // luego el efecto de sync en el resto de la img
    // triangulo central: como cuadrado, pero esta mas abajo el "origen"
    (prueba_uno, prueba_dos, prueba_tres).display("Bases [1, 2, 3]");

    (magn_tdf(prueba_uno), magn_tdf(prueba_dos), magn_tdf(prueba_tres))
        .display("Dos rectas, Added Cuadrado, Nuevo Triangulo");

}

/// EJERCICIO 1 INCISO [4]
void guia5_eje1_part2() {

    CImg<bool> base(512, 512),
        rotada(base);

    base.fill(0); rotada.fill(0);

    // Dibujo la linea vertical
    base = art_draw_line(base, 256);

    // Rotamos 20º
    rotada = base.get_rotate(20.0);

    // Cropeamos ambas un rectangulo de 256x256
    base.crop(
        base.width() / 2 - 128, base.height() / 2 - 128, 
        base.width() / 2 + 128, base.height() / 2 + 128);

    rotada.crop(
        rotada.width() / 2 - 128, rotada.height() / 2 - 128, 
        rotada.width() / 2 + 128, rotada.height() / 2 + 128);

    (
        base.get_normalize(0, 255), 
        magn_tdf(base).get_normalize(0, 255), 
        rotada.get_normalize(0, 255), 
        magn_tdf(rotada).get_normalize(0, 255)
    ).display("Original cropeada y FFT, Rotada cropeada y FFT");

}

/// EJERCICIO 1 INCISO [5]
void guia5_eje1_part3(const char * filename) {

    CImg<double> base(filename);

    (base, magn_tdf(base)).display("Base con su espectro de frecuencias");
}

/// Devuelve la magnitud y la fase en dos imagenes de la CImgList del espectro de fourier
CImgList<> get_magnitude_phase(CImgList<> fourier) {

    CImgList<> retorno(fourier);

    cimg_forXY(fourier[0], x, y) {

        double magnitud = sqrt(pow(fourier[0](x, y), 2) + pow(fourier[1](x, y), 2)),
            fase = atan2(fourier[1](x, y), fourier[0](x, y)); // uso atan2, no atan, ver c++ reference

        retorno[0](x, y) = magnitud;
        retorno[1](x, y) = fase;
        
    }

    return retorno;
}

/// A partir de la imagen de magnitud y fase, las une y retorna la imagen procesada
CImg<double> get_image_from_magn_phse(CImg<double> magnitud, CImg<double> fase) {

    CImg<double> retorno(magnitud);

    complex<double> j(0, 1);

    cimg_forXY(retorno, x, y) {
        retorno(x, y) = std::real(magnitud(x, y) * exp(-j * fase(x, y)));
    }

    return retorno;
}

/// EJERCICIO 2
void guia5_eje2_part1(const char * filename) {

    CImg<double> base(filename),
        procesada(base);

    // Devuelve real [0]  e imaginaria [1]
    CImgList<> TDF_base = base.get_FFT(),
        magnitud_fase(get_magnitude_phase(TDF_base));

//    complex<double> resolucion = magnitud;// exp(-j * fase);



    (base, 
        magnitud_fase[0].log().get_normalize(0, 255), 
        magnitud_fase[1], 
        get_image_from_magn_phse(magnitud_fase[0], magnitud_fase[1])).display();

}


int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/avioncito.png", "Imagen");
    
    //const unsigned char op1_level_gray = cimg_option("-g", 33, "Max Level Gray Water");

    guia5_eje2_part1(filename);

    return 0;
}
