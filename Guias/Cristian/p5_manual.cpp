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

void automatically_rotate_page(
	const char * filename,
	const double UMBRAL) {

	CImg<double> page(filename);

	// Hago un gray-slicing (me quedo solo con los valores de grises (no images))
	CImg<double> mask_text(page.width(), page.height(), 1, 1, 0);

	cimg_forXY(mask_text, x, y) {
		double red = page(x, y, 0, 0);
		double TOL = 5;
		bool is_gray = true;

		for (unsigned int c = 1; c < page.spectrum() ; c++) {
			if (abs(red - page(x, y, 0, c)) > TOL) {
				is_gray = false;
			}
		}

		mask_text(x, y) = is_gray;
	}

	// Le aplico la mascara a mi pagina dejandola en blanco y negro
	CImg<double> page_bw(cimg_ce::apply_mask(cimg_ce::transform_to_grayscale(page), mask_text));

	// Y me quedo con una region central para evitar ser afectado por bordes
	page_bw.crop(page_bw.width()/5, page_bw.height()/5, page_bw.width()*4/5, page_bw.height()*4/5);
	page_bw.display();

	// Le paso un filtro pasa altos
	CImg<double> h_filtro_pa(cimg_ce::get_filter_from_file<double>("filtros/laplaciano2.txt"));
	CImg<double> page_PA(page_bw.get_convolve(h_filtro_pa).get_threshold(UMBRAL));

	// Saco la magnitud de su FFT en escala de grises (me quedo con un solo canal)
	CImg<double> page_magn(magn_tdf(page_PA).get_channel(0));

	// Y luego umbralizo
	CImg<double> page_magn_umb(page_magn.get_threshold(UMBRAL));

	// Y ahora aplicamos hough
	CImg<double> page_magn_hough(hough(page_magn_umb));

	// Y buscamos el maximo pico
	double max_theta = 0;
	double max_rho_coord = 0;

	cimg_ce::get_max_peak<double>(page_magn_hough, max_theta, max_rho_coord);

	// Ahora que se donde esta el maximo pico, se cual es su inclinacion, por lo que deberia
	// rotarlo hacia 90 o hacia 0, depende cual este mas cerca
	std::cout << max_theta << std::endl;

	// Si theta es negativo, tomo consideracion especial
	max_theta = (max_theta < 0) ? 180 + max_theta : max_theta;

	// Me va dar 0 (<45), 90 (< 135), 180 (< 225), 270 (<315), o 360
	double degree_to_go = round(max_theta / 90) * 90;

	// Y lo rotamos
	CImg<double> page_rotate(page.get_rotate(max_theta - degree_to_go));

	(page, page_PA, page_magn_umb, page_magn_hough, page_rotate).display();

}


int main (int argc, char* argv[]) {

    srand(time(0));

    const char* _filename = cimg_option("-i", "training/page/04.png", "Imagen");
    
    const double _umbral = cimg_option("-umbral", 178.0, "Umbral");

	automatically_rotate_page(_filename, _umbral);

    return 0;
}