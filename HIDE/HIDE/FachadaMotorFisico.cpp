#include "FachadaMotorFisico.h"

FachadaMotorFisico* FachadaMotorFisico::c_ptrInstanciaFachadaMotorFisico = 0;

FachadaMotorFisico* FachadaMotorFisico::dameFachadaMotorFisico()
{
	if (c_ptrInstanciaFachadaMotorFisico == 0)
		c_ptrInstanciaFachadaMotorFisico = new FachadaMotorFisico();
	return c_ptrInstanciaFachadaMotorFisico;
}

FachadaMotorFisico::FachadaMotorFisico()
{
	c_mundoFisico = new b2World(b2Vec2(0.f, 0.f));
}

FachadaMotorFisico::~FachadaMotorFisico()
{
	delete c_mundoFisico;
}

b2World* FachadaMotorFisico::dameMundoFisico()
{
	if (c_mundoFisico == nullptr)
		c_mundoFisico = new b2World(b2Vec2(0.f, 0.f));
	return c_mundoFisico;
}

void FachadaMotorFisico::actualizaMundoFisico(long p_tiempoTranscurridoUltimaActualizacion)
{
	c_mundoFisico->Step(float(p_tiempoTranscurridoUltimaActualizacion), VELOCITYITERATIONS, POSITIONITERATIONS);
}
