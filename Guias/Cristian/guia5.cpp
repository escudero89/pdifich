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

/// A partir de la magnitud y fase, obtiene la imagen en componentes complejas
CImgList<> get_fft_from_magn_phse(CImg<double> magnitud, CImg<double> fase) {
    CImgList<> real_imag(2, magnitud.width(), magnitud.height());

    complex<double> j(0, 1);

    cimg_forXY(real_imag[0], x, y) {
        complex<double> resultado = magnitud(x, y) * exp(j * fase(x, y));

        real_imag[0](x, y) = std::real(resultado);
        real_imag[1](x, y) = std::imag(resultado);
    }

    return real_imag;
}

/// Version sobrecargado de lo anterior
CImgList<>  get_fft_from_magn_phse(CImgList<> magnitud_fase) {
    return get_fft_from_magn_phse(magnitud_fase[0], magnitud_fase[1]);
}

/// A partir de la imagen de magnitud y fase, las une y retorna la imagen procesada antitransformada
CImg<double> get_image_from_magn_phse(CImg<double> magnitud, CImg<double> fase) {
    return get_fft_from_magn_phse(magnitud, fase).get_FFT(true)[0];
}

/// Version sobrecargado de lo anterior
CImg<double> get_image_from_magn_phse(CImgList<> magnitud_fase) {
    return get_image_from_magn_phse(magnitud_fase[0], magnitud_fase[1]);
}

/// EJERCICIO 2 INCISO 1
void guia5_eje2_part1(const char * filename) {

    CImg<double> 
        base(filename),
        procesada(base),
        magnitud_uno,
        fase_cero;

    // Devuelve real [0]  e imaginaria [1]
    CImgList<> TDF_base = base.get_FFT(),
        magnitud_fase(get_magnitude_phase(TDF_base));

    // Magnitud 1
    procesada.fill(1);
    magnitud_uno = get_image_from_magn_phse(procesada, magnitud_fase[1]);

    // Fase 0
    procesada.fill(0);
    fase_cero = get_image_from_magn_phse(magnitud_fase[0], procesada);

    (   
        base, 
        magnitud_fase[0].get_log().get_normalize(0, 255), 
        magnitud_fase[1],
        fase_cero.get_log(),
        magnitud_uno

    ).display("Base, Magnitud, Fase, Solo Magnitud, Solo Fase", 0);

}

/// EJERCICIO 2 INCISO 2
void guia5_eje2_part2(const char * filename, const char * oth_file) {

    CImg<double> 
        img1(filename), 
        img2(oth_file);

    // Si no son del mismo tamanho, lo hacemos al tamanho de la primera
    if (!img1.is_sameXYZ(img2)) {
        img2.resize(img1);
    }

    CImgList<> 
        img1_mag_fase(get_magnitude_phase(img1.get_FFT())),
        img2_mag_fase(get_magnitude_phase(img2.get_FFT())),
        imgs_mixed(2);

    imgs_mixed[0] = get_image_from_magn_phse(img1_mag_fase[0], img2_mag_fase[1]);
    imgs_mixed[1] = get_image_from_magn_phse(img2_mag_fase[0], img1_mag_fase[1]);

    (img1, img2, imgs_mixed).display("Original 1, 2, y mezcla [mg1/ph2] y [mg2/ph1]", 0);
}

/// EJERCICIO 3
/* Pasos segun fer:
1- definis mascara 21x21
2.0- definis m = filtro.width (21)
2.00- definis n = filtro.height (21)
2- definis P = img.width + m - 1
3- definis Q = img.height + n - 1
4- imagen.resize(p,q,-100,-100,0)
5- filtro.resize(p,q,-100,-100,0)
6- fft_i = imagen.fft
7- fft_f = filtro.fft
8- resultado = fft_i * fft_j
9- salida = resultado.ifft
10- salida_fin = resultado.crop(m/2, n/2, p - m/2, q - n/2);
11- tomas mate

por que haces todo eso?
porque se te agrandan las imagenes
como en señales, tenes que hacer zero padding
el zero padding aca significa agrandar la imagen y 
agrandar el filtro a la suma de sus tamaños, como en señales

asi te queda despues del zero padding y ANTES de transformar:
1 1 1 0 0 0 0 
1 1 1 0 0 0 0 
1 1 1 0 0 0 0
0 0 0 0 0 0 0 
0 0 0 0 0 0 0
*/

/// EJERCICIO 4
/// Obtengo la distancia al punto (x, y) desde cada puntos de una matriz
CImg<double> get_D_matriz(CImg<double> base, int x = -1, int y = -1) {

    CImg<double> D_matriz(base.width(), base.height());

    // Si no especificamos el punto (-1, -1), toma el centro de la matriz
    if (x == -1 && y == -1) {
        x = D_matriz.width() / 2;
        y = D_matriz.height() / 2;
    } 

    cimg_forXY(D_matriz, u, v) {
        D_matriz(u, v) = pow(pow(u - x, 2) + pow(v - y, 2), 0.5);
    }

    return D_matriz;
}

/// Obtengo el filtro Butterworth (orden 2 es una buena eleccion entre pasabajo y ringing)
CImgList<> get_butterworth(CImg<double> base, unsigned int cutoff_frecuency, unsigned int orden = 2) {

    CImg<double> butterworth(base.width(), base.height()),
        D_matriz(get_D_matriz(base));

    // Aplico formula de Butterworth (p173)
    cimg_forXY(butterworth, u, v) {
        double factor = pow(D_matriz(u,v) / cutoff_frecuency, 2 * orden);
        butterworth(u, v) = 1 / (1 + factor);
    }

    // Y desshifteo porque asi es la vida
    butterworth.shift(-butterworth.width()/2, -butterworth.height()/2, 0, 0, 2);

    // La parte imaginaria siempre es 0
    return (butterworth, butterworth.get_fill(0));
}


/// Obtengo un filtro (ideal), parte real y parte imaginaria (que es siempre 0 para que sea zero-phase-shift)
CImgList<> get_filter(CImg<double> base, unsigned int cutoff_frecuency) {

    // La base solo la uso para determinar el tamanho
    CImg<double> filtro(base.width(), base.height()),
        D_matriz(get_D_matriz(base));

    // Aplico formula para construir filtro ideal (p167)
    cimg_forXY(filtro, u, v) {
        filtro(u, v) = (D_matriz(u, v) <= cutoff_frecuency) ? 1 : 0;
    }

    filtro.shift(-filtro.width()/2, -filtro.height()/2, 0, 0, 2);

    return (filtro, filtro.get_fill(0));
}

/// Retorno una convolucion de una imagen con un filtro trabajando en el espectro de frec
CImg<double> get_img_from_filter(CImg<double> base, CImgList<> magnitud_filtro) {

    // Obtengo la transformada y su magnitud/fase
    CImgList<> fft = base.get_FFT();

    // Multiplico por el filtro
    cimg_forXY(fft[0], u, v) {
        complex<double> 
            part1(fft[0](u, v), fft[1](u, v)),
            part2(magnitud_filtro[0](u, v), magnitud_filtro[1](u, v)),
            resultado = part1 * part2;
        
        fft[0](u, v) = real(resultado);
        fft[1](u, v) = imag(resultado);
    }

    CImg<double> prueba = fft.get_FFT(true)[0];

    (
        base,
        magnitud_filtro[0], 
        get_magnitude_phase(base.get_FFT())[0].get_log(), 
        get_magnitude_phase(prueba.get_FFT())[0].get_log(), 
        get_magnitude_phase(fft)[1], 
        prueba
    ).display("Base, PB, Base con PB", 0);
}

void guia5_eje4_part1(
    const char * filename, 
    const unsigned int option_extra = 10.0,
    const unsigned int option_extra_2 = 2) {

    CImg<double> base(filename),
        filtro_ideal(base.width(), base.height());

    get_img_from_filter(base, get_filter(base, option_extra));

    get_img_from_filter(base, get_butterworth(base, option_extra, option_extra_2));

}


int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/avioncito.png", "Image");
    const char* oth_file = cimg_option("-a", "../../img/huang1.jpg", "Another Image");
    
    const unsigned int option_extra = cimg_option("-o", 33, "Option Extra");
    const unsigned int option_extra_2 = cimg_option("-n", 2, "Option Extra_2");

    guia5_eje4_part1(filename, option_extra, option_extra_2);

    return 0;
}
