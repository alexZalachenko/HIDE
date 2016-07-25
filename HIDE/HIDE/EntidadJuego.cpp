#include "EntidadJuego.h"
#include "FachadaMotorFisico.h"


EntidadJuego::EntidadJuego(float p_posicionX, float p_posicionZ, char* p_modelo3D)
{
	creaCuerpoFisico(p_posicionX, p_posicionZ, b2_dynamicBody);
	c_mallaGraficaEntidad = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena(p_modelo3D);
	c_mallaGraficaEntidad->setPosition(irr::core::vector3df(p_posicionX, 0.f, p_posicionZ));
}

EntidadJuego::EntidadJuego(float p_posicionX, float p_posicionZ, char* p_modelo3D, bool p_esObjeto)
{
	creaCuerpoFisico(p_posicionX, p_posicionZ, b2_kinematicBody);
	c_mallaGraficaEntidad = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena(p_modelo3D);
	c_mallaGraficaEntidad->setPosition(irr::core::vector3df(p_posicionX, 0.f, p_posicionZ));
}

EntidadJuego::~EntidadJuego()
{
	destruyeEntidad();
	c_mallaGraficaEntidad->remove();
}

void EntidadJuego::destruyeEntidad()
{
	c_mallaGraficaEntidad->setVisible(false);
	if (c_cuerpoFisicoEntidad!=0)
	{
		FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->DestroyBody(c_cuerpoFisicoEntidad);
		c_cuerpoFisicoEntidad = 0;
	}
}

void EntidadJuego::reanimaEntidad(b2Vec2 p_posicion, b2BodyType p_tipoBody)
{
	c_mallaGraficaEntidad->setVisible(true);
	c_mallaGraficaEntidad->setPosition(irr::core::vector3df(p_posicion.x, 0, p_posicion.y));
	creaCuerpoFisico(p_posicion.x, p_posicion.y, p_tipoBody);
}

void EntidadJuego::setPosicion(b2Vec2 p_posicionNueva)
{
	c_mallaGraficaEntidad->setPosition(irr::core::vector3df(p_posicionNueva.x, 0, p_posicionNueva.y));
	c_cuerpoFisicoEntidad->SetTransform(b2Vec2(p_posicionNueva.y, p_posicionNueva.x), c_cuerpoFisicoEntidad->GetAngle());
}

void EntidadJuego::setPosicionMallaGrafica(irr::core::vector3df p_nuevaPosicionMallaGrafica, irr::core::vector3df p_nuevaRotacionMallaGrafica)
{
	if (c_mallaGraficaEntidad == nullptr)
		exit(1);
	c_mallaGraficaEntidad->setPosition(p_nuevaPosicionMallaGrafica);
	c_mallaGraficaEntidad->setRotation(p_nuevaRotacionMallaGrafica);
}

irr::core::vector3df EntidadJuego::damePosicionMallaGrafica()
{
	if (c_mallaGraficaEntidad == nullptr)
		exit(1);
	return c_mallaGraficaEntidad->getPosition();
}

irr::core::vector3df EntidadJuego::dameRotacionMallaGrafica()
{
	if (c_mallaGraficaEntidad == nullptr)
		exit(1);
	return c_mallaGraficaEntidad->getRotation();
}

void EntidadJuego::creaCuerpoFisico(float p_posicionX, float p_posicionZ, b2BodyType p_tipoCuerpoFisico)
{
	//CREO UNA FIXTURE CON FORMA DE CIRCULO Y DENSIDAD 1
	b2CircleShape t_formaCirculo;
	t_formaCirculo.m_radius = 0.5;
	b2FixtureDef t_boxFixtureDef;
	t_boxFixtureDef.shape = &t_formaCirculo;
	t_boxFixtureDef.density = 1;

	b2BodyDef t_myBodyDef;
	t_myBodyDef.type = p_tipoCuerpoFisico;
	t_myBodyDef.position.Set(p_posicionZ, p_posicionX);
	c_cuerpoFisicoEntidad = FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->CreateBody(&t_myBodyDef);
	c_cuerpoFisicoEntidad->CreateFixture(&t_boxFixtureDef);
	c_cuerpoFisicoEntidad->SetUserData(this);//PARA PILLAR LA ENTIDAD LUEGO EN EL RAYCAST
}

b2Body* EntidadJuego::dameCuerpoFisicoEntidad()
{
	return c_cuerpoFisicoEntidad;
}

void EntidadJuego::setSensor(bool p_estadoSensor)
{
	c_cuerpoFisicoEntidad->GetFixtureList()->SetSensor(p_estadoSensor);
}