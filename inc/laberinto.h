#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int ancho, alto;
int * lab;
bool * visitado;

typedef enum {
	invalido = 0b0000,
	arriba = 0b0001,
	abajo = 0b0010,
	izquierda = 0b0100,
	derecha = 0b1000
} direccion;

typedef struct {
	int x;
	int y;
} posicion;

posicion salida, salidaAlternativa;

void FijarSemilla(int seed);
direccion DireccionRandom(void);
direccion InvertirDireccion(direccion d);
posicion Mover(posicion p, direccion d);
bool VerificarPosicion(posicion p);
bool LadosTodosVisitados(posicion p);
void CrearLaberinto(void);
