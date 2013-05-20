#include <cassert>
#include <cmath>
#include <iostream>

#include "../../CImg-1.5.4/CImg.h"

using namespace cimg_library;

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


/// Retorna una imagen a la que le aplicamos un filtro de 3x3
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
/*
    unsigned int filas, columnas;

    // Los dos primeros valores del renglon determinan mi M x N (filas, columnas)
    f >> filas;
    f >> columnas;

    CImg<T> salida(columnas, filas);

    for (unsigned int i = 0; i < filas; i++) { 
        for (unsigned int j = 0; j < columnas; j++) {
            f >> valor;
            salida(j, i) = valor;
        }
    }
*/
    f.close();
    salida.display();
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

/// END NAMESPACE
}