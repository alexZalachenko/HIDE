#pragma once
#include "Reloj.h"
#include "Box2D\Box2D.h"
class Objeto;
class GeneradorObjetos;

class PuntoGeneracionObjetos
{
public:
	PuntoGeneracionObjetos(float p_posicionX, float p_posicionY);
	~PuntoGeneracionObjetos();
	bool actualizaPuntoGeneracion();
	void setObjeto(Objeto* p_objeto);
	void eliminaObjeto();
	b2Vec2 damePosicion(){ return c_posicionPuntoGeneracion; }

private:
	b2Vec2 c_posicionPuntoGeneracion;
	Reloj c_reloj;
	Objeto* c_objetoGenerado;
	
	
};

