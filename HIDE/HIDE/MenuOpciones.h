#pragma once
#include "Menu.h"

class MenuOpciones : public Menu
{
public:
	MenuOpciones(GestorEntidadesJuego* p_gestorEntidadesJuego);
	~MenuOpciones();
	void cambiaEstadoMenu();
};

