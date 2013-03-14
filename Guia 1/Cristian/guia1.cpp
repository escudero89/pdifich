/// Como maneja memoria: http://cimg.sourceforge.net/reference/group__cimg__storage.html
/// g++ -o guia1_bin guia1.cpp -O0 -lm -lpthread -lX11

#include <CImg.h>

using namespace cimg_library;

// Eje 5 => get_resize()
// Eje 6 => get_quantize()

/// Ejercicio 1 de la Guia 1
void guia1_eje1() {
 
 	// coordenadas para la subimagen
	unsigned int 
		img_width = 64,
		x_min = 80,
		x_max = x_min + img_width,
		y_min = 30,
		y_max = y_min + img_width;

	// Pixel values are stored first along the X-axis, then the Y-axis, then the Z-axis, then the C-axis :
	CImg<unsigned char> imagen_desde_archivo("../../img/cameraman.tif");

	CImg<unsigned char> imagen_modificada(img_width, img_width, 1, 1, 0);

	// Recorremos la matriz de la imagen original
	cimg_forXY(imagen_desde_archivo, x, y) {
		if ((x >= x_min && x < x_max) && (y >= y_min && y < y_max)) {
			imagen_modificada(x - x_min, y - y_min) = imagen_desde_archivo(x, y);
		}
	}

	imagen_modificada.resize_tripleXY();

	// Mostramos imagenes
	CImgDisplay ventana(imagen_desde_archivo, "Imagen Original", 0);

	CImgDisplay ventana2(imagen_modificada, "Imagen Modificada", 0);

	// Mostramos ventana
	while (!ventana.is_closed() && !ventana2.is_closed() && !ventana2.is_keyQ() && !ventana.is_keyQ()) { }

	// Y lo guardamos (el *3 es por RGB de 8 bits)
	// Tamanho= 54 bytes (cabezera) + [(64 * 3)^2 * 3] = 110.646 bytes = 110.6 Kbytes
	imagen_modificada.save("guia1_eje1_subimagen.bmp");
}

int main(int argc, char *argv[]) {

	guia1_eje1();

	return 0;
}