#include "Grafo.h"
#include "Nodo.h"

Grafo::Grafo()
{
}

Grafo::Grafo(const Grafo& p_grafoACopiar)
{
	for each (Nodo* t_nodoCopiar in p_grafoACopiar.nodosGrafo)
		AnadeNodo(t_nodoCopiar->GetPosicion());
}

Grafo::~Grafo()
{
	for each (Nodo* t_nodo in nodosGrafo)
		delete t_nodo;
}

void Grafo::AnadeNodo(b2Vec2 pos)
{
	Nodo* adyacente = NULL;
	Nodo* nodoAnadir = new Nodo(pos);
	float dist = -1;
	float nuevaDist;
	b2Vec2 vecDist;
	//ANADO NODOS ADYACENTES EN VERTICAL
	for each (Nodo* nod in nodosGrafo)
	{
		if (nod->GetPosicion().x == pos.x  && nod->GetPosicion().y != pos.y)
		{
			if (adyacente == NULL && nod->GetPosicion().y<pos.y)
			{
				adyacente = nod;
				vecDist = nod->GetPosicion() - pos;
				dist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
			}
			else
			{
				vecDist = nod->GetPosicion() - pos;
				nuevaDist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
				if (dist > nuevaDist && nod->GetPosicion().y<pos.y)//MIRO LOS DE DEBAJO
				{
					adyacente = nod;
					dist = nuevaDist;
				}
			}
		}
	}
	if (adyacente!=NULL)
		nodoAnadir->AnadeAdyacente(adyacente, true);
	adyacente = NULL;
	for each (Nodo* nod in nodosGrafo)
	{
		if (nod->GetPosicion().x == pos.x  && nod->GetPosicion().y != pos.y)
		{
			if (adyacente == NULL && nod->GetPosicion().y>pos.y)
			{
				adyacente = nod;
				vecDist = nod->GetPosicion() - pos;
				dist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
			}
			else
			{
				vecDist = nod->GetPosicion() - pos;
				nuevaDist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
				if (dist > nuevaDist && nod->GetPosicion().y>pos.y)//MIRO LOS DE ARRIBA
				{
					adyacente = nod;
					dist = nuevaDist;
				}
			}
		}
	}
	//ANADO NODOS ADYACENTES EN HORIZONTAL
	if (adyacente != NULL)
		nodoAnadir->AnadeAdyacente(adyacente, true);
	adyacente = NULL;
	for each (Nodo* nod in nodosGrafo)
	{
		if (nod->GetPosicion().y == pos.y  && nod->GetPosicion().x != pos.x)
		{
			if (adyacente == NULL && nod->GetPosicion().x>pos.x)
			{
				adyacente = nod;
				vecDist = nod->GetPosicion() - pos;
				dist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
			}
			else
			{
				vecDist = nod->GetPosicion() - pos;
				nuevaDist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
				if (dist > nuevaDist && nod->GetPosicion().x>pos.x)//MIRO LOS DE LA DERECHA
				{
					adyacente = nod;
					dist = nuevaDist;
				}
			}
		}
	}
	if (adyacente != NULL)
		nodoAnadir->AnadeAdyacente(adyacente, true);
	adyacente = NULL;
	for each (Nodo* nod in nodosGrafo)
	{
		if (nod->GetPosicion().y == pos.y  && nod->GetPosicion().x != pos.x)
		{
			if (adyacente == NULL && nod->GetPosicion().x < pos.x)
			{
				adyacente = nod;
				vecDist = nod->GetPosicion() - pos;
				dist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
			}
			else
			{
				vecDist = nod->GetPosicion() - pos;
				nuevaDist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
				if (dist > nuevaDist && nod->GetPosicion().x<pos.x)//MIRO LOS DE LA IZQUIERDA
				{
					adyacente = nod;
					dist = nuevaDist;
				}
			}
		}
	}
	if (adyacente != NULL)
		nodoAnadir->AnadeAdyacente(adyacente, true);
	nodosGrafo.push_back(nodoAnadir);
}

float Grafo::DistanciaHasta(Nodo* origen, Nodo* dest)
{
	b2Vec2 vecDist = dest->GetPosicion() -  origen->GetPosicion();
	float distancia = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
	return distancia;
}

Nodo* Grafo::GetAdyacenteMasCercano(Nodo* desde)
{
	Nodo* masCercano = NULL;
	float distancia = 100000;
	for each (Nodo* nodo in desde->GetAdyacentes())
	{
		if (DistanciaHasta(desde, nodo) < distancia)
		{
			distancia = DistanciaHasta(desde, nodo);
			masCercano = nodo;
		}
	}
	return masCercano;
}
