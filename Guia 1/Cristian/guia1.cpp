/// Como maneja memoria: http://cimg.sourceforge.net/reference/group__cimg__storage.html
/// g++ -o guia1_bin guia1.cpp -O0 -lm -lpthread -lX11

#include <CImg.h>

#include <string>
#include <sstream>

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
	imagen_modificada.save("resultados/guia1_eje1_subimagen.bmp");

}

/// Ejercicio 2
void guia1_eje2() {

	CImg<unsigned char> imagen_desde_archivo("../../img/orion.jpg");
	CImg<unsigned char> imagen_desde_archivo2("../../img/lenna.gif");

	// Me tira informacion varia, no se bien que hace stats porque no me anda :_
	imagen_desde_archivo.print();
	
	// Anexamos las imagenes
	CImgList<unsigned char> compartido(imagen_desde_archivo, imagen_desde_archivo2);

	CImgDisplay ventana(compartido, "Imagenes Compartidas", 0);

	while (!ventana.is_closed() && !ventana.is_keyQ()) { }

}

/// Ejercicio 3
void guia1_eje3() {

	CImg<float> imagen_modificada("../../img/lenna.gif"),
		val_intensidad(500, 400, 1, 3, 0);

	// La transformamos en escala de grises
	cimg_forXY(imagen_modificada, x, y) {
		// Sumo los valores de los 3 canales y lo promedio
		unsigned int promedio = (imagen_modificada(x,y,0) 
			+ imagen_modificada(x,y,1)
			+ imagen_modificada(x,y,2)) / 3;

		for (int v = 0; v<imagen_modificada.spectrum(); v++) {
			imagen_modificada(x, y, v) = promedio;
		}
	}

	// Guardamos la imagen original para evitar ser sobreescrita por texto
	CImg<float> imagen_original(imagen_modificada);

	const unsigned char white[] = { 255,255,255 }, gray[] = { 100,100,100 };

	CImgDisplay ventana(imagen_modificada, "Imagen de intensidad (modificada)");
	CImgDisplay ventana2(val_intensidad, "Grafico de intensidad");

	// Inicializamos algunas variables fuera del while
	bool first_click = false;
	int primer_mouse_y, primer_mouse_x, y, x;

	while (!ventana.is_closed() && !ventana.is_keyQ() && !ventana2.is_keyQ()) { 
		// Wait for any user event occuring on the current display
		ventana.wait();
		y = ventana.mouse_y();
		x = ventana.mouse_x();
		
		if (ventana.button() && ventana.mouse_y()>=0) {
			std::stringstream ss;
			ss << imagen_modificada(x, y);

			std::string mensaje = "Intensidad: " + ss.str(),
						mensaje_esperar = "Se espera por otro click.",
						mensaje_exito = "Se ha generado un perfil con ese segmento.";
			
			imagen_modificada.clear();
			imagen_modificada = imagen_original;
			imagen_modificada.draw_text(2,2,mensaje.c_str(), white, gray);
			imagen_modificada.display(ventana);

			if (!first_click) {
				// Avisamos que falta otro click
				imagen_modificada.draw_text(2, 20, mensaje_esperar.c_str(), white, gray);
				
				// Establecemos algunas variables antiguas
				primer_mouse_y = y;
				primer_mouse_x = x;
				first_click = true;

				/// Esperamos otro punto
				imagen_modificada.display(ventana);
				ventana.wait();
			} else {
				// Dibujamos el perfil de intensidad
				val_intensidad.fill(0);

				// Obtenemos una linea de la imagen
				CImg<float> subimagen(
					imagen_original.get_crop(
						primer_mouse_x, primer_mouse_y, 0,0,
						x, y, 0, 0));

				val_intensidad.draw_graph(subimagen, white, 1, 1, 1, 255);
				val_intensidad.display(ventana2);

				// Avisamos del exito
				imagen_modificada = imagen_original;
				imagen_modificada.draw_line(primer_mouse_x, primer_mouse_y, x, y, white);
				imagen_modificada.draw_text(2, 2, mensaje_exito.c_str(), white, gray);
				imagen_modificada.display(ventana);

				first_click = false;
			}
		}
    }
}

int main(int argc, char *argv[]) {

	guia1_eje3();

	return 0;
}