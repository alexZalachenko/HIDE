#pragma once
#include "Menu.h"
#include "Mochila.h"
#include <vector>

struct ObjetoSimplificado
{
	std::string nombre;
	std::string nombreImagen;
	short cantidad;
	bool esApilable;
};

class MenuConstruccion : public Menu
{
public:
	MenuConstruccion(GestorEntidadesJuego* p_gestorEntidadesJuego);
	~MenuConstruccion();
	void cambiaEstadoMenu();
	void RecibeEvento(const irr::SEvent* event);

private:
	irr::gui::IGUIListBox* c_listaObjetos;
	void iniciaMenuConstruccion();
	Mochila* c_mochila;
	irr::gui::IGUIImage* c_imagenObjeto1;
	irr::gui::IGUIImage* c_imagenObjeto2;
	irr::gui::IGUIImage* c_imagenObjeto3;
	irr::gui::IGUIImage* c_imagenHerramienta;
	irr::gui::IGUIImage* c_imagenObjetoResultado;

	/*************************************************************
	************************DRAG AND DROP*************************
	*************************************************************/


	std::vector<ObjetoSimplificado> c_copiaMochila;
	std::vector<ObjetoSimplificado> c_objetosEnImagenes;
	irr::gui::IGUIElement* c_guiElement_hovered;
	ObjetoSimplificado c_draggado;
	irr::gui::IGUIElement* c_padre;
	ObjetoSimplificado dameObjetoSeleccionado(short p_id);
	void añadeObjetoACasilla();
	void actualizaListaObjetos();
	void actualizaObjetoResultado();
	void eliminaObjetoMochilaCopia(std::string p_objeto);
	void actualizaMochilaOriginal();
};

