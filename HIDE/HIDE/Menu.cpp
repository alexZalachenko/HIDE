#include "Menu.h"
#include "GestorEventosEntrada.h"
#include "GestorEntidadesJuego.h"
#include "Protagonista.h"
#include "FachadaMotorGrafico.h"
#include "EscenaConEntidad.h"


Menu::Menu(GestorEntidadesJuego* p_gestorEntidadesJuego)
	: c_gestorEntidadesJuego(p_gestorEntidadesJuego)
{
}

Menu::~Menu()
{
}

void Menu::cambiaEstadoMenu()
{
	bool t_estadoMenu = c_ventanaMenu->isVisible();
	c_ventanaMenu->setVisible(!t_estadoMenu);
	GestorEventosEntrada::dameGestorEventosEntrada()->setBloqueoRaton(t_estadoMenu);
	GestorEventosEntrada::dameGestorEventosEntrada()->setCursorVisible(!t_estadoMenu);
	EscenaConEntidad::dameEscenaConEntidad()->setJuegoPausado();
	c_gestorEntidadesJuego->dameProtagonista()->setJuegoPausado(!t_estadoMenu);
	if (t_estadoMenu)
		GestorEventosEntrada::dameGestorEventosEntrada()->reseteaRaton();
}

void Menu::creaMenuPausa(wchar_t* p_nombreVentana, const wchar_t* p_textoBotones[])
{
	irr::core::dimension2d<irr::u32> t_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();
	c_ventanaMenu = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addWindow(
		irr::core::rect<irr::s32>(t_tamañoVentana.Width / 4, (t_tamañoVentana.Height / 6) * 2
		, (t_tamañoVentana.Width / 4) * 3, (t_tamañoVentana.Height / 6) * 4),
		false, p_nombreVentana, 0, 1);
	c_ventanaMenu->setDrawTitlebar(false);
	c_ventanaMenu->getCloseButton()->remove();
	c_ventanaMenu->setDraggable(false);
	short t_espaciadoX = c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 3;
	short t_espaciadoY = c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 3;
	short posx = t_espaciadoX / 2 - ANCHO_BOTON / 2;
	short posy = t_espaciadoY + t_espaciadoY / 2 - ALTO_BOTON / 2;
	char t_numeroBotones = 3;
	char id = 4;
	for (char t_boton = 0; t_boton < t_numeroBotones; t_boton++)
	{
		FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addButton(
			irr::core::rect<irr::s32>(posx, posy
			, posx + ANCHO_BOTON, posy + ALTO_BOTON)
			, c_ventanaMenu, id, p_textoBotones[t_boton], p_textoBotones[t_boton]);
		posx += t_espaciadoX;
		id++;
	}
	c_ventanaMenu->setVisible(false);
}

void Menu::creaMenuDuranteJuego(wchar_t* p_nombreVentana, const wchar_t* p_textoBotones[])
{
	irr::core::dimension2d<irr::u32> t_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();
	c_ventanaMenu = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addWindow(
		irr::core::rect<irr::s32>(t_tamañoVentana.Width / 4, (t_tamañoVentana.Height / 6) * 2
		, (t_tamañoVentana.Width / 4) * 3, (t_tamañoVentana.Height / 6) * 4),
		false, L"MENU JUEGO", 0, 1);
	c_ventanaMenu->setDrawTitlebar(false);
	c_ventanaMenu->getCloseButton()->remove();
	c_ventanaMenu->setDraggable(false);
	char id = 7;
	short t_espaciadoX = c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 3;
	short t_espaciadoY = c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 3;
	short posx = t_espaciadoX / 2 - ANCHO_BOTON / 2;
	short posy = t_espaciadoY + t_espaciadoY / 2 - ALTO_BOTON / 2;
	char t_numeroBotones = 3;
	for (char t_boton = 0; t_boton < t_numeroBotones; t_boton++)
	{
		FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addButton(
			irr::core::rect<irr::s32>(posx, posy
			, posx + ANCHO_BOTON, posy + ALTO_BOTON)
			, c_ventanaMenu, id, p_textoBotones[t_boton], p_textoBotones[t_boton]);
		posx += t_espaciadoX;
		id++;
	}
	c_ventanaMenu->setVisible(false);
}