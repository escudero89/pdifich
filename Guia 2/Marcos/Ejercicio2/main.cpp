#include <iostream>
#include "../../../CImg-1.5.4/CImg.h"
#include <vector>
#include <cstdlib>
#include <string>


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

    return imagen_salida;
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

/// FUNCIONES EJERCICIO 2
CImg<unsigned char> generarLUTlog(unsigned char p_ini = 0, unsigned char p_fin = 255){
    CImg<unsigned char> LUT(256,1,1,1,0);
    float val;

    for(int i=p_ini; i<p_fin+1; i++){
        val = log10(1.0 + (float)i);
        if (val <= 255)
            LUT(i) = (unsigned char) val;
        else
            LUT(i) = 255;
    }

    return LUT;
}


CImg<unsigned char> generarLUTpot(float potencia, unsigned char p_ini = 0, unsigned char p_fin = 255){
    CImg<unsigned char> LUT(256,1,1,1,0);
    float val;

    for(int i=p_ini; i<p_fin+1; i++){
        val = pow(i,potencia);
        if (val <= 255)
            LUT(i) = (unsigned char) val;
        else
            LUT(i) = 255;
    }

    return LUT;
}

/// FUNCIONES EJERCICIO 3
CImg<unsigned char> suma(CImg<unsigned char> I1, CImg<unsigned char> I2){

    CImg<unsigned char> I3(max(I1.width(), I2.width()), max(I1.height(), I2.height()));
    cimg_forXY(I3,i,j){
        I3(i,j) = (I1(i,j) + I2(i,j)) / 2;
    }

    return I3;
}

CImg<unsigned char> resta(CImg<unsigned char> I1, CImg<unsigned char> I2){

    CImg<unsigned char> I3(max(I1.width(), I2.width()), max(I1.height(), I2.height()));
    cimg_forXY(I3,i,j){
        I3(i,j) = (I1(i,j) - I2(i,j) + 255) / 2;
    }

    return I3;
}

CImg<unsigned char> producto(CImg<unsigned char> I1, CImg<unsigned char> I2){

    CImg<unsigned char> I3(max(I1.width(), I2.width()), max(I1.height(), I2.height()));
    cimg_forXY(I3,i,j){
        I3(i,j) = I1(i,j) * I2(i,j);
    }

    return I3;
}

CImg<unsigned char> cociente(CImg<unsigned char> I1, CImg<unsigned char> I2){

    CImg<unsigned char> I3(max(I1.width(), I2.width()), max(I1.height(), I2.height()));
    cimg_forXY(I3,i,j){

       I3(i,j) = ((float) I1(i,j) /(float) ((I2(i,j)!= 0) ? I2(i,j) : 1));


    }

    return I3;
}

CImg<unsigned char> promediar(CImgList<unsigned char> L){

    //Uso double para no overflowear el unsigned char
    CImg<double> acum(L(0).width(), L(0).height(), 1, 1, 0);

    for(int i=0; i< L.size(); i++){
        acum = acum + L(i);
    }

    return acum/L.size();
}

CImg<unsigned char> promediarRuido(CImg<unsigned char> imagen,  unsigned int cant_imagenes,
                                                                unsigned int sigma){
    CImgList<unsigned char> L(cant_imagenes, imagen);

    for(int i=0; i<cant_imagenes; i++){
        L(i).noise(sigma, 0); //0 -> tipo gaussiano
    }

    return promediar(L);
}
/// FUNCIONES EJERCICIO 4
CImg<unsigned char> emboss(CImg<unsigned char> imagen, int dx, int dy){

    //Obtenemos negativo de la imagen
    CImg<unsigned char> negativo = transfLineal(imagen, generarLUT(-1,0));

    // Desplazamos negativo en x en dx pixeles
    for(int i=negativo.width() - 1; i>=dx; i--){
        for(int j=0; j<negativo.height(); j++)
            negativo(i,j) = negativo(i-dx,j);
        }
    // Desplazamos negrativo en y en dy pixeles
    for(int j=negativo.height() - 1; j>=dy; j--){
        for(int i=0; i<negativo.width(); i++)
            negativo(i,j) = negativo(i,j-dy);
        }
    //Retornamos la suma(promediada) del negativo y la imagen
    return suma(negativo, imagen);

}
/// FUNCIONES EJERCICIO 6

string dec2bin (int v) {
    if (v > 255) {
        return "";
    }
    else {
        string bin;
        int oneorzero;
        for(int i=8;i>0;i--) {
            oneorzero = v % 2;
            if (oneorzero == 1) {
                bin = "1" + bin;
            }
            else {
                bin = "0" + bin;
            }
            v /= 2;

        }

    return bin;
    }
}

CImgList<unsigned char> rodajasBits(CImg<unsigned char> imagen, bool display = false){

    //Obligamos a la imagen a tener 8 bits de profundidad
    //imagen.quantize(256);

    //Creamos Vector de String
    vector<string> imagen_binaria;

    //Colocamos en el vector los valores de la imagen en binario
    cimg_forXY(imagen,i,j){
        imagen_binaria.push_back(dec2bin((int) imagen(i,j)));
    }

    //Declaramos algunas variables
    CImgList<unsigned char> L(0, imagen.width(), imagen.height(), 1, 1);
    CImg<unsigned char> I(imagen);
    string s_aux;
    int i_aux;

    //Armamos imagenes binarias por bits
    for(int k=0; k<8; k++){
        for(int i=0; i<imagen_binaria.size(); i++){
            //Generamos substring con el ultimo caracter
            s_aux =  imagen_binaria.at(i).substr(imagen_binaria[i].length() - 1, 1);
            //Transformamos string a int
            i_aux =  (s_aux == "1") ? 1 : 0;
            //Mapeamos a fila-columna correcta
            I(i%imagen.width(), i/imagen.width()) = i_aux;
            //Eliminamos ultimo caracter del string i
            imagen_binaria.at(i).erase(imagen_binaria.at(i).length()-1,1);
        }
        //Guardamos imagen en lista
        L.push_back(I);
    }

    if(display){
        CImgDisplay V1(L, "Rodajas de plano de bits",1);
        while(!V1.is_closed()){}
    }

    return L;
}




int main(){
#if 0 ///   EJERCICIO 1
   CImg<unsigned char> imagen("../../../img/cameraman.tif");


       // Transformaciones lineales por trozos
  /* transfLineal(imagen,
                generarLUT(2,50,0,100) +     /// Parte 1
                generarLUT(0.5,0,101,200) + /// Parte 2
                generarLUT(-1,0,201,255),   /// Parte 3
                true);
*/

        //Transf lineal con mouse
 /* transfLinealMouse(imagen);   */
#endif

#if 0/// EJERCICIO 2
    CImg<unsigned char> imagen("../../../img/rmn.jpg");
    transfLineal(imagen ,generarLUTlog(), true);
    transfLineal(imagen, generarLUTpot(1.5), true);

#endif

#if 0 ///EJERCICIO 3_1
    CImg<unsigned char> imagen1("../../../img/cameraman.tif");
    CImg<unsigned char> imagen2("../../../img/rmn.jpg");
    CImg<unsigned char> mascara(imagen1);
    mascara.fill(0);

    for(int i=100; i<200; i++){
        for(int j=100; j<200; j++){
            mascara(i,j)=1;
        }
    }

    /*

    suma(imagen1,imagen2).display();
    resta(imagen1,imagen2).display();
    producto(imagen1, mascara).display();
    cociente(imagen1, imagen2).display(); ///Ver foro
    promediarRuido(imagen1,100,20).display();

     */
#endif

#if 0 ///Ejercicio 4
 CImg<unsigned char> imagen("../../../img/cameraman.tif");
 emboss(imagen, 1, 1).display();
#endif

#if 0 ///Ejercicio 5
    CImg<unsigned char> imagen1("../../../img/cameraman.tif"),
                        imagen2("../../../img/clown.jpg"),
                        imagen_and(imagen1),
                        imagen_or(imagen1),
                        imagen_not_1(imagen1),
                        imagen_not_2(imagen1),
                        imagen_xor(imagen1),
                        imagen_rel_1(imagen1),
                        imagen_rel_2(imagen1);


    imagen1.threshold(128).display();
    imagen2.threshold(128).display();

    cimg_forXY(imagen1, i, j){
        imagen_and(i,j) = imagen1(i,j) and imagen2(i,j);
        imagen_or(i,j) = imagen1(i,j) or imagen2(i,j);
        imagen_not_1(i,j) = not imagen1(i,j);
        imagen_not_2(i,j) = not imagen2(i,j);
        imagen_xor(i,j) = imagen1(i,j) xor imagen2(i,j);
        imagen_rel_1(i,j) = not imagen1(i,j) and imagen2(i,j);
        imagen_rel_2(i,j) = imagen1(i,j) or imagen2(i,j) and imagen_xor(i,j);

    }

    (imagen1, imagen_and, imagen2).display("Operacion logica: AND");
    (imagen1, imagen_or, imagen2).display("Operacion logica: OR");
    (imagen1, imagen_not_1).display("Operacion logica: NOT");
    (imagen2, imagen_not_2).display("Operacion logica: NOT");
    (imagen1, imagen_xor, imagen2).display("Operacion logica: XOR");
    (imagen1, imagen_rel_1, imagen2).display("Operacion logica: NOT I1 AND I2");
    (imagen1, imagen_rel_2, imagen2).display("Operacion logica: I1 OR I2 AND I1 XOR I2");

#endif

#if 0 ///Ejercicio 6
 CImg<unsigned char> imagen("../../../img/cameraman.tif");
 rodajasBits(imagen, true);

#endif


#if 0 ///Ejercicio 7a
while(true){
    CImg<unsigned char> imagen("../../../img/earth.bmp");
    transfLinealMouse(imagen); //Realzar las tonalidades bajas y dejar en la diagonal lo anterior.
}
#endif
    return 0;
}

