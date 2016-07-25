#include "Estado.h"
#include "Estado_Exploracion.h"
#include "Estado_Ataque.h"
#pragma once
class Estado_Alerta : public Estado
{
public:
	static Estado_Alerta* GetInstancia();
	~Estado_Alerta();
	void Execute(Infectado* infectado);
	void EntrarEstado(Infectado* infectado);
	void SalirEstado(Infectado* infectado);
private:
	Estado_Alerta();
};
