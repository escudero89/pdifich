/// Como maneja memoria: http://cimg.sourceforge.net/reference/group__cimg__storage.html
/// g++ -o guia1_bin guia1.cpp -O0 -lm -lpthread -lX11

#include <CImg.h>

#include <vector>

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

#define PI 3.14159265359

using namespace cimg_library;

// Trabaja con un vector de 0 a 255, y devuelve el vector con cierta transformacion
CImg<int> get_image_transformed(CImg<int> imagen, CImg<int> &grafico, float a = 1, float c = 0) {
	
	CImg<float> LUT(256, 1, 1); // de 0 a 255

	for (int i = 0; i < LUT.width(); i++) {
		float f_x = a * i + c;
		std::cout << f_x << std::endl;
		LUT(i) = (f_x < 0) ? 0 : ((f_x > 255) ? 255 : f_x);
	}

	// HAGO EL GRAFICO
	unsigned char white[3] = {255, 255, 255};
	grafico.draw_graph(LUT, white, 1, 1, 1, 255, 0);

	cimg_forXYC(imagen, x, y, v) {
		imagen(x, y, v) = LUT(imagen(x, y, v));
	}

	return imagen;
}

/// Ejercicio 1 de la Guia 2
void guia2_eje1() {

	CImg<int> imagen_desde_archivo("../../img/huang1.jpg"),
		grafico(imagen_desde_archivo.width(), imagen_desde_archivo.height()),
		imagen_modificada(get_image_transformed(imagen_desde_archivo, grafico, .25, 0));

	CImgList<int> compartido(imagen_desde_archivo, grafico, imagen_modificada);

	// Mostramos imagen
	compartido.display("Imagen original, imagen modificada por una transformacion");
}

void guia2_eje2() {

}


int main(int argc, char *argv[]) {

  guia2_eje1();

  return 0;
}