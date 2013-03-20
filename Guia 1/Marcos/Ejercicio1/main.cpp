#include <iostream>
#include "../../../CImg-1.5.4/CImg.h"

using namespace cimg_library;
using namespace std;

/*
How CImg store pixel in memory?

When an image is instanced, all its pixel values are stored in
memory at the same time. A CImg<T> is basically a 4th-dimensional array
(width,height,depth,dim), and its pixel data are stored linearly
 in a single memory buffer of general size (width*height*depth*dim).
So, a color image with dim=3 and depth=1, will be stored in memory
as :R1R2R3R4R5R6......G1G2G3G4G5G6.......B1B2B3B4B5B6....
(i.e following a 'planar' structure)and not as
R1G1B1R2G2B2R3G3B3... (interleaved channels)

*/
int main(){

    cout << "Hello world!" << endl;
    CImg<unsigned char> img_original("cameraman.tif");

    img_original.display("Imagen Original");

    /* Coordenadas a recortar */
    int cordx0=90,
        cordy0=40,

        cordx1=90,
        cordy1=80,

        cordx2=140,
        cordy2=80,

        cordx3=140,
        cordy3=40,

        dx,
        dy;

    dx = cordx3 - cordx0;
    dy =  cordy1 - cordy0;


    CImg<unsigned char> img_modificada(dx,dy,1,1);

        for(int i = cordx0; i < cordx3; i++){

            for(int j = cordy0; j < cordy1; j++){

                img_modificada(i - cordx0, j - cordy0) = img_original(i,j);
                img_original(i,j) = 128;

            }
        }

    img_modificada.display("Imagen Modificada");
    img_original.display("Imagen Original");

   return 0;
}
