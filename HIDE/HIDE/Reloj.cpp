#include "Reloj.h"
#include "Constantes.h"
#include <time.h>

Reloj::Reloj()
{
	c_ultimoTiempoRelojTicks = (short)clock();
}

Reloj::~Reloj()
{
}

long Reloj::dameTiempoTranscurridoMilisegundos()
{
	long t_clock = clock();
	long r_tiempoTranscurrido = long(((t_clock - c_ultimoTiempoRelojTicks) / float(CLOCKS_PER_SEC)) * 1000);
	return r_tiempoTranscurrido;
}

long Reloj::dameTiempoTranscurridoMilisegundosYReinicia()
{
	long t_tiempoClock = clock();
	long r_tiempoTranscurrido = long(((t_tiempoClock - c_ultimoTiempoRelojTicks) / float(CLOCKS_PER_SEC)) * 1000);
	c_ultimoTiempoRelojTicks = t_tiempoClock;
	return r_tiempoTranscurrido;
}

bool Reloj::tocaActualizarJuego()
{
	if (dameTiempoTranscurridoMilisegundos() > TIEMPO_ACTUALIZACION_JUEGO)
		return true;
	else
		return false;
}

float Reloj::dameCantidadFrameTranscurrido()
{
	float t_cantidadFrameTranscurrido = dameTiempoTranscurridoMilisegundos() / TIEMPO_ACTUALIZACION_JUEGO;
	if (1.f > t_cantidadFrameTranscurrido)
		return t_cantidadFrameTranscurrido;
	else
		return 1.f;
}
