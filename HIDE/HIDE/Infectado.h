#pragma once
#include "EntidadInteractuable.h"
#include "EntidadInterpolable.h"
#include "MaquinaEstadosFinita.h"
#include "PlanificadorCaminos.h"
#include "Suscriptor.h"
class GestorEntidadesJuego;
const float			VELOCIDAD_ESTANDAR_INFECTADO = 0.003f;//0.015f;
const float			VELOCIDAD_ATAQUE_INFECTADO = 0.004f;

class Infectado : public EntidadInteractuable, public EntidadInterpolable, public Suscriptor
{
public:
	Infectado(float p_posicionX, float p_posicionZ, char p_tipoInfectado, Grafo* p_grafoMapa, Protagonista* p_protagonista, GestorEntidadesJuego* p_gestorEntidadesJuego);
	~Infectado();
	void actualizaEntidadJuego();
	bool estaElJugadorVisible();
	void mueveInfectado(b2Vec2 p_direccionMovimiento, float p_velocidadMovimiento);
	void setColorMalla(char p_color);
	void aullar();
	void mueveInfectadoHaciaPersonaje();
	bool protagonistaEnRangoAtaque();
	void ataca();
	float damePorcentajeVidaRestante(){ return c_vidaActual / (float)c_vidaInicial; }
	void interactua(Protagonista* p_protagonista);
	b2Vec2 damePosicionAlerta(){ return c_posicionAlerta; }
	void setPosicionAlerta(b2Vec2 p_posicionAlerta){ c_posicionAlerta.x = p_posicionAlerta.y; c_posicionAlerta.y = p_posicionAlerta.x; }
	PlanificadorCaminos* damePlanificador(){ return &c_planificadorCaminos; }
	MaquinaEstadosFinita* dameMEF(){ return &c_maquinaEstados; }
	b2Vec2 calculaDireccionMovimiento();
	Protagonista* dameProtagonista(){ return c_protagonista; }
	void recibeNotificacion(float p_posicionSonidox, float p_posicionSonidoy, VolumenSonidos p_volumen);
	void recibeDaño(char p_daño);
	void recibeDañoUsandoFisicas(char p_daño);
	void setMovimientoRestringido(bool p_movimientoRestringido){ c_movimientoRestringido = p_movimientoRestringido; }

private:
	bool c_eliminarEntidad;
	char c_vidaActual;
	char c_vidaInicial;
	char c_daño;
	MaquinaEstadosFinita c_maquinaEstados;
	PlanificadorCaminos c_planificadorCaminos;
	Protagonista* c_protagonista;
	b2Vec2 c_posicionAlerta;
	int c_ultimoTiempoAtaque;
	void giraInfectado(b2Vec2 dir);
	GestorEntidadesJuego* c_gestorEntidadesJuego;
	bool c_movimientoRestringido;
};

