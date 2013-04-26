#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions"
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

CImg<unsigned char> normalizar(CImg<float> imagen_entrada,int min_in = 0,
                                                        int max_in = 0,
                                                        int min_out= 0,
                                                        int max_out= 255){

    CImg<unsigned char> imagen_salida(imagen_entrada.width(),
                                      imagen_entrada.height(),
                                      1,1);

    if(min_in == 0 and max_in == 0){
        //Obtenemos valores maximos y minimos de la imagen para realizar el mapeo
        min_in = imagen_entrada.min_max( max_in );
    }

    //Realizamos mapeo lineal en rango [min_in max_in] => [min_out max_out]
    cimg_forXY(imagen_entrada,i,j){

        imagen_salida(i,j) = (unsigned char)(((imagen_entrada(i,j) - min_in) * (max_out - min_out))
                                    /
                        (max_in - min_in) + min_out);
    }

    return imagen_salida;
}



int main(int argc, char *argv[]){

#if 0     ///          /// EJERCICIO 1 ///          ///

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
     CImg<float>    img_h(img_hsi.get_channel(0)),
                    img_s(img_hsi.get_channel(1)),
                    img_i(img_hsi.get_channel(2));

     (img_original,
      img_h, img_s, img_i).display("Imagen color y sus planos HSI");

    ////        Transformamos degradado de azul a rojo:         ////
     CImg<float> nueva_img_hsi(img_hsi);
     cimg_forXYZ(nueva_img_hsi,i,j,k){
        nueva_img_hsi(i,j,0) = img_hsi( img_hsi.width()-1 -i, j, 0);
     }

    CImg<float> nueva_img_rgb( nueva_img_hsi.get_HSItoRGB() );

    (img_original,
     img_h,
     nueva_img_rgb,
     nueva_img_hsi.get_channel(0)
    ).display("Reversion, degradado azul a rojo y plano h");

    ////        //////////////////////////////////////          ////



    ////               Saturacion y brillo maximos              ////
    cimg_forXYZ(nueva_img_hsi,i,j,k){
        nueva_img_hsi(i,j,2) = 1;
        nueva_img_hsi(i,j,1) = 1;
    }

    nueva_img_rgb = nueva_img_hsi.get_HSItoRGB();

    (img_original,
     //img_s,
     nueva_img_rgb,
     nueva_img_hsi.get_channel(1)
    ).display("Brillo maximo y plano i");
    ////        //////////////////////////////////////          ////


    ////               Colores complementarios                 ////
    nueva_img_hsi = img_hsi;
    cimg_forXYZ(nueva_img_hsi,i,j,k){
        if( nueva_img_hsi(i,j,0) <= 180){
            nueva_img_hsi(i,j,0) =  nueva_img_hsi(i,j,0) + 180;
        }
        else{
            nueva_img_hsi(i,j,0) =  nueva_img_hsi(i,j,0) - 180;
        }
    }

    nueva_img_rgb = nueva_img_hsi.get_HSItoRGB();

    (img_original,
     img_h,
     nueva_img_rgb,
     nueva_img_hsi.get_channel(0)
    ).display("Colores complementarios y plano h");
    ////        //////////////////////////////////////          ////

#endif     ///          /// FIN E1 ///          ///

#if 1     ///          /// EJERCICIO 2 ///          ///

        //cargar_paleta("../../paletas/bone.pal")

#endif     ///          /// FIN E2 ///          ///
    return 0;
}
