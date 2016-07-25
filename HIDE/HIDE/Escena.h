#pragma once

class Escena
{
public:
	Escena();
	virtual ~Escena();
	virtual void actualizar(long p_tiempoTranscurridoUltimaActualizacion) = 0;
	virtual void gestionarEvento() = 0;
	virtual void dibujar(float p_cantidadFrameTranscurrido) = 0;
	virtual void iniciar() = 0;
	virtual void terminar() = 0;
};

