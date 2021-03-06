#include <cmath>
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
// Devuelve una imagen convolucionada con una matriz de NxN, con los valores pasados en el array
CImg<double> get_filter(
    CImg<double> base, 
    unsigned int N, 
    double array[], 
    double factor_escala = 1,
    bool acotar = false) {

    CImg <double> mascara_promediado(N, N);

    cimg_forXY(mascara_promediado, x, y) {
        mascara_promediado(x, y) = array[x + y * N];
    }

    // La convolucionamos
    base.convolve(mascara_promediado);

    // Si acotamos, evitamos que se vaya del rango 0 ~ 255
    if (acotar) {
        cimg_forXY(base, x, y) {
            if (base(x, y) > 255) {
                base(x, y) = 255;
            } else if (base(x, y) < 0) {
                base(x, y) = 0;
            }
        }
    }

    // Y retornamos aplicada el factor de escala, normalizando
    return (base * factor_escala).get_normalize(0, 255);
}

void guia3_eje3(const char * filename) {

    double array[9] = {
        0.0, 1.0, 0.0, 
        1.0, 1.0, 1.0, 
        0.0, 1.0, 0.0
    },
    array_mayor[25] = {
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0
    };

    CImg<double> base(filename),
        convolucionada(get_filter(base, 3, array, 1.0/5.0)),
        convolucionada_mas(get_filter(base, 5, array_mayor, 1.0/25.0));

    (base, convolucionada, convolucionada_mas).display("Efectos de desenfocado");
}

/// Cuarto ejercicio
// Le pasamos el tamanho NxN, el desvio (?), y el factor escala que va a afectar a la matriz
CImg<double> get_gaussian_mask(unsigned int N, double desvio, double &factor_escala) {

    CImg<double> gaussian_mask(N, N),
        matriz_covarianza(2, 2);

    const char white[] = {1};

    // Lleno sus diagonales
    matriz_covarianza(0, 0) = desvio;
    matriz_covarianza(1, 1) = desvio;

    gaussian_mask.draw_gaussian(N/2, N/2, matriz_covarianza, white);

    gaussian_mask.normalize(0, 255);

    cimg_forXY(gaussian_mask, x,  y) {
        factor_escala += gaussian_mask(x, y);
        std::cout << gaussian_mask(x,y) << " : ";
    }

    return gaussian_mask;

}

void guia3_eje4(const char * filename) {

    /// INCISO A

    double factor_escala = 0,
        array_mayor[25] = {
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0
    };

    CImg<double> base(filename),
        gaussian_mask(get_gaussian_mask(5, 10, factor_escala)),
        con_gaussian(base.get_convolve(gaussian_mask) / factor_escala),
        con_array(get_filter(base, 5, array_mayor, 1.0/25.0));

    // Comparamos los resultados con un filtro de promediado del mismo tamanho
    (base, con_gaussian, con_array).display("Original, gaussiano, promediado");

    /// INCISO B

    // Aplicamos un filtro de promediado
    CImg<double> hubble("../../img/hubble.tif");
    con_array = get_filter(hubble, 5, array_mayor, 1.0/25.0);

    (hubble, con_array, con_array.get_threshold(150)).display("Imagen con los mayores elementos");

}

/// Quinto Ejercicio
void guia3_eje5(const char * filename) {

    double PA_sumaUno_1[] = {
        0.0, -1.0, 0.0,
        -1.0, 5.0, -1.0,
        0.0, -1.0, 0.0
    }, PA_sumaUno_2[] = {
        -1.0, -1.0, -1.0,
        -1.0, 9.0, -1.0,
        -1.0, -1.0, -1.0
    }, PA_sumaUno_3[] = {
        1.0, -2.0, 1.0,
        -2.0, 5.0, -2.0,
        1.0, -2.0, 1.0
    }, PA_sumaCero_1[] = {
        0.0, -1.0, 0.0,
        -1.0, 4.0, -1.0,
        0.0, -1.0, 0.0
    }, PA_sumaCero_2[] = {
        -1.0, -1.0, -1.0,
        -1.0, 8.0, -1.0,
        -1.0, -1.0, -1.0
    }, PA_sumaCero_3[] = {
        1.0, -2.0, 1.0,
        -2.0, 4.0, -2.0,
        1.0, -2.0, 1.0
    };

    CImg<double> base(filename),
        sumUno_1(get_filter(base, 3, PA_sumaUno_1, 1, true)),
        sumUno_2(get_filter(base, 3, PA_sumaUno_2, 1, true)),
        sumUno_3(get_filter(base, 3, PA_sumaUno_3, 1, true)),

        sumCero_1(get_filter(base, 3, PA_sumaCero_1, 1, true)),
        sumCero_2(get_filter(base, 3, PA_sumaCero_2, 1, true)),
        sumCero_3(get_filter(base, 3, PA_sumaCero_3, 1, true));

    (base, sumUno_1, sumUno_2, sumUno_3).display("Suma uno");
    (base, sumCero_1, sumCero_2, sumCero_3).display("Suma cero");
}

// Le paso una imagen y el A, y retorna A f(x,y) - f_PB(x,y)
CImg<double> get_high_boost(CImg<double> base, CImg<double> base_PB, double A = 1) {

    CImg<double> img(base);

    cimg_forXY(img, x, y) {
        double diff = A * base(x, y) - base_PB(x, y);

        // Evitamos que se vaya de 0
        img(x, y) = (diff > 255) ? 255 : (diff < 0) ? 0 : diff;
    }

    return img;
}

/// Sexto Ejercicio
void guia3_eje6(const char * filename) {

    double array[9] = {
        0.0, 1.0, 0.0, 
        1.0, 1.0, 1.0, 
        0.0, 1.0, 0.0
    };

    CImg<double> base(filename),
        img, img_hb, img_hb_2v(base),
        base_PB(get_filter(base, 3, array, 1.0/5.0));

    /// INCISO A

    img = get_high_boost(base, base_PB);
  
    /// INCISO B

    double A = 2;

    img_hb = get_high_boost(base, base_PB, A);

    // Otra version
    cimg_forXY(base, x, y) {
        // (A − 1)f (x, y) + f (x, y) − PB(f (x, y))
        double diff = (A - 1) * base(x, y) + img(x, y);

        img_hb_2v(x, y) = (diff > 255) ? 255 : (diff < 0) ? 0 : diff;
    }


    (base, base_PB, img, img_hb, img_hb_2v).display("Base, Pasa Bajos, Pasa Alto y High Boosted");

}

/// A partir de una imagen, me devuelve la matriz de todos los pixeles vecindarios al pixel en (x,y)
CImg<double> get_neighborhood(CImg<double> base, 
    int pos_x, int pos_y, unsigned int N, unsigned int M) {

    CImg<double> retorno(N, M);

    double valor_retornado;

    int step_x = N / 2,
        step_y = M / 2;

    // Recorremos horizontalmente y verticalmente el vecindario
    for ( int x = pos_x - step_x ; x <= pos_x + step_x ; x++ ) {
        for ( int y = pos_y - step_y ; y <= pos_y + step_y ; y++ ) {
            // Si nos vamos de los limites asignamos color 0 (fern)
            if (x < 0 || y < 0 || x >= base.width() || y > base.height()) {
                valor_retornado = 0;
            } else {
                valor_retornado = base(x, y);
            }

            retorno(x - pos_x + step_x, y - pos_y + step_y) = valor_retornado;
        }
    }

    return retorno;
}


/// Le paso una imagen, retorna la imagen con todos los pixeles equalizados en NxM vecindarios
CImg<double> get_local_equalization(CImg<double> base, unsigned int N, unsigned int M) {

    CImg<double> resultado_equalization(base),
        neighborhood(N, M);

    // Recorro cada pixel de la imagen
    cimg_forXY(base, x, y) {

        // Por cada pixel, saco su vecindario, ecualizo, y guardo su pixel central
        neighborhood = get_neighborhood(base, x, y, N, M);
        neighborhood.equalize(256, 0, 255);

        resultado_equalization(x, y) = neighborhood(N/2, M/2);
    }

    return resultado_equalization;
}


/// Septimo Ejercicio inciso a
void guia3_eje7_a(const char * filename, unsigned int N, unsigned int M) {

    CImg<double> base(filename);

    (base, get_local_equalization(base, N, M)).display();

}

/// Te devuelve una imagen con high_boost
CImg<double> get_high_boost_from_base(
    CImg<double> base,
    unsigned int N,
    double array [],
    double factor_escala,
    double A = 1) {

    CImg<double> base_PB(get_filter(base, N, array, factor_escala));

    return get_high_boost(base, base_PB, A);

}

/// Septimo Ejercicio inciso b
void guia3_eje7_b(const char * filename) {

    double array[9] = {
        1.0, 1.0, 1.0, 
        1.0, 1.0, 1.0, 
        1.0, 1.0, 1.0
    };

    CImg<double> base(filename),
        potenciada(base), // para expandir oscuros
        hb(get_high_boost_from_base(base, 3, array, 1.0/9.0, 2));

    // Aplicamos la transformacion raiz para expandir oscuros
    cimg_forXY(potenciada, x, y) {
        potenciada(x, y) = pow(potenciada(x, y), 0.5);
    }

    potenciada.normalize(0, 255);

    (base, potenciada, hb, (potenciada + hb).get_normalize(0, 255))
        .display("Original, potenciada [gamma = 0.5], high_boost [A = 2], suma ultimas dos");

}



int main (int argc, char* argv[]) {

    const char* filename = cimg_option("-i", "../../img/cuadros.tif", "Imagen");
    const unsigned int mascara_N = cimg_option("-w", 7, "Mascara Width"),
                       mascara_M = cimg_option("-h", 7, "Mascara Height");

    guia3_eje7_a(filename, mascara_N, mascara_M);

    return 0;
}