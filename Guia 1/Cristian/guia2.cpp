/// Como maneja memoria: http://cimg.sourceforge.net/reference/group__cimg__storage.html
/// g++ -o guia1_bin guia1.cpp -O0 -lm -lpthread -lX11

#include <CImg.h>

#include <vector>

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

#define PI 3.14159265359

using namespace cimg_library;

/// Interpolacion de Lagrange, retorna una imagen de Nx1 con los valores de f(x) entre p0 y p3
CImg<int> get_lagrange_interpolation(short p0[2], short p1[2], short p2[2], short p3[2]) {

	CImg<int> f_x(p3[0] - p0[0], 1);

	unsigned int nro_puntos = 3;

	float x0 = p0[0], x1 = p1[0], x2 = p2[0], x3 = p3[0],
		y0 = p0[1], y1 = p1[1], y2 = p2[1], y3 = p3[1];

	// Recorro el desde el x_min al x_max
	cimg_forXYC(f_x, x, y, v) {
		float f_x_cal,
			l0 = ((x - x1) * (x - x2) * (x - x3)) / ((x0 - x1) * (x0 - x2) * (x0 - x3)),
			l1 = ((x - x0) * (x - x2) * (x - x3)) / ((x1 - x0) * (x1 - x2) * (x1 - x3)),
			l2 = ((x - x0) * (x - x1) * (x - x3)) / ((x2 - x0) * (x2 - x1) * (x2 - x3)),
			l3 = ((x - x0) * (x - x1) * (x - x2)) / ((x3 - x0) * (x3 - x1) * (x3 - x2));

		// Interpolacion de Lagrange
		f_x_cal = l0 * y0 + l1 * y1 + l2 * y2 + l3 * y3;

		f_x_cal = (f_x_cal > 255) ? 255 : (f_x_cal < 0) ? 0 : f_x_cal;

		f_x(x, y, v) = f_x_cal;
	}

	return f_x;

}

// Trabaja con un vector de 0 a 255, y devuelve el vector con cierta transformacion
CImg<int> get_image_transformed(CImg<int> imagen, 
								CImg<int> &grafico, 
								char tipo = ' ', 
								float a = 1, float c = 0) {
	
	CImg<float> LUT(256, 1, 1); // de 0 a 255

	for (int i = 0; i < LUT.width(); i++) {
		float f_x;

		if (tipo == 'l') { // logaritmica
			f_x = log(1 + i);
		} else if (tipo == 'p') {// potencia
			f_x = pow(i, a);
		} else { // lineal
			f_x = a * i + c;
		}

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

/// Le paso una imagen y un LUT_function y mapea los valores de uno a otro
CImg<unsigned char> get_image_from_LUT(CImg<unsigned char> base, CImg<float> LUT_function) {

	cimg_forXYC(base, x, y, v) {
		base(x, y, v) = LUT_function(base(x, y, v));
	}

	return base;
}

// Maneja un LUT variable aplicado a la imagen que le paso por parametro
/// Eje1, inciso 5
CImg<int> get_image_by_LUT(CImg<unsigned char> imagen) {

	// Creo el LUT de 256x256
	CImg<bool> LUT(256, 256), old_LUT(LUT);
	CImg<float> LUT_function(256, 1, 1);

	// Muestro mi imagen, y en otra ventana el LUT
	CImgDisplay ventana(LUT, "Perfil del LUT"),
		ventana_muestra(imagen, "Imagen modificada");
		
	// Puntos para la interpolacion
	short	p0[2] = {0, 0}, 
			p1[2], 
			p2[2], 
			p3[2] = {256, 256};
	
	unsigned char white[3] = {1, 1, 1};

	bool first_click = false;

	while (!ventana.is_closed() && !ventana.is_keyQ()) { 
		// Dibujo la identidad
		for (int i = 0; i < LUT.width(); i++) {
			LUT_function(i) = i;
		}

		// resizeo LUT_function
		LUT_function.resize(256, 1);

		LUT.draw_graph(LUT_function, white, 1, 1, 1, 255, 0);

		// Hora de capturar clicks!
		// Wait for any user event occuring on the current display
		ventana.wait();
		
		short y = ventana.mouse_y(),
			x = ventana.mouse_x();

		if (ventana.button() && ventana.mouse_y()>=0) {
			LUT.draw_point(x, y, white);

			if (!first_click) {
				first_click = true;

				// Y actualizo el punto
				p1[0] = x;
				p1[1] = 255 - y; // para invertir el eje y

			} else {
				first_click = false;

				// Y actualizo el punto
				p2[0] = x;
				p2[1] = 255 - y;

				// Reviso que p1 sea menor a p2
				if (p1[0] > p2[0]) {
					p0[0] = p1[0]; p0[1] = p1[1]; // lo uso como temporal

					p1[0] = p2[0]; p1[1] = p2[1];
					p2[0] = p0[0]; p2[1] = p0[1];
					p0[0] = 0; p0[1] = 0;
				}

				// Interpolacion llamando!!!!!!!!
				LUT_function = get_lagrange_interpolation(p0, p1, p2, p3);

				LUT.draw_graph(LUT_function, white);
			}

			LUT.display(ventana);

			if (!first_click) {
				get_image_from_LUT(imagen, LUT_function).display(ventana_muestra);
			}
		}

		// Y limpio
		if (!first_click) {
			LUT = old_LUT;
		}
	}

}

/// Ejercicio 1 de la Guia 2
void guia2_eje1() {

	CImg<int> imagen_desde_archivo("../../img/huang1.jpg"),
		grafico(imagen_desde_archivo.width(), imagen_desde_archivo.height()),
		imagen_modificada(get_image_transformed(imagen_desde_archivo, grafico, ' ', -1, 255));

	CImgList<int> compartido(imagen_desde_archivo, grafico, imagen_modificada);

	// Mostramos imagen
	compartido.display("Imagen original, imagen invertida por una transformacion");

	get_image_by_LUT(imagen_desde_archivo);
}

void guia2_eje2() {

	CImg<int> imagen_desde_archivo("../../img/rmn.jpg"),
		
		grafico_log(imagen_desde_archivo.width(), imagen_desde_archivo.height()),
		grafico_pot(grafico_log),

		imagen_log(get_image_transformed(imagen_desde_archivo, grafico_log, 'l')),
		imagen_pot(get_image_transformed(imagen_desde_archivo, grafico_pot, 'p', .8));

	CImgList<int> compartido(
		imagen_desde_archivo, 
		grafico_log, imagen_log,
		grafico_pot, imagen_pot);

	// Mostramos imagen
	compartido.display("Imagen original, imagen modificada por transformaciones");

}

// Implementa operaciones aritmeticas en dos imagenes pasada por parametros, retorna la imagen final
CImg<unsigned char> get_image_from_operations(
						CImg<unsigned char> A, 
						CImg<unsigned char> B, 
						char ope='s') {

	std::cout << A.width() << " " << B.width() << " | " << A.height() << " " << B.height() << std::endl;
	// Si son distintos tamanios, explota
	assert(A.is_sameXY(B)); // thanks @fer

	CImg<unsigned char> salida(A.width(), A.height());

	cimg_forXYC(A, x, y, v) {
		int resultado;

		if (ope == 's') { // suma
			resultado = (A(x, y, v) + B(x, y, v))/2;
		} else if (ope == 'r') { // resta o diferencia
			resultado = (A(x, y, v) - B(x, y, v) + 255)/2;
		} else if (ope == 'm') { // multiplicacion
			// La idea es que sea binaria la imagen A para que sirva de mascara		
			if (A(x, y, v) == 0) { // si es 0, funciona como mascara
				resultado = 0;
			} else {
				resultado = B(x, y, v);
			}
		} else if (ope == 'd') { // division
			if (A(x, y, v) == 0) { // si es 0, funciona como mascara
				resultado = 0;
			} else {
				resultado = 255 - B(x, y, v); // es la reciproca
			}
		}

		salida(x, y, v) = (resultado < 0) ? 0 : ((resultado > 255) ? 255 : resultado);
	}

	return salida;

}

// EJERCICIO 3
void guia2_eje3() {

	CImg<unsigned char> 
		A("../../img/letras1.tif"),
		B("../../img/huang2.jpg"),
		promedio,
		imagen_dividida_n;

	CImgList<unsigned char> compilado(A, B, 
		get_image_from_operations(A, B, 's'),
		get_image_from_operations(A, B, 'r'),
		get_image_from_operations(A.get_quantize(2).get_normalize(0,1), B, 'm'),
		get_image_from_operations(A.get_quantize(2).get_normalize(0,1), B, 'd'));

	compilado.display("A, B, suma, diferencia, multiplicacion, division");

	/// Creamos una imagen con ruido (usamos la huang2)
	double sigma = sqrt(100);

	promedio = B.get_noise(sigma);
	// Queremos 50 imagenes 
	for (unsigned int k = 0, n = 50 ; k < n ; k++) {
		// Las voy sumando varias veces (50 para ser exacto)
		imagen_dividida_n = B.get_noise(sigma);

		cimg_forXYC(imagen_dividida_n, x, y, v) {
			imagen_dividida_n(x, y, v) = imagen_dividida_n(x, y, v) / n;
		}

		promedio = get_image_from_operations(promedio, B.get_noise(sigma), 's');
	}

	// Mostramos que quedo
	compilado.assign(B, B.get_noise(sigma), promedio)
		.display("Imagen original, con ruido, y promediada");

}

// Invierte la imagen que le pasamos
CImg<unsigned char> get_inversion(CImg<unsigned char> base) {

	CImg<unsigned char> salida(base.width(), base.height());

	cimg_forXYC(base, x, y, v) {
		salida(x, y, v) = 255 - base(x, y, v);
	}

	return salida;
}

// Le pasamos una imagen y la cantidad de desplazamiento que queremos
CImg<unsigned char> emboss(CImg<unsigned char> base, int move_x, int move_y = 0) {

	// Sacamos su negativo
	CImg<unsigned char> inverso(get_inversion(base));

	// Si es negativo el desplazamiento o positivo, lo consideramos
	int new_x0 = (move_x < 0) ? 0 : move_x,
		new_x1 = (move_x > 0) ? base.width() : base.width() + move_x,

		new_y0 = (move_y < 0) ? 0 : move_y,
		new_y1 = (move_y > 0) ? base.height() : base.height() + move_y;

	// Recortamos la base
	base.crop(0, 0, base.width() - abs(move_x), base.height() - abs(move_y));

	// Y la imagen invertida (pero la cortamos de forma desplazada)
	inverso.crop(new_x0, new_y0, new_x1, new_y1);

	// Y ahora la sumamos y lo retornamos
	return get_image_from_operations(base, inverso, 's');

}

void guia2_eje4() {
	CImg<unsigned char> imagen("../../img/huang1.jpg");

	CImgList<unsigned char> compilado(imagen, emboss(imagen, -2, 3));

	compilado.display("Imagen original y con un filtro de emboss");
}

void guia2_eje5() {
	CImg<unsigned char> imagen("../../img/huang1.jpg"),
		imagen_dos("../../img/huang2.jpg"),
		umbral(imagen.get_threshold(128).get_resize(256, 256)),
		umbral_dos(imagen_dos.get_threshold(128));

	CImgList<unsigned char> compilado(imagen, 
		imagen, umbral, get_inversion(umbral), imagen_dos, umbral_dos, get_inversion(umbral_dos));

	//compilado.display("Imagen original, con threshold e invertida. Imagen Dos al lado");

	// Aplicamos una serie de operaciones relacionales
	compilado.assign(
		~umbral&~umbral_dos,
		~umbral|umbral_dos,
		umbral^umbral_dos,
		umbral&~umbral_dos,
		umbral^(~umbral&umbral_dos)
		);

	compilado.display("NOT 1 AND NOT 2, NOT then 1 OR 2, 1 XOR 2, 1 AND NOT 2, 1 XOR (NOT 1 AND 2)");
}

/// Le paso una imagen y el bit en el que quiero que me devuelva la imagen
CImg<unsigned char> get_rodaja(CImg<unsigned char> imagen, short bit = 0) {
	
	CImg<unsigned char> imagen256(imagen.quantize(8)); // la transformo a 8 bits

	cimg_forXYC(imagen256, x, y, v) {
		float val_pixel = imagen256(x, y, v),
			nuevo_val_pixel = 0;

		// Del mayor al menor bit, hasta llegar al bit base
		for (short i = 7; i >= bit; i--) {
			float val_binario = pow(2, i);

			if (val_pixel / val_binario >= 1) { // Entonces tiene ese bit activo
				val_pixel -= val_binario; // y se lo resto

				nuevo_val_pixel += val_binario;
			} 
		}

		imagen256(x, y, v) = nuevo_val_pixel;
	}

	return imagen256;

}

/// Ejercicio 6, de rodajas
void guia2_eje6() {
	CImg<unsigned char> imagen("../../img/lenna.gif"),
		rodajeada;

	imagen.quantize(8);

	for (short i = 7; i >= 0; i--) {
		std::stringstream ss;
		rodajeada = get_rodaja(imagen, i);

		ss << "Imagen generada desde el bit " << i << ". MSE: " << rodajeada.MSE(imagen);
		rodajeada.display(ss.str().c_str());
	}

	std::stringstream ss;
	ss << "Original. MSE: " << imagen.MSE(imagen);

	imagen.display(ss.str().c_str());

}

/// Le paso una imagen, retorna la placa (1: SE, 2:X)
short calculate_asus(CImg<unsigned char> imagen) {
	
	// Dividimos la imagen en el umbral
	CImg<unsigned char> umbral = imagen.get_threshold(200);

	// Medimos la cantidad de negro en un subrectangulo de la imagen
	short x0 = 137, xf = 143, y0 = 164, yf = 175,
		resultado = 0,
		cant_blanco = 0,
		cant_blanco_divisora = 48; // este es un numero promediado de 59 (X) y 38 (SE)

	// Recorremos ese rectangulo en la imagen contando la cantidad de blanco
	for (unsigned int x = x0 ; x <= xf ; x++) {
		for (unsigned int y = y0 ; y <= yf ; y++) {
			cant_blanco += umbral(x, y);
		}
	}

	std::cout << "cant_blanco: " << cant_blanco << std::endl;

	if (cant_blanco > cant_blanco_divisora) {
		std::cout << "El tipo de placa es a7v600-X\n";
		resultado = 2;
	} else {
		std::cout << "El tipo de placa es a7v600-SE\n";
		resultado = 1;
	}

	return resultado;
}

/// Voy a determinar el tamanho de la pastilla midiendo el trozo mas largo
short get_number_of_pills_helper(CImg<unsigned char> umbral) {
	short pastilla_width = 0,
		min_pastilla_width = umbral.width(),
		max_pastilla_width = 0,

		x_min_local = 0;
		
	bool en_pastilla = false;

	for (unsigned int y = 0; y < umbral.height(); y++) {
		x_min_local = 0;

		for (unsigned int x = 0; x < umbral.width(); x++) {
			// Si encuentro la pastilla
			if (umbral(x, y) != 0 && !en_pastilla) {
				en_pastilla = true;

				// Busco el mas chico de todos
				min_pastilla_width = (x < min_pastilla_width) ? x : min_pastilla_width;

				x_min_local = x;
			}

			// Si "salgo" de la pastilla
			if (umbral(x, y) == 0 && en_pastilla) {
				en_pastilla = false;

				// No usamos el mismo x, sino otro para comparar (debido a que puede tomar la ultima pastilla)
				unsigned int x_r = x - x_min_local;
				// Busco el mas largo
				max_pastilla_width = (x_r > max_pastilla_width) ? x_r : max_pastilla_width;
				break;
			}
		}
	}

	// Retorno el ancho de la pastilla
	return max_pastilla_width - min_pastilla_width;

}

/// Le paso una imagen, me devuelve la cantidad de remedio faltante y su ubicacion
short get_number_of_pills(CImg<unsigned char> &base, short cant_pills_x = 5, short cant_pills_y = 2) {

	CImg<unsigned char> umbral = base.get_threshold(100);

	unsigned int min_x = base.width(),
		max_x = 0,
		min_y = base.height(),
		max_y = 0; // minimo valor de x para recortar

	// Recorro la imagen y busco donde empiezan las pildoras
	cimg_forXY(umbral, x, y) {
		// Si no es negro
		if (umbral(x, y) != 0) {
			// Y el x es menor al guardado (o mayor)
			min_x = (x < min_x) ? x : min_x;
			max_x = (x > max_x) ? x : max_x;

			// Lo mismo con el y
			min_y = (y < min_y) ? y : min_y;
			max_y = (y > max_y) ? y : max_y;
		}
	}

	// Ahora lo cropeo
	umbral.crop(min_x, min_y, max_x, max_y);

	// Obtengo el ancho de la pastilla
	short pastilla_width = get_number_of_pills_helper(umbral),
		// Y el largo al rotar la imagen 90º
		pastilla_height = get_number_of_pills_helper(umbral.get_rotate(90));

	// Voy moviendo entre centros de cada pastilla (cuadrados de nxn)
	// Para sacar el step, hago una cosa loca (se ve mejor si lo haces a mano)
	short step_x = (umbral.width() - cant_pills_x * pastilla_width) / (cant_pills_x - 1) + pastilla_width,
		x_start = pastilla_width / 2, 
		x_start_base = x_start,

		step_y = (umbral.height() - cant_pills_y * pastilla_height) / (cant_pills_y - 1) + pastilla_height,
		y_start = pastilla_height / 2,
		y_start_base = y_start,

		cant_blanco = 0,
		cant_negro = 0,
		pastillas_faltantes = 0,
		n = ((pastilla_width < pastilla_height) ? pastilla_width : pastilla_height) / 3;

	for (unsigned int j = 0; j < cant_pills_y; j++) {
		y_start = y_start_base + step_y * j;

		for (unsigned int i = 0; i < cant_pills_x; i++) {
			// Empiezo en la primera pastilla
			x_start = x_start_base + step_x * i;

			// Recorro el rectangulo de nxn
			for (unsigned int y = y_start - n ; y <= y_start + n ; y++) {
				for (unsigned int x = x_start - n ; x <= x_start + n ; x++) {
					// Voy contando la cantidad de pixeles blancos y negros
					if (umbral(x, y) != 0) {
						cant_blanco++;
					} else {
						cant_negro++;
					}
				}
			}
			std::cout << x_start << " @@ " << y_start << std::endl;
			// Si tuve mas pixeles blancos que negro, es porque hay una pastilla
			if (cant_blanco > cant_negro) {
				std::cout << "Pastilla [" << i + j * cant_pills_x << "] okay!\n";
			} else {
				std::cout << "Pastilla [" << i + j * cant_pills_x << "] BAD!\n";
				pastillas_faltantes++;

				// Voy a dibujar en el umbral donde falta la pastilla
				unsigned char white[3] = {1, 1, 1}, black[3] = {0, 0, 0};
				
				// Dibujamos un rectangulo a dentro de otro
				umbral.draw_rectangle(x_start - n, y_start - n, x_start + n, y_start + n, white);
				umbral.draw_rectangle(x_start - n/2, y_start - n/2, x_start + n/2, y_start + n/2, black);
			}

			// Y renicializamos contadores
			cant_blanco = cant_negro = 0;
		}
	}

	umbral.display();

	return pastillas_faltantes;

}

/// Ejercicio 7
void guia2_eje7() {

	/// INCISO A
	// Hay unos aliens arriba a la derecha de los simpsons :3
	CImg<unsigned char> earth("../../img/earth.bmp");
	get_image_by_LUT(earth);

	/// INCISO B
	CImg<unsigned char> imag_SE("../../img/a7v600-SE.gif"),
	 	imag_SE_r("../../img/a7v600-SE(RImpulsivo).gif"),
	 	imag_X("../../img/a7v600-X.gif"),
	 	imag_X_r("../../img/a7v600-X(RImpulsivo).gif");

	CImgList<unsigned char> compartido(imag_X.get_threshold(200), imag_SE.get_threshold(200));

	calculate_asus(imag_X);
	calculate_asus(imag_SE);

	calculate_asus(imag_X_r);
	calculate_asus(imag_SE_r);
	compartido.display("Ambas placas");

	/// INCISO C
	CImg<unsigned char> blister("../../img/blister_completo.jpg"),
		blister_incompleto("../../img/blister_incompleto.jpg");

	get_number_of_pills(blister_incompleto);

}

int main(int argc, char *argv[]) {

  	guia2_eje7();
  	/*
	CImg<unsigned char> grafico(256,256);

	short p0[2] = {0 ,0 },
		p1[2] = {40 , 220},
		p2[2] = {230 , 30},
		p3[2] = {256 , 256},

		white[3] = {255, 255, 255};

	CImg<unsigned char> f_x = get_lagrange_interpolation(p0,p1,p2,p3);

	grafico.draw_graph(f_x, white).display();
*/
	return 0;
}