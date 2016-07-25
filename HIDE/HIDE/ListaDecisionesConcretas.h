#pragma once
#include "Decision.h"

class DecisionVeJugador : Decision 
{
public:
	DecisionVeJugador(Infectado2* p_infectado)
		: Decision(p_infectado)
	{
	}
	~DecisionVeJugador(){}
	NodoArbolDecision* test()
	{
		if (c_infectado->dameVeJugador())
		{
			return c_nodoTrue;
		}
		else
		{
			return c_nodoFalse;
		}
	}
};


class DecisionNivelVidaInfectado : Decision
{
public:
	DecisionNivelVidaInfectado(Infectado2* p_infectado)
		: Decision(p_infectado)
	{
	}
	~DecisionNivelVidaInfectado(){}
	NodoArbolDecision* test()
	{
		if (c_infectado->dameVida() < 0.2)
		{
			return c_nodoTrue;
		}
		else
		{
			return c_nodoFalse;
		}
	}
};


class DecisionDa�oInfectado : Decision
{
public:
	DecisionDa�oInfectado(Infectado2* p_infectado)
		: Decision(p_infectado)
	{
	}
	~DecisionDa�oInfectado(){}
	NodoArbolDecision* test()
	{
		if (c_infectado->dameDa�o() > 10)
		{
			return c_nodoTrue;
		}
		else
		{
			return c_nodoFalse;
		}
	}
};


