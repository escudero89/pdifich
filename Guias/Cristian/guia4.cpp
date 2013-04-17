#include <cmath>
#include <iostream>

#include "../../CImg-1.5.4/CImg.h"

using namespace cimg_library;

/// Primer Ejercicio
/// INCISO A
void guia4_eje1_a(const char *filename = "../../img/patron.tif") {

    CImg<double> base(filename),
        base_hsi(base.get_RGBtoHSI()),
        buffer(base_hsi);

    (base,
        base.get_channel(0),
        base.get_channel(1),
        base.get_channel(2),
        base_hsi.get_channel(0), 
        base_hsi.get_channel(1),
        base_hsi.get_channel(2)).display("RGB, R, G, B, H, S, I", 0);

    // Matices variando de azul a rojo
    double max_range = 240;
    // Saturacion maxima (intensidad maxima dejaria toda la imagen blanca EN TEORIA, pero cimg se lo pasa por las pelotas)
    cimg_forXY(base_hsi, x, y) {
        // Si pasamos el 1, damos vuelta
        base_hsi(x, y, 0, 0) = buffer(base.width() - x - 1, y, 0, 0);

        base_hsi(x, y, 0, 1) = 1.0; // max sat
        base_hsi(x, y, 0, 2) = 1.0; // max int
    }

    base = base_hsi.get_HSItoRGB();

    (base,
        base.get_channel(0),
        base.get_channel(1),
        base.get_channel(2),
        base_hsi.get_channel(0), 
        base_hsi.get_channel(1),
        base_hsi.get_channel(2)).display("RGB, R, G, B, H, S, I", 0);

}

/// INCISO B
void guia4_eje1_b(const char * filename = "../../img/pattern.tif") {

    CImg<double> base(filename),
        base_hsi(base.get_RGBtoHSI());

    base_hsi.get_channel(0).display();

    cimg_forXY(base_hsi, x, y) {
        // Trabajamos en el HUE (max range es 360)
        double val = 180 + base_hsi(x, y, 0, 0);

        base_hsi(x, y, 0, 0) = (val > 360) ? val - 360 : val;
    }

    base_hsi.get_channel(0).display();

    base_hsi.HSItoRGB();

    // Si no se  porque me da mas oscurito los complementarios, pero en teoria esta bien
    (base, base_hsi).display("Normal, complementaria", 0);
}

///****************************************
/// Cargar paleta
///****************************************
CImg<float> cargar_paleta(const char * filename="../../paletas/gray.pal"){

    CImg<float> paleta(1, 256, 1, 3, 0);

    FILE *fichero;
    float x0, x1, x2;

    fichero = fopen(filename, "r");

    for(int leidos, i = 1; i <= 256; i++ ) {
        leidos = fscanf(fichero, "%e\t%e\t%e\n", &x0, &x1, &x2);

        if (leidos) {
            paleta(0, i - 1, 0, 0) = x0;
            paleta(0, i - 1, 0, 1) = x1;
            paleta(0, i - 1, 0, 2) = x2;
        }
    }

    return paleta;
}

// Mapea una imagen con una paleta (paso imagen y la direccion de la paleta)
CImg<double> get_image_from_pallete(CImg<double> base, const char * filename = "../../paletas/gray.pal" ) {

    CImg<double> paleta(cargar_paleta(filename)),
        retorno(base.width(), base.height(), base.depth(), 3);

    // Normalizo la base por las dudas
    base.normalize(0, 255);

    // El retorno siempre tiene 3 canales (RGB)
    cimg_forXYC(retorno, x, y, c) {
        retorno(x, y, c) = paleta(0, base(x, y), c);
    }

    return retorno;
}

/// EJERCICIO 2
void guia4_eje2(const char * filename = "../../img/parrot.tif", bool inciso_b = false) {

    CImg<double> base(filename),
        degradado(256, 256);

    /// INCISO A
    cimg_forXY(degradado, x, y) {
        degradado(x, y) = x;
    }

    // Si estamos en el inciso B trabajamos con la base
    if (inciso_b) {
        degradado = base;
    }

    (degradado, 
        get_image_from_pallete(degradado, "../../paletas/bone.pal"),
        get_image_from_pallete(degradado, "../../paletas/cool.pal"),
        get_image_from_pallete(degradado, "../../paletas/copper.pal"),
        get_image_from_pallete(degradado, "../../paletas/gray.pal"),
        get_image_from_pallete(degradado, "../../paletas/hot.pal"),
        get_image_from_pallete(degradado, "../../paletas/hsv.pal"),
        get_image_from_pallete(degradado, "../../paletas/jet.pal"),
        get_image_from_pallete(degradado, "../../paletas/pink.pal"))
        .display("Base, paletas (bone, cool, copper, gray, hot, hsv, jet, pink)", 0);

    // INCISO C
    // Lo que haria es convertir primero la imagen a RGB, luego aplicara una transformacion
    // en el canal R de la forma de un umbral escalon: de 0 a 128 coloco 255, de 129 a 255 coloco 0
    // lo inverso lo haria en el canal B, y el canal G pondria un valor constante de 0 a todos
}

/// EJERCICIO 3
// max_gray_water: maximo nivel de gris en el agua, el minimo es 0
void guia4_eje3(const char * filename = "../../img/rio.jpg", const unsigned char max_gray_water = 33) {

    CImg<double> base(filename),
        coloreado(base.width(), base.height(), base.depth(), 3); // matriz de color

    base.get_histogram(256).display_graph("Histograma del Rio");

    unsigned char yellow[] = {255, 255, 0};

    cimg_forXY(coloreado, x, y) {
        
        for (unsigned int c = 0; c < coloreado.spectrum(); c++) {

            if (base(x, y) <= max_gray_water) {
                coloreado(x, y, c) = yellow[c];
            } else {
                coloreado(x, y, c) = base(x, y);
            }

        }
    }

    (base, coloreado).display("Base, coloreado", 0);

}

int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/rio.jpg", "Imagen");
    
    const unsigned char op1_level_gray = cimg_option("-g", 33, "Max Level Gray Water");

    guia4_eje3(filename, op1_level_gray);

    return 0;
}