#include <iostream>

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

/// Primer Ejercicio parte 2 (suposicion debajo)
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

/// Segundo ejercicio
void guia3_eje2_helper(const char * filename, bool nube = true) {
    // Conclusiones en base a los histogramas:
    // a: ruido gaussiano
    // b: ruido uniforme
    // c: ruido sal y pimienta

    CImg<unsigned char> img(filename);

    // Buscamos una zona homogenea de pixeles, tomamos una nube o una roca.
    unsigned int
        region_min_x = nube ? 1344 : 224, region_min_y = nube ? 13 : 494,
        region_max_x = nube ? 1653 : 337, region_max_y = nube ? 81 : 568;

    // La cropeamos
    img.crop(region_min_x, region_min_y, region_max_x, region_max_y);

    // Sacamos su varianza
    float img_mean, img_var = img.variance_mean(1, img_mean);

    std::cout << std::endl << "Filename: " << filename << std::endl;
    std::cout << "Media: " << img_mean << std::endl;
    std::cout << "Varianza: " << img_var << std::endl;
    std::cout << "Varianza estimada del ruido: " << img.variance_noise() << std::endl;

    img.get_histogram(256, 0, 255).display_graph(filename);

    //img.display();
}

void guia3_eje2() {

    guia3_eje2_helper("../../img/FAMILIA_a.jpg", false);
    guia3_eje2_helper("../../img/FAMILIA_b.jpg", false);
    guia3_eje2_helper("../../img/FAMILIA_c.jpg", false);

}

/// Tercer ejercicio
void guia3_eje3() {
    
}

int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/FAMILIA_a.jpg", "Imagen");

    guia3_eje3();

    return 0;
}