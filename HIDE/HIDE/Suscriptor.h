#pragma once
#include "Constantes.h"

class Suscriptor
{
public:
	Suscriptor();
	~Suscriptor();
	virtual void recibeNotificacion(float x, float y, VolumenSonidos p_volumen) = 0;
};

