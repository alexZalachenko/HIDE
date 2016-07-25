#include "EntidadInterpolable.h"

EntidadInterpolable::EntidadInterpolable(float p_posicionX, float p_posicionZ, char* p_modelo3D)
	: EntidadJuego(p_posicionX, p_posicionZ, p_modelo3D)
{
	c_posicionAntigua.X = p_posicionX;
	c_posicionAntigua.Y = 0;
	c_posicionAntigua.Z = p_posicionZ;
	c_posicionNueva = c_posicionAntigua;

	c_rotacionAntigua.X = 0; 
	c_rotacionAntigua.Y = 0;
	c_rotacionAntigua.Z = 0;
	c_rotacionNueva = c_rotacionAntigua;
}

EntidadInterpolable::~EntidadInterpolable()
{
}

void EntidadInterpolable::guardaEstadoNuevoEnEstadoAntiguo()
{
	c_posicionAntigua = c_posicionNueva;
	c_rotacionAntigua = c_rotacionNueva;
}

void EntidadInterpolable::interpolaPosicion(float p_cantidadFrameTranscurrido)
{
	irr::core::vector3df t_nuevaPosicionMallaGrafica;
	t_nuevaPosicionMallaGrafica.X = c_posicionAntigua.X*(1 - p_cantidadFrameTranscurrido) + c_posicionNueva.X * p_cantidadFrameTranscurrido;
	t_nuevaPosicionMallaGrafica.Y = c_posicionAntigua.Y*(1 - p_cantidadFrameTranscurrido) + c_posicionNueva.Y * p_cantidadFrameTranscurrido;
	t_nuevaPosicionMallaGrafica.Z = c_posicionAntigua.Z*(1 - p_cantidadFrameTranscurrido) + c_posicionNueva.Z * p_cantidadFrameTranscurrido;

	irr::core::vector3df t_nuevaRotacionMallaGrafica;
	t_nuevaRotacionMallaGrafica.X = c_rotacionAntigua.X*(1 - p_cantidadFrameTranscurrido) + c_rotacionNueva.X * p_cantidadFrameTranscurrido;
	t_nuevaRotacionMallaGrafica.Y = c_rotacionAntigua.Y*(1 - p_cantidadFrameTranscurrido) + c_rotacionNueva.Y * p_cantidadFrameTranscurrido;
	t_nuevaRotacionMallaGrafica.Z = c_rotacionAntigua.Z*(1 - p_cantidadFrameTranscurrido) + c_rotacionNueva.Z * p_cantidadFrameTranscurrido;
	
	setPosicionMallaGrafica(t_nuevaPosicionMallaGrafica, t_nuevaRotacionMallaGrafica);
}