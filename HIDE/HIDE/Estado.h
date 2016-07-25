#ifndef INC_ESTADO
#define INC_ESTADO
#pragma once
class Infectado;

class Estado
{
public:
	Estado();
	~Estado();
	virtual void Execute(Infectado* infectado) = 0;
	virtual void EntrarEstado(Infectado* infectado) = 0;
	virtual void SalirEstado(Infectado* infectado) = 0;
};
#endif
