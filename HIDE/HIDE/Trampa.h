#pragma once
#include "Objeto.h"
#include "Constantes.h"
#include"Reloj.h"
#include "Box2D\Box2D.h"

class GestorEntidadesJuego;
class Infectado;

class Trampa : public Objeto, public b2ContactListener
{
public:
	Trampa(float p_posicionX, float p_posicionZ, char* p_modelo3D, float p_peso,
		   char* p_nombre, char* p_descripcion, char* p_imagenObjeto, TipoTrampa p_tipoTrampa, GestorEntidadesJuego* p_gestorEntidades);
	~Trampa();
	char usar();
	void actualizaEntidadJuego();
	void BeginContact(b2Contact* contact);

private:
	char c_usosTrampaClavos;
	Infectado* c_infectadoCapturado;
	TipoTrampa c_tipoTrampa;
	Reloj c_reloj;
	int c_delay;
	int c_duracion;
	char c_daño;
	char c_radio;
	bool c_enEstadoDelay;
	GestorEntidadesJuego* c_gestorEntidades;
	void actualizaTrampaBomba();
	void actualizaTrampaClavos(b2Contact* contact);
	void actualizaTrampaSoga(b2Contact* contact);
	void actualizaTrampaSonora();
	void actualizaTrampaFuego(b2Contact* contact);
	void colisionTrampaBomba(b2Contact* contact);
};

