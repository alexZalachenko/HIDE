#pragma once
#include "Constantes.h"
#include "Box2D\Box2D.h"	
#include "FachadaMotorGrafico.h"
class FachadaMotorFisico
{
public:
	static FachadaMotorFisico* dameFachadaMotorFisico();
	~FachadaMotorFisico();
	b2World* dameMundoFisico();
	void actualizaMundoFisico(long p_tiempoTranscurridoUltimaActualizacion);
	void borraMundoFisico(){ delete c_mundoFisico; c_mundoFisico = nullptr; }
private:
	static FachadaMotorFisico* c_ptrInstanciaFachadaMotorFisico;
	FachadaMotorFisico();
	b2World* c_mundoFisico;
};
