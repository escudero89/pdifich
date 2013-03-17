/// Como maneja memoria: http://cimg.sourceforge.net/reference/group__cimg__storage.html
/// g++ -o guia1_bin guia1.cpp -O0 -lm -lpthread -lX11

#include <CImg.h>

#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

#define PI 3.14159265359

using namespace cimg_library;

// Eje 5 => get_resize()
// Eje 6 => get_quantize()

/// Le pasas dos puntos, obtiene el angulo entre ellos en radianes
float get_angle_from_points(float x0, float y0, float x1, float y1) {

	// Desplazo al eje 0,0, trabajando sobre un vector normal (1,0) 
	float vector_x = x1 - x0, 
		vector_y = y1 - y0,
		norm_x = 1,
		norm_y = 0,

		producto_punto = vector_x * norm_x + vector_y * norm_y,
		producto_magnitud = sqrt(pow(vector_x, 2) + pow(vector_y, 2)) 
			* sqrt(pow(norm_x, 2) + pow(norm_y, 2));

	std::cout << "x0: " << x0 << " " << y0 <<" ; x1: "<<x1<<" "<<y1 << std::endl;

	short is_negativo = (y0 <= y1) ? 1 : -1;

	return is_negativo * acos(producto_punto/producto_magnitud);
}

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
	float primer_y, primer_x, y, x;

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
				primer_y = y;
				primer_x = x;
				first_click = true;

				/// Esperamos otro punto
				imagen_modificada.display(ventana);
				ventana.wait();
			} else {
				// Dibujamos el perfil de intensidad
				val_intensidad.fill(0);

				// Rotamos la imagen para luego tomar el valor horizontal
				float angulo_a_rotar = get_angle_from_points(primer_x, primer_y, x, y),
					primer_x_r = primer_x * cos(angulo_a_rotar) + primer_y * sin(angulo_a_rotar),
					primer_y_r = primer_x * -sin(angulo_a_rotar) + primer_y * cos(angulo_a_rotar),
					x_r = x * cos(angulo_a_rotar) + y * sin(angulo_a_rotar),
					y_r = x * -sin(angulo_a_rotar) + y * cos(angulo_a_rotar);

				imagen_modificada = imagen_original;

				// La idea es rotarlo para el otro lado
				imagen_modificada = imagen_modificada.get_rotate(-angulo_a_rotar * 180 / PI);

				std::cout << "Angulo: " << angulo_a_rotar << std::endl;
				std::cout << "Y_r: " << y_r << std::endl;

				// Obtenemos una linea de la imagen
				CImg<float> subimagen(
					imagen_modificada.get_crop(
						primer_x_r,
						primer_y_r,
						x_r,
						y_r));

				imagen_modificada.draw_line(
					primer_x_r,
					primer_y_r,
					x_r,
					y_r,
					white);

				CImg<float> imagen_test(imagen_modificada);

				val_intensidad.draw_graph(subimagen, white, 1, 1, 1, 255);
				val_intensidad.display(ventana2);

				// Avisamos del exito
				imagen_modificada = imagen_original;
				imagen_modificada.draw_line(primer_x, primer_y, x, y, white);
				imagen_modificada.draw_text(2, 2, mensaje_exito.c_str(), white, gray);
				imagen_modificada.display(ventana);

				first_click = false;
				imagen_test.display();
			}
		}
    }
}

/*te tiro una
agarras el p0 y p1
le calculas la pendiente
le sacas el angulo
rotas la imagen
y haces un crop horizontal
pero el x0,y0 te cambian en la imagen rotada
tenes que rotarlos tambien
porque si vos haces img.get_rotate(30).get_crop(x0,y0,xf,yf)
te va a dar mal
tenes que hacer
img.get_rotate(30).get_crop(x0*cos(30),y0*sin(30),xf*cos(30),yf*sin(30))
*/

/// Ejercicio 4
void guia1_eje4() {
	
	CImg<unsigned char> matriz(256, 256),
		matriz_100(100, 100);

	CImg<bool> matriz_bin(100, 100);

	// Voy a recorrer la matriz y cambiar los colores por columnas
	cimg_forXY(matriz, x, y) {
		matriz(x, y) = x;

		if (x < matriz_100.width() && y < matriz_100.height()) {
			matriz_100(x, y) = x;
			// Intercala 1 y 0 por columnas
			matriz_bin(x, y) = (x % 2 == 0) ? 1 : 0;
		}
	}
	
	// Value normalization is disabled
	CImgDisplay ventana2(matriz_100, "0] Mi matriz 100x100", 0);
	// Value normalization is always performed
	CImgDisplay ventana3(matriz_100, "1] Mi matriz 100x100", 1);
	// Value normalization is performed once
	CImgDisplay ventana4(matriz_100, "2] Mi matriz 100x100", 2);
	// Value normalization depends on the pixel type of the data to display
	CImgDisplay ventana5(matriz_100, "3] Mi matriz 100x100", 3);

	CImgDisplay ventana_bin(matriz_bin, "Mi imagen binaria");

	CImgDisplay ventana(matriz, "Mi matriz 256x256");

	while (!ventana.is_closed() && !ventana.is_keyQ()) { }

}

/// Ultimo inciso, genera un circulo blanco en un cuadrado negro
void guia1_eje4_circ(bool interactivo = false, unsigned int size = 256, unsigned int radius = 50) {

	// Si pedimos al usuario informacion externa por consola
	if (interactivo) {
		std::cout << "Ingrese el tamanho N de la ventana NxN: ";
		std::cin >> size;
		std::cout << "Ingrese el radio del circulo: ";
		std::cin >> radius;
	}

	CImg<bool> circ(size, size);

	circ.fill(0);

	int middle = (int) size / 2;

	cimg_forXY(circ, x, y) {
		int x_real = x - middle,
			y_real = y - middle,
			hipot = x_real * x_real + y_real * y_real;

		if (hipot <= radius*radius) {
			circ(x, y) = 1;
		}
	}

	std::stringstream mensaje;
	mensaje << "Mi circulo [radio: " << radius <<
			"] en rectangulo [" << size << "x" << size << "].";

	CImgDisplay ventana(circ, mensaje.str().c_str());

	while (!ventana.is_closed() && !ventana.is_keyQ()) { }
}

int main(int argc, char *argv[]) {

	guia1_eje3();

	return 0;
}