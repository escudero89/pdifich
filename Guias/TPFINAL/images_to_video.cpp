//Para compilar: g++ -o tp main.cpp -O0 -lm -lpthread -lX11 -lfftw3

#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions.h"
#include <cstdlib>
#include <complex>
#include <string>
#include <cmath>
#include <cassert>

#define EPSILON 0.1

using namespace cimg_library;
using namespace std;

///Funcion principal que hace todo
void images_to_video(
    const char* images_file) {

    string nombreFile = string(images_file).substr(0, string(images_file).find(".txt"));

    string carpetaIn = "CasosPrueba/";
    string carpetaOut = "Temp/";

    string carpetaInResultado = carpetaIn + nombreFile + "/";
    string carpetaOutResultado = carpetaOut + nombreFile + "/";

    cout << "Tomando casos de prueba desde: " << carpetaInResultado << endl;
    cout << "Retornando resultados en: " << carpetaOutResultado << endl;

    string str_resultado = carpetaOutResultado + "resultado.png";

    /// Abrimos y trabajamos imagen por imagen
    ifstream f(string(carpetaIn + images_file).c_str());
    string image_file;
    string ignorar;

    unsigned int contador = 0;

    // Ignoro las dos primeras lineas (el dia y la noche base)
    f >> ignorar;
    f >> ignorar;

    // Vamos recorriendo cada path en el archivo y analizando la imagen
    while(!f.eof()) {

        f >> image_file;

        CImg<double> image((carpetaInResultado + image_file).c_str());
        image.save(str_resultado.c_str(), contador);

        cout << "Imagen procesada: " << image_file;
        cout << "\tImagen salida: " << "resultado_" << contador << ".png" << endl;

        contador++;
    }

    f.close();
}

int main(int argc, char *argv[]){
   
    const char* _images_filename = cimg_option("-imagesf","images.txt", "Imagen de entrada");

    images_to_video(_images_filename);

    return 0;
}
