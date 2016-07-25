#pragma once
#include "D:\RepositorioABP\Codigo\HIDE\HIDE\Box2D\Dynamics\b2WorldCallbacks.h"
#include "Box2D\Box2D.h"
class Protagonista;

class RaycastColocaTrampa : public b2RayCastCallback
{
public:
	RaycastColocaTrampa(Protagonista* p_protagonista);
	~RaycastColocaTrampa();
	bool sePuedeColocarTrampa();
	b2Vec2 damePosicionColocacionTrampa(){ return c_posicionColocacionTrampa; }
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

private:
	b2Vec2 c_posicionColocacionTrampa;
	Protagonista* c_protagonista;
	bool c_raycastAprobado;
};

