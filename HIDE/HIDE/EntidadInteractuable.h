#pragma once
class Protagonista;

class EntidadInteractuable
{
public:
	EntidadInteractuable();
	virtual ~EntidadInteractuable();
	virtual void interactua(Protagonista* p_protagonista) = 0;
};

