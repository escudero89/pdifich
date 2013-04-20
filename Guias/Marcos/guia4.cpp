#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include <vector>
#include <cstdlib>
#include <string>

using namespace cimg_library;
using namespace std;

/*
Hola a todos,
Subí el tp 4 para que empiecen a hacerlo. Les paso algunos tips para resolver los ejercicios.

Ejercicio 1:
- Al pasar a HSI usen tipo de dato <float> ya que H tendrá valores en [0-360] que
  exceden el 255 de <unsigned char>.

- Para poder interpretar visualmente las componentes H, S e I les conviene normalizar
  a 0-255 cada componente. Recalco nuevamente que esto es sólo para visualizar e
  interpretar, NO para operar.

Ejercicio 2:
- Estan subidas las paletas de colores en archivos de textos que podrán levantar con
  la función cargar_paleta(), que está en PDI_functions.h. Incluirlo colocando:
  #include "../PDI_functions.h", luego del #include <CImg.h>

Ejercicio 5:
- Para saber si un píxel cae dentro de la esfera de segmentación en el modelo RGB, primero
  computen la distancia entre el píxel y el centro de la esfera (a,b,c) y luego comprueben
  si esa distancia es menor al radio R.
    cimg_forXY(img,x,y){
    D=sqrt(pow(img(x,y,0)-a,2)+pow(img(x,y,1)-b,2)+pow(img(x,y,2)-c,2));
    if (D<R){
        mascara(x,y,0)=1;
        mascara(x,y,1)=1;
        mascara(x,y,2)=1;
    }

Estoy disponible para cualquier consulta a través del foro o bien personalmente cualquier
día de 8 a 17hs. También podemos revisar lo que necesiten el jueves en clase, donde
empezaremos con Fourier.

Saludos,
Omar.

*/

int main(int argc, char *argv[]){

    //Ejercicio 1
    const char* filename = cimg_option("-i", "../../img/patron.tif", "Input Image File");
    CImg<unsigned char> img_original(filename);
    CImg<float> img_hsi(img_original.get_RGBtoHSI());

    //Imagen color y sus planos RGB
    (img_original,
     img_original.get_channel(0),
     img_original.get_channel(1),
     img_original.get_channel(2)
     ).display("Imagen color y sus planos RGB");

     //Imagen color y sus planos HSI
     img_hsi.display();

     (img_original,
     img_hsi.get_channel(0),
     img_hsi.get_channel(1),
     img_hsi.get_channel(2)
     ).display("Imagen color y sus planos HSI");


    return 0;
}

