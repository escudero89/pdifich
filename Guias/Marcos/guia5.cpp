//Para compilar: g++ -o guia5 guia5.cpp -O0 -lm -lpthread -lX11 -lfftw3 && ./guia5

#include <iostream>
#include "../../CImg-1.5.4/CImg.h"
#include "../../PDI_functions.h"
#include <cstdlib>
#include <complex>
#include <string>


using namespace cimg_library;
using namespace std;

CImgList<double> RealImag2MagnitudFase(CImgList<double> FFT){
    CImg<double>    TDF_real = FFT[0],
                    TDF_imaginaria = FFT[1];
    CImg<double> img(TDF_real);


    //Definicion de la constante imaginaria I=sqrt(-1):
    complex<double> I(0.,1.);
    CImg<double> magnitud(img.width(),img.height(),1,1);
    CImg<double> fase(img.width(),img.height(),1,1);
    for (int i=0;i<img.width();i++){
        for (int j=0;j<img.height();j++){
            magnitud(i,j) = sqrt(pow(TDF_real(i,j),2)+pow(TDF_imaginaria(i,j),2));

            //Expresion de cada valor complejo de la TDF a partir de su parte real e imaginaria:
            complex<double>complejo=TDF_real(i,j)+I*TDF_imaginaria(i,j);

            //La funcion "arg" devuelve el argumento ( angulo) del numero complejo:
            fase(i,j)=arg(complejo);
            }
        }
    CImgList<double> L(magnitud, fase);
    return L;
}

CImgList<double> MagnitudFase2RealImag(CImgList<double> FFT){
//Definicion de la constante imaginaria I=sqrt(-1):
    CImg<double>    magnitud = FFT[0],
                    fase = FFT[1];

    complex<double>I(0.,1.);
    CImg<double>p_real(magnitud.width(),magnitud.height(),1,1);
    CImg<double>p_imaginaria(magnitud.width(),magnitud.height(),1,1);
    for (int i=0;i<magnitud.width();i++){
        for (int j=0;j<magnitud.height();j++){
            //Obtencion de las partes real e imaginaria
            //de la TDF expresada en coordenadas polares.
            //Las funciones ‘‘real’’ e ‘‘imag’’ se encuentran
            //definidas en la libreria estandar ‘‘complex.h’’a
            p_real(i,j)=real(magnitud(i,j)*exp(I*fase(i,j)));
            p_imaginaria(i,j)=imag(magnitud(i,j)*exp(I*fase(i,j)));
        }
    }
    CImgList<double> L(p_real, p_imaginaria);
    return L;
}

CImg<double> get_filtro(CImg<double> img, double frecuencia_corte,
                        string tipo ="i", bool draw = false,
                        float origen_x = 0, float origen_y = 0){
    int M = img.width(),
        N = img.height(),
        bw_orden = 2;

    CImg<double> filtro(M,N,1,1),
                 filtro_completo(M,N,1,1,0);
    double distancia;

    //Armamos el filtro
     cimg_forXY(filtro,i,j){
        distancia = sqrt(pow((i - origen_x),2) + pow((j - origen_y),2));

        if( tipo == "i" ){ // Pasa bajos Ideal
            filtro(i,j) = distancia > frecuencia_corte ? 0 : 1;
        }

        if(tipo.substr(0,1) == "b") { //Pasa bajos butterworth
            if(tipo.size() == 1){
                bw_orden = 2;
            }else{
                string bw_orden_string = tipo.substr(1,1);
                bw_orden = atoi(bw_orden_string.c_str());
            }

            filtro(i,j) = 1/(1 + pow((distancia/frecuencia_corte), 2*bw_orden));
        }

        if(tipo == "g") { //Pasa bajos Gauss
            filtro(i,j) = exp((-pow(distancia,2))/ (2 * pow(frecuencia_corte,2)));
        }
     }


    //Armamos filtro completo (4 cuadrantes)
    filtro_completo =   filtro +
                        filtro.get_mirror("x") +
                        filtro.get_mirror("y") +
                        filtro.get_mirror("xy");

    //Mostramos filtro 2D
    //filtro_completo.display();
    //filtro_completo.get_shift(M/2, N/2, 0, 0, 2).display();

    //Mostramos filtro 3D
    if(draw){
        draw_3D_image(filtro_completo.get_shift(M/2,N/2,0,0,2) * 10);
    }

    return filtro_completo;

}

CImg<double> filtrar(CImg<double> img, CImg<double> filtro ){



    //Obtenemos espectro de magnitud
    CImgList<double> espectro = RealImag2MagnitudFase(img.get_FFT());

//  Mostramos filtro
    filtro.display("Filtro H(u,v)");

//  Muestra espectro de magnitud antes de filtrado
    CImg<double> magnitud(espectro[0]);
    cimg_forXY(magnitud,i,j){
        magnitud(i,j)=log(espectro[0](i,j) + 0.000001);
    }
    magnitud.normalize(0,255);
    magnitud.display("Espectro de Magnitud antes de Filtrar");

    //Realizamos producto punto a punto H(u,v) F(u,v)
    cimg_forXY(espectro[0],i,j){
        espectro[0](i,j) = espectro[0](i,j) * filtro(i,j);
    }

    //  Muestra espectro de magnitud despues de filtrado
    cimg_forXY(magnitud,i,j){
        magnitud(i,j)=log(espectro[0](i,j) + 0.000001);
    }
    magnitud.normalize(0,255);
    magnitud.display("Espectro de magnitud despues de filtrar");

    //Volvemos al espacio de la imagen
    CImg<double> img_filtrada = ( MagnitudFase2RealImag(espectro).get_FFT(true) )[0];

    //Mostramos imagen original y filtrada
    (img, img_filtrada.display()).display("Imagen original y filtrada");

    return img_filtrada;
}

int main(int argc, char *argv[]){

#if 0     ///          /// EJERCICIO 4 ///   (menos 4.3)       ///

    const char* filename = cimg_option("-i", "../../img/cameraman.tif", "Input Image File");
    const char* fc = cimg_option("-fc", "30", "Frecuencia de corte");
    const char* tipoFiltrado = cimg_option("-f", "g", "Tipo Filtrado");
    CImg<double>img(filename);
    img.channel(0);

    if(atoi(fc) == 0){
        (img,
         filtrar(img, get_filtro(img, 10, tipoFiltrado)),
         filtrar(img, get_filtro(img, 20, tipoFiltrado)),
         filtrar(img, get_filtro(img, 40, tipoFiltrado)),
         filtrar(img, get_filtro(img, 60, tipoFiltrado))).display();
    }
    else{

        (img, filtrar(img, get_filtro(img, atoi(fc), tipoFiltrado))).display();

    }


#endif     ///          /// FIN E4 ///          ///


#if 1       ///          /// EJERCICIO 4.3 ///                 ///

    const char* filename = cimg_option("-i", "../../img/cameraman.tif", "Input Image File");
    CImg<double>img(filename);
    img.channel(0);
    int M = img.width(),
        N = img.height();

    //Definimos filtro pasa bajo en espacio h(x,y)
    CImg<double> f_pasa_bajo(M,N,1,1);
    int frecuencia_corte = 2;
    double distancia;

    cimg_forXY(f_pasa_bajo, i, j){
        distancia = sqrt(pow((i),2) + pow((j),2));
        f_pasa_bajo(i,j) = exp((-pow(distancia,2))/ (2 * pow(frecuencia_corte,2)));
    }

    f_pasa_bajo =   f_pasa_bajo +
                    f_pasa_bajo.get_mirror("x") +
                    f_pasa_bajo.get_mirror("y") +
                    f_pasa_bajo.get_mirror("xy");

    //f_pasa_bajo.shift(img.width()/2, img.height()/2, 0, 0, 2);
    f_pasa_bajo.display();

    //Aplicamos transformada para obtener H(u,v)
    CImgList<double> L= RealImag2MagnitudFase(f_pasa_bajo.get_FFT());
    magn_tdf(f_pasa_bajo).display();
    L[0].normalize(0,1);
    cimg_forXY(L[0],i,j){
        L[0](i,j) = exp(L[0](i,j))/exp(1);
    }
    filtrar(img, L[0]);


#endif      ///          /// FIN E4.3 ///          ///

    return 0;
}
