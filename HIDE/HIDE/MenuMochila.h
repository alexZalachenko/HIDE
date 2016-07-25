#pragma once
#include "Menu.h"
#include <irrlicht.h>
#include "Mochila.h"
class Protagonista;

class MenuMochila : public Menu
{
public:
	MenuMochila(GestorEntidadesJuego* p_gestorEntidadesJuego);
	void cambiaEstadoMenu();
	void actualizaObjetoSeleccionado();
	void equipaObjetoSeleccionado();
	void eliminaObjetoSeleccionado();
	~MenuMochila();

private:
	irr::gui::IGUIImage* c_imagenObjeto;
	irr::gui::IGUIStaticText* c_textoPeso;
	irr::gui::IGUIStaticText* c_textoCantidad;
	irr::gui::IGUIStaticText* c_textoDescripcion;
	irr::gui::IGUIStaticText* c_textoPesoMochila;
	irr::gui::IGUIListBox* c_listaObjetos;
	Mochila* c_mochila;
	Protagonista* c_protagonista;
	void iniciaMenuMochila();
	void setItemGenericoInterfaz();
};

