#include "EscenaOpciones.h"
#include "FachadaMotorGrafico.h"
#include "GestorEventosEntrada.h"
#include "Constantes.h"
#include <irrlicht.h>

EscenaOpciones* EscenaOpciones::ptrInstanciaEscenaOpciones = 0;

EscenaOpciones* EscenaOpciones::dameEscenaOpciones()
{
	if (ptrInstanciaEscenaOpciones == 0)
		ptrInstanciaEscenaOpciones = new EscenaOpciones();
	return ptrInstanciaEscenaOpciones;
}

EscenaOpciones::EscenaOpciones()
{
}

EscenaOpciones::~EscenaOpciones()
{
}

void EscenaOpciones::actualizar(long p_tiempoTranscurridoUltimaActualizacion)
{
}

void EscenaOpciones::dibujar(float p_cantidadFrameTranscurrido)
{
	FachadaMotorGrafico::dameFachadaMotorGrafico()->dibuja();
}

void EscenaOpciones::gestionarEvento()
{
}

void EscenaOpciones::iniciar()
{
	irr::core::dimension2d<irr::u32> t_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();
	short t_espaciadoX = t_tamañoVentana.Width / 6;
	short t_espaciadoY = t_tamañoVentana.Height / 6;

	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addStaticText(
		L"VOLUMEN"
		, irr::core::rect<irr::s32>(t_tamañoVentana.Width / 6, t_tamañoVentana.Height / 6
		, (t_tamañoVentana.Width / 6) * 5, (t_tamañoVentana.Height / 6) * 5)
		, false, false, 0);

	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addScrollBar(
		true,
		irr::core::rect<irr::s32>((t_tamañoVentana.Width / 6) * 2, t_tamañoVentana.Height / 6
								, (t_tamañoVentana.Width / 6) * 4, (t_tamañoVentana.Height / 6) + ALTO_BOTON), 0, ID_MENU_OPCIONES_SCROLLBAR);

	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addButton(
		irr::core::rect<irr::s32>(t_tamañoVentana.Width / 2 - ANCHO_BOTON / 2, (t_tamañoVentana.Height / 7) * 6
		, t_tamañoVentana.Width / 2 + ANCHO_BOTON / 2, (t_tamañoVentana.Height / 7) * 6 + ALTO_BOTON)
		, 0, ID_BOTON_MENU_CREDITOS_VOLVER, L"VOLVER", L"VOLVER");

}

void EscenaOpciones::terminar()
{
	FachadaMotorGrafico::dameFachadaMotorGrafico()->borraGUI();
}