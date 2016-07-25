#include "GestorEventosEntrada.h"
#include "FachadaMotorGrafico.h"
#include "Constantes.h"
#include "GestorEscenas.h"
#include "EscenaConEntidad.h"
#include "EscenaMenuPrincipal.h"
#include "EscenaCreditos.h"
#include "EscenaOpciones.h"

using namespace irr;
using namespace core;

GestorEventosEntrada* GestorEventosEntrada::ptrInstanciaGestorEventosEntrada = 0;

GestorEventosEntrada* GestorEventosEntrada::dameGestorEventosEntrada()
{
	if (ptrInstanciaGestorEventosEntrada == 0)
		ptrInstanciaGestorEventosEntrada = new GestorEventosEntrada();
	return ptrInstanciaGestorEventosEntrada;
}

GestorEventosEntrada::GestorEventosEntrada()
	: c_desplazamientoRaton(0)
	, c_bloquearRaton(false)
	, c_menuAbierto(false)
	, c_hayMovimientoRuedaRaton(false)
	, c_clicIzquierdo(false)
	, c_notificaEscenaConEntidad(false)
{
	for (unsigned char t_teclaAIniciar = 0; t_teclaAIniciar<KEY_KEY_CODES_COUNT; t_teclaAIniciar++)
		c_teclas[t_teclaAIniciar] = false;
}

GestorEventosEntrada::~GestorEventosEntrada()
{
	delete ptrInstanciaGestorEventosEntrada;
	ptrInstanciaGestorEventosEntrada = 0;
}

bool GestorEventosEntrada::estaPresionadaTecla(irr::EKEY_CODE keyCode)
{
	return c_teclas[keyCode];
}

bool GestorEventosEntrada::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		c_teclas[event.KeyInput.Key] = event.KeyInput.PressedDown;
		if (event.KeyInput.Key == KEY_ESCAPE)
			GestorEscenas::dameGestorEscenas()->termina();
	}
	else if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
			case EMIE_MOUSE_MOVED:
				if (c_bloquearRaton && (c_cursorRaton->getPosition().X != c_centroPantallaX || c_cursorRaton->getPosition().Y != c_centroPantallaY))
				{
					vector2di c_desplazamientoAhora = vector2di(  c_cursorRaton->getPosition().X - c_centroPantallaX
																, c_cursorRaton->getPosition().Y - c_centroPantallaY);
					c_desplazamientoRaton.X = c_desplazamientoAhora.X + c_desplazamientoRaton.X;
					c_desplazamientoRaton.Y = c_desplazamientoAhora.Y + c_desplazamientoRaton.Y;
					c_cursorRaton->setPosition(vector2di(c_centroPantallaX, c_centroPantallaY));
				}
				break;

			case EMIE_LMOUSE_LEFT_UP:
				if (c_notificaEscenaConEntidad)
					EscenaConEntidad::dameEscenaConEntidad()->dameMenuConstruccion()->RecibeEvento(&event);
				c_clicIzquierdo = true;
				break;

			case EMIE_RMOUSE_PRESSED_DOWN:
				c_estaPulsadoBotonDerechoRaton = true;
				break;

			case EMIE_RMOUSE_LEFT_UP:
				c_estaPulsadoBotonDerechoRaton = false;
				break;

			case EMIE_MOUSE_WHEEL:
				c_hayMovimientoRuedaRaton = true;
				c_direccionMovimientoRuedaRaton = event.MouseInput.Wheel;
				break;
		}
	}
	else if (event.EventType == EET_GUI_EVENT) 
	{
		if (c_notificaEscenaConEntidad)
			EscenaConEntidad::dameEscenaConEntidad()->dameMenuConstruccion()->RecibeEvento(&event);
		switch (event.GUIEvent.EventType)
		{
			case gui::EGET_BUTTON_CLICKED:
				switch (event.GUIEvent.Caller->getID())
				{
					/***********************************************************************
					************************ MENU PRINCIPAL*********************************
					***********************************************************************/
					case ID_BOTON_MENU_PRINCIPAL_JUGAR:
						GestorEscenas::dameGestorEscenas()->cambiaEscena(EscenaConEntidad::dameEscenaConEntidad());
						break;
					case ID_BOTON_MENU_PRINCIPAL_OPCIONES:
						GestorEscenas::dameGestorEscenas()->cambiaEscena(EscenaOpciones::dameEscenaOpciones());
						break;
					case ID_BOTON_MENU_PRINCIPAL_CREDITOS:
						GestorEscenas::dameGestorEscenas()->cambiaEscena(EscenaCreditos::dameEscenaCreditos());
						break;
					case ID_BOTON_MENU_PRINCIPAL_SALIR:
						GestorEscenas::dameGestorEscenas()->termina();
						break;

					/***********************************************************************
					*****************************MENU PAUSA*********************************
					***********************************************************************/
					case ID_BOTON_MENU_PAUSA_OPCIONES:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuPausa()->cambiaEstadoMenu();
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuOpciones()->cambiaEstadoMenu();
						break;
					case ID_BOTON_MENU_PAUSA_MENU_PRINCIPAL:
						GestorEscenas::dameGestorEscenas()->cambiaEscena(EscenaMenuPrincipal::dameEscenaMenuPrincipal());
						break;
					case ID_BOTON_MENU_PAUSA_VOLVER:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuPausa()->cambiaEstadoMenu();
						c_menuAbierto = false;
						hayClicIzquierdo();
						break;

					/***********************************************************************
					*************************MENU DURANTE JUEGO*****************************
					***********************************************************************/
					case ID_BOTON_MENU_DURANTE_JUEGO_MOCHILA:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuJuego()->cambiaEstadoMenu();
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuMochila()->cambiaEstadoMenu();
						break;
					case ID_BOTON_MENU_DURANTE_JUEGO_CONSTRUCCION:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuJuego()->cambiaEstadoMenu();
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuConstruccion()->cambiaEstadoMenu();
						break;
					case ID_BOTON_MENU_DURANTE_JUEGO_VOLVER:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuJuego()->cambiaEstadoMenu();
						c_menuAbierto = false;
						hayClicIzquierdo();
						break;


					/***********************************************************************
					*************************MENU OPCIONES JUEGO****************************
					***********************************************************************/
					case ID_BOTON_MENU_OPCIONES_JUEGO_VOLVER:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuOpciones()->cambiaEstadoMenu();
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuPausa()->cambiaEstadoMenu();
						break;


					/***********************************************************************
					*****************************MENU MOCHILA*******************************
					***********************************************************************/
					case ID_BOTON_MENU_MOCHILA_EQUIPA:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuMochila()->equipaObjetoSeleccionado();
						break;
					case ID_BOTON_MENU_MOCHILA_ELIMINA:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuMochila()->eliminaObjetoSeleccionado();
						break;
					case ID_BOTON_MENU_MOCHILA_VOLVER:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuMochila()->cambiaEstadoMenu();
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuJuego()->cambiaEstadoMenu();
						break;

					/***********************************************************************
					****************************MENU CONSTRUCCION***************************
					***********************************************************************/
					case ID_BOTON_MENU_CONSTRUCCION_CREAR:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuMochila()->equipaObjetoSeleccionado();
						break;
					case ID_BOTON_MENU_CONSTRUCCION_VOLVER:
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuConstruccion()->cambiaEstadoMenu();
						EscenaConEntidad::dameEscenaConEntidad()->dameMenuJuego()->cambiaEstadoMenu();
						break;

					/***********************************************************************
					************************ MENU PRINCIPAL*********************************
					***********************************************************************/
					case ID_BOTON_MENU_CREDITOS_VOLVER:
						GestorEscenas::dameGestorEscenas()->cambiaEscena(EscenaMenuPrincipal::dameEscenaMenuPrincipal());
						break;
				}
				break;

			case gui::EGET_LISTBOX_CHANGED:
				EscenaConEntidad::dameEscenaConEntidad()->dameMenuMochila()->actualizaObjetoSeleccionado();
				break;
		}
	}
	return false;
}

bool GestorEventosEntrada::estaPresionadoRatonDerecho()
{
	return c_estaPulsadoBotonDerechoRaton;
}

vector2di GestorEventosEntrada::dameDesplazamientoRaton()
{
	vector2di r_desplazamientoRaton = c_desplazamientoRaton;
	c_desplazamientoRaton = vector2di(0, 0);
	return r_desplazamientoRaton;
}

bool GestorEventosEntrada::hayMovimientoRaton()
{
	if (c_desplazamientoRaton.X != 0 || c_desplazamientoRaton.Y != 0)
		return true;
	return false;
}

bool GestorEventosEntrada::hayMovimientoRuedaRaton()
{
	bool t_hayMovimientoRuedaRaton = c_hayMovimientoRuedaRaton;
	c_hayMovimientoRuedaRaton = false;
	return t_hayMovimientoRuedaRaton;
}

float GestorEventosEntrada::dameDireccionMovimientoRuedaRaton()
{
	float t_direccionMovimientoRuedaRaton = c_direccionMovimientoRuedaRaton;
	return t_direccionMovimientoRuedaRaton;
}

void GestorEventosEntrada::iniciaCursorRaton(irr::gui::ICursorControl* p_cursorRaton)
{
	c_centroPantallaX = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana().Width / 2;
	c_centroPantallaY = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana().Height / 2;
	c_cursorRaton = p_cursorRaton;
	c_cursorRaton->setVisible(false);
}

void GestorEventosEntrada::reseteaRaton()
{
	c_cursorRaton->setPosition(vector2di(c_centroPantallaX, c_centroPantallaY));
	c_desplazamientoRaton = vector2di(0, 0);
}

bool GestorEventosEntrada::hayClicIzquierdo()
{
	bool t_clicIzquierdo = c_clicIzquierdo;
	c_clicIzquierdo = false;
	return t_clicIzquierdo;
}

