#pragma once
class Infectado;
#include "Grafo.h" 

class PlanificadorCaminos
{
public:
	PlanificadorCaminos(Infectado* i, Grafo* g);
	~PlanificadorCaminos();
	void SetNodoActual(Nodo* n);
	void SetNodoActual();
	void SetNodoDestino();
	void SetNodoDestinoAlerta();
	void SetNodoDestinoHuir();
	void SetNodoDestino(b2Vec2 n);
	Nodo* GetNodoDestino();
	Nodo* GetNodoActual();
	void CompruebaSiLlegadoDestino();
	void CompruebaSiLlegadoDestinoAlerta();
	void CompruebaSiLlegadoDestinoHuir();
	void ReiniciaPesosGrafo();
private:
	Infectado* propietario;
	Grafo* grafoMapa;
	Nodo* nodoActual;
	Nodo* nodoDestino;
	Nodo* BuscaNodoActual();
};
