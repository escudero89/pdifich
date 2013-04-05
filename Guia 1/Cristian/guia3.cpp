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

/// Segundo Ejercicio (suposicion debajo)
// histo1.tif : Distribucion bastante pareja, mas densidad en los tonos oscuros. Probablemente sea una imagen con un buen contraste, con detalles oscuros.
    // => Suposicion: ImagenC; Real: No son tan parecidos los histogramas.
// histo2.tif : Distribucion concentrada alrededor del gris100. Mal contraste. Imagen oscura. Poco variedad de intensidad.
    // => Suposicion: ImagenA; Real: Correcto.
// histo3.tif : Aun mas concentrada que la anterior, alrededor de gris25. Mal contraste. Imagen muy oscura.
    // => Suposicion: ImagenE; Real: Correcto.
// histo4.tif : Caso inverso al anterior, con la concentracion en gris225. Imagen brillosa, con algunos detalles de ~gris80. 
    // => Suposicion: ImagenB; Real: Correcto.
// histo5.tif : Distribucion bastante distribuida. Contraste medio. Mayormente brillante.
    // => Suposicion: ImagenD; Real: Correcto.

int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/cameraman.tif", "Imagen");

    guia3_eje1(filename);

    return 0;
}