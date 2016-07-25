#pragma once
#include "IEventReceiver.h"
#include <irrlicht.h>

class GestorEventosEntrada : public irr::IEventReceiver
{
public:
	static GestorEventosEntrada* dameGestorEventosEntrada();
	bool OnEvent(const irr::SEvent& event);
	bool estaPresionadaTecla(irr::EKEY_CODE keyCode);
	bool estaPresionadoRatonDerecho();
	bool hayMovimientoRaton();
	bool hayMovimientoRuedaRaton();
	float dameDireccionMovimientoRuedaRaton();
	irr::core::vector2di dameDesplazamientoRaton();
	void iniciaCursorRaton(irr::gui::ICursorControl* p_cursorRaton);
	void setBloqueoRaton(bool p_bloquearRaton){ c_bloquearRaton = p_bloquearRaton; }
	void setCursorVisible(bool p_cursorVisible){ c_cursorRaton->setVisible(p_cursorVisible); }
	void setMenuAbierto(bool p_menuAbierto){ c_menuAbierto = p_menuAbierto; }
	bool dameMenuAbierto(){ return c_menuAbierto; }
	void reseteaRaton();
	bool hayClicIzquierdo();
	void setNotificaEscenaConEntidad(bool p_notifica){ c_notificaEscenaConEntidad = p_notifica; }
	
private:
	static GestorEventosEntrada* ptrInstanciaGestorEventosEntrada;
	GestorEventosEntrada();
	~GestorEventosEntrada();
	bool c_teclas[irr::KEY_KEY_CODES_COUNT];
	bool c_estaPulsadoBotonDerechoRaton;
	bool c_hayMovimientoRuedaRaton;
	float c_direccionMovimientoRuedaRaton;
	irr::core::vector2di c_desplazamientoRaton;
	irr::gui::ICursorControl* c_cursorRaton;
	int c_centroPantallaX;
	int c_centroPantallaY;
	bool c_bloquearRaton;
	bool c_menuAbierto;
	bool c_clicIzquierdo;
	bool c_botonIzquierdoPulsado;
	bool c_notificaEscenaConEntidad;
};

