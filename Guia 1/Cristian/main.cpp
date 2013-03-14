#include "../CImg-1.5.4/CImg.h"
using namespace cimg_library;

// Eje 5 => get_resize()
// Eje 6 => get_quantize()

/// Ejercicio 1 de la Guia 1
void guia1_eje1() {
 
  // Pixel values are stored first along the X-axis, then the Y-axis, then the Z-axis, then the C-axis :
  CImg<unsigned char> imagen_desde_archivo("img/cameraman.tif");
  
  // Mostramos imagen
  CImgDisplay ventana(imagen_desde_archivo, "Titulo", 0);
  
  // Mostramos ventana
  while (!ventana.is_closed() && !ventana.is_keyQ()) { }
}


int main(int argc, char *argv[]) {
  /*
  short dx = 640,
    dy = 480,
    dz = 1,	// [1, 2, 3] =>  [R, G, B]
    dc = 1,	// 1 escala de grises, 3 color
    val = 0,	// De 0 a 255, negro => blanco
  
    n = 0; // normalizacion
  
  CImg<unsigned char> imagen(dx, dy, dz, dc, val);
  
  CImg<unsigned char> imagen_desde_archivo("img/orion.jpg");
  
  // Mostramos imagen
  CImgDisplay ventana(imagen_desde_archivo, "Titulo", n);
  
  cimg_usage("Este programa realiza...");
  
  // Mantiene ventana abierta
  while (!ventana.is_closed() && !ventana.is_keyQ()) { }
  
  */
  guia1_eje1();

  return 0;
}