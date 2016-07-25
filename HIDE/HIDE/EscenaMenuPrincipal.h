#pragma once
#include "Escena.h"
#include <irrlicht.h>
class EscenaMenuPrincipal : public Escena
{
public:
	static EscenaMenuPrincipal* dameEscenaMenuPrincipal();
	~EscenaMenuPrincipal();
	void actualizar(long p_tiempoTranscurridoUltimaActualizacion);
	void dibujar(float p_cantidadFrameTranscurrido);
	void gestionarEvento();
	void iniciar();
	void terminar();

private:
	static EscenaMenuPrincipal* ptrInstanciaEscenaMenuPrincipal;
	EscenaMenuPrincipal();
	const char c_cantidadBotones = 4;
};

