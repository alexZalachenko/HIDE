#include "RaycastVeoPosicion.h"
#include "Infectado.h"
#include "FachadaMotorFisico.h"
#include "Constantes.h"

//MANDAR COORDENADAS MOTOR FISICO
RaycastVeoPosicion::RaycastVeoPosicion(Infectado* p_infectado, b2Vec2 p_posicionObjetivo)
	: c_infectado(p_infectado)
	, c_posicionObjetivo(p_posicionObjetivo)
{
}

RaycastVeoPosicion::~RaycastVeoPosicion()
{
}

bool RaycastVeoPosicion::veoPosicion()
{
	b2Vec2 t_punto1 = c_infectado->dameCuerpoFisicoEntidad()->GetPosition();
	c_veoPosicion = true;
	FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->RayCast(this, t_punto1, c_posicionObjetivo);
	return c_veoPosicion;
}

float32 RaycastVeoPosicion::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	b2Body* body = fixture->GetBody();
	if (body->GetType() == b2_staticBody)//EL RAYCAST HA CHOCADO CON UNA PARED
	{
		//COMPRUEBO LA ALTURA DEL OBJETO
		if (body->GetUserData() == "ALTA" || body->GetUserData() == "BAJA"){
			c_veoPosicion = false;
			return 0.f;//TERMINO EL RAYCAST
		}
	}
	return 1.f;//CONTINUA RAYCAST
}