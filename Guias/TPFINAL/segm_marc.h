#include <vector>

void media(CImg<bool> img, int & media_x, int & media_y){

    double m_x = 0;
    double m_y = 0;
    int contador = 0;

    cimg_forXY(img, i, j){

        if(img(i,j) == 1){
            m_x += i;
            m_y += j;
            contador++;
        }

    }

    media_x = (int) m_x/contador;
    media_y = (int) m_y/contador;


}

void varianza(CImg<bool> img, int media_x, int media_y, int &var_x, int &var_y){

    double v_x = 0;
    double v_y = 0;
    int contador = 0;

    cimg_forXY(img, i, j){

        if(img(i,j) == 1){
            v_x += pow(i - media_x, 2);
            v_y += pow(j - media_y, 2);

            contador++;
        }

    }

    var_x = (int) v_x/contador;
    var_y = (int) v_y/contador;

}

extern int roi_ulx; //roi upper left x
extern int roi_uly; //roi upper left y
extern int roi_lrx; //roi lower right y
extern int roi_lry; //roi lower right y

CImg<bool> roi(CImg<bool> img, int contador) {

    //Obtenemos media y varianza de los puntos de la imagen binaria
    int media_x = 0;
    int media_y = 0;
    media(img, media_x, media_y);

    int var_x = 0;
    int var_y = 0;
    varianza(img, media_x, media_y, var_x, var_y);

    //Transformamos varianza en desvio por un factor de ampliacion de la roi
    double alfa_roi = 1.5;
    var_x = sqrt(var_x) * alfa_roi;
    var_y = sqrt(var_y) * alfa_roi;

    //Definimos esquinas superior izquierda e inferior derecha de la roi
    int sup_izq_x = (media_x - var_x) < 0 ? 0 : (media_x - var_x);
    int sup_izq_y = (media_y - var_y) < 0 ? 0 : (media_y - var_y);

    int inf_der_x = (media_x + var_x) > img.width() ? img.width() : (media_x + var_x);
    int inf_der_y = (media_y + var_y) > img.height() ? img.height() : (media_y + var_y);

    //Actualizamos variables globales de ROI
    roi_ulx = sup_izq_x; //roi upper left x
    roi_uly = sup_izq_y; //roi upper left y
    roi_lrx = inf_der_x; //roi lower right x
    roi_lry = inf_der_y; //roi lower right y

//   Generamos imagen copia de img pero que permita color, para mostrar ROI
     int color[3] = {0, 255, 0};
     CImg<unsigned char> img_color(img.width(),img.height(),1,3);

     cimg_forXY(img,i,j){
        if(img(i,j) == 1){
            img_color(i,j,0,0) = (char) 255;
             img_color(i,j,0,1) = (char) 255;
             img_color(i,j,0,2) = (char) 255;
         }
     }

     //Dibujamos ROI, solo a motivos de control
     img_color.draw_rectangle(roi_ulx,
                              roi_uly,
                              roi_lrx,
                              roi_lry,
                              color, 1, 2).save("Temp/mascara.png", contador);


     CImg<int> img_int(label_cc(img));

     std::vector<int> array;
     array.resize(img.width() * img.height(), 0);

     unsigned int array_pos = 0;

    for (unsigned int x = sup_izq_x ; x <= inf_der_x; x++) {
      for (unsigned int y = sup_izq_y ; y <= inf_der_y ; y++) {

          unsigned int img_xy = img_int(x, y);

            // Pertenece a una clase de objeto != 0
            if (img_xy != 0) {
              // Me fijo si ya no lo habia guardado
              bool sin_almacenar = true;

              for (unsigned int k = 0; k <= array_pos ; k++) {
                if (array[k] == img_xy) {
                  sin_almacenar = false;
                  break;
                }
              }

              if (sin_almacenar) {
                array[array_pos] = img_xy;
                array_pos++;
              }
            }
      }
    }

      // Vuelvo a recorrer por fuera de los limites
    cimg_forXY(img_int, x, y) {
        // Pertenece a una clase de objeto != 0
        if (img_int(x, y) != 0) {
          // Y si estoy fuera de los limites
          if (!(x >= sup_izq_x && x <= inf_der_x && y >= sup_izq_y && y <= inf_der_y)) {
              bool inside = false;

              // Reviso si ya tenia el elemento dentro del roi
              for (unsigned int x_arr = 0 ; x_arr <= array_pos ; x_arr++) {
                if (array[x_arr] == img_int(x, y)) {
                  inside = true;
                  break;
                }
              }

              // Si estaba el objeto en el roi, lo dejo en uno
              if (inside) {
                img(x, y) = 1;
              } else {
                img(x, y) = 0;
              }
            }
        }
    }

    // Retornamos la ROI cropeada de la img original
    return img;//.get_crop(sup_izq_x, sup_izq_y, inf_der_x, inf_der_y);

}


// Fusiona la mascara que le pasas con una que se forma por la saturacion de la
// imagen base con el fondo de noche
CImg<bool> fusionar_con_diff_saturacion(
  CImg<bool> base,
  CImg<double> image,
  CImg<double> sat_old) {

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

    std::cout << "\n>> Usando la funcion de Segmentacion de: ROI mejorado <<\n";

    // Por alguna razon el contador arranca desde 1 en el main. Aca es necesario
    // que arranque en cero.
    contador = contador - 1;

    //Nos guardamos las dimensiones originales de la imagen para la reconstruccion
    int original_width = img1.width();
    int original_height = img1.height();

    //El valor de esta variable indica cada cuantos frames se recalcula la ROI.
    int frames_roi = 1;

    //Cada x frames actualizamos la ROI
    if( (contador % frames_roi) != 0){
        img1.crop(roi_ulx,roi_uly,roi_lrx,roi_lry);
        img2.crop(roi_ulx,roi_uly,roi_lrx,roi_lry);
    }

    //Suavizamos la imagen para hacer la segmentacion menos sensible a detalles
    CImg<double> filtro_suavizado(tam_suavizado, tam_suavizado, 1, 3, 1);
    img1.convolve(filtro_suavizado);
    img2.convolve(filtro_suavizado);

    //Creamos una imagen con el valor absoluto de la diferencia de las dos imagenes de entrada.
    CImg<double> diferencia(abs(img1 - img2));

    //Suavizamos nuevamente para homogenenizar
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
    mascara = fusionar_con_diff_saturacion(mascara, img1, sat_old);

    //Aplicamos erosion y dilatacion para eliminar puntos espureos
    mascara.erode(20);
    mascara.dilate(20);

    //Si es ==  0, actualizamos ROI
    if( (contador % frames_roi) == 0){
        mascara = roi(mascara, contador);
    }

    CImg<bool> mascara_reconstruida(mascara);

//    (mascara_reconstruida * 255).save("Temp/mascara_reconstruida.png", contador);

    return mascara_reconstruida;

}
