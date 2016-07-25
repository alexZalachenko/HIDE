#pragma once
#include "Decision.h"
class ArbolDecisionEstadoPrueba : public Decision
{
public:
	ArbolDecisionEstadoPrueba(Infectado2* p_infectado);
	~ArbolDecisionEstadoPrueba();
	NodoArbolDecision* test()
	{
		return nullptr;
	}
};

