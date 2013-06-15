#!/bin/sh

echo "$(tput setaf 3)Nota: Recuerda ingresar el parámetro sin '.txt'$(tput sgr0)\n";

echo "$(tput setaf 1)Removiendo viejo directorio 'Temp/$1'...$(tput sgr0)\n";
rm Temp/$1 -fR;

echo "$(tput setaf 6)Creando nuevo directorio 'Temp/$1'...$(tput sgr0)\n";
mkdir Temp/$1;

echo "$(tput setaf 6)Aplicando procesamiento a imágenes según '$1.txt'...$(tput sgr0)\n";
./images_to_video -imagesf "$1.txt";

echo "$(tput setaf 7)Convirtiendo a video las imágenes en 'Temp/$1' [salida: output_$1.mp4]...$(tput sgr0)\n";
avconv -f image2 -i Temp/$1/resultado_%06d.png Videos/cimg/output_$1.mp4;

echo -n "$(tput setaf 1)Desea borrar el directorio 'Temp/$1'?$(tput sgr0) [Y/n] ";
read opcion;

if [[ $opcion == "n" ]]; then
	echo "$(tput setaf 6)Directorio ignorado, imágenes guardadas en 'Temp/$1'.$(tput sgr0)";
else
	echo "$(tput setaf 1)Removiendo directorio trás conversión 'Temp/$1'...$(tput sgr0)\n";
	rm Temp/$1 -fR;
fi

echo "\nFin del proceso. Video creado en 'Videos/cimg/output_$1.mp4'.";
