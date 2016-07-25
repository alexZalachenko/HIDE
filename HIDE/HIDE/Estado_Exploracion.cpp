#include "Estado_Exploracion.h"
#include "Infectado.h"

Estado_Exploracion::Estado_Exploracion()
{
}

Estado_Exploracion* Estado_Exploracion::GetInstancia()
{
	static Estado_Exploracion instancia;
	return &instancia;
}

Estado_Exploracion::~Estado_Exploracion()
{
}

void Estado_Exploracion::Execute(Infectado* infectado)
{
	b2Vec2 dir = infectado->calculaDireccionMovimiento();
	infectado->mueveInfectado(dir, VELOCIDAD_ESTANDAR_INFECTADO);
	infectado->damePlanificador()->CompruebaSiLlegadoDestino();
}

void Estado_Exploracion::EntrarEstado(Infectado* infectado)
{
	infectado->damePlanificador()->ReiniciaPesosGrafo();
	infectado->damePlanificador()->SetNodoActual();
	infectado->damePlanificador()->SetNodoDestino();
}

void Estado_Exploracion::SalirEstado(Infectado* infectado)
{
}