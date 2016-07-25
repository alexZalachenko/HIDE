#pragma once
#include "NodoArbolDecision.h"
class Accion : public NodoArbolDecision
{
public:
	Accion(){}
	~Accion(){}
	virtual void tomaDecision() = 0;
};

