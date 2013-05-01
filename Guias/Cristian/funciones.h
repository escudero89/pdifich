#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

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

/// Obtengo un filtro desde un archivo de texto (se lo robe a fer :3)
template <typename T>
CImg<T> get_filter_from_file(std::string nombre) {

    std::ifstream f(nombre.c_str());

    // Si no pudo abrirlo, problema vieja
    assert(f.is_open());

    unsigned int filas, columnas;
    T valor;

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

    f.close();
    
    return salida;
}

/// END NAMESPACE
}