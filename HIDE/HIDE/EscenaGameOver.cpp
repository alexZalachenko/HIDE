#include "EscenaGameOver.h"
#include "FachadaMotorGrafico.h"
#include "GestorEventosEntrada.h"
#include "Constantes.h"
#include <irrlicht.h>

EscenaGameOver* EscenaGameOver::ptrInstanciaEscenaGameOver = 0;

EscenaGameOver* EscenaGameOver::dameEscenaGameOver()
{
	if (ptrInstanciaEscenaGameOver == 0)
		ptrInstanciaEscenaGameOver = new EscenaGameOver();
	return ptrInstanciaEscenaGameOver;
}

EscenaGameOver::EscenaGameOver()
{
}

EscenaGameOver::~EscenaGameOver()
{
}

void EscenaGameOver::actualizar(long p_tiempoTranscurridoUltimaActualizacion)
{
}

void EscenaGameOver::dibujar(float p_cantidadFrameTranscurrido)
{
	FachadaMotorGrafico::dameFachadaMotorGrafico()->dibuja();
}

void EscenaGameOver::gestionarEvento()
{
}

void EscenaGameOver::iniciar()
{
	GestorEventosEntrada::dameGestorEventosEntrada()->setBloqueoRaton(false);
	GestorEventosEntrada::dameGestorEventosEntrada()->setCursorVisible(true);
	irr::core::dimension2d<irr::u32> t_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();
	short t_espaciadoX = t_tamañoVentana.Width / 6;
	short t_espaciadoY = t_tamañoVentana.Height / 6;
	const wchar_t* t_textoGameOver = L"PARTIDA FINALIZADA";

	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addStaticText(
		t_textoGameOver
		, irr::core::rect<irr::s32>((t_tamañoVentana.Width / 2) - ANCHO_BOTON, t_tamañoVentana.Height / 2
		, (t_tamañoVentana.Width / 6) * 5, (t_tamañoVentana.Height / 6) * 5)
		, false, false, 0);

	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addButton(
		irr::core::rect<irr::s32>(t_tamañoVentana.Width / 2 - ANCHO_BOTON / 2, (t_tamañoVentana.Height / 7) * 6
		, t_tamañoVentana.Width / 2 + ANCHO_BOTON / 2, (t_tamañoVentana.Height / 7) * 6 + ALTO_BOTON)
		, 0, ID_BOTON_MENU_CREDITOS_VOLVER, L"SALIR", L"VOLVER");

}

void EscenaGameOver::terminar()
{
	FachadaMotorGrafico::dameFachadaMotorGrafico()->borraGUI();
}