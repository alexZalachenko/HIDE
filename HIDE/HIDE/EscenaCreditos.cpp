#include "EscenaCreditos.h"
#include "FachadaMotorGrafico.h"
#include "GestorEventosEntrada.h"
#include "Constantes.h"
#include <irrlicht.h>

EscenaCreditos* EscenaCreditos::ptrInstanciaEscenaCreditos = 0;

EscenaCreditos* EscenaCreditos::dameEscenaCreditos()
{
	if (ptrInstanciaEscenaCreditos == 0)
		ptrInstanciaEscenaCreditos = new EscenaCreditos();
	return ptrInstanciaEscenaCreditos;
}

EscenaCreditos::EscenaCreditos()
{
}

EscenaCreditos::~EscenaCreditos()
{
}

void EscenaCreditos::actualizar(long p_tiempoTranscurridoUltimaActualizacion)
{
}

void EscenaCreditos::dibujar(float p_cantidadFrameTranscurrido)
{
	FachadaMotorGrafico::dameFachadaMotorGrafico()->dibuja();
}

void EscenaCreditos::gestionarEvento()
{
}

void EscenaCreditos::iniciar()
{
	irr::core::dimension2d<irr::u32> t_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();
	short t_espaciadoX = t_tamañoVentana.Width / 6;
	short t_espaciadoY = t_tamañoVentana.Height / 6;
	const wchar_t* t_textoCreditos = L" CREDITOS                                                  SOFTWARE UTILIZADO:\n\n IDEA ORIGINAL: ALEX VERDU                            - ERIN CATTO'S BOX2D\n\n DESARROLLADOR: ALEX VERDU                          - IRRLICHT ENGINE\n\n MODELADO 3D: ALEX VERDU\n\n COMPOSITOR: TOMAS ESCOLANO\n\n ILUSTRACION: TOMAS ESCOLANO\n\n";

	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addStaticText(
		t_textoCreditos
		, irr::core::rect<irr::s32>(t_tamañoVentana.Width / 6,		t_tamañoVentana.Height / 6
								  ,(t_tamañoVentana.Width / 6) * 5,(t_tamañoVentana.Height / 6) * 5)
		, false, false, 0);

	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addButton(
		irr::core::rect<irr::s32>(t_tamañoVentana.Width / 2 - ANCHO_BOTON / 2, (t_tamañoVentana.Height / 7) * 6
								, t_tamañoVentana.Width / 2 + ANCHO_BOTON / 2, (t_tamañoVentana.Height / 7) * 6 + ALTO_BOTON)
								, 0, ID_BOTON_MENU_CREDITOS_VOLVER, L"VOLVER", L"VOLVER");

}

void EscenaCreditos::terminar()
{
	FachadaMotorGrafico::dameFachadaMotorGrafico()->borraGUI();
}