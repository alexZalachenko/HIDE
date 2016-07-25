#pragma once
#include <irrlicht.h>
#include "EntidadInterpolable.h"
#include "Mochila.h"
#include "Reloj.h"
class GestorEntidadesJuego;
class HUD;
class Arma;
class EntidadInteractuable;

class Protagonista : public EntidadInterpolable
{
public:
	Protagonista(float p_posicionX, float p_posicionY, GestorEntidadesJuego* p_gestorEntidades);
	~Protagonista();
	void actualizaEntidadJuego();
	void calculaMovimiento();
	EntidadInteractuable* dameEntidadEnCruceta();
	Mochila* dameMochila();
	void recibeDaño(char p_dano);	
	char dameVidaActual(){ return c_vidaActual; }
	char damePeligrosidadArma();
	void interpolaPosicion(float p_cantidadFrameTranscurrido);
	void setJuegoPausado(bool p_juegoPausado);
	void equipaObjeto(Objeto* p_objeto);
	void usaObjetoEquipado();
	char ataca();
	Objeto* dameObjetoEquipado(){ return c_objetoEquipado; }
	void eliminaObjetoEquipado();
	bool c_muerto;

private:
	char c_vidaActual;
	Mochila c_mochila;
	irr::scene::ICameraSceneNode* c_camaraProtagonista;
	EnumEstaturaPersonaje c_estaturaActual;
	Objeto* c_objetoEquipado;
	irr::scene::IMeshSceneNode* c_auraObjetoApuntado;
	HUD* c_HUD;
	GestorEntidadesJuego* c_gestorEntidades;
	void recargaArmaEquipada();
	bool c_morfinaActiva;
	Reloj c_relojMorfina;
	Reloj c_relojUsoObjeto;
};

