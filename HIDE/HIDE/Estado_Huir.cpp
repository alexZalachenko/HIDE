#include "Estado_Huir.h"
#include "Infectado.h"
#include "Nodo.h"
#include "RaycastVeoPosicion.h"

Estado_Huir::Estado_Huir()
{
}

Estado_Huir* Estado_Huir::GetInstancia()
{
	static Estado_Huir instancia;
	return &instancia;
}

Estado_Huir::~Estado_Huir()
{
}

void Estado_Huir::Execute(Infectado* infectado)
{
	//COMPRUEBO SI HE LLEGADO AL NODO DESTINO
	infectado->damePlanificador()->CompruebaSiLlegadoDestinoHuir();

	//SI VEO NODO DESTINO SIN INTERRUPCIONES ME MUEVO HACIA EL NODO DESTINO
	Nodo* t_nodoDestino = infectado->damePlanificador()->GetNodoDestino();
	b2Vec2 t_posicionNodoDestino(t_nodoDestino->GetPosicion().y, t_nodoDestino->GetPosicion().x);
	RaycastVeoPosicion t_rayCastDestino(infectado, t_posicionNodoDestino);
	b2Vec2 posInf(infectado->dameCuerpoFisicoEntidad()->GetPosition().y, infectado->dameCuerpoFisicoEntidad()->GetPosition().x);
	if (t_rayCastDestino.veoPosicion())
	{
		b2Vec2 dir = t_nodoDestino->GetPosicion() - posInf;
		dir.Normalize();
		infectado->mueveInfectado(dir, VELOCIDAD_ESTANDAR_INFECTADO);
		return;
	}

	//ME MUEVO HACIA EL NODO ACTUAL PARA QUE CUANDO LLEGUE AL NODO ACTUAL PUEDA VER EL NODO DESTINO
	b2Vec2 dir = infectado->damePlanificador()->GetNodoActual()->GetPosicion() - posInf;
	dir.Normalize();
	infectado->mueveInfectado(dir, VELOCIDAD_ESTANDAR_INFECTADO);
	return;
}

void Estado_Huir::EntrarEstado(Infectado* infectado)
{
	infectado->damePlanificador()->ReiniciaPesosGrafo();
	infectado->damePlanificador()->SetNodoActual();
	infectado->damePlanificador()->SetNodoDestinoHuir();
}

void Estado_Huir::SalirEstado(Infectado* infectado)
{
}

