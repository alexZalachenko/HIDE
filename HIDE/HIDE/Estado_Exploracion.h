#ifndef INC_ESTADOEXPLORACION
#define INC_ESTADOEXPLORACION
#include "Estado.h"
#include "Infectado.h"
#pragma once
class Estado_Exploracion : public Estado
{
public:
	static Estado_Exploracion* GetInstancia();
	~Estado_Exploracion();
	void Execute(Infectado* infectado);
	void EntrarEstado(Infectado* infectado);
	void SalirEstado(Infectado* infectado);
private:
	Estado_Exploracion();
};
#endif
