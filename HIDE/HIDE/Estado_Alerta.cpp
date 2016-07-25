#include "Estado_Alerta.h"
#include "Infectado.h"
#include "Nodo.h"
#include "RaycastVeoPosicion.h"

Estado_Alerta::Estado_Alerta()
{
}

Estado_Alerta* Estado_Alerta::GetInstancia()
{
	static Estado_Alerta instancia;
	return &instancia;
}

Estado_Alerta::~Estado_Alerta()
{
}

void Estado_Alerta::Execute(Infectado* infectado)
{
	//COMPRUEBO SI HE LLEGADO AL NODO DESTINO
	infectado->damePlanificador()->CompruebaSiLlegadoDestinoAlerta();

	//SI HE LLEGADO A LA POSICION DE ALERTA PASO A ESTADO DE EXPLORACION
	b2Vec2 posInf(infectado->dameCuerpoFisicoEntidad()->GetPosition().y, infectado->dameCuerpoFisicoEntidad()->GetPosition().x);
	if ((posInf - infectado->damePosicionAlerta()).Length() < 3.f)
	{
		infectado->dameMEF()->CambiarEstado(Estado_Exploracion::GetInstancia());
		return;
	}
		
	//SI PUEDO VER POSICION ALERTA SIN OBSTRUCCIONES ME MUEVO A ELLA
	b2Vec2 t_posicionAlerta(infectado->damePosicionAlerta().y, infectado->damePosicionAlerta().x);
	RaycastVeoPosicion t_rayCastAlerta(infectado, t_posicionAlerta);
	if (t_rayCastAlerta.veoPosicion())
	{
		b2Vec2 dir = infectado->damePosicionAlerta() - posInf;
		dir.Normalize();
		infectado->mueveInfectado(dir, VELOCIDAD_ESTANDAR_INFECTADO);
		return;
	}

	//SI VEO NODO DESTINO SIN INTERRUPCIONES ME MUEVO HACIA EL NODO DESTINO
	Nodo* t_nodoDestino = infectado->damePlanificador()->GetNodoDestino();
	b2Vec2 t_posicionNodoDestino(t_nodoDestino->GetPosicion().y, t_nodoDestino->GetPosicion().x);
	RaycastVeoPosicion t_rayCastDestino(infectado, t_posicionNodoDestino);
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

void Estado_Alerta::EntrarEstado(Infectado* infectado)
{
	infectado->damePlanificador()->ReiniciaPesosGrafo();
	infectado->damePlanificador()->SetNodoActual();
	infectado->damePlanificador()->SetNodoDestinoAlerta();
}

void Estado_Alerta::SalirEstado(Infectado* infectado)
{

}