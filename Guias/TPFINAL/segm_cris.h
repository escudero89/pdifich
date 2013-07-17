#include <sstream>
// Le pasas una cadena tipo "dibujo", una extension ".bmp", un contador "334" y la cantidad de ceros "6"
// devuelve "dibujo_000334.bmp"
std::string add_number_to_file(
    std::string cadena,
    std::string extension,
    unsigned int contador,
    unsigned int cant_zeros = 6
    ) {

    unsigned int zeros = 0;

    std::stringstream ss;
    ss << contador;
    std::string number(ss.str());

    while (cant_zeros - zeros > 0) {
        double val = 1.0 * contador / pow(10, zeros);
        if (val < 1) {
            // comienzo a agregar ceros
            number = "0" + number;
        } 
        zeros++;
    }

    return cadena + "_" + number + extension;
}

// Fusiona la mascara que le pasas con una que se forma por la saturacion de la 
// imagen base con el fondo de noche
CImg<bool> fusionar_con_diff_saturacion(
    CImg<bool> base, 
    CImg<double> image, 
    CImg<double> sat_old,
    unsigned int contador) {

    std::string f_fusionmask("mascara_acoplada");

    // Me quedo con su canal de saturacion
    CImg<double> sat(image.get_RGBtoHSI().get_channel(1));

    // Desenfoco ambas imagenes
    CImg<double> filtro_suavizado(15, 15, 1, 3, 1);

    sat_old.convolve(filtro_suavizado);
    sat.convolve(filtro_suavizado);

    // Las umbralizo
    sat.threshold(sat_old.mean());
    sat_old.threshold(sat_old.mean());

    // Hago la diferencia
    sat = abs(sat - sat_old);
    
    // Umbralizo la saturacion (igual tiene valores 1 y 0)
    CImg<bool> sat_bool(sat);

    // Recorro y voy acoplando con la mascara ya existente
    cimg_forXY(base, x, y) {
        base(x, y) = (base(x, y) == 0 && sat_bool(x, y) == 1) ? 1 : base(x, y);
    }

    return base;
}

///FUNCION SEGMENTAR:
///     INPUT:
///         img1: Imagen de entrada 1 (Formato RGB)
///         img2: Imagen de entrada 2 (Formato RGB)
///         img3: Imagen de entrada 3 (Formato RGB)
///         tam_suavizado: tamanio de mascara utilizado para suavizar la diferencia de imagenes
///         umbral_segmentacion: umbral que define que parte pasa y que parte no en la segmentacion

///     OUTPUT:
///         Mascara booleana con la imagen segmentada
CImg<bool> segmentar(
    CImg<double> img1, 
    CImg<double> img2,
    CImg<double> img3,
    unsigned int contador,
    unsigned int tam_suavizado = 7,
    double umbral_segmentacion = 0.3){
    // image, nighttime_bg, daytime_bg, contador, option_pseg, option_useg

    std::cout << "\n>> Usando la funcion de Segmentacion de: CRISTIAN <<\n";

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

    // Fusiono con la mascara de saturacion (le paso el canal de saturacion de background night)
    CImg<double> sat_old(img2.get_RGBtoHSI().get_channel(1));
    mascara = fusionar_con_diff_saturacion(mascara, img1, sat_old, contador);

    mascara.erode(9);
    mascara.dilate(9);

    // Guardamos la mascara
    (mascara * 255).save("Temp/mascara.png", contador);
    
    return mascara;

}