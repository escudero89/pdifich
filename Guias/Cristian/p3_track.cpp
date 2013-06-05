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

void track_coloring(
	const char * filename,
	const double UMBRAL,
	const double A) {

	CImg<double> track(filename);

	// Aplicamos un filtro mediana varias veces
	CImg<double> track_filtrada(cimg_ce::apply_mean(track, 'm'));
	track_filtrada = cimg_ce::apply_mean(track, 'm', 0, 7, 7);
	track_filtrada = cimg_ce::apply_mean(track, 'm');
	track_filtrada = cimg_ce::apply_mean(track, 'a', 3, 7, 7);
	
	// Y luego otro geometrico para mejorar el resultado
	track_filtrada = cimg_ce::apply_mean(track_filtrada, 'g');

	// Le paso un filtro high-boost
	CImg<double> filtro_promediado(7, 7, 1, 1, 1);
	double factor_promediado = filtro_promediado.width() * filtro_promediado.height();

	// Y cambio su valor central por A
	CImg<double> track_hb(A * track_filtrada - track_filtrada.get_convolve(filtro_promediado) / factor_promediado);

	// Obtengo ahora solo la pista
	CImg<double> track_only(track_hb.get_threshold(UMBRAL));

	// Y uso hough
	CImg<double> track_hough(hough(track_only));

	// Busco donde esta su maxima colinearidad
	unsigned int max_x = 0;
	unsigned int max_y = 0;

	double max_val = track_hough.max();

	cimg_forXY(track_hough, x, y) {
		if (track_hough(x, y) == max_val) {
			max_x = x;
			max_y = y;
			break;
		}
	}

	double val_theta = cimg_ce::coord_hough_to_value(track_hough, max_x, 't');
	double val_rho = cimg_ce::coord_hough_to_value(track_hough, max_y, 'p');
	
	std::cout << "(x,y): " << max_x << " | " << max_y << std::endl;
	std::cout << "(theta, rho): " << val_theta << " | " << val_rho << std::endl;

	CImg<double> track_back(hough(cimg_ce::slice_hough(track_hough, val_theta, max_y, 1, 1), true));

	// Mostramos la imagen final
	(track_filtrada * 0.7 + track_back * 0.3).display("Final", 0);

}

int main (int argc, char* argv[]) {

    srand(time(0));

    const char* _filename = cimg_option("-i", "training/track/01.jpg", "Imagen");
    
    const double _umbral = cimg_option("-umbral", 200.0, "Umbral dps de PA");
    const double _hb = cimg_option("-hb", 2.0, "A para el filtro HB");

    track_coloring(_filename, _umbral, _hb);
   
    return 0;
}