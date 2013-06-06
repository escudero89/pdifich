#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <complex>
//#include <CImg.h>
using namespace std;
using namespace cimg_library;

#define EVITAR_PIXEL -123.321
#define EPSILON 0.00001


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


/// FITRO PARA IMAGENES A COLOR (robado a cristian):
// usar funcion: filtrar_color_impulsivo(...);
double get_R_from_window_helper(CImg<double> S, CImg<double> &R, unsigned int &i_min, unsigned int &j_min) {
    // Saco la distancia promedio, y voy a determinar para mi menor aquellos pixeles
    // que sean menores o iguales a esta distancia
    double promedio = 0;
    double R_min = 1/EPSILON;

    // En cada cuadrado de R
    cimg_forXY(R, x, y) {
        // Cuando tengo EVITAR_PIXEL, no utilizo ese cuadrante
        if (S(x, y, 0) != EVITAR_PIXEL) {
            R(x, y) = 0;

            // No aplico raiz cuadrada, si total es para comparar
            cimg_forXYC(S, s, t, c) {
                // Si S(s, t, c) = EVITAR_PIXEL, no lo contabilizo
                if (S(s, t, c) != EVITAR_PIXEL) {
                    R(x, y) += pow(S(s, t, c) - S(x, y, c), 2);
                }
            }

            promedio += R(x, y);

            // Voy guardando el indice del elemento de menor valor
            if (R(x, y) < R_min) {
                i_min = x;
                j_min = y;
                R_min = R(x, y);
            }

        } else {
            R(x, y) = EVITAR_PIXEL;
        }
    }

    return promedio /= (R.width() * R.height());
}

/// A partir de una ventana, me construye la distancia acumulada en ella usando distancia euclideana
// Para evitar que los pixeles impulsivos me muevan el "pixel central elegido", elimino los que
// esten a mayor distancia
CImg<double> get_R_from_window(CImg<double> S, unsigned int &i_min, unsigned int &j_min) {

    CImg<double> R(S.width(), S.height());

    double promedio;

    // Obtengo R y S
    promedio = get_R_from_window_helper(S, R, i_min, j_min);

    // Recorro otra vez, pero esta vez buscando el minimo y salteando el resto
    cimg_forXY(R, x, y) {
        if (R(x, y) > promedio) {
            cimg_forC(S, c) {
                S(x, y, c) = EVITAR_PIXEL;
            }
        }
    }

    // Vuelvo a llamar a la funcion para obtener una nueva ventana
    get_R_from_window_helper(S, R, i_min, j_min);

    return R;

}

/// Aplica un filtro basado en un ordenamiento usando distancias acumuladas
// Trabaja con una vencidad S de mxn
CImg<double> filtrar_color_impulsivo(CImg<double> base, unsigned int m = 3, unsigned int n = 3) {

    CImg<double> R;
    CImg<double> S;

    // Para determinar el tamanho de las ventanas
    int step_x = m / 2;
    int step_y = n / 2;

    // Recorro la base y voy tomando ventanas
    cimg_forXY(base, x, y) {

        // Esto es para evitar que se me vaya del rango
        int x0 = (x - step_x < 0) ? 0 : x - step_x;
        int y0 = (y - step_y < 0) ? 0 : y - step_y;
        int x1 = (x + step_x >= base.width()) ? base.width() - 1 : x + step_x;
        int y1 = (y + step_y >= base.height()) ? base.height() - 1 : y + step_y;

        // Obtengo la ventana S (con todos sus espectros)
        S = base.get_crop(x0, y0, x1, y1);

        // Obtengo la ventana R de distancias acumuladas
        unsigned int i_min = 0;
        unsigned int j_min = 0;

        R = get_R_from_window(S, i_min, j_min);

        // Le asigno el menor valor a f(x, y)
        cimg_forC(base, c) {
            base(x, y, c) = S(i_min, j_min, c);
        }

    }

    return base;

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


///**************************************************************************///
///***************************DETECTORES DE BORDES **************************///
///**************************************************************************///


/// DETECTAR BORDES CON DERIVADAS
// RECIBE:
//  img:  imagen con bordes a detectar

//  tipo: tipo de mascara a usar
//        strings validos: | roberts| prewitt | sobel | laplaciano | LoG |

//  orientacion: si es un metodo de gradiente se puede elegir entre Gx Gy o magnitud
//               string validos: | Gx: gradiente en X | Gy: gradiente en Y |magnitud: Magnitud|
//               No usar magnitud si usas laplaciano o LoG

//  umbral: umbral para la binarizacion, si es -1 lo hace automaticamente

//  binarizar: si es true devuelve la imagen binaria, si es false no.
//
//DEVUELVE
//   imagen filtrada: binaria si binarizacion es true, o en double si binarizacion es false
CImg<double> bordes(CImg<double> img, string tipo = "prewitt",string orientacion = "magnitud", double umbral = -1, bool binarizar = true){

    CImg<int> mascara(2,2,1,1);
    CImg<double> resultado(img.width(),img.height(),1,1);


    if(tipo == "roberts"){
        if(orientacion == "Gx"){
            CImg<int> mascara_x(2, 2, 1, 1, -1,0,0,1);
            mascara = mascara_x;
        }

        if(orientacion == "Gy"){
            CImg<int> mascara_y(2, 2, 1, 1,  0,-1,1,0);
            mascara = mascara_y;
        }

    }else if(tipo == "prewitt"){

        if(orientacion == "Gx"){
            CImg<int> mascara_x(3, 3, 1, 1, -1,-1,-1,
                                             0, 0, 0,
                                             1, 1, 1);
            mascara = mascara_x;
        }

        if(orientacion == "Gy"){
            CImg<int> mascara_y(3, 3, 1, 1,  -1, 0, 1,
                                             -1, 0, 1,
                                             -1, 0, 1);
            mascara = mascara_y;
        }

    }else if(tipo == "sobel"){

        if(orientacion == "Gx"){
            CImg<int> mascara_x(3, 3, 1, 1, -1,-2,-1,
                                             0, 0, 0,
                                             1, 2, 1);
            mascara = mascara_x;
        }

        if(orientacion == "Gy"){
            CImg<int> mascara_y(3, 3, 1, 1,  -1, 0, 1,
                                             -2, 0, 2,
                                             -1, 0, 1);
            mascara = mascara_y;
        }

    } else if(tipo == "laplaciano"){

        if(orientacion == "Gx"){
            CImg<int> mascara_x(3, 3, 1, 1, -1,-1,-1,
                                            -1, 8,-1,
                                            -1,-1,-1);
            mascara = mascara_x;
        }

        if(orientacion == "Gy"){
            CImg<int> mascara_y(3, 3, 1, 1,   0, -1, 0,
                                             -1,  4, -1,
                                              0, -1, 0);
            mascara = mascara_y;
        }

    } else if(tipo == "LoG"){

        if(orientacion == "Gx"){
            CImg<int> mascara_x(5, 5, 1, 1,  0, 0,-1, 0, 0,
                                             0,-1,-2,-1, 0,
                                            -1,-2,16,-2,-1,
                                             0,-1,-2,-1, 0,
                                             0, 0,-1, 0, 0);
            mascara = mascara_x;
        }

        if(orientacion == "Gy"){
            CImg<int> mascara_y(3, 3, 1, 1,   0, -1, 0,
                                             -1,  4, -1,
                                              0, -1, 0);
            mascara = mascara_y;
        }

    }else{
        cout<<"TIPO DE DETECTOR DE BORDE INVALIDO, ESCRIBI BIEN EL NOMBRE!"<<endl;
        getchar();
    }


    if(orientacion == "magnitud"){
        CImg<double> Gx (bordes(img, tipo, "Gx", umbral, false));
        CImg<double> Gy (bordes(img, tipo, "Gy", umbral, false));

        cimg_forXY(img,i,j){
            //Calculamos la magnitud del gradiente
            resultado(i,j) = sqrt( pow(Gx(i,j), 2) + pow(Gy(i,j), 2) );
        }

    }else{
        //Convolucionamos
        resultado = img.get_convolve(mascara);
        resultado.normalize(0,1);
    }

    //Si pedimos binarizar aplicamos umbrales
    if(binarizar == true){

        //Si el umbral es -1 usamos como umbral la media.
        if(umbral == -1){
            //Calculamos umbral
            double media = 0;
            double desvio = sqrt(resultado.variance_mean(0, media));
            umbral = media + 1.5 * desvio;
        }

        //Umbralizamos
        cimg_forXY(resultado,i,j){
            resultado(i,j) = resultado(i,j) > umbral ? 1 : 0;
        }
    }

    return resultado;

}


/// TRANSFORMADA DE HOUGH CON ESPECIFICACION DE THETA Y RHO

CImg<double> my_hough(CImg<double> img, bool inverse=false,
                      double theta_deseado = 0, double rho_deseado = 0,
                      double tolerancia_theta = INFINITY, double tolerancia_rho = INFINITY ) {

  CImg<double> iHough(img); iHough.fill(0.0);
  const unsigned M = img.width(),
                 N = img.height();

  double max_rho = sqrt(float(pow(N-1,2)+pow(M-1,2))), //maximo valor posible de radio se da en la diagonal pcipal
         step_rho = 2.*max_rho/(N-1), //paso en eje rho (rho=[-max_rho , max_rho])
         step_theta = M_PI/(M-1),     //paso en eje theta (M_PI=pi) (theta=[-90,90])
         rho, theta;

  if (!inverse){
        int r;  // radio mapeado en los N pixeles
        cimg_forXY(img,y,x){

        if (img(y,x) > 0.5){

            for (int t=0; t<M; t++) { //calculo rho variando theta en todo el eje, con x e y fijo
              theta=t*step_theta-M_PI/2;  // mapea t en [0,M-1] a t en [-90,90]
              rho=x*cos(theta)+y*sin(theta); // calcula rho para cada theta
              r=floor((rho+max_rho)/step_rho+.5); // mapea r en [-max_rho , max_rho] a r en [0,N-1] el floor(r+.5) sirve para redondear

              if((abs(theta - theta_deseado) < tolerancia_theta) and (abs(rho - rho_deseado) < tolerancia_rho)){

                iHough(t,r)+= 1; // suma el acumulador

              }

            }
        }
    }
  }else{
    const double blanco[1] = {255.f};
    float x0, x1, y0, y1;
    cimg_forXY(img,t,r){
      if (img(t,r) > 0.5) {
        theta=t*step_theta-M_PI/2;   // mapea t en [0,M-1] a t en [-90,90]
        rho=r*step_rho-max_rho;      // mapea r en [0,N-1] a r en [-max_rho,max_rho]
        if (theta>-M_PI/2 && theta<M_PI/2){
	  y0=0; y1=M-1;
          x0=rho/cos(theta);      // calcula y para y=0
          x1=rho/cos(theta)-(M-1)*tan(theta); // calcula y para y=M-1
	}else{
	  x0=0; x1=N-1;
          y0=rho/sin(theta);      // calcula y para x=0
          y1=rho/sin(theta)-(N-1)/tan(theta); // calcula y para x=M-1
	}
	//cout<<endl<<"("<<t<<","<<r<<")->("<<theta<<","<<rho<<") "<<"("<<y0<<","<<x0<<")->("<<y1<<","<<x1<<")"<<endl;
        iHough.draw_line(y0,x0,y1,x1,blanco); // dibuja una línea de (0,y0) a (M-1,y1)
      }
    }
  }
  return iHough;
}


/// FUNCION QUE DEVUELVE IMAGEN BINARIA CON SUS N MAXIMOS
//RECIBE:
//  cord_x: cordenada x
//  cord_y: cordenada y
//  puntos: Imagen con coordenadas de los puntos para calcular distancias
//DEVUELVE:
//  imagen con distancia de MANHANTAN de cada punto de la imagen puntos
//  al punto definido por las coordenadas x e y
//
//NOTA: Solo para ser usada por funcion n_maximos definida abajo
int distancia_minima(int cord_x, int cord_y, CImg<int> puntos){

    CImg<int> distancias(puntos.width(),1,1,1,0);

    cimg_forX(distancias, i){

        distancias(i) = abs(cord_x - puntos(i,0)) + abs(cord_y - puntos(i,1));

    }

    return distancias.min();

}

/// FUNCION QUE DEVUELVE IMAGEN BINARIA CON SUS N MAXIMOS
//RECIBE:
//  img: Imagen a computar maximos
//  n:   Cantidad de maximos a encontrar
//  separacion: Distancia de manhattan entre maximos
//DEVUELVE:
//  imagen binaria todos ceros y 1's en los maximos
//
//NOTA: utiliza funcion distancia_minima definida arriba
template<typename T>
CImg<T> n_maximos(CImg<T> img , int n, int separacion){

    int contador = 0;
    int maximo_k = 1;
    T max;
    img = img * (-1);
    CImg<T> maximos(img.width(), img.height(),1,1,0);
    CImg<T> detectados(n,2,1,1,0);

    while(contador < n){
        max = img.kth_smallest(maximo_k);
        maximo_k++;

        cimg_forXY(img,i,j){

            if ( (img(i,j) == max) and (contador < n) and (distancia_minima(i,j, detectados) > separacion)) {

                maximos(i,j) =  1;

                //Guardamos las coordenadas de los puntos ya detectados
                detectados(contador, 0) = i;
                detectados(contador, 1) = j;

                //Aumentamos el contador de maximos detectados
                contador ++;
            }

        }

    }

    return maximos;
}


/// SEGMENTADO DE COLOR
//RECIBE:
//  img: Imagen RGB a segmentar
//  r g b : valores del color buscado
//  delta: rango permitido de colores
//DEVUELVE:
//  imagen binaria de segmentacion
//
CImg<double> color_slicing(CImg<double> img, double r, double g, double b, double delta){
    CImg<double> mascara(img.width(), img.height(), 1, 1);

    img.normalize(0,1);

    cimg_forXY(img,x,y){

        double distancia = pow( pow((img(x,y,0) - r), 2.0) +
                                pow((img(x,y,1) - g), 2.0) +
                                pow((img(x,y,2) - b), 2.0), (1.0/3));


//        cout<<"img R: "<<img(x,y,0)<<endl;
//        cout<<"img G: "<<img(x,y,0)<<endl;
//        cout<<"img B: "<<img(x,y,0)<<endl;
//
//        cout<<"Diferencia al cuadrado de r "<<pow((img(x,y,0) - r), 2.0)<<endl;
//        cout<<"Diferencia al cuadrado de g "<<pow((img(x,y,1) - g), 2.0)<<endl;
//        cout<<"Diferencia al cuadrado de b "<<pow((img(x,y,2) - b), 2.0)<<endl;
//
//        cout<<"Distancia: "<<distancia<<endl;

        mascara(x,y) = (distancia < delta) ? 1 : 0;

    }

    return mascara;

}


/// UNIQUE PARA IMAGENES
//RECIBE:
//  img: Imagen
//DEVUELVE:
//  Vector con los valores de la imagen no repetidos
//NOTA: Usada para contar dsps de componente_conectada
template<typename T>
vector<T> unique_element_image(CImg<T> img){
    vector<int> V;
    cimg_forXY(img, x,y){
        if( V.end() == find(V.begin(), V.end(), img(x,y)) ){
            V.push_back(img(x,y));
        }
    }

    return V;
}

/// DIBUJAR CIRCULOS CENTRALES EN IMAGENES SEGMENTADAS
//RECIBE:
//  img_seg:        Imagen segmentada binaria
//  img_original:   Imagen original
//  m n:            tamanio de mascara
//  cant_circulos:  cantidad de circulos a dibujar
//  sep:            separacion minima entre circulos
//DEVUELVE:
//  Vector con los valores de la imagen no repetidos
//NOTA: Usada para contar dsps de componente_conectada
template<typename T>
CImg<T> dibujar_circulos_centrales(CImg<bool> img_seg, CImg<T> img_original,
                                   int tam_m, int tam_n, int cant_circulos, int sep){

    const unsigned char color[] = { 0,255,0 };
    CImg<bool> mascara(tam_m, tam_n, 1, 1);

    //Convolucionamos
    CImg<int> valores(img_seg.get_convolve(mascara));
    valores.display("Convolucionado");

    //Obtenemos N centros
    valores = n_maximos(valores, cant_circulos, sep);
    valores.display("N maximos");

    //Dibujamos circulos
    cimg_forXY(valores, x, y){
        if( valores(x,y) ){
            img_original.draw_circle(x,y,(tam_m + tam_n)/2, color, 1, 4);
        }
    }

    img_original.display();

    return img_original;
}


