#include <iostream>
#include "../../../CImg-1.5.4/CImg.h"

using namespace cimg_library;
using namespace std;


int main(){

    ///Inciso 1
   //Cargamos imagenes
   CImg<unsigned char> imagen1("../../../img/camino.tif");
   CImg<unsigned char> imagen2("../../../img/casilla.tif");

   //Mostramos información
   imagen1.print();
   cout<<endl;
   imagen2.print();

   cout<<endl<<endl;
/*
   imagen1.stats();// (no se bien que hace)
   imagen2.stats();// (no se bien que hace)
*/
#if 0
   ///Inciso 2
   //Modo de visualizacion directo
   imagen1.display();
   imagen2.display();

   //Modo de visualizacion por ventana
   CImgDisplay ventana1(imagen1, "Ventana para imagen 1", 0);
   getchar();

   CImgDisplay ventana2(imagen2, "Ventana para imagen 2", 0);
   getchar();
#endif

#if 0
   ///Inciso 3  CImgList

 /*  CImgList	(	const unsigned int 	n,  //Number of images
                    const unsigned int 	width,
                    const unsigned int 	height = 1,
                    const unsigned int 	depth = 1,
                    const unsigned int 	spectrum = 1
                )
Pixel values are not initialized and may probably contain garbage.
*/
    CImgList<unsigned char> L1(2,imagen1.width(), imagen1.height(),1,3);
    L1.insert(imagen1,0); //tambien podría usar L1.push_back(imagen1);
    L1.insert(imagen2,1);
    L1.get_select("CImgList");

#endif


   return 0;
}
