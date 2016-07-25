#include "GestorEscenas.h"
#include "Escena.h"
#include "FachadaMotorGrafico.h"
#include "Reloj.h"

GestorEscenas* GestorEscenas::ptrInstanciaGestorEscenas = 0;

GestorEscenas* GestorEscenas::dameGestorEscenas()
{
	if (ptrInstanciaGestorEscenas == 0)
		ptrInstanciaGestorEscenas = new GestorEscenas();
	return ptrInstanciaGestorEscenas;
}

GestorEscenas::GestorEscenas()
	: c_escenaActual(nullptr)
	, c_terminar(false)
{
}

GestorEscenas::~GestorEscenas()
{
}

void GestorEscenas::bucleEscena()
{
	Reloj t_reloj;
	long t_tiempoTranscurridoUltimaActualizacion=0;
	bool t_juegoHaSidoActualizado = false;
	while (c_terminar != true)
	{
		if (t_reloj.tocaActualizarJuego())
		{
			t_tiempoTranscurridoUltimaActualizacion = t_reloj.dameTiempoTranscurridoMilisegundosYReinicia();
			c_escenaActual->actualizar(t_tiempoTranscurridoUltimaActualizacion);
			t_juegoHaSidoActualizado = true;
		}
		if (t_juegoHaSidoActualizado)
			c_escenaActual->dibujar(t_reloj.dameCantidadFrameTranscurrido());
	}
	FachadaMotorGrafico::dameFachadaMotorGrafico()->termina();
}

void GestorEscenas::cambiaEscena(Escena* p_escenaNueva)
{
	if (c_escenaActual != nullptr)
		c_escenaActual->terminar();
	c_escenaActual = p_escenaNueva;
	c_escenaActual->iniciar();
}

void GestorEscenas::termina()
{
	c_terminar = true;
}
