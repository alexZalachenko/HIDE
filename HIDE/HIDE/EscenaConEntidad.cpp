#include "EscenaConEntidad.h"
#include "EscenaGameOver.h"
#include "FachadaMotorGrafico.h"
#include "FachadaMotorFisico.h"
#include "GestorEventosEntrada.h"
#include "CreadorMapa.h"
#include "GestorEscenas.h"
#include "EntidadInterpolable.h"
#include "Protagonista.h"
#include "Constantes.h"
#include "Objeto.h"

EscenaConEntidad* EscenaConEntidad::ptrInstanciaEscenaConEntidad = 0;

EscenaConEntidad* EscenaConEntidad::dameEscenaConEntidad()
{
	if (ptrInstanciaEscenaConEntidad == 0)
		ptrInstanciaEscenaConEntidad = new EscenaConEntidad();
	return ptrInstanciaEscenaConEntidad;
}

EscenaConEntidad::EscenaConEntidad()
{
}

EscenaConEntidad::~EscenaConEntidad()
{
		
}

void EscenaConEntidad::actualizar(long p_tiempoTranscurridoUltimaActualizacion)
{
	gestionarEvento();
	if (c_gestorEntidadesJuego.dameProtagonista()->c_muerto)
		GestorEscenas::dameGestorEscenas()->cambiaEscena(EscenaGameOver::dameEscenaGameOver());
	if (!c_juegoPausado)
	{
		c_gestorEntidadesJuego.guardaEstadoNuevoEnEstadoAntiguo();
		c_gestorEntidadesJuego.calculaEstadoNuevo(p_tiempoTranscurridoUltimaActualizacion);
		
		c_gestorEntidadesJuego.actualizaGeneradorInfectados();
		c_gestorEntidadesJuego.actualizaGeneradorObjetos();
	}
}

void EscenaConEntidad::dibujar(float p_cantidadFrameTranscurrido)
{
	if (!c_juegoPausado)
	{
		for each (EntidadInterpolable* t_entidadInterpolable in c_gestorEntidadesJuego.getEntidadesInterpolables())
			t_entidadInterpolable->interpolaPosicion(p_cantidadFrameTranscurrido);
	}
	FachadaMotorGrafico::dameFachadaMotorGrafico()->dibuja();
}

void EscenaConEntidad::gestionarEvento()
{
	if (GestorEventosEntrada::dameGestorEventosEntrada()->estaPresionadaTecla(irr::EKEY_CODE::KEY_KEY_P))
	{
		if (!GestorEventosEntrada::dameGestorEventosEntrada()->dameMenuAbierto())
		{
			c_menuPausa->cambiaEstadoMenu();
			GestorEventosEntrada::dameGestorEventosEntrada()->setMenuAbierto(true);
		}
	}
	if (GestorEventosEntrada::dameGestorEventosEntrada()->estaPresionadoRatonDerecho())
	{
		if (!GestorEventosEntrada::dameGestorEventosEntrada()->dameMenuAbierto())
		{
			c_menuJuego->cambiaEstadoMenu();
			GestorEventosEntrada::dameGestorEventosEntrada()->setMenuAbierto(true);
		}
	}
	if (GestorEventosEntrada::dameGestorEventosEntrada()->hayMovimientoRuedaRaton())
	{
		Protagonista* t_protagonista = c_gestorEntidadesJuego.dameProtagonista();
		if (GestorEventosEntrada::dameGestorEventosEntrada()->dameDireccionMovimientoRuedaRaton() > 0)
			t_protagonista->equipaObjeto(t_protagonista->dameMochila()->dameSiguienteObjeto(t_protagonista->dameObjetoEquipado()));
		else
			t_protagonista->equipaObjeto(t_protagonista->dameMochila()->dameAnteriorObjeto(t_protagonista->dameObjetoEquipado()));
	}
}

void EscenaConEntidad::iniciar()
{
	GestorEventosEntrada::dameGestorEventosEntrada();
	FachadaMotorGrafico::dameFachadaMotorGrafico();
	FachadaMotorGrafico::dameFachadaMotorGrafico()->iniciaCursorRaton();
	GestorEventosEntrada::dameGestorEventosEntrada()->setBloqueoRaton(true);
	GestorEventosEntrada::dameGestorEventosEntrada()->setMenuAbierto(false);
	c_juegoPausado = false;
	CreadorMapa t_creadorMapas(FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico());
	t_creadorMapas.LeeFicheroMapa("assets/mapas/mapa1.txt", &c_gestorEntidadesJuego);
	GestorEventosEntrada::dameGestorEventosEntrada()->reseteaRaton();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////ATAQUE////////////////////////////////
	c_gestorEntidadesJuego.creaArma(4, -4, MACHETE);
	c_gestorEntidadesJuego.creaArma(11, -11, PISTOLA);
	Objeto* o = c_gestorEntidadesJuego.creaObjetoSimple(9, -5, BALAS_PISTOLA);
	o->aumentaCantidad(); o->aumentaCantidad(); o->aumentaCantidad(); o->aumentaCantidad(); o->aumentaCantidad();
	o->aumentaCantidad(); o->aumentaCantidad(); o->aumentaCantidad(); o->aumentaCantidad(); o->aumentaCantidad();
	///////////////////////////////////////////////////////////////////


	/////////////////////////CRAFTEOS/////////////////////////////////
	c_gestorEntidadesJuego.creaObjetoSimple(6, -5, LISTON_MADERA);
	c_gestorEntidadesJuego.creaObjetoSimple(7, -5, CLAVOS);
	//////////////////////////////////////////////////////////////////

	
	/////////////////////////TODOS LOS OBJETOS///////////////////////////
	/*FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(0, 3, 0));
	c_gestorEntidadesJuego.creaTrampa(0, 0, TRAMPA_BOMBA);
	c_gestorEntidadesJuego.creaTrampa(1, 0, TRAMPA_SOGA);
	c_gestorEntidadesJuego.creaTrampa(2, 0, TRAMPA_SONORA);
	c_gestorEntidadesJuego.creaTrampa(3, 0, TRAMPA_FUEGO);
	c_gestorEntidadesJuego.creaTrampa(4, 0, TRAMPA_CLAVOS);
	c_gestorEntidadesJuego.creaArma(0, -2, ARCO);
	c_gestorEntidadesJuego.creaArma(1, -2, PISTOLA);
	c_gestorEntidadesJuego.creaArma(2, -2, REVOLVER);
	c_gestorEntidadesJuego.creaArma(3, -2, CUCHILLO);
	c_gestorEntidadesJuego.creaArma(4, -2, MACHETE);
	c_gestorEntidadesJuego.creaArma(5, -2, BATEBEISBOL);
	c_gestorEntidadesJuego.creaObjetoSimple(0, -4, POLVORA);
	c_gestorEntidadesJuego.creaObjetoSimple(1, -4, CUERDA);
	c_gestorEntidadesJuego.creaObjetoSimple(2, -4, HIERRO_DIMINUTO);
	c_gestorEntidadesJuego.creaObjetoSimple(3, -4, HIERRO_GRANDE);
	c_gestorEntidadesJuego.creaObjetoSimple(4, -4, HIERRO_PEQUEÑO);
	c_gestorEntidadesJuego.creaObjetoSimple(5, -4, LISTON_MADERA);
	c_gestorEntidadesJuego.creaObjetoSimple(6, -4, TABLON_MADERA);
	c_gestorEntidadesJuego.creaObjetoSimple(7, -4, CLAVOS);
	c_gestorEntidadesJuego.creaObjetoSimple(8, -4, MARTILLO);
	c_gestorEntidadesJuego.creaObjetoSimple(9, -4, PIEDRA_AFILAR);
	c_gestorEntidadesJuego.creaObjetoSimple(10, -4, SIERRA);
	c_gestorEntidadesJuego.creaObjetoSimple(11, -4, MECHERO);
	c_gestorEntidadesJuego.creaObjetoSimple(12, -4, HOJA_CUCHILLO);
	c_gestorEntidadesJuego.creaObjetoSimple(13, -4, HOJA_MACHETE);
	c_gestorEntidadesJuego.creaObjetoSimple(14, -4, MANGO_CUCHILLO);
	c_gestorEntidadesJuego.creaObjetoSimple(15, -4, MANGO_MACHETE);
	c_gestorEntidadesJuego.creaObjetoSimple(16, -4, BALAS_PISTOLA);
	c_gestorEntidadesJuego.creaObjetoSimple(17, -4, FLECHAS);*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//CREO MENU DE PAUSA
	const wchar_t* t_textoBotones[] = { L"OPCIONES", L"MENU PRINCIPAL", L"VOLVER" };
	c_menuPausa = new Menu(&c_gestorEntidadesJuego);
	c_menuPausa->creaMenuPausa(L"MENU DE PAUSA", t_textoBotones);
	
	//CREO MENU DURANTE JUEGO
	const wchar_t* t_textoBotones1[] = { L"MOCHILA", L"CONSTRUCCION", L"VOLVER" };
	c_menuJuego = new Menu(&c_gestorEntidadesJuego);
	c_menuJuego->creaMenuDuranteJuego(L"MENU DE JUEGO", t_textoBotones1);

	//CREO MENU MOCHILA
	c_menuMochila = new MenuMochila(&c_gestorEntidadesJuego);

	//CREO MENU CONSTRUCCION
	c_menuConstruccion = new MenuConstruccion(&c_gestorEntidadesJuego);

	//CREO MENU OPCIONES		
	c_menuOpciones = new MenuOpciones(&c_gestorEntidadesJuego);
}

void EscenaConEntidad::terminar()
{
	GestorEventosEntrada::dameGestorEventosEntrada()->setBloqueoRaton(false);
	c_gestorEntidadesJuego.eliminaTodasEntidades();
	FachadaMotorFisico::dameFachadaMotorFisico()->borraMundoFisico();
	FachadaMotorGrafico::dameFachadaMotorGrafico()->borraMapaJuego();
	FachadaMotorGrafico::dameFachadaMotorGrafico()->borraGUI();
	c_menuConstruccion = nullptr;
	GestorEventosEntrada::dameGestorEventosEntrada()->setNotificaEscenaConEntidad(false);
	delete ptrInstanciaEscenaConEntidad;
	ptrInstanciaEscenaConEntidad = nullptr;
}

