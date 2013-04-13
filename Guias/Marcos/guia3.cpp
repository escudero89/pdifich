#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include <vector>
#include <cstdlib>
#include <string>

using namespace cimg_library;
using namespace std;

void caracterizarRuido(CImg<unsigned char> imagen){
    CImg<unsigned char> sub_img(200,200,3);

    int x0,y0,x1,y1;
    bool    first = false,
            second = false;
    unsigned char rojo[] = {255,255,255};

    CImgDisplay ventana_imagen(imagen, "Seleccione area a analizar",0);
    ventana_imagen.resize(imagen);
    while(!ventana_imagen.is_closed()){

        ventana_imagen.wait();

        if(ventana_imagen.button()){
            if(!first){
                cout<<"hereeeeee111111"<<endl;
                x0 = ventana_imagen.mouse_x();
                y0 = ventana_imagen.mouse_y();
                cout<<x0<<endl;
                cout<<y0<<endl;
                first = true;
            }
            else{
                cout<<"hereeeeee222222"<<endl;
                x1 = ventana_imagen.mouse_x();
                y1 = ventana_imagen.mouse_y();
                cout<<x1<<endl;
                cout<<y1<<endl;
                second = true;
            }
        }

        if(second){break;}

    }

    sub_img = imagen.get_crop(x0,y0,x1,y1);
    sub_img.display();
    imagen.draw_rectangle(x0,y0,x1,y1,rojo).display();
    sub_img.get_histogram(256, 0, 255).display_graph(0,3);


}
CImg<unsigned char> normalizar(CImg<int> imagen_entrada){

    CImg<unsigned char> imagen_salida(imagen_entrada.width(),
                                      imagen_entrada.height(),
                                      1,1);
    int min_in = 0,
        max_in = 0,
        min_out = 0,
        max_out = 255;

    //Obtenemos valores maximos y minimos de la imagen para realizar el mapeo
    min_in = imagen_entrada.min_max( max_in );

    //Realizamos mapeo lineal en rango [min_in max_in] => [min_out max_out]
    cimg_forXY(imagen_entrada,i,j){

        imagen_salida(i,j) = (int)((float)((imagen_entrada(i,j) - min_in) * (max_out - min_out))
                                    /
                        (float)(max_in - min_in) + min_out);
    }

    return imagen_salida;
}

CImg<unsigned char> ecualizarLocal(CImg<unsigned char> imagen, int x0,
                                        int y0, int x1, int y1){

    CImg<unsigned char> base(imagen.get_crop(x0,y0,x1,y1)),
        ecualizada(base.get_equalize(256));

    (base, ecualizada).display();
    base.get_histogram(256,0,255).display_graph("Base",3);
     ecualizada.get_histogram(256,0,255).display_graph("Ecualizado",3);

    return imagen;
}


void ecualizarLocalMouse(CImg<unsigned char> imagen){


CImg<unsigned char> sub_img(200,200,3);

    int x0,y0,x1,y1;
    bool    first = false,
            second = false;
    unsigned char rojo[] = {255,255,255};

    CImgDisplay ventana_imagen(imagen, "Seleccione area a analizar",0);
    ventana_imagen.resize(imagen);
    while(!ventana_imagen.is_closed()){

        ventana_imagen.wait();

        if(ventana_imagen.button()){
            if(!first){
                cout<<"hereeeeee111111"<<endl;
                x0 = ventana_imagen.mouse_x();
                y0 = ventana_imagen.mouse_y();
                cout<<x0<<endl;
                cout<<y0<<endl;
                first = true;
            }
            else{
                cout<<"hereeeeee222222"<<endl;
                x1 = ventana_imagen.mouse_x();
                y1 = ventana_imagen.mouse_y();
                cout<<x1<<endl;
                cout<<y1<<endl;
                second = true;
            }
        }

        if(second){
            sub_img = ecualizarLocal(imagen,x0,y0,x1,y1);
            first= second = false;
            //break;
        }

    }

    //sub_img = ecualizarLocal(imagen,x0,y0,x1,y1);
    //sub_img.display();
    //imagen.draw_rectangle(x0,y0,x1,y1,rojo).display();





}

int main(int argc, char *argv[]){
#if 0   //Ejercicio 1 - inciso 1
    CImg<unsigned char>     imagen_0("../../img/cameraman.tif"),
                            imagen_1(imagen_0),
                            hist_0(imagen_0.get_histogram(256)),
                            hist_1(hist_0);


    imagen_1 = imagen_0.get_equalize(256);
    hist_1 = imagen_1.get_histogram(256);

    hist_0.display_graph(0,3);
    hist_1.display_graph(0,3);

    (imagen_0, imagen_1).display();

#endif

#if 0   //Ejercicio 1 - inciso 2

    CImg<unsigned char>     imagen_A("../../img/imagenA.tif"),
                            imagen_B("../../img/imagenB.tif"),
                            imagen_C("../../img/imagenC.tif"),
                            imagen_D("../../img/imagenD.tif"),
                            imagen_E("../../img/imagenE.tif"),
                            hist_a(imagen_A.get_histogram(256, 0, 255)),
                            hist_b(imagen_B.get_histogram(256, 0, 255)),
                            hist_c(imagen_C.get_histogram(256, 0, 255)),
                            hist_d(imagen_D.get_histogram(256, 0, 255)),
                            hist_e(imagen_E.get_histogram(256, 0, 255));

    imagen_A.display();
    hist_a.display_graph(0,3);

    imagen_B.display();
    hist_b.display_graph(0,3);

    imagen_C.display();
    hist_c.display_graph(0,3);

    imagen_D.display();
    hist_d.display_graph(0,3);

    imagen_E.display();
    hist_e.display_graph(0,3);

#endif

# if 0//Ejercicio 2
    //Cargamos imagenes
    CImg<unsigned char>     imagen_a("../../img/FAMILIA_a.jpg"),
                            imagen_b("../../img/FAMILIA_b.jpg"),
                            imagen_c("../../img/FAMILIA_c.jpg"),
                            sub_img(150,150,1,1,0);

    //Definimos rectangulo uniforme en la imagen
    int x0 = 1418 , y0 = 174, x1 = 1875, y1 = 288;
    int media, varianza;
    unsigned char blanco[] ={255,255,255};
    imagen_a = imagen_c;
    // Aplicamos histograma a ese rectangulo
    sub_img = imagen_a.get_crop(x0,y0,x1,y1);

    imagen_a.display();
    sub_img.display();
    imagen_a.draw_rectangle(x0,y0,x1,y1,blanco);
    imagen_a.display();
    media = sub_img.mean();
    varianza = sub_img.variance_mean(0,media);
    sub_img.get_histogram(256, 0, 255).display_graph(0,3);

    cout<<"Media: "<< media<<endl;
    cout<<"Varianza: "<< varianza<<endl;

    //Lo mismo pero capturando puntos con el mouse
    /*
    const char* filename = cimg_option("-i", "cameraman.tif", "Imagen");
    while(true){
        caracterizarRuido(imagen_a);
        caracterizarRuido(imagen_b);
        caracterizarRuido(imagen_c); }
    */

# endif

#if 0 //Ejercicio 3,4
    CImg<float> f_promediado_3x3(3,3,1,1,
                                         0,1,0,
                                         1,1,1,
                                         0,1,0
                                        ),
                f_promediado_5x5(5,5,1,1,
                                 0,1,1,1,0,
                                 1,2,3,2,1,
                                 1,3,4,3,1,
                                 1,2,3,2,1,
                                 0,1,1,1,0),

                f_promediado_7x7(7,7,1,1,
                                 1,1,1,1,1,1,1,
                                 1,1,1,1,1,1,1,
                                 1,1,1,1,1,1,1,
                                 1,1,1,1,1,1,1,
                                 1,1,1,1,1,1,1,
                                 1,1,1,1,1,1,1,
                                 1,1,1,1,1,1,1),

                f_promediado_15x15(15,15,1,1,1);

    CImg<float> imagen("../../img/hubble.tif");
    CImgList<float> L(imagen);

    f_promediado_3x3 = f_promediado_3x3 / 5;
    f_promediado_5x5 = f_promediado_5x5 / 36;
    f_promediado_7x7 = f_promediado_7x7 / 49;
    f_promediado_15x15 = f_promediado_15x15/(15*15);

    L.push_back(imagen.get_convolve(f_promediado_3x3));
    L.push_back(imagen.get_convolve(f_promediado_5x5));
    L.push_back(imagen.get_convolve(f_promediado_7x7));
    L.push_back(imagen.get_convolve(f_promediado_15x15));

    CImgDisplay ventana(L,"Filtros pasa bajo",0);
    while(!ventana.is_closed()){}

#endif

#if 0 //Ejercicio 5
    const char* filename = cimg_option("-i", "../../img/coins.tif", "Input Image File");
    //Filtro Pasa altos de 3x3 con suma 1
    CImg<int> f_pasaAlto_S1_3x3_a(3,3,1,1,
                                         1,-2, 1,
                                        -2, 5,-2,
                                         1,-2, 1
                                                ),
            f_pasaAlto_S0_3x3_a(3,3,1,1,
                                         0,-1, 0,
                                        -1, 4,-1,
                                         0,-1, 0
                                                ),

            f_pasaAlto_S1_3x3_b(3,3,1,1,
                                         -1, -1, -1,
                                         -1,  9, -1,
                                         -1, -1, -1
                                                ),
            f_pasaAlto_S0_3x3_b(3,3,1,1,
                                         -1, -1, -1,
                                         -1,  8, -1,
                                         -1, -1, -1
                                                );

    //Cargamos imagen
    CImg<int> imagen(filename);
    imagen.channel(0);
    CImgList<unsigned char> Lista(imagen);

    //Realizamos convolucion con kernel, normalizamos [0-255] y guardamos en Lista
    Lista.push_back( normalizar(imagen.get_convolve(f_pasaAlto_S1_3x3_a)) );
    Lista.push_back( normalizar(imagen.get_convolve(f_pasaAlto_S1_3x3_b)) );
    Lista.push_back( normalizar(imagen.get_convolve(f_pasaAlto_S0_3x3_a)) );
    Lista.push_back( normalizar(imagen.get_convolve(f_pasaAlto_S0_3x3_b)) );

    //Mostramos imagen
    CImgDisplay ventana(Lista,"Filtros pasa alto: S1_a || S1_b || S0_a || S0_b",0);
    while(!ventana.is_closed()){}



#endif

#if 0 ///Ejercicio 6
        //Filtrado de Mascara Difusa  f (x,y) - PB(f(x,y))

    const char* filename = cimg_option("-i", "../../img/camaleon.tif", "Input Image File");
    CImg<int> imagen(filename);
    imagen.channel(0);

    //Definimos filtro pasa bajo
    CImg<unsigned char> f_pasaBajo_3x3(3,3,1,1,
                                         1,1,1,
                                         1,1,1,
                                         1,1,1
                                        );
    float A = 1.2; //factor para high boost filter
    (
     imagen,
     normalizar(imagen - imagen.get_convolve(f_pasaBajo_3x3).normalize(0,255)),
     normalizar(A * imagen - imagen.get_convolve(f_pasaBajo_3x3).normalize(0,255))

     ).display("Original / Mascara difusa / High boost con 1.2",0);


#endif


#if 1 ///EJERCICIO 7 A


const char* filename = cimg_option("-i", "../../img/cuadros.tif", "Input Image File");
    CImg<int> imagen(filename);
    imagen.channel(0);


    imagen.get_equalize(256).display();

    ecualizarLocalMouse(imagen);

  //ecualizarLocal(imagen, 12, 12, 135, 135);
// ecualizarLocal(imagen, 374, 376, 497, 499);


#endif
    return 0;
}

