#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
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

/// Ejercicio 7.3
void checkBlister(CImg<unsigned char> imagen){
    CImg<unsigned char> imagen_original(imagen);

    ///Parametros
    int umbral = 100,               //de grises para aplicar a la imagen
        pixel_consecutivos= 3,      //Para encontrar pastilla de referencia
        radio_pastillas = 14,       //Radio de las pastillas
        separacion_pastillas_y = 18,//Separacion Vertical entre pastillas
        separacion_pastillas_x = 19,//Separacion Horizontal entre pastillas
        fila_central_1,             //Coordenada "y" de la primera fila de pastillas
        fila_central_2,             //Coordenada "y" de la segunda fila de pastillas
        ancho_verificacion = 10;    //Para realizar el perfil de intensidad de la
                                    //fila de pastillas (DEBE SER MENOR QUE RADIO PASTILLAS)

    //Aplicamos umbral a la imagen
    imagen.threshold(umbral);


    ///Obtencion de fila_central_1 y fila_central_2

    //Variablea a utilizar en el ciclo que sigue
    bool flag = true;
    int cont = 0;
    //Ciclo
    cimg_forXY(imagen, i, j){
        if(imagen(i,j) == 1){
            cont++;
            if(cont == pixel_consecutivos && flag){
                fila_central_1 = j + radio_pastillas;
                if(fila_central_1 < imagen.height()/2){
                    fila_central_2 = fila_central_1 + 2*radio_pastillas + separacion_pastillas_y;
                    flag = false;
                }else{//si la fila central 1 no tiene pastillas, asignamos cero
                    fila_central_2 = fila_central_1;
                    fila_central_1 = 0;
                }
            }
        }
        else{
             cont = 0;
        }
    }


     ///Perfil de intensidad multiple 1 y 2
    //Obtenemos perfil de intensidad promediando en una franja
    //de ancho: ancho_verificacion y redondeamos el promedio a valores 0 o 1

    //Declaramos perfiles de intensidad
    CImg<unsigned char> intensidad_1(imagen.width(),1,1,1,0),
                        intensidad_2(intensidad_1);

    //Sumamos los perfiles dentro del ancho dado
    if(fila_central_1 != 0){ //si fila_central_1 no esta vacia
        for(int i=-ancho_verificacion/2; i<ancho_verificacion/2; i++){
            intensidad_1 = intensidad_1 + imagen.get_row(fila_central_1 + i);
        }
    }

    for(int i=-ancho_verificacion/2; i<ancho_verificacion/2; i++){
        intensidad_2 = intensidad_2 + imagen.get_row(fila_central_2 + i);
    }

    //Dividimos por el ancho (promedio)
    if(fila_central_1!=0){
        cimg_forX(intensidad_1,i){
            intensidad_1(i) = ((intensidad_1(i)/(float)(ancho_verificacion)) > 0.5) ? 1 : 0;
        }
    }
    cimg_forX(intensidad_2,i){
        intensidad_2(i) = ((intensidad_2(i)/(float)(ancho_verificacion)) > 0.5) ? 1 : 0;
    }

    ///Conteo de pastillas
    //Declaraciones
    vector<bool> pastillas(10, false);  //Vector booleano 1 si la pastilla esta 0 si no

    int cont_ceros = 0;                 //Para contar los ceros entre pastillas, si hay
    int max_ceros = 2*radio_pastillas +   // mas ceros que max_ceros, entonces se considera
            separacion_pastillas_x;     // que en ese lugar falta una pastilla
    int borde = 15;
    int max_ceros_primer_pastilla = max_ceros + borde ;
    int id_pastilla = 0;                // Identificador de pastilla, de izq a derecha de arriba hacia abajo
    bool dentro_de_pastilla = false;    // Bandera indicadora, true si estoy dentro de una pastilla

    if(fila_central_1 != 0){
        cimg_forX(intensidad_1, i){

            if(intensidad_1(i) == 0){
                cont_ceros++;
                dentro_de_pastilla = false;
            }

            if((cont_ceros == max_ceros) and (id_pastilla != 0)){
                pastillas[id_pastilla] = false;
                id_pastilla ++;
                cont_ceros = 0;
            }

            if( (id_pastilla == 0) and (cont_ceros == max_ceros_primer_pastilla) ){
                pastillas[id_pastilla] = false;
                id_pastilla ++;
                cont_ceros = 0;
            }

            if(intensidad_1(i) == 1 && !dentro_de_pastilla){
                pastillas[id_pastilla] = true;
                id_pastilla++;
                cont_ceros = 0;
                dentro_de_pastilla = true;
            }
        }
    }
    //Reseteamos parametros
    cont_ceros = 0;
    id_pastilla = 5;
    dentro_de_pastilla = false;

    cimg_forX(intensidad_2, i){

        if(intensidad_2(i) == 0){
            cont_ceros++;
            dentro_de_pastilla = false;
        }

        if(cont_ceros == max_ceros){
            pastillas[id_pastilla] = false;
            id_pastilla ++;
            cont_ceros = 0;
        }

        if(intensidad_2(i) == 1 && !dentro_de_pastilla){
            pastillas[id_pastilla] = true;
            id_pastilla++;
            cont_ceros = 0;
            dentro_de_pastilla = true;
        }
    }

    ///Mostramos resultados
    for(int i=0; i<pastillas.size(); i++){
        cout<<"Pastilla "<< i <<": "<<pastillas[i]<<endl;
    }

    imagen_original.display();
    //imagen.display();
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


#if 1 ///Ejercicio 7a
while(true){
    CImg<unsigned char> imagen("../../../ingles1.jpg");
    imagen.channel(0);
    transfLinealMouse(imagen); //Realzar las tonalidades bajas y dejar en la diagonal lo anterior.
}
#endif

///Ejercicio 7c
#if 0
    CImg<unsigned char> imagen1("../../../img/blister_incompleto.jpg");
    CImg<unsigned char> imagen2("../../../img/blister_incompleto_other.jpg");
    CImg<unsigned char> imagen3("../../../img/blister_completo.jpg");

    /*
    (imagen1, imagen1.get_threshold(100)).display();
    (imagen2, imagen2.get_threshold(100)).display();
    (imagen3, imagen3.get_threshold(100)).display();
    */
    checkBlister(imagen1);
    checkBlister(imagen2);
    checkBlister(imagen3);

#endif
    return 0;
}

