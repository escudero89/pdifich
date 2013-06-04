#include <cassert>
#include <cmath>
#include <complex>
#include <ctime>
#include <iostream>
#include <cstring>

#include "../../CImg-1.5.4/CImg.h"
#include "PDI_functions.h"
#include "funciones.h"

#define EPSILON 0.00001
#define PI 3.14159265359
using namespace cimg_library;

// Comence a las 11:10
// Mi procedimiento sera recortar las monedas, e irlas analizando de a una en una
void get_amount_money(
    const char * filename,
    const int TOLERANCIA) {

    CImg<double> coins(filename);

    // Hacemos un color slicing del fondo (255, 255, 255)
    CImg<bool> mask_coins(cimg_ce::get_mask_from_RGB<int>(coins, 255, 255, 255, 10));

    // E invertimos para quedarnos con las monedas
    mask_coins = 1 - mask_coins;

    // Ahora aplico etiquetado de regiones
    CImg<int> coins_labeled(label_cc(mask_coins));

    // Aca voy guardando el valor de mis monedas (max 300)
    CImg<double> monedas(300, 1, 1, 1, 0);
    unsigned int kMonedaIdx = 0;

    // Un filtro de promediado
    CImg<double> f_promediado(7, 7, 1, 1, 1);
    double f_promediado_escala = 1.0 / (f_promediado.width() * f_promediado.height());

    // Mientras mi maximo no sea cero (el fondo)
    while (coins_labeled.max() > 0) {

        unsigned int x_min;
        unsigned int y_min;
        unsigned int x_max;
        unsigned int y_max;

        // Voy ahora sacando cada moneda por separado
        cimg_ce::get_sliced_object(coins_labeled, coins_labeled.max(), x_min, y_min, x_max, y_max);

        // Recorto de mi imagen original la moneda obtenida
        CImg<double> coin(coins.get_crop(x_min, y_min, x_max, y_max));

        // Desenfocamos la imagen
        CImg<double> coin_blurred(coin.get_convolve(f_promediado) * f_promediado_escala);

        /// MONEDA INDIVIDUAL
        /// Voy a analizar el canal del HUE para determinar el color del centro de la moneda
        // Para eso saco un pedazo central
        int x0_coin = coin_blurred.width() / 4;
        int x1_coin = x0_coin * 3;
        int y0_coin = coin_blurred.height() / 4;
        int y1_coin = y0_coin * 3;

        CImg<double> coin_center(coin_blurred.get_crop(x0_coin, y0_coin, x1_coin, y1_coin));
        
        // Vuelvo a desenfocar
        coin_center.convolve(f_promediado);
        coin_center *= f_promediado_escala;

        coin_center.RGBtoHSI();

        // La clasifico en acero_cobre, laton, cuproniquel (en saturacion)
        double tol = TOLERANCIA / 100.0;
        double satur_mean = coin_center.get_channel(1).mean();
        double hue_mean = coin_center.get_channel(0).mean();

        double satur_cupre = 0.05;
        double hue_laton = 34;

        // Es cuproniquel? 
        if (satur_mean > satur_cupre * (1 - tol) && satur_mean < satur_cupre * (1 + tol)) {
            std::cout << "Cuproniquel (GRIS), 1€.\n";
            // Ya la agrego
            monedas(kMonedaIdx) = 1;

        } else {
            // Es laton? monedas de 2 , 0.5, 0.2 y 0.1
            // Lo sacamos por su tamanho (area)
            double area = coin.width() * coin.height();

            if (hue_mean > hue_laton * (1 - tol) && hue_mean < hue_laton * (1 + tol)) {
                std::cout << "Laton (AMARILLO), ";

                // Reviso el borde asi ya la descarto (mas o menos 1/6 de altura)
                CImg<double> coin_border(
                    coin_blurred.get_crop(x0_coin, 0, x1_coin, 1.0/6.0 * coin_blurred.height()));

                double satur_border_mean = coin_border.get_RGBtoHSI().get_channel(1).mean();
                
                // Es cuproniquel? Si es asi, ya sabemos que es 2 euro
                if (satur_border_mean > satur_cupre * (1 - tol) && 
                    satur_border_mean < satur_cupre * (1 + tol)) {

                    std::cout << "2€\n";
                    monedas(kMonedaIdx) = 2;
                } else { // es de 0.5, 0.2 o 0.1?

                    // Valores experimentales del area de las monedas
                    const double AREA_50 = 92 * 92;
                    const double AREA_20 = 84 * 84;

                    if (area > AREA_50) {
                        std::cout << "0.5€\n";
                        monedas(kMonedaIdx) = 0.5;

                    } else if (area > AREA_20) {
                        std::cout << "0.2€\n";
                        monedas(kMonedaIdx) = 0.2;
                        
                    } else {
                        std::cout << "0.1€\n";
                        monedas(kMonedaIdx) = 0.1;
        
                    }
                }

            } else { // es acero banhado en cobre, o sea 0.01, 0.05, o 0.02
                std::cout << "Acero banhado en cobre (ROJO), ";

                // Comparamos tamanhos aca tambien
                const double AREA_05 = 80 * 80;
                const double AREA_02 = 71 * 71;

                 if (area > AREA_05) {
                        std::cout << "0.05€\n";
                        monedas(kMonedaIdx) = 0.05;

                } else if (area > AREA_02) {
                    std::cout << "0.02€\n";
                    monedas(kMonedaIdx) = 0.02;
                    
                } else {
                    std::cout << "0.01€\n";
                    monedas(kMonedaIdx) = 0.01;
    
                }
            }
        }

        // Al agregar moneda, aumento el indice
        kMonedaIdx++;

        // Muestro para analisis
        coin.display("Moneda analizada", 0);

        // Elimino el valor ya analizado de mi imagen
        coins_labeled = cimg_ce::replace_value_for(coins_labeled, coins_labeled.max());

    }
    
    // Valor total
    std::cout << "Valor total acumulado en la figura: " << monedas.sum() << "€.\n"; 

}



int main (int argc, char* argv[]) {

    srand(time(0));

    const char* _filename = cimg_option("-i", "training_old/coins/01.jpg", "Imagen");
    
    const int _tolerancia = cimg_option("-tol", 50, "Tolerancia +-(0~100\%)");
   
    get_amount_money(_filename, _tolerancia);

    return 0;
}