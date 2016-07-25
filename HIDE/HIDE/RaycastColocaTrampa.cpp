#include "RaycastColocaTrampa.h"
#include "Protagonista.h"
#include "FachadaMotorFisico.h"

RaycastColocaTrampa::RaycastColocaTrampa(Protagonista* p_protagonista)
	: c_protagonista(p_protagonista)
{
}

RaycastColocaTrampa::~RaycastColocaTrampa()
{
}

bool RaycastColocaTrampa::sePuedeColocarTrampa()
{
	float t_distanciaHastaTrampa = c_protagonista->damePosicionMallaGrafica().Y / tan(c_protagonista->dameRotacionMallaGrafica().X * DEGTORAD);
	if (t_distanciaHastaTrampa > RANGO_MAXIMO_INTERACCION)
		return false;
	
	b2Vec2 t_posicionProtagonista = c_protagonista->dameCuerpoFisicoEntidad()->GetPosition();
	b2Vec2 t_posicionTrampa(t_posicionProtagonista.x + cos(c_protagonista->dameMallaGrafica()->getRotation().Y * DEGTORAD),
							t_posicionProtagonista.y + sin(c_protagonista->dameMallaGrafica()->getRotation().Y * DEGTORAD));
	c_posicionColocacionTrampa.x = t_posicionProtagonista.y;
	c_posicionColocacionTrampa.y = t_posicionProtagonista.x;

	c_raycastAprobado = true;
	FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->RayCast(this, t_posicionProtagonista , t_posicionTrampa);
	return c_raycastAprobado;
}

float32 RaycastColocaTrampa::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	b2Body* body = fixture->GetBody();
	if (body->GetType() == b2_staticBody)//EL RAYCAST HA CHOCADO CON UNA PARED
	{
		//COMPRUEBO LA ALTURA DEL OBJETO
		if (body->GetUserData() == "ALTA" || body->GetUserData() == "BAJA"){
			c_raycastAprobado = false;
			return 0.f;//TERMINO EL RAYCAST
		}
	}
	return 1.f;//CONTINUA RAYCAST
}