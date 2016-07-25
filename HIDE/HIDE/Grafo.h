#ifndef INC_GRAFO
#define INC_GRAFO
#pragma once
#include <Box2D\Box2D.h>
#include <vector>
class Nodo;

class Grafo
{
public:///GUARDAR EL NODO ACTUAL EN EL INFECTADO
	Grafo();
	Grafo(const Grafo& p_grafoACopiar);
	~Grafo();
	void AnadeNodo(b2Vec2 pos);
	Nodo* GetAdyacenteMasCercano(Nodo* desde);
	std::vector<Nodo*> GetNodosGrafo(){ return nodosGrafo; }
private:
	std::vector<Nodo*> nodosGrafo;
	float DistanciaHasta(Nodo* origen, Nodo* dest);
};
#endif

