#ifndef INC_ESTADOGRUPO
#define INC_ESTADOGRUPO
#include "Estado.h"
#pragma once
class Estado_Grupo : public Estado
{
public:
	static Estado_Grupo* GetInstancia();
	~Estado_Grupo();
	void Execute(Infectado* infectado);
	void EntrarEstado(Infectado* infectado);
	void SalirEstado(Infectado* infectado);
private:
	Estado_Grupo();
};
#endif

