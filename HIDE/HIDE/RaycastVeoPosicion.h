#pragma once
#include "D:\RepositorioABP\Codigo\HIDE\HIDE\Box2D\Dynamics\b2WorldCallbacks.h"
#include "Box2D\Box2D.h"
class Infectado;

class RaycastVeoPosicion : public b2RayCastCallback
{
public:
	RaycastVeoPosicion(Infectado* p_infectado, b2Vec2 p_posicionObjetivo);
	~RaycastVeoPosicion();
	bool veoPosicion();
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

private:
	bool c_veoPosicion;
	Infectado* c_infectado;
	b2Vec2 c_posicionObjetivo;
};

