#include "MaquinaEstadosFinita.h"
#include "Infectado.h"
#include "Estado_Global.h"
#include "Estado_Exploracion.h"


MaquinaEstadosFinita::MaquinaEstadosFinita(Infectado* i)
	: propietario(i)
	, estadoActual(Estado_Exploracion::GetInstancia())
	, estadoGlobal(Estado_Global::GetInstancia())
{
}

MaquinaEstadosFinita::~MaquinaEstadosFinita()
{
}

void MaquinaEstadosFinita::SetEstadoActual(Estado* e)
{
	estadoActual = e;
}

void MaquinaEstadosFinita::SetEstadoGlobal(Estado* e)
{
	estadoGlobal = e;
}

void MaquinaEstadosFinita::ActualizarMEF()
{
	estadoGlobal->Execute(propietario);
	estadoActual->Execute(propietario);
}

void MaquinaEstadosFinita::CambiarEstado(Estado* nuevoEstado)
{
	if (estadoActual != nullptr)
		estadoActual->SalirEstado(propietario);
	estadoActual = nuevoEstado;
	estadoActual->EntrarEstado(propietario);
}

