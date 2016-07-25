#ifndef INC_ESTADOHUIR
#define INC_ESTADOHUIR
#include "Estado.h"
#pragma once
class Estado_Huir : public Estado
{
public:
	static Estado_Huir* GetInstancia();
	~Estado_Huir();
	void Execute(Infectado* infectado);
	void EntrarEstado(Infectado* infectado);
	void SalirEstado(Infectado* infectado);
private:
	Estado_Huir();
};
#endif

