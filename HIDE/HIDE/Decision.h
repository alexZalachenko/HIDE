#pragma once
#include "NodoArbolDecision.h"
#include "Infectado2.h"

class Decision : public NodoArbolDecision
{
public:
	Decision(Infectado2* p_infectado)
		: c_infectado(p_infectado)
	{
	}

	~Decision()
	{
	}

	void tomaDecision()
	{
		NodoArbolDecision* t_resultadoTest = test();
		if (t_resultadoTest != nullptr)
			t_resultadoTest->tomaDecision();
	}

	void setNodoTrue(NodoArbolDecision* p_nodoTrue);

	void setNodoFalse(NodoArbolDecision* p_nodoFalse);

protected:
	NodoArbolDecision* c_nodoTrue;
	NodoArbolDecision* c_nodoFalse;
	Infectado2* c_infectado;
	virtual NodoArbolDecision* test() = 0;
};

void Decision::setNodoTrue(NodoArbolDecision* p_nodoTrue)
{
	c_nodoTrue = c_nodoTrue;
}

void Decision::setNodoFalse(NodoArbolDecision* p_nodoFalse)
{
	c_nodoFalse = c_nodoFalse;
}