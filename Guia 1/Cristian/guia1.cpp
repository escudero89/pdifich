/// Como maneja memoria: http://cimg.sourceforge.net/reference/group__cimg__storage.html
/// g++ -o guia1_bin guia1.cpp -O0 -lm -lpthread -lX11

#include <CImg.h>

#include <iostream>

using namespace cimg_library;

// Eje 5 => get_resize()
// Eje 6 => get_quantize()

/// Ejercicio 1 de la Guia 1
void guia1_eje1() {
 
	// Pixel values are stored first along the X-axis, then the Y-axis, then the Z-axis, then the C-axis :
	CImg<unsigned char> imagen_desde_archivo("img/cameraman.tif");

	CImg<unsigned char> imagen_modificada(640, 480, 1, 1, 0);

	// Recorremos la matriz de la imagen original
	cimg_forXY(imagen_desde_archivo, x, y) {
		if (x > 30) {
			imagen_modificada(x, y) = imagen_desde_archivo(x, y);
		}
	}

	// Apuntamos al primero elemento de la matriz 4D que guarda datos de la imagen
	unsigned char *ptr = imagen_desde_archivo.data(1, 1, 1, 1);

	std::cout << "Hey: [" << &(imagen_desde_archivo(1, 1, 1, 1)) << "]";

	// Mostramos imagenes
	CImgDisplay ventana(imagen_desde_archivo, "Imagen Original", 0);

	CImgDisplay ventana2(imagen_modificada, "Imagen Modificada", 0);

	// Mostramos ventana
	while (!ventana.is_closed() && !ventana2.is_closed() && !ventana2.is_keyQ() && !ventana.is_keyQ()) { }
}

int main(int argc, char *argv[]) {

	guia1_eje1();

	return 0;
}