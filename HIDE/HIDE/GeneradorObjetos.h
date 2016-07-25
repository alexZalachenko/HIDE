#pragma once
#include <vector>
#include "PuntoGeneracionObjetos.h"
class GestorEntidadesJuego;

class GeneradorObjetos
{
public:
	GeneradorObjetos(GestorEntidadesJuego* p_gestorEntidadesJuego);
	~GeneradorObjetos();
	void actualizaGeneradorObjetos();
	void añadePuntoGeneracionObjetos(float p_posicionX, float p_posicionY);

private:
	std::vector<PuntoGeneracionObjetos> c_puntosGeneracionObjetos;
	GestorEntidadesJuego* c_gestorEntidadesJuego;
	Objeto* generaObjeto(b2Vec2 p_posicion);
};

