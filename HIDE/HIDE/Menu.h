#pragma once
#include <irrlicht.h>
#include "GestorEntidadesJuego.h"

class Menu
{
public:
	Menu(GestorEntidadesJuego* p_gestorEntidadesJuego);
	~Menu();
	virtual void cambiaEstadoMenu();
	void creaMenuPausa(wchar_t* p_nombreVentana, const wchar_t* p_textoBotones[]);
	void creaMenuDuranteJuego(wchar_t* p_nombreVentana, const wchar_t* p_textoBotones[]);

protected:
	irr::gui::IGUIWindow* c_ventanaMenu;
	GestorEntidadesJuego* c_gestorEntidadesJuego;
};

