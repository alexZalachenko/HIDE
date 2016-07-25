#pragma once
#include <irrlicht.h>
#include "Box2D\Dynamics\b2Body.h"

class EntidadJuego
{
public:
	EntidadJuego(float p_posicionX, float p_posicionZ, char* p_modelo3D);
	EntidadJuego(float p_posicionX, float p_posicionZ, char* p_modelo3D, bool p_esObjeto);
	virtual ~EntidadJuego();
	void setPosicion(b2Vec2 p_posicionNueva);
	void setPosicionMallaGrafica(irr::core::vector3df p_nuevaPosicionMallaGrafica, irr::core::vector3df p_nuevaRotacionMallaGrafica);
	irr::core::vector3df damePosicionMallaGrafica();
	irr::core::vector3df dameRotacionMallaGrafica();
	virtual void actualizaEntidadJuego() = 0;
	b2Body* dameCuerpoFisicoEntidad();
	irr::scene::IMeshSceneNode* dameMallaGrafica(){ return c_mallaGraficaEntidad; }
	//NO BORRA LA ENTIDAD DE MEMORIA. ELIMINA CUERPO FISICO Y HACE MALLA INVISIBLE
	void destruyeEntidad();
	void reanimaEntidad(b2Vec2 p_posicion, b2BodyType p_tipoBody);
	void setSensor(bool p_estadoSensor);

private:
	irr::scene::IMeshSceneNode* c_mallaGraficaEntidad;
	b2Body* c_cuerpoFisicoEntidad;
	void creaCuerpoFisico(float p_posicionX, float p_posicionZ, b2BodyType p_tipoCuerpoFisico);
};

