#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
//#include <CImg.h>
using namespace std;
using namespace cimg_library;


/// FILTRO DE MEDIA GEOMETRICA
//RECIBE:
//   img:      Imagen a filtrar (por seguridad usar DOUBLE)
//   tam_masc_x: tamanio de la mascara de filtrado en x
//   tam_masc_y: tamanio de la mascara de filtrado en y
//DEVUELVE>
//   Imagen filtrada normalizada en [0 1]
template <typename T>
CImg<T> filtrar_mediaGeometrica(CImg<T> img, int tam_masc_x = 3,
                                             int tam_masc_y = 3){

    //Normalizamos para evitar los problemas del 0
    img.normalize(1,2);

    double productoria;
    double area_masc = tam_masc_x * tam_masc_y;
    //Recorremos la imagen pixel a pixel
    cimg_forXY(img, x, y){

        productoria = 1.0;

    //Obtenemos productoria dentro del vecindario establecido
        for(int i = -tam_masc_x/2; i<tam_masc_x/2 + 1; i++){
            for(int j = -tam_masc_y/2; j<tam_masc_y/2 + 1; j++){

                int cord_x = ( (x+i) >= 0 ) && ( (x+i) < img.width() ) ? (x+i) : x;
                int cord_y = ( (y+j) >= 0 ) && ( (y+j) < img.height() ) ? (y+j) : y;

                //cout<<"i:      "<<i<<" ||  j:     "<<j<<endl;
                //cout<<"Cord x: "<<cord_x<<" || Cord y: "<<cord_y<<endl;

                productoria = productoria * img(cord_x, cord_y);
            }
        }
        //cout<<"Productoria: "<<productoria<<endl;
        //getchar();

        //Aplicamos raiz enesima
        img(x,y) = pow(productoria, (1.0/area_masc) );
    }
    return img.normalize(0, 1);
}


/// FILTRO DE MEDIA CONTRA ARMONICA
//RECIBE:
//   img:      Imagen a filtrar (por seguridad usar DOUBLE)
//   tam_masc_x: tamanio de la mascara de filtrado en x
//   tam_masc_y: tamanio de la mascara de filtrado en y
//DEVUELVE:
//   Imagen filtrada
template <typename T>
CImg<T> filtrar_mediaContraArmonica(CImg<T> img, int Q = 0,
                                            int tam_masc_x = 3,
                                            int tam_masc_y = 3){

    double sumatoria_Q;
    double sumatoria_Q_mas_1;
    img.normalize(1,2);
    //Recorremos la imagen pixel a pixel
    cimg_forXY(img, x, y){
        sumatoria_Q = 0;
        sumatoria_Q_mas_1 = 0;

    //Obtenemos sumatorias dentro del vecindario establecido
        for(int i = -tam_masc_x/2; i<tam_masc_x/2 + 1; i++){
            for(int j = -tam_masc_y/2; j<tam_masc_y/2 + 1; j++){

                int cord_x = ( (x+i) >= 0 ) && ( (x+i) < img.width() ) ? (x+i) : x;
                int cord_y = ( (y+j) >= 0 ) && ( (y+j) < img.height() ) ? (y+j) : y;

                sumatoria_Q += pow(img(cord_x, cord_y), Q);
                sumatoria_Q_mas_1 += pow(img(cord_x, cord_y), Q + 1);
            }
        }

        //Aplicamos raiz enesima
        img(x,y) = sumatoria_Q_mas_1 / sumatoria_Q;
    }
    return img.normalize(0,1);
}


/// FILTRO DE MEDIANA
//RECIBE:
//   img:      Imagen a filtrar (cualquier tipo)
//   tam_masc_x: tamanio de la mascara de filtrado en x
//   tam_masc_y: tamanio de la mascara de filtrado en y
//DEVUELVE:
//   Imagen filtrada
template <typename T>
CImg<T> filtrar_mediana(CImg<T> img, int tam_masc_x = 3, int tam_masc_y = 3){

    //Recorremos la imagen pixel a pixel
    cimg_forXY(img, x, y){
        CImg<T> valores(tam_masc_x*tam_masc_y,1,1,1);
        int contador = 0;

    //Obtenemos valores dentro del vecindario establecido
        for(int i = -tam_masc_x/2; i<tam_masc_x/2 + 1; i++){
            for(int j = -tam_masc_y/2; j<tam_masc_y/2 + 1; j++){

                int cord_x = ( (x+i) >= 0 ) && ( (x+i) < img.width() ) ? (x+i) : x;
                int cord_y = ( (y+j) >= 0 ) && ( (y+j) < img.height() ) ? (y+j) : y;

                valores(contador)= img(cord_x, cord_y);
                contador ++;
            }
        }

        //Calculamos la mediana de los valores
        img(x,y) = valores.median();
    }
    return img;
}



/// FILTRO DE PUNTO MEDIO
//RECIBE:
//   img:      Imagen a filtrar (cualquier tipo)
//   tam_masc_x: tamanio de la mascara de filtrado en x
//   tam_masc_y: tamanio de la mascara de filtrado en y
//DEVUELVE:
//   Imagen filtrada
template <typename T>
CImg<T> filtrar_puntoMedio(CImg<T> img, int tam_masc_x = 3, int tam_masc_y = 3){

    //Recorremos la imagen pixel a pixel
    cimg_forXY(img, x, y){
        CImg<T> valores(tam_masc_x*tam_masc_y,1,1,1);
        int contador = 0;

    //Obtenemos valores dentro del vecindario establecido
        for(int i = -tam_masc_x/2; i<tam_masc_x/2 + 1; i++){
            for(int j = -tam_masc_y/2; j<tam_masc_y/2 + 1; j++){

                int cord_x = ( (x+i) >= 0 ) && ( (x+i) < img.width() ) ? (x+i) : x;
                int cord_y = ( (y+j) >= 0 ) && ( (y+j) < img.height() ) ? (y+j) : y;

                valores(contador)= img(cord_x, cord_y);
                contador ++;
            }
        }

        //Aplicamos promedio entre maximo y minimo
        img(x,y) = (valores.max() + valores.min()) / 2;
    }
    return img;
}


/// FILTRO MEDIAS ALFA RECORTADO
//RECIBE:
//   img:      Imagen a filtrar (cualquier tipo)
//   tam_masc_x: tamanio de la mascara de filtrado en x
//   tam_masc_y: tamanio de la mascara de filtrado en y
//   alfa:       cantidad de valores que elimina de cada extremo
//DEVUELVE:
//   Imagen filtrada
template <typename T>
CImg<T> filtrar_mediasAlfaRecortado(CImg<T> img, int alfa = 2, int tam_masc_x = 3, int tam_masc_y = 3){

    //Recorremos la imagen pixel a pixel
    cimg_forXY(img, x, y){
        CImg<T> valores(tam_masc_x*tam_masc_y,1,1,1);
        int contador = 0;

    //Obtenemos valores dentro del vecindario establecido
        for(int i = -tam_masc_x/2; i<tam_masc_x/2 + 1; i++){
            for(int j = -tam_masc_y/2; j<tam_masc_y/2 + 1; j++){

                int cord_x = ( (x+i) >= 0 ) && ( (x+i) < img.width() ) ? (x+i) : x;
                int cord_y = ( (y+j) >= 0 ) && ( (y+j) < img.height() ) ? (y+j) : y;

                valores(contador)= img(cord_x, cord_y);
                contador ++;
            }
        }

        //Quitamos valores extremos y promediamos
        valores.sort();
        T acumulador = 0;
        for(int i=alfa; i<valores.width() - alfa; i++){
            acumulador += valores(i);
        }
        img(x,y) = float(acumulador) / float(valores.width() - 2 * alfa);
    }
    return img;
}






///**************************************************************************///
///*********** FUNCIONES RELACIONADAS A LA TRANSFORMADA DE FOURIER **********///
///**************************************************************************///

/// CONVERSION (REAL, IMAGINARIO) => (MAGNITUD, FASE)
//RECIBE:
//   CImgList FFT: componente real e imaginaria de la
//                 transformada de Fourier de una imagen.
//DEVUELVE:
//   CImgList L : Espectro de magnitud y de fase de la TDF
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

            //La funcion "arg" DEVUELVE el argumento ( angulo) del numero complejo:
            fase(i,j)=arg(complejo);
            }
        }
    CImgList<double> L(magnitud, fase);
    return L;
}


/// CONVERSION (MAGNITUD, FASE => (REAL, IMAGINARIO)
//RECIBE:
//   CImgList L : Espectro de magnitud y de fase de la TDF
//DEVUELVE:
//   CImgList FFT: componente real e imaginaria de la
//                 transformada de Fourier de una imagen.
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



/// DISENIAR FILTRO (IDEAL, BW, GAUS, ETC)
//RECIBE:
//   img: imagen para la cual se quiere aplicar el filtro.
//   frecuencia_corte: frecuencia de corte del filtro
//   tipo: tipo de filtro a generar: |i=ideal|
//                                   |bwx=butterworth orden x|
//                                   |g = gauss|
//   origen_x: coordenada x del origen del filtro.
//   origen_y: coordenada y del origen del filtro.
//   Las coordenadas se usan para filtros tipo notch
//   dar las coordenadas segun la TDF ORIGINAL, NO la CENTRADA
//DEVUELVE:
//   filtro: filtro PASA BAJOS diseniado con los parametros de entrada
// Para filtros pasa/rechaza banda pasa altos, etc jugar con sumas y restas de filtros PB
CImg<double> get_filtro(CImg<double> img, double frecuencia_corte,
                        string tipo ="i",
                        float origen_x = 0, float origen_y = 0,
                        bool draw = false){
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
                        //filtro.get_mirror("x") +
                        //filtro.get_mirror("y") +
                        filtro.get_mirror("xy");

    //Mostramos filtro 2D
    //filtro_completo.display();
    //filtro_completo.get_shift(M/2, N/2, 0, 0, 2).display();

    //Mostramos filtro 3D
    if(draw){
        draw_3D_image(filtro_completo.get_shift(M/2,N/2,0,0,2) * 10);
    }

    return filtro_completo.normalize(0,1);

}


/// FILTRAR EN FRECUENCIA
//RECIBE:
//   img: imagen para la cual se quiere aplicar el filtro.
//   filtro: filtro generado con la funcion get_filtro
//DEVUELVE:
//   imagen filtrada: Imagen filtrada en frecuencia
CImg<double> filtrar_frecuencia(CImg<double> img, CImg<double> filtro, bool mostrar = false){

    //Obtenemos espectro de magnitud
    CImgList<double> espectro = RealImag2MagnitudFase(img.get_FFT());

//  Mostramos filtro
    if(mostrar){
        filtro.display("Filtro H(u,v)");
    }

//  Muestra espectro de magnitud antes de filtrado
    CImg<double> magnitud_antes(log(espectro[0]).normalize(0,255));
    if(mostrar){
         magnitud_antes.display("Espectro de Magnitud antes de Filtrar");
    }

    //Realizamos producto punto a punto H(u,v) F(u,v)
    cimg_forXY(espectro[0],i,j){
        espectro[0](i,j) = espectro[0](i,j) * filtro(i,j);
    }

    //  Muestra espectro de magnitud despues de filtrado
    CImg<double> magnitud_despues(log(espectro[0]).normalize(0,255));
    if(mostrar){
        (magnitud_antes,
         filtro,
         magnitud_despues).display("Espectro de magnitud antes y despues de filtrar");
    }
    //Volvemos al espacio de la imagen
    CImg<double> img_filtrada = ( MagnitudFase2RealImag(espectro).get_FFT(true) )[0];

    //Mostramos imagen original y filtrada
    (img, img_filtrada.display()).display("Imagen original y filtrada");

    return img_filtrada;
}
