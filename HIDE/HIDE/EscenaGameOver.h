#pragma once
#include "Escena.h"

class EscenaGameOver : public Escena
{
public:
	static EscenaGameOver* dameEscenaGameOver();
	~EscenaGameOver();
	void actualizar(long p_tiempoTranscurridoUltimaActualizacion);
	void dibujar(float p_cantidadFrameTranscurrido);
	void gestionarEvento();
	void iniciar();
	void terminar();

private:
	static EscenaGameOver* ptrInstanciaEscenaGameOver;
	EscenaGameOver();
};
