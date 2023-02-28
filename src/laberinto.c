#include "../inc/laberinto.h"

void FijarSemilla(int seed) { srand(seed); }

direccion DireccionRandom() { return (direccion)(1 << (rand() % 4)); }

direccion InvertirDireccion(direccion d)
{
	if(d == arriba) return abajo;
	else if(d == abajo) return arriba;
	else if(d == derecha) return izquierda;
	else if(d == izquierda) return derecha;
	return invalido;
}

posicion Mover(posicion p, direccion d)
{
	if(d == arriba) {
		if(p.y > 0) p.y --;
	}
	else if(d == abajo) {
		if(p.y < alto-1) p.y ++;
	}
	else if(d == izquierda) {
		if(p.x > 0) p.x --;
	}
	else if(d == derecha) {
		if(p.x < ancho-1) p.x ++;
	}
	return p;
}

bool VerificarPosicion(posicion p)
{
	if(p.x < 0 || p.x > ancho-1) return false;
	if(p.y < 0 || p.y > alto-1) return false;
	if(visitado[p.y*ancho + p.x]) return false;
	return true;
}

bool LadosTodosVisitados(posicion p)
{
	int visitados = 0;
	posicion tempPos;
	for(int offset = 0; offset < 4; offset ++)
	{
		tempPos = Mover(p, (direccion)(1 << offset));
		if(visitado[tempPos.y*ancho + tempPos.x]) visitados ++;
	}
	return (visitados == 4) ? true : false;
	return false;
}

void CrearLaberinto(void)
{
	lab = (int*)malloc(sizeof(int)*alto*ancho);
	visitado = (bool*)malloc(sizeof(bool)*alto*ancho);
	direccion labOrigen[ancho * alto];//[alto];
	posicion posActual; posActual.x = 0; posActual.y = 0;
	bool labTerminado = false;
	

	for(int i = 0; i < ancho*alto; i++) {
		lab[i] = 0;
		labOrigen[i] = invalido;
		visitado[i] = false;
	}
	visitado[0] = true;
	
	// -----------------------------
	while(!labTerminado)
	{
		bool moverValido = false;
		while(!moverValido)
		{
			direccion nuevaDir = DireccionRandom();
			posicion newPos = Mover(posActual, nuevaDir);
			if(VerificarPosicion(newPos))
			{
				lab[posActual.y*ancho + posActual.x] |= nuevaDir;
				lab[newPos.y*ancho + newPos.x] |= InvertirDireccion(nuevaDir);
				visitado[newPos.y*ancho + newPos.x] = true;
				if(labOrigen[newPos.y*ancho + newPos.x] == invalido) labOrigen[newPos.y*ancho + newPos.x] = InvertirDireccion(nuevaDir);
				posActual = newPos;
				moverValido = true;
			}
		}
		bool interseccionValida = false;
		while(!interseccionValida)
		{
			if(LadosTodosVisitados(posActual))
			{
				if(posActual.x == ancho-1)
				{
					if(lab[posActual.y*ancho + posActual.x] == arriba ||
					lab[posActual.y*ancho + posActual.x] == abajo ||
					lab[posActual.y*ancho + posActual.x] == derecha ||
					lab[posActual.y*ancho + posActual.x] == izquierda) { salida.x = posActual.x; salida.y = posActual.y; }
				}
				if(salidaAlternativa.x == 0 && salidaAlternativa.y == 0)
				{
					salidaAlternativa.x = posActual.x;
					salidaAlternativa.y = posActual.y;
				}
				posActual = Mover(posActual, labOrigen[posActual.y*ancho + posActual.x]);
				if(posActual.x == 0 && posActual.y == 0) { labTerminado = true; break; }
			}
			else interseccionValida = true;
		}
		if(labTerminado) break;
	}
	if(salida.x == 0 && salida.y == 0)
	{
		salida.x = salidaAlternativa.x;
		salida.y = salidaAlternativa.y;
	}
}
