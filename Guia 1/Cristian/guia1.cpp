/// g++ -o guia1_bin guia1.cpp -O0 -lm -lpthread -lX11

#include <CImg.h>
using namespace cimg_library;

// Eje 5 => get_resize()
// Eje 6 => get_quantize()

/// Ejercicio 1 de la Guia 1
void guia1_eje1() {
 
	// Pixel values are stored first along the X-axis, then the Y-axis, then the Z-axis, then the C-axis :
	CImg<unsigned char> imagen_desde_archivo("img/cameraman.tif");

	// Mostramos imagen
	CImgDisplay ventana(imagen_desde_archivo, "Imagen Original", 0);

	// Mostramos ventana
	while (!ventana.is_closed() && !ventana.is_keyQ()) { }
}

int main(int argc, char *argv[]) {

	guia1_eje1();

	return 0;
}