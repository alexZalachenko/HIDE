#include "Estado.h"
#include "Infectado.h"
#include "Estado_Alerta.h"
#include "Estado_Ataque.h"
#pragma once
class Estado_Global : public Estado
{
public:
	static Estado_Global* GetInstancia();
	~Estado_Global();
	void Execute(Infectado* infectado);
	void EntrarEstado(Infectado* infectado);
	void SalirEstado(Infectado* infectado);
private:
	Estado_Global();
};

