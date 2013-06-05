#include <cassert>
#include <cmath>
#include <complex>
#include <ctime>
#include <iostream>
#include <cstring>

#include "../../CImg-1.5.4/CImg.h"
#include "PDI_functions.h"
#include "funciones.h"

#define EPSILON 0.00001
#define PI 3.14159265359
using namespace cimg_library;

CImg<double> paste_publicty(
	const char * filename,
	const char * file_publicity) {

	/// Parametros de la publicidad
	CImg<double> publicidad(file_publicity);

	CImg<double> tennis(filename);

	// Uso color slicing para quedarme con el marco de la cancha
	CImg<double> mask_tennis(cimg_ce::get_mask_from_RGB<double>(tennis, 230, 230, 230, 90));

	// Luego hago un gaussiano y el laplaciano, para quedarme como con los cruces por cero
	CImg<double> f_promediado(3, 3, 1, 1, 1);
	double factor_promediado = f_promediado.width() * f_promediado.height();

	mask_tennis.convolve(f_promediado);
	mask_tennis /= factor_promediado;

	CImg<double> laplaciano(cimg_ce::get_filter_from_file<double>("filtros/laplaciano1.txt"));
	
	// Le aplico el gradiente a la mascara
	CImg<double> tennis_field = mask_tennis.get_convolve(laplaciano);

	// Y umbralizo
	tennis_field.threshold(0.1);

	/// Aplico un promediado para que todo sea del color de la cancha
	CImg<double> f_promediado_2(9, 9, 1, 1, 1);
	double factor_promediado_2 = f_promediado_2.width() * f_promediado_2.height();

	// No es necesario trabajar con toda la imagen, la resizeo a la mitad (para q sea mas rapido)
	CImg<double> field(tennis.get_resize_halfXY().get_convolve(f_promediado_2) / factor_promediado_2);
	
	// Y aplico una mascara para obtener solo el color de la cancha (RGB)
	CImg<double> mask_field(
		cimg_ce::get_mask_from_RGB<double>(
			field, 
			field.get_channel(0).mean(),
			field.get_channel(1).mean(),
			field.get_channel(2).mean(),
			50));

	// Aplico otro gaussiano, y umbralizo
	mask_field.convolve(f_promediado_2);
	mask_field /= factor_promediado_2;
	mask_field.threshold(0.5);

	// Tomo un rectangulo del medio, y voy bajando hasta encontrar un 1 (empieza cancha)
	unsigned int start_field = 0;
	unsigned int middle_mask = mask_field.width() / 2;

	cimg_forY(mask_field, y) {
		if (mask_field(middle_mask, y) == 1) {
			start_field = y * 2; // hago *2 porque resizee a la mitad antes
			break;
		}
	}

	// AHORA borro desde start_field para arriba de mi tennis_field
	cimg_forX(tennis_field, x) {
		for (unsigned int y = 0; y < start_field; y++) {
			tennis_field(x, y) = 0;
		}
	}

	// DESENFOCOOO MUCHOO
	tennis_field.convolve(f_promediado);
	tennis_field /= factor_promediado;
	tennis_field.threshold(0.5);

	// Y le pongo hough a ver que sale
	CImg<double> hough_tennis(hough(tennis_field));

	hough_tennis = cimg_ce::slice_hough(hough_tennis, 0, hough_tennis.height() / 2, 3, 200);

	// Vuelvo a tener la cancha
	CImg<bool> tennis_hough(hough(hough_tennis, true));

	unsigned int high_border = 0;
	unsigned int low_border = 0;

	// Recorro verticalmente la imagen, en el medio
	unsigned int middle_hough_x = tennis_hough.width() / 2;

	// Desde arriba
	for (unsigned int y = 0; y < tennis_hough.height(); y++) {
		if (tennis_hough(middle_hough_x, y) == 1) {
			low_border = y;
			break;
		}
	}

	// Desde abajo
	for (unsigned int y = tennis_hough.height() - 1 ; y >= 0 ; y--) {
		if (tennis_hough(middle_hough_x, y) == 1) {
			high_border = y;
			break;
		}	
	}

	/// Y FINALMENTE CONSEGUI LA PUTA RELACION DE ASPECTO
	double rel_aspecto = 1.0 * (tennis_hough.height() - (high_border - low_border)) / tennis_hough.height();
	std::cout << "Relacion de aspecto:" << rel_aspecto << std::endl;

	// Y se la aplico a mi imagen de publicidad (a lo alto no mas)
	publicidad.resize(publicidad.width(), publicidad.height() * rel_aspecto);

	unsigned int publicidad_alto = publicidad.height();

	// Y la pego en la cancha, por sobre la linea de saque
	publicidad.resize(tennis.width(), tennis.height(), -100, -100, 0);

	publicidad.shift(tennis.width() / 3, high_border - publicidad_alto - 10);

	// Y le aplico la mascara para que solo se vea pegada en la cancha
	publicidad = cimg_ce::apply_mask(publicidad, mask_field.get_resize_doubleXY());

	CImg<double> final(tennis *.9 + publicidad * .1);

	(tennis, final).display();

	return final;
}


int main (int argc, char* argv[]) {

    srand(time(0));

    const char* _filename = cimg_option("-i", "training/tennis/01.jpg", "Imagen");
    const char* _file_publicity = cimg_option("-publi", "../../img/letras1.tif", "Imagen");
 
 	paste_publicty(_filename, _file_publicity);

    return 0;
}