#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "./inc/laberinto.h"

#define colorNORM  "\x1B[0m"
#define colorROJO  "\x1B[31m"
#define colorVERD  "\x1B[32m"

const int coutValores[] = {
	254, 223, 220, 186,
	'<', 188, 187, 185,
	'>', 200, 201, 204,
	205, 202, 203, 206
};

int main(int argc, char **argv)
{
	// -----------------------------
	FijarSemilla(time(NULL));
	ancho = 15; alto = 15;
	CrearLaberinto();
	
	// -----------------------------
	for(int i = 0; i < ancho*alto; i ++)
	{
		if(i % ancho == 0 && i != 0) printf("\n");
		if(i == 0) printf(colorROJO);
		else if(i == salida.y*ancho + salida.x) printf(colorVERD);
		else printf(colorNORM);
		printf("%c", coutValores[lab[i]]);
	}
	getch();
	return 1;
}
