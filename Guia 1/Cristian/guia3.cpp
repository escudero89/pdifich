#include "../../CImg-1.5.4/CImg.h"

using namespace cimg_library;

/// Primer Ejercicio
void guia3_eje1(const char *filename) {

    CImg<unsigned char> 
        img(filename), 
        img_equalized,
        hist, 
        hist_equalized;

    CImgDisplay hist_wdw, hist_equalized_wdw;

    img_equalized = img.get_equalize(256, 0, 255);

    hist = img.get_histogram(256, 0, 255);
    hist_equalized = img_equalized.get_histogram(256, 0, 255);

    hist.display_graph(hist_wdw, 3);
    hist_equalized.display_graph(hist_equalized_wdw, 3);

    (img, img_equalized).display();

}

/// Segundo Ejercicio

int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/cameraman.tif", "Imagen");

    guia3_eje1(filename);

    return 0;
}