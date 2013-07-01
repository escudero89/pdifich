///FUNCION SEGMENTAR:
///     INPUT:
///         img1: Imagen de entrada 1 (Formato RGB)
///         img2: Imagen de entrada 2 (Formato RGB)
///         tam_suavizado: tamanio de mascara utilizado para suavizar la diferencia de imagenes
///         umbral_segmentacion: umbral que define que parte pasa y que parte no en la segmentacion

///     OUTPUT:
///         Mascara booleana con la imagen segmentada
CImg<bool> segmentar(
    CImg<double> img1, 
    CImg<double> img2,
    unsigned int tam_suavizado = 7,
    double umbral_segmentacion = 0.3){

    std::cout << "\n>> Usando la funcion de Segmentacion de: MARCUS <<\n";

    //Suavizamos la imagen para hacer la segmentacion menos sensible a detalles
     CImg<double> filtro_suavizado(tam_suavizado, tam_suavizado, 1, 3, 1);
     img1.convolve(filtro_suavizado);
     img2.convolve(filtro_suavizado);

    //Creamos una imagen con el valor absoluto de la diferencia de las dos imagenes de entrada.
     CImg<double> diferencia(abs(img1 - img2));

    //Suavizamos nuevamente para eliminar pequenios puntos
     diferencia.convolve(filtro_suavizado).normalize(0,1);

    //Aplicamos umbralizacion
     CImg<bool> mascara(img1.width(), img1.height(), 1, 1);

     cimg_forXY(mascara, x, y){
         mascara(x,y) = (pow(diferencia(x, y, 0), 2)+
                         pow(diferencia(x, y, 1), 2)+
                         pow(diferencia(x, y, 2), 2) > pow(umbral_segmentacion, 2)) ? 1 : 0;
     }

     return mascara;

}
