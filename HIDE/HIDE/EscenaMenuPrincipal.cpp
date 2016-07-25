#include "EscenaMenuPrincipal.h"
#include "FachadaMotorGrafico.h"
#include "GestorEventosEntrada.h"
#include "GestorEscenas.h"
#include "Constantes.h"
#include <irrlicht.h>

EscenaMenuPrincipal* EscenaMenuPrincipal::ptrInstanciaEscenaMenuPrincipal = 0;

EscenaMenuPrincipal* EscenaMenuPrincipal::dameEscenaMenuPrincipal()
{
	if (ptrInstanciaEscenaMenuPrincipal == 0)
		ptrInstanciaEscenaMenuPrincipal = new EscenaMenuPrincipal();
	return ptrInstanciaEscenaMenuPrincipal;
}

EscenaMenuPrincipal::EscenaMenuPrincipal()
{
}

EscenaMenuPrincipal::~EscenaMenuPrincipal()
{
}

void EscenaMenuPrincipal::actualizar(long p_tiempoTranscurridoUltimaActualizacion)
{
	gestionarEvento();
}

void EscenaMenuPrincipal::dibujar(float p_cantidadFrameTranscurrido)
{
	FachadaMotorGrafico::dameFachadaMotorGrafico()->dibuja();
}

void EscenaMenuPrincipal::gestionarEvento()
{
}

void EscenaMenuPrincipal::iniciar()
{
	GestorEventosEntrada::dameGestorEventosEntrada();
	FachadaMotorGrafico::dameFachadaMotorGrafico();
	FachadaMotorGrafico::dameFachadaMotorGrafico()->iniciaCursorRaton();
	GestorEventosEntrada::dameGestorEventosEntrada()->setCursorVisible(true);
	
	irr::core::dimension2d<irr::u32> t_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();
	short t_espaciadoX = t_tamañoVentana.Width / 2 - ANCHO_BOTON / 2;
	short t_espaciadoY = t_tamañoVentana.Height / c_cantidadBotones;
	short t_mitadEspaciadoY = t_espaciadoY / 2;
	const wchar_t* t_textoBotones[] = { L"JUGAR", L"OPCIONES", L"CREDITOS", L"SALIR" };

	
	//IMAGEN DE FONDO
	irr::video::ITexture* t_fondo = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/fondo.jpg");
	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addImage(t_fondo, irr::core::vector2di(0, 0), false, 0, 1, L"");

	for (char t_boton = 0; t_boton < c_cantidadBotones; t_boton++)
	{
		FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addButton(
			irr::core::rect<irr::s32>(t_espaciadoX,				    t_espaciadoY * t_boton + t_mitadEspaciadoY
									, t_espaciadoX + ANCHO_BOTON,	t_espaciadoY * t_boton + t_mitadEspaciadoY + ALTO_BOTON)
									, 0, t_boton, t_textoBotones[t_boton], t_textoBotones[t_boton]);
	}
}

void EscenaMenuPrincipal::terminar()
{
	FachadaMotorGrafico::dameFachadaMotorGrafico()->borraGUI();
}