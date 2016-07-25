#pragma once
#include "D:\RepositorioABP\Codigo\HIDE\HIDE\Box2D\Dynamics\b2WorldCallbacks.h"
#include "Box2D\Box2D.h"
class Protagonista;
class EntidadJuego;
class EntidadInteractuable;

class LanzadorRayCast : public b2RayCastCallback
{
private:
	Protagonista* c_protagonista;
	float c_distanciaEntidadEncontrada;
	float c_alturaRayo;
	float c_anguloRayo;
	float c_longitudRayo;
	EntidadJuego* c_entidadEncontrada;
	b2Vec2 c_posicionColision;
	float c_alturaColision;
	float c_distanciaParedMasCercana;
	b2Vec2 calculaPunto2(b2Vec2 p_punto1);
	bool TestAltura(float p_longitudRayo, float _alturaMaximaRayo);

public:
	LanzadorRayCast(Protagonista* p_protagonista, float p_alcanceArmaEquipada);
	~LanzadorRayCast();
	EntidadInteractuable* lanzaRayoYDameEntidad();
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
};

