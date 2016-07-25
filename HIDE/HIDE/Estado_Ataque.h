#ifndef INC_ESTADOATAQUE
#define INC_ESTADOATAQUE
#include "Estado.h"
#include "Infectado.h"
#pragma once
class Estado_Ataque : public Estado
{
public:
	static Estado_Ataque* GetInstancia();
	~Estado_Ataque();
	void Execute(Infectado* infectado);
	void EntrarEstado(Infectado* infectado);
	void SalirEstado(Infectado* infectado);
private:
	Estado_Ataque();
};
#endif
