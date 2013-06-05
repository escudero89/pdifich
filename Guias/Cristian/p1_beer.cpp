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

/// Voy a suponer que el tamanho de espuma h se considera segun la altura h + altura de la cerveza.

void get_percent_of_foam(
	const char * filename,
	const int UMBRAL,
	const double MIN_INTENSITY,
	const double MIN_FOAM_INT,
	const unsigned int X_COLS_TOL) {

	CImg<double> beer(filename);

	CImg<double> laplaciano_diag(cimg_ce::get_filter_from_file<double>("filtros/laplaciano2.txt"));

	// Le hago un pasaltos
	CImg<double> beer_pa(cimg_ce::transform_to_grayscale(beer).get_convolve(laplaciano_diag));

	// Y umbralizo
	CImg<bool> umbralizada(beer_pa.get_threshold(UMBRAL));

	// Ahora con los bordes, resizeo la imagen
	//(beer, beer_pa, umbralizada * 255).display("Display", 0);

	// Para recortar
	unsigned int x_min, x_max, y_min, y_max;

	// Me quedo solo con el vaso de cerveza
	cimg_ce::get_sliced_object<bool>(umbralizada, 1, x_min, y_min, x_max, y_max);

	// Recorto el vaso de cerveza
	CImg<double> beer_only(beer.get_crop(x_min, y_min, x_max, y_max));

	/// ACA ANALIZAMOS SI ES RUBIA O NEGRA
	bool is_black = false;

	// Lo paso a HSI
	beer_only.RGBtoHSI();

	// Y reviso ahora la intensidad que tiene predominante
	double beer_predominant_intensity = beer_only.get_channel(2).mean();

	// Ahora determino si es rubia o negra, en base a intensidad promedio
	if (beer_predominant_intensity > MIN_INTENSITY) { // es rubia
		std::cout << "Es rubia." << std::endl;
	} else { // es negra
		std::cout << "Es negra." << std::endl;
		is_black = true;
	}

	/// FIN RUBIA O NEGRA

	// Me quedo solo con una franja vertical de x cols
	int x_cols = beer_only.width() / 2;
	double y_foam = 1; 

	CImg<double> beer_col(
		beer_only.get_crop(
			x_cols - X_COLS_TOL, 
			0, 
			x_cols + X_COLS_TOL, 
			beer_only.height()).get_channel(2));

	// Cuando encuentro un salto de intensidad mientras bajo, digo que ahi esta termina la espuma
	for (unsigned int x = 0; x < (X_COLS_TOL * 2 + 1) ; x++) {
		for (unsigned int y = 0; y < beer_col.height() ; y++) {
			/// Si encuentro un valor de min, corto
			// Si es negra, usamos una tolerancia de intensidad mucho menor
			if (beer_col(x, y) * (2 * is_black + 1) < MIN_FOAM_INT) {
				std::cout << "y: " << y << "(" << beer_col(x, y) << ")" << std::endl;

				// Voy calculando la media geometrica (le sumo 1 si es cero asi no me arruina todo)
				y_foam *= (y > 0) ? y : 1;
				break;
			}

		}
	}

	// y saco el valor final de la media geometrica
	y_foam = pow(y_foam, 1.0 / (X_COLS_TOL * 2 + 1));

	std::cout << "Y_foam: " << y_foam << std::endl;
	std::cout << "Porcentaje de espuma: " << y_foam * 100.0 / beer_col.height() << "\%.\n\n";

	beer_col.display("Cervezaaa", 0);
	
}


int main (int argc, char* argv[]) {

    srand(time(0));

    const char* _filename_r = cimg_option("-i", "training/beer/01.jpg", "Imagen");
    const char* _filename_o = cimg_option("-i2", "training/beer/31.jpg", "Imagen");
    
    const int _umbral = cimg_option("-umbral", 32, "Umbral del laplaciano");

    const double _minint = cimg_option("-minint", 0.6, "Intensidad minima para detectar rubias");
    const double _minfoam = cimg_option("-minfoam", 0.55, "Intensidad minima para cortar bordes");

    const unsigned int _col_tol = cimg_option("-coltol", 1, "Cantidad de columnas a considerar (1 + x * 2)");
   
    get_percent_of_foam(_filename_r, _umbral, _minint, _minfoam, _col_tol);
    get_percent_of_foam(_filename_o, _umbral, _minint, _minfoam, _col_tol);

    return 0;
}