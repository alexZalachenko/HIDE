#ifndef INC_NODO
#define INC_NODO
#pragma once
#include <Box2D\Box2D.h>
#include <vector>
#include "FachadaMotorFisico.h"

class Nodo
{
public:
	Nodo(b2Vec2 pos);
	~Nodo();
	void AnadeAdyacente(Nodo* n, bool replica);
	std::vector<Nodo*> GetAdyacentes();
	b2Vec2 GetPosicion();
	void IncrementaPeso();
	char GetPeso();
	void ReiniciaPeso();
private:
	//LA POSICION SE GUARDA BIEN, SIENDO LA X DE IRRLICH LA X DE LA POSICION Y LA Z DE IRRLICHT LA Y DE LA POSICION
	b2Vec2 posicion;
	std::vector<Nodo*> adyacentes;
	bool RaycastNodoVisible(Nodo* objetivo);
	char peso;
};
#endif 
