#pragma once
#include "Escena.h"

class EscenaOpciones : public Escena
{
public:
	static EscenaOpciones* dameEscenaOpciones();
	~EscenaOpciones();
	void actualizar(long p_tiempoTranscurridoUltimaActualizacion);
	void dibujar(float p_cantidadFrameTranscurrido);
	void gestionarEvento();
	void iniciar();
	void terminar();

private:
	static EscenaOpciones* ptrInstanciaEscenaOpciones;
	EscenaOpciones();
};
