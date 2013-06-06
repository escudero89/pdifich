#include <cassert>
#include <cmath>
#include <iostream>
#include <cstring>

#define EPSILON 0.00001
#define PI 3.14159265359

#include "../../CImg-1.5.4/CImg.h"

using namespace cimg_library;

//************************************************************************************************//
/*
/// Le paso 3 imagenes distintas (con un canal cada una), y me retorna una imagen combinada de estas    
CImg<T> join_channels(CImg<T> canal_1, CImg<T> canal_2 = CImg<T>(), CImg<T> canal_3 = CImg<T>());

/// Devuelve una imagen convolucionada con una matriz de NxN, con los valores pasados en el array
CImg<T> get_filter(
    CImg<T> base, 
    unsigned int N, 
    double array[], 
    double factor_escala = 1,
    bool acotar = false);

/// Retorna una imagen a la que le aplicamos un filtro de 3x3 definidos aqui
CImg<T> get_image_filtered(CImg<T> base, char tipo_filtro, char version_filtro = 0);

/// Le pasas una imagen y una mascara: Retorna la imagen con la mascara aplicada
CImg<T> apply_mask(CImg<T> base, CImg<bool> mascara);

/// Obtengo un filtro desde un archivo de texto 
CImg<T> get_filter_from_file(const char * nombre);

/// Aplica el logaritmo a cada pixel de una imagen
CImg<T> get_log(CImg<T> base);

/// Obtengo la distancia al punto (x, y) desde cada punto de base, o al punto ubicado
// en (x - x0, v - v0) y (x + x0, v + v0), siendo que este separado del centro (para notch-filters)
CImg<T> get_D_matriz(CImg<T> base, int x = -1, int y = -1, int x0 = 0, int y0 = 0);

/// Devuelve la magnitud y la fase en dos imagenes de la CImgList del espectro de fourier
CImgList<T> get_magnitude_phase(CImgList<T> fourier);

/// A partir de la magnitud y fase, obtiene la imagen en componentes complejas
CImgList<T> get_fft_from_magn_phse(CImg<T> magnitud, CImg<T> fase);

/// Version sobrecargado de lo anterior
CImgList<T> get_fft_from_magn_phse(CImgList<T> magnitud_fase);

/// A partir de la imagen de magnitud y fase, las une y retorna la imagen procesada antitransformada
CImg<T> get_image_from_magn_phse(CImg<T> magnitud, CImg<T> fase);

/// Version sobrecargado de lo anterior
CImg<T> get_image_from_magn_phse(CImgList<T> magnitud_fase);

/// Retorno una convolucion de una imagen con un filtro trabajando en el espectro de frec
CImg<T> get_img_from_filter(CImg<T> base, CImgList<T> filtro);

/// Me fusiona dos imagenes complejas (fusiona, NO suma, se queda con el valor mas grande)
// El ultimo parametro es para preguntar que tiene mas ponderancia (valores altos o bajos)
CImgList<T> fusion_complex_images(CImgList<T> f1, CImgList<T> f2, bool lower = false);

/// Transforma una imagen a escala de grises, con depth cantidad de canales (rgb=3, else 1)
CImg<T> transform_to_grayscale(CImg<T> imagen, bool rgb = false);

/// Obtengo un filtro (i: ideal, b: butterworth [requiere orden], g: gaussian [requiere var])
// El modificador va a ser el orden en el caso del butterworth, y la varianza en el gaussiano
CImgList<> get_filter(
    CImg<double> base, 
    unsigned int cutoff_frecuency, 
    unsigned char tipo_filtro = 'i', 
    double modificador = 2);

/// Le pasas una imagen, un centro y un radio de la esfera en el plano R, G, y B. 
 // Devuelve la mascara (el tipo me dice si es norma2 [s])
CImg<bool> get_mask_from_RGB(
    CImg<T> base, 
    T centro_R, 
    T centro_G, 
    T centro_B, 
    T radio, 
    char tipo = 's');

/// Similar al anterior, pero en un solo canal
CImg<bool> get_mask_from_channel(CImg<T> base, T value, T radio)

/// Guarda los valores de una imagen 2D en un archivo (lo deja como vector)
void image_to_text(CImg<T> image, const char * filename);

// Le pasas una imagen, retorna la imagen recortada segun el valor buscado, y las cuatro coord
// que me indican desde donde fue el corte
CImg<T> get_sliced_object(
    CImg<T> base, 
    T valor_buscado, 
    unsigned int &x_min, 
    unsigned int &y_min, 
    unsigned int &x_max, 
    unsigned int &y_max);

/// Aplico un filtro de gradiente (r: roberts, p: prewitt, s: sobel) a una imagen que le paso
CImg<T> apply_gradient(CImg<T> base, unsigned char tipo = 's');

/// Convierte cierto valor X de una imagen a Y
CImg<T> replace_value_for(CImg<T> base, T referencia, T reemplazo = 0);

///#################################################################################///

/// Aplico la media contra-armonica a una ventana que me pasan con orden Q,
// y retorno el valor del punto x,y
double apply_contraharmonic_mean(CImg<double> ventana, double Q);

/// Filtros de ordenamiento: mediana
double apply_median(CImg<double> ventana);

/// Filtro del punto medio
double apply_midpoint(CImg<double> ventana);

/// Filtro de media-alfa recortado (el d es la mitad de la formula 5.3-11 p246)
double apply_alpha_trimmed_mean(CImg<double> ventana, unsigned int d = 2);

/// Aplico el filtro de la media geometrica a una imagen base, usando una ventana S de MxN
// Tipo_filtro : g [Geometrica], c [Contra-armonica], m [mediana], p [midpoint], a [alpha-trimmed]
// el factor es el orden en el contraarmonica, y el d en el alfa recortado
CImg<double> apply_mean(
    CImg<double> base,
    unsigned char tipo_filtro = 'g',
    double factor = 0,
    int m = 3,
    int n = 3);

///#################################################################################///

/// En base a la coordenada y al eje, me retorna el valor que correspende la transformada Hough
// en grados para theta (t) entre [-90 ; 90] y entre [-sqrt(2)M;sqrt(2)M] el rho (p)
double coord_hough_to_value(CImg<T> hough, int coord, unsigned char axis);

/// Le mandamos una transformada de Hough, y recorta solo en el angulo y rho que le pedimos
// El angulo se lo pasas en grados [-90..90], y el coord_rho en posicion en pixeles en hough
// La tolerancia se mide en celdas acumuladoras de separacion (no en %).
// El just_max me indica si saca todos los puntos en el area, o solo el maximo.
CImg<T> slice_hough(
    CImg<T> Hough, 
    double angulo = -180, 
    double row_hough = -1,
    int ang_tol = 0, 
    int rho_tol = 0,
    bool just_max = false);

/// Busco la posicion de maximia colinealidad en Hough, y retorno por referencia el valor de
// tetha entre [-90, 90] y el valor en coord de posicion de rho [0, hough.height()]
// tambien retorno la transformada Hough sin ese maximo pico
CImg<T> get_max_peak(CImg<T> hough, T &theta, T &rho_coord, unsigned int difuminacion = 5);

*/
//************************************************************************************************//

/// Utilizo un propio namespace asi no conflictuo con otras funciones
namespace cimg_ce {

/// Le paso 3 imagenes distintas (con un canal cada una), y me retorna una imagen combinada de estas	
template <typename T>
CImg<T> join_channels(CImg<T> canal_1, CImg<T> canal_2 = CImg<T>(), CImg<T> canal_3 = CImg<T>()) {

	CImg<T> base(canal_1);

	if (!canal_2.is_empty()) {
		base.append(canal_2, 'c');

		if (!canal_3.is_empty()) {
			base.append(canal_3, 'c');		
		}
	}

	return base;
}

/// Devuelve una imagen convolucionada con una matriz de NxN, con los valores pasados en el array
template <typename T>
CImg<T> get_filter(
    CImg<T> base, 
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


/// Retorna una imagen a la que le aplicamos un filtro de 3x3 definidos aqui
template <typename T>
CImg<T> get_image_filtered(CImg<T> base, char tipo_filtro, char version_filtro = 0) {

	double PB_1[] = {
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0
	}, PB_2[] = {
		1.0, 2.0, 1.0,
		2.0, 4.0, 2.0,
		1.0, 2.0, 1.0
	/////////////////////
	}, PA_sumaUno_1[] = {
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
    }, elegido[9];

    // Si es un filtro de acentuado, acoto si se me va del rango
    bool acoto = (tipo_filtro == 'a') ? true : false;
	
	// Por si tenemos un filtro PA esto no influye
	double factor_escala = 1;

	// Cantidad de elementos en cada matriz
	unsigned int cant_elem = 9;
	size_t memsize = sizeof(double)* cant_elem;

	// Filtro pasa bajo (de promediado)
	if (tipo_filtro == 'b') {

		// Elegimos el array
		switch(version_filtro) {
			case 1: memcpy(elegido, PB_1, memsize); break;
			case 2: memcpy(elegido, PB_2, memsize); break;

			default: memcpy(elegido, PB_1, memsize); break;
		}

		// Obtenemos el factor de escala sumando los elementos de la matriz
		factor_escala = 0;

		for ( unsigned int k = 0; k < cant_elem; k++ ) {
			factor_escala += elegido[k];
		}

	// Filtro pasa alto (de acentuado)
	} else if (tipo_filtro == 'a') {
		// Elegimos el array
		switch(version_filtro) {
			// el 1 o el 0 en el ultimo digito es si es suma cero o uno
			case 11: memcpy(elegido, PA_sumaUno_1, memsize); break;
			case 21: memcpy(elegido, PA_sumaUno_2, memsize); break;
			case 31: memcpy(elegido, PA_sumaUno_3, memsize); break;

			case 10: memcpy(elegido, PA_sumaCero_1, memsize); break;
			case 20: memcpy(elegido, PA_sumaCero_2, memsize); break;
			case 30: memcpy(elegido, PA_sumaCero_3, memsize); break;
			
			default: memcpy(elegido, PA_sumaUno_1, memsize); break;
		}
	}

	CImg<T> retorno(get_filter(base, sqrt(cant_elem), elegido, factor_escala, acoto));

	return retorno;
}
/// Le pasas una imagen y una mascara: Retorna la imagen con la mascara aplicada
template <typename T>
CImg<T> apply_mask(CImg<T> base, CImg<bool> mascara) {

	// Si no es el mismo tamanho, tiramos error.
	assert(base.is_sameXYZ(mascara));

	cimg_forXYZC(base, x, y, z, c) {
		base(x, y, z, c) *= mascara(x, y, z);
	}

	return base;
}

/// Obtengo un filtro desde un archivo de texto (se lo robe a fer :3 y la mejore :$)
template <typename T>
CImg<T> get_filter_from_file(const char * nombre) {

    std::ifstream f(nombre);

    // Si no pudo abrirlo, problema vieja
    assert(f.is_open());

    T valor;
    unsigned int counter = 0;
    unsigned int WIDTH_MAX = 81; // un tamanho base para la longitud de la matriz (9x9)

    // Para ir guardando la matriz
    CImg<double> matrix(WIDTH_MAX);

    // Mientras vaya avanzando
    while (!f.eof()) {
        f >> valor;
        matrix(counter) = valor;
        counter++;

        // Si superamos el tamanho, resizeamos al doble y seguimos agregando
        if (counter > WIDTH_MAX) {
            WIDTH_MAX *= 2;
            matrix.resize(WIDTH_MAX, -100, -100, -100, 0); // sin interpolacion
        }
    }

    // Una vez termino, considero la matriz de filtro como cuadrada (MxM)
    unsigned int M = sqrt(counter);

    CImg<double> salida(M, M);

    // Voy cortando trozos y los agrego a la salida
    for (unsigned int i = 0 ; i < M ; i++) {
        for (unsigned int j = 0; j < M ; j++) {
            salida(i, j) = matrix(j + i * M);
        }
    }

    f.close();
    //salida.display("from_file", 0);
    return salida;
}

/// Aplica el logaritmo a cada pixel de una imagen (otra robada mas yeeiy :D)
template<typename T>
CImg<T> get_log(CImg<T> base) {

    CImg<T> log_base(base.width(), base.height());

    cimg_forXY(base, x, y) {
        log_base(x, y) = (base(x, y) < 1.0) ? 0.0 : log(base(x, y));
    }

    return log_base;
}

/// Obtengo la distancia al punto (x, y) desde cada punto de base, o al punto ubicado
// en (x - x0, v - v0) y (x + x0, v + v0), siendo que este separado del centro (para notch-filters)
template<typename T>
CImg<T> get_D_matriz(CImg<T> base, int x = -1, int y = -1, int x0 = 0, int y0 = 0) {

    CImg<T> D_matriz(base.width(), base.height());

    // Si no especificamos el punto (-1, -1), toma el centro de la matriz
    if (x == -1 && y == -1) {
        x = D_matriz.width() / 2;
        y = D_matriz.height() / 2;
    } 

    cimg_forXY(D_matriz, u, v) {
        D_matriz(u, v) = pow(pow(u - x + x0, 2) + pow(v - y + y0, 2), 0.5);
    }

    return D_matriz;
}

///#################################################################################//
/// Devuelve la magnitud y la fase en dos imagenes de la CImgList del espectro de fourier
template<typename T>
CImgList<T> get_magnitude_phase(CImgList<T> fourier) {

    CImgList<T> retorno(fourier);

    cimg_forXY(fourier[0], x, y) {

        T magnitud = sqrt(pow(fourier[0](x, y), 2) + pow(fourier[1](x, y), 2));
        T fase = atan2(fourier[1](x, y), fourier[0](x, y)); // uso atan2, no atan, ver c++ reference

        retorno[0](x, y) = magnitud;
        retorno[1](x, y) = fase;

    }

    return retorno;
}

/// A partir de la magnitud y fase, obtiene la imagen en componentes complejas
template<typename T>
CImgList<T> get_fft_from_magn_phse(CImg<T> magnitud, CImg<T> fase) {
    CImgList<T> real_imag(2, magnitud.width(), magnitud.height());

    complex<T> j(0, 1);

    cimg_forXY(real_imag[0], x, y) {
        complex<T> resultado = magnitud(x, y) * exp(j * fase(x, y));

        real_imag[0](x, y) = std::real(resultado);
        real_imag[1](x, y) = std::imag(resultado);
    }

    return real_imag;
}

/// Version sobrecargado de lo anterior
template<typename T>
CImgList<T> get_fft_from_magn_phse(CImgList<T> magnitud_fase) {
    return get_fft_from_magn_phse(magnitud_fase[0], magnitud_fase[1]);
}

/// A partir de la imagen de magnitud y fase, las une y retorna la imagen procesada antitransformada
template<typename T>
CImg<T> get_image_from_magn_phse(CImg<T> magnitud, CImg<T> fase) {
    return get_fft_from_magn_phse(magnitud, fase).get_FFT(true)[0];
}

/// Version sobrecargado de lo anterior
template<typename T>
CImg<T> get_image_from_magn_phse(CImgList<T> magnitud_fase) {
    return get_image_from_magn_phse(magnitud_fase[0], magnitud_fase[1]);
}
///#################################################################################//

/// Retorno una convolucion de una imagen con un filtro trabajando en el espectro de frec
template<typename T>
CImg<T> get_img_from_filter(CImg<T> base, CImgList<T> filtro) {

    // Obtengo la transformada y su magnitud/fase
    CImgList<T> fft = base.get_FFT();

    // Multiplico por el filtro
    cimg_forXY(fft[0], u, v) {
        complex<T> 
            part1(fft[0](u, v), fft[1](u, v)),
            part2(filtro[0](u, v), filtro[1](u, v)),
            resultado = part1 * part2;
        
        fft[0](u, v) = real(resultado);
        fft[1](u, v) = imag(resultado);
    }

    CImg<T> resultado = fft.get_FFT(true)[0];

    (
        base,
        filtro[0], 
        get_magnitude_phase<double>(base.get_FFT())[0].get_log(), 
        get_magnitude_phase<double>(resultado.get_FFT())[0].get_log(),
        resultado
    ).display("Base, PB, magnitud base, magnitud resultado, Base con PB");

    return resultado;
}

/// Me fusiona dos imagenes complejas (fusiona, NO suma, se queda con el valor mas grande)
// El ultimo parametro es para preguntar que tiene mas ponderancia (valores altos o bajos)
template<typename T> 
CImgList<T> fusion_complex_images(CImgList<T> f1, CImgList<T> f2, bool lower = false) {
    // Siempre que sean del mismo tamanho
    assert(f1[0].is_sameXYZ(f2[0]));

    CImgList<T> retorno(f1);

    cimg_forXYZ(f1[0], u, v, z) {
        // Nos quedamos con el mas grande de ambos
        if (!lower) {
            retorno[0](u, v, z) = (f1[0](u, v, z) > f2[0](u, v, z)) ? f1[0](u, v, z) : f2[0](u, v, z);
            retorno[1](u, v, z) = (f1[1](u, v, z) > f2[1](u, v, z)) ? f1[1](u, v, z) : f2[1](u, v, z);
        // con el mas bajo
        } else {
            retorno[0](u, v, z) = (f1[0](u, v, z) < f2[0](u, v, z)) ? f1[0](u, v, z) : f2[0](u, v, z);
            retorno[1](u, v, z) = (f1[1](u, v, z) < f2[1](u, v, z)) ? f1[1](u, v, z) : f2[1](u, v, z);
        }
    }

    return retorno;
}

/// Transforma una imagen a escala de grises, con depth cantidad de canales (rgb=3, else 1)
template<typename T>
CImg<T> transform_to_grayscale(CImg<T> imagen, bool rgb = false) {
    
    unsigned int spectrum = imagen.spectrum();

    // Si ya tiene un solo canal, no tiene sentido procesarla
    if (spectrum > 1) {

        // Si no es rgb, solo trabajo con un canal
        if (!rgb) {
            spectrum = 1;
        }

        // La transformamos en escala de grises
        cimg_forXY(imagen, x, y) {
            // Sumo los valores de los canales y lo promedio
            unsigned int promedio = 0;

            cimg_forC(imagen, c) {
                promedio += imagen(x, y, c);
            }

            promedio /= imagen.spectrum();

            for (int v = 0 ; v < spectrum ; v++) {
                imagen(x, y, v) = promedio;
            }
        }

        // Nuevamente, si no es rgb, me quedo con un unico canal
        if (!rgb) {
            imagen = imagen.get_channel(0);
        }
        
    }

    return imagen;
}

///#################################################################################//

/// Obtengo un filtro (i: ideal, b: butterworth [requiere orden], g: gaussian [requiere var])
// El modificador va a ser el orden en el caso del butterworth, y la varianza en el gaussiano
CImgList<> get_filter(
    CImg<double> base, 
    unsigned int cutoff_frecuency, 
    unsigned char tipo_filtro = 'i', 
    double modificador = 2) {

    CImg<double> H(base.width(), base.height()),
        D_matriz(get_D_matriz(base));

    cimg_forXY(H, u, v) {

        double resultante;

        // ideal
        if (tipo_filtro == 'i') {
            resultante = (D_matriz(u, v) <= cutoff_frecuency) ? 1 : 0;
        } else
        // butterworth
        if (tipo_filtro == 'b') {
            double factor = pow(D_matriz(u,v) / cutoff_frecuency, 2 * modificador);
            resultante = 1 / (1 + factor);
        } else
        // gaussian
        if (tipo_filtro == 'g') {
            // e^(-D(u,v)^2 / (2 varianza^2))
            resultante = exp(-pow(D_matriz(u, v), 2) / (2 * pow(modificador, 2)));
        } else {
            // Else error
            std::cout << "No se especifico el tipo de filtro en cimg_ce::get_filter.\n";
            assert(0);
        }

        H(u, v) = resultante;
    }

    // Y desshifteo porque asi es la vida
    H.shift(-H.width()/2, -H.height()/2, 0, 0, 2);

    // La parte imaginaria siempre es 0
    return (H, H.get_fill(0));
}

/// Le pasas una imagen, un centro y un radio de la esfera en el plano R, G, y B (color slicing)
 // Devuelve la mascara (el tipo me dice si es RGB o un solo canal)
template<typename T>
CImg<bool> get_mask_from_RGB(
    CImg<T> base, 
    T centro_R, 
    T centro_G, 
    T centro_B, 
    T radio, 
    bool only_one_channel = false) {

    CImg<bool> mascara(base.width(), base.height(), 1, 1, 0);

    // Recorro cada pixel
    cimg_forXYZ(base, x, y, z) {

        T distancia;

        /// Si no tiene un solo canal
        if (!only_one_channel) {
            // Saco las distancias de cada pixel por canal (z_r - a_r)
            T c_r = pow(base(x, y, z, 0) - centro_R, 2.0);
            T c_g = pow(base(x, y, z, 1) - centro_G, 2.0);
            T c_b = pow(base(x, y, z, 2) - centro_B, 2.0);

            // Mido la distancia a cada centro (pag 333)
            distancia = pow(c_r + c_g + c_b, 0.5);

        } else {
            // Uso solo un canal para determinarlo (no es por radio)
            distancia = base(x, y, z) - centro_R;
        }

        // Esto quiere decir que esta dentro de la esfera (la mascara es 1)
        if (distancia < radio) {
            mascara(x, y, z) = 1;
        }

    }

    return mascara;
}

/// Similar al anterior, pero en un solo canal
template<typename T>
CImg<bool> get_mask_from_channel(CImg<T> base, T value, T radio) {
    return get_mask_from_RGB<T>(base, value, 0, 0, radio, true);
}

/// Guarda los valores de una imagen 2D en un archivo (lo deja como vector)
template<typename T>
void image_to_text(CImg<T> image, const char * filename) {

    unsigned int MAX_ELEMENTS = image.width() * image.height() * image.spectrum();
    unsigned int kContador = 0;

    ofstream f(filename);
    assert(f.is_open());

    cimg_forXYC(image, x, y, c) {

        f << image(x, y, c);

        // Le agregamos comas a todos menos al ultimo elemento
        if (kContador < MAX_ELEMENTS - 1) {
             f << " ";
             kContador++;
        }

    }


    f.close();

}

/// Restaura los valores de un vector 1D desde un archivo
template<typename T>
CImg<T> image_to_text(const char * filename) {

    CImg<T> retorno;

    ifstream f(filename);
    assert(f.is_open());

    T valor;

    while (f >> valor) {
        retorno.resize(retorno.width() + 1, -100, -100, -100, 0);
        retorno(retorno.width() - 1) = valor;
    }

    f.close();

    return retorno;
}

/// Le paso una imagen, una mascara, y un valor, la idea es retornar el (x, y) de los bordes de 
// el objeto que tenga ese valor en la imagen, y la imagen recortada en base a la mascara

// Le pasas una imagen, retorna la imagen recortada segun el valor buscado, y las cuatro coord
// que me indican desde donde fue el corte
template<typename T>
CImg<T> get_sliced_object(
    CImg<T> base, 
    T valor_buscado, 
    unsigned int &x_min, 
    unsigned int &y_min, 
    unsigned int &x_max, 
    unsigned int &y_max) {

    // Estos me van a encerrar a mi imagen
    x_min = base.width();
    y_min = base.height();
    x_max = 0;
    y_max = 0;

    cimg_forXY(base, x, y) {
        if (base(x, y) == valor_buscado) {
            if (x > x_max) {
                x_max = x;
            } 
            if (x < x_min) {
                x_min = x;
            }

            if (y > y_max) {
                y_max = y;
            } 
            if (y < y_min) {
                y_min = y;
            }
        }
    }

    base.crop(x_min, y_min, x_max, y_max);

    return base;
}

/// Aplico un filtro de gradiente (r: roberts, p: prewitt, s: sobel) a una imagen que le paso
template <typename T>
CImg<T> apply_gradient(CImg<T> base, unsigned char tipo = 's') {

    std::string filter_name("filtros/");

    if (tipo == 'r') {
        filter_name += "roberts_";

    } else if (tipo == 'p') {
        filter_name += "prewitt_";

    } else {
        filter_name += "sobel_";
    }

    CImg<double> filtro_gx(get_filter_from_file<double>((filter_name + "gx.txt").c_str()));
    CImg<double> filtro_gy(get_filter_from_file<double>((filter_name + "gy.txt").c_str()));

    CImg<T> retorno(base.get_convolve(filtro_gx).abs() + base.get_convolve(filtro_gy).abs());

    return retorno;
}

/// Convierte cierto valor X de una imagen a Y
template <typename T>
CImg<T> replace_value_for(CImg<T> base, T referencia, T reemplazo = 0) {

    for (unsigned int x = 0 ; x < base.width() ; x++) {
        for (unsigned int y = 0 ; y < base.height() ; y++) {
            if (base(x, y) == referencia) {
                base(x, y) = reemplazo;
            }
        }
    }

    return base;
}

///#################################################################################///
/// FILTROS DE MEDIA Y ORDENAMIENTO ///
///#################################################################################///

/// ESTOS SON SOLO VENTANAS
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

/// Aplico la media contra-armonica a una ventana que me pasan con orden Q,
// y retorno el valor del punto x,y
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

    double retorno = coeff * sumatoria;

    // Si el valor del factor es 0 o menor, retorno el pixel original sin procesar
    if (factor <= 0) {
        retorno = ventana(m / 2, n / 2);
    }

    return retorno;
}

/// Aplico el filtro de la media geometrica a una imagen base, usando una ventana S de MxN
// Tipo_filtro : g [Geometrica], c [Contra-armonica], m [mediana], p [midpoint], a [alpha-trimmed]
// el factor es el orden en el contraarmonica, y el d en el alfa recortado
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

///#################################################################################///

/// En base a la coordenada y al eje, me retorna el valor que correspende la transformada Hough
// en grados para theta (t) entre [-90 ; 90] y entre [-sqrt(2)M;sqrt(2)M] el rho (p)
template <typename T>
double coord_hough_to_value(CImg<T> hough, int coord, unsigned char axis) {

    unsigned int M = hough.width();
    unsigned int N = hough.height();

    // Maximos valores absolutos de theta y de rho
    double max_theta = 90;
    double max_rho = pow(pow(M, 2.0) + pow(N, 2.0), 0.5); // si M = N, max_rho = sqrt(2) * M

    // Y le resto para ir al rango normal [-1.0 ~ 1.0]
    double valor;

    if (axis == 't') { // theta
        valor = (2.0 * coord / M - 1.0) * max_theta;
    } else if (axis == 'p') { //rho
        valor = (2.0 * coord / N - 1.0) * max_rho;
    } else {
        assert(axis && 0); // aviso del error
    }

    return valor;
}

/// Le mandamos una transformada de Hough, y recorta solo en el angulo y rho que le pedimos
// El angulo se lo pasas en grados [-90..90], y el coord_rho en posicion en pixeles en hough
// La tolerancia se mide en celdas acumuladoras de separacion (no en %).
// El just_max me indica si saca todos los puntos en el area, o solo el maximo.
template <typename T>
CImg<T> slice_hough(
    CImg<T> Hough, 
    double angulo = -180, 
    double row_hough = -1,
    int ang_tol = 0, 
    int rho_tol = 0,
    bool just_max = false) {

    // Si le pasamos -180 (por defecto), me devuelve toda la columna (sin importar ang_tol)
    if (angulo == -180) {
        angulo = 0;
        ang_tol = Hough.width() / 2;
    }

    // Obtenemos la columna (le sumo 90 para hacer el rango [0..180])
    double col_hough = (angulo + 90) / 180 * Hough.width(); 

    // Si le paso row_hough -1 (por defecto), me trabaja toda la fila (sin importar rho_tol)
    if (row_hough == -1) {
        row_hough = Hough.height() / 2;
        rho_tol = Hough.height() / 2;
    }

    // Guardo el maximo pico
    double max_pico = 0;
    double x_max_pico = 0;
    double y_max_pico = 0;

    CImg<double> auxiliar(Hough.width(), Hough.height(), 1, 1, 0);

    for (int i = -ang_tol ; i <= ang_tol ; i++) {
        for (int j = -rho_tol ; j <= rho_tol ; j++) {
            // Evitamos que se nos salga de los limites
            if (col_hough + i < Hough.width() && col_hough + i >= 0 &&
                row_hough + j < Hough.height()&& row_hough + j >= 0) {

                x_max_pico = col_hough + i;
                y_max_pico = row_hough + j;

                // Si solo es el max, sacamos el max, sino todos
                if (just_max) {
                    if (Hough(col_hough + i, row_hough + j) > max_pico) {
                        max_pico = Hough(x_max_pico, y_max_pico);
                    }
                } else {
                    // si es menor o igual a 0, no tiene sentido guardarlo
                    if (Hough(x_max_pico, y_max_pico) > 0) {
                        auxiliar(x_max_pico, y_max_pico) = Hough(x_max_pico, y_max_pico);
                        std::cout << auxiliar(x_max_pico, y_max_pico) << "(" << x_max_pico << "," << y_max_pico << ")"<< std::endl;
                    }
                }
            }
        }
    }

    if (just_max) {
        auxiliar(x_max_pico, y_max_pico) = Hough(x_max_pico, y_max_pico);
    } else { // Aplico un umbral asi no me devuelve  todooo
        auxiliar.threshold(0.3 * auxiliar.mean() + 0.7 * auxiliar.max());
    }

    return auxiliar;
}

/// Busco la posicion de maximia colinealidad en Hough, y retorno por referencia el valor de
// tetha entre [-90, 90] y el valor en coord de posicion de rho [0, hough.height()]
// tambien retorno la transformada Hough sin ese maximo pico
template<typename T>
CImg<T> get_max_peak(CImg<T> hough, T &theta, T &rho_coord, unsigned int difuminacion = 5) {

    unsigned int max_x = 0;
    unsigned int max_y = 0;

    double max_val = hough.max();

    bool go_loop = true;

    for (unsigned int x = 0; x < hough.width() && go_loop; x++) {
        for (unsigned int y = 0; y < hough.height() && go_loop; y++) {
            if (fabs(hough(x, y) - max_val) < EPSILON) {
                max_x = x;
                max_y = y;
                go_loop = false;
            }
        }
    }

    // Guardo los valores
    theta = coord_hough_to_value<T>(hough, max_x, 't');
    rho_coord = max_y;

    //  Dibujo un circulo negro (0's) de radio difuminacion en hough
    unsigned char color[] = {0};

    hough.draw_circle(int(max_x), int(max_y), difuminacion, color);

    return hough;
}

/// END NAMESPACE
}
