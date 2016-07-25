#pragma once
#include "Estado.h"
class Infectado;

class MaquinaEstadosFinita
{
public:
	MaquinaEstadosFinita(Infectado* i);
	~MaquinaEstadosFinita();
	void SetEstadoActual(Estado* e);
	void SetEstadoGlobal(Estado* e);
	void ActualizarMEF();
	void CambiarEstado(Estado* nuevoEstado);
	Estado* GetEstadoActual(){ return estadoActual; }
private:
	Infectado* propietario;
	Estado* estadoActual;
	Estado* estadoGlobal;
};
