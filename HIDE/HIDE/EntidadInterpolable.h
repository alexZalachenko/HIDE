#pragma once
#include <irrlicht.h>
#include "EntidadJuego.h"

class EntidadInterpolable : public EntidadJuego
{
public:
	EntidadInterpolable(float p_posicionX, float p_posicionZ, char* p_modelo3D);
	virtual ~EntidadInterpolable();
	void guardaEstadoNuevoEnEstadoAntiguo();
	void setPosicionNueva(irr::core::vector3df p_posicionNueva){ c_posicionNueva = p_posicionNueva; }
	irr::core::vector3df damePosicionNueva(){ return c_posicionNueva; }
	void setRotacionNueva(irr::core::vector3df p_rotacionNueva){ c_rotacionNueva = p_rotacionNueva; }
	virtual void actualizaEntidadJuego() = 0;
	virtual void interpolaPosicion(float p_cantidadFrameTranscurrido);

private:
	irr::core::vector3df c_posicionAntigua;
	irr::core::vector3df c_posicionNueva;
	irr::core::vector3df c_rotacionAntigua;
	irr::core::vector3df c_rotacionNueva;
};

