#include "MenuOpciones.h"
#include "FachadaMotorGrafico.h"


MenuOpciones::MenuOpciones(GestorEntidadesJuego* p_gestorEntidadesJuego)
	: Menu(p_gestorEntidadesJuego)
{
	irr::gui::IGUIEnvironment* t_GUIEnviroment = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment();
	irr::core::dimension2d<irr::u32> t_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();

	c_ventanaMenu = t_GUIEnviroment->addWindow(
		irr::core::rect<irr::s32>(t_tamañoVentana.Width / 6, (t_tamañoVentana.Height / 6)
							   , (t_tamañoVentana.Width / 6) * 5, (t_tamañoVentana.Height / 6) * 5)
							   , false, L"MOCHILA", 0, 1);

	c_ventanaMenu->setDrawTitlebar(false);
	c_ventanaMenu->getCloseButton()->remove();
	c_ventanaMenu->setDraggable(false);
	
	irr::core::rect<irr::s32> t_tamañoMenu = c_ventanaMenu->getAbsoluteClippingRect();

	t_GUIEnviroment->addStaticText(
		L"VOLUMEN"
		, irr::core::rect<irr::s32>(t_tamañoMenu.getWidth() / 6, t_tamañoMenu.getHeight() / 6
		, (t_tamañoMenu.getWidth() / 6) * 5, (t_tamañoMenu.getHeight() / 6) * 5)
		, false, false, c_ventanaMenu, -1);

	t_GUIEnviroment->addScrollBar(
		true,
		irr::core::rect<irr::s32>((t_tamañoMenu.getWidth() / 6) * 2, t_tamañoMenu.getHeight() / 6
		, (t_tamañoMenu.getWidth() / 6) * 4, (t_tamañoMenu.getHeight() / 6) + ALTO_BOTON), c_ventanaMenu, ID_MENU_OPCIONES_SCROLLBAR);

	t_GUIEnviroment->addButton(
		irr::core::rect<irr::s32>(t_tamañoMenu.getWidth() / 2 - ANCHO_BOTON / 2, (t_tamañoMenu.getHeight() / 7) * 6
		, t_tamañoMenu.getWidth() / 2 + ANCHO_BOTON / 2, (t_tamañoMenu.getHeight() / 7) * 6 + ALTO_BOTON)
		, c_ventanaMenu, ID_BOTON_MENU_OPCIONES_JUEGO_VOLVER, L"VOLVER", L"VOLVER");

	c_ventanaMenu->setVisible(false);
}

MenuOpciones::~MenuOpciones()
{
}

void MenuOpciones::cambiaEstadoMenu()
{
	Menu::cambiaEstadoMenu();
}
