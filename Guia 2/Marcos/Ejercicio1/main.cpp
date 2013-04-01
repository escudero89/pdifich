#include <iostream>
#include "../../../CImg-1.5.4/CImg.h"
#include <vector>

using namespace cimg_library;
using namespace std;

CImg<unsigned char> transfLineal(CImg<unsigned char> imagen_entrada,
                                 CImg<unsigned char> LUT,
                                 bool display = false){

    int blanco[3] = {255, 255, 255};
    CImg<unsigned char> imagen_salida(imagen_entrada),
                        visu(256,256,1,1,0);

    cimg_forXY(imagen_entrada, i, j){
        imagen_salida(i,j) = LUT(imagen_entrada(i,j));
    }

    if (display){
        visu.fill(0).draw_graph(LUT,blanco,1,1,1,255,0);
        CImgList<unsigned char> lista(imagen_entrada, visu, imagen_salida);
        CImgDisplay ventana(lista, "Transformacion Lineal", 0);
        while(!ventana.is_closed()){}
    }


}

CImg<unsigned char> generarLUT(float a, float c,unsigned char p_ini = 0,
                                                unsigned char p_fin = 255){
    CImg<unsigned char> LUT(256,1,1,1,0);
    float val;

    for(int i=p_ini; i<p_fin+1; i++){
        val = (i * a + c);
        if (val <= 255)
            LUT(i) = (unsigned char) val;
        else
            LUT(i) = 255;
    }

    return LUT;
}


void transfLinealMouse(CImg<unsigned char> imagen){
    int blanco[] = {255, 255, 255};
    int rojo[] = {255, 0, 0};

    CImg<unsigned char> cuadro(256, 256, 1, 1, 0),
                        LUT_identidad(256,1,1,1,0),
                        LUT(256,1,1,1,0);

    vector<int> cords_x;
    vector<int> cords_y;
    cords_x.push_back(0);
    cords_y.push_back(255);

    cimg_forX(LUT_identidad, i){LUT_identidad(i) = i;}
    cuadro.draw_graph(LUT_identidad, blanco,1,1,1,255,0);
    CImgDisplay v_cuadro(cuadro,"Clickee los puntos que desee, ENTER para (255,255)",0);

    while(!v_cuadro.is_closed()){

        v_cuadro.wait();

        if(v_cuadro.button()){
            cords_x.push_back(v_cuadro.mouse_x());
            cords_y.push_back(v_cuadro.mouse_y());
            cuadro.draw_point(cords_x.back(),cords_y.back(),rojo);
            cuadro.display(v_cuadro);
        }

        if(v_cuadro.is_key(cimg::keyENTER)){
            cords_x.push_back(255);
            cords_y.push_back(0);
            break;
        }
    }

    for(int i=0; i< cords_x.size(); i++){
        cout<<"Cord: x"<<i<<": "<<cords_x.at(i)<<endl;
        cout<<"Cord: y"<<i<<": "<<cords_y.at(i)<<endl;
    }

    int x1=0, x2=0, y1=0, y2=0, tam = cords_x.size();
    float a=0, b=0;
    for (int i = 0; i<tam-1; i++){
        x1= cords_x.at(i);
        x2= cords_x.at(i+1);
        if(i>0){x1++;} ///Para que no se overlapeen en el LUT

        y1= 255 - cords_y.at(i);
        y2 = 255 - cords_y.at(i+1);

        a = (float)(y1 - y2) /(float) (x1 - x2);
        b = y1 - a * x1;

        LUT = LUT + generarLUT(a,b,x1,x2);

    }

    transfLineal(imagen, LUT, true);
}

int main(){

   CImg<unsigned char> imagen("../../../img/cameraman.tif");

   /// Transformaciones lineales por trozos
  /* transfLineal(imagen,
                generarLUT(2,50,0,100) +     /// Parte 1
                generarLUT(0.5,0,101,200) + /// Parte 2
                generarLUT(-1,0,201,255),   /// Parte 3
                true);
*/

    transfLinealMouse(imagen);

    return 0;
}

