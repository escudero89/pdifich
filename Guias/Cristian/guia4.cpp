#include <cmath>
#include <iostream>

#include "../../CImg-1.5.4/CImg.h"

using namespace cimg_library;

/// Primer Ejercicio
/// INCISO A
void guia4_eje1_a(const char *filename) {

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
void guia4_eje1_b(const char * filename) {

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

int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/patron.tif", "Imagen");

    guia4_eje1_a(filename);

    return 0;
}