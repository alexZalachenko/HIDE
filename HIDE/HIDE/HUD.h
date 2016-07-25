#pragma once
#include <irrlicht.h>
#include <string>
class Objeto;
class Arma;

class HUD
{
public:
	HUD();
	~HUD();
	void dibujaHUD();
	void setDriver(irr::video::IVideoDriver* p_driver){ c_driver = p_driver; }
	void pierdeVida(char p_dano); 
	void ganaVida(char p_ganancia);
	void equipaObjeto(Objeto* p_objeto);
	void eliminaObjetoEquipado();
	void setMirillaVisible(bool p_mirillaVisible){ c_mirillaVisible = p_mirillaVisible; }

private:
	irr::video::ITexture* c_barraVida;
	irr::video::ITexture* c_equipado;
	irr::video::ITexture* c_mirilla;
	irr::core::dimension2d<irr::u32> c_mitadMirilla;
	irr::video::IVideoDriver* c_driver;
	irr::core::dimension2d<irr::u32> c_tamañoVentana;
	irr::core::dimension2d<irr::u32> c_posicionMirilla;
	irr::gui::IGUIFont* c_fuente;
	short c_pixelesVida;
	char c_vidaProtagonista;
	Objeto* c_objetoEquipado;
	std::string c_nombreObjeto;
	irr::core::stringw c_cantidadObjeto;
	Arma*  c_armaEquipada;
	bool c_mirillaVisible;

	const short c_tamañoCruzBarraVida = 55;
	const short c_tamañoBarraVida = 245;
};

