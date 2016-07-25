#pragma once
#include "Escena.h"

class EscenaCreditos : public Escena
{
public:
	static EscenaCreditos* dameEscenaCreditos();
	~EscenaCreditos();
	void actualizar(long p_tiempoTranscurridoUltimaActualizacion);
	void dibujar(float p_cantidadFrameTranscurrido);
	void gestionarEvento();
	void iniciar();
	void terminar();

private:
	static EscenaCreditos* ptrInstanciaEscenaCreditos;
	EscenaCreditos();
};

