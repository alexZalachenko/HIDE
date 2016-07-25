#pragma once
#include "Escena.h"
#include "GestorEntidadesJuego.h"
#include <irrlicht.h>
#include "Menu.h"
#include "MenuMochila.h"
#include "MenuConstruccion.h"
#include "MenuOpciones.h"

class EscenaConEntidad : public Escena
{
public:
	static EscenaConEntidad* dameEscenaConEntidad();
	~EscenaConEntidad();
	void actualizar(long p_tiempoTranscurridoUltimaActualizacion);
	void dibujar(float p_cantidadFrameTranscurrido);
	void gestionarEvento();
	void iniciar();
	void terminar();
	Menu* dameMenuPausa(){ return c_menuPausa; }
	Menu* dameMenuJuego(){ return c_menuJuego; }
	MenuMochila* dameMenuMochila(){ return c_menuMochila; }
	MenuConstruccion* dameMenuConstruccion(){ return c_menuConstruccion; }
	MenuOpciones* dameMenuOpciones(){ return c_menuOpciones; }
	GestorEntidadesJuego* dameGestorEntidadesJuego(){ return &c_gestorEntidadesJuego; }
	void setJuegoPausado(){ c_juegoPausado = !c_juegoPausado; }


private:
	static EscenaConEntidad* ptrInstanciaEscenaConEntidad;
	EscenaConEntidad();
	GestorEntidadesJuego c_gestorEntidadesJuego;
	Menu* c_menuPausa;
	Menu* c_menuJuego;
	MenuMochila* c_menuMochila;
	MenuConstruccion* c_menuConstruccion;
	MenuOpciones* c_menuOpciones;
	bool c_juegoPausado;
};

