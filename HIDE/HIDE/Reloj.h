#pragma once

class Reloj
{
public:
	Reloj();
	~Reloj();
	long dameTiempoTranscurridoMilisegundos();
	long dameTiempoTranscurridoMilisegundosYReinicia();
	bool tocaActualizarJuego();
	float dameCantidadFrameTranscurrido();
	void setTiempoTranscurrido(long p_tiempoTranscurrido){ c_ultimoTiempoRelojTicks = p_tiempoTranscurrido; }

private:
	long c_ultimoTiempoRelojTicks;
};

