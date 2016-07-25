#include "HUD.h"
#include "FachadaMotorGrafico.h"
#include "Constantes.h"
#include "Arma.h"
#include "Objeto.h"


HUD::HUD()
	: c_mirillaVisible(true)
{
	FachadaMotorGrafico::dameFachadaMotorGrafico()->setHUD(this);
	c_barraVida = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTextura("assets/imagenes/barraVida.png");
	c_pixelesVida = c_barraVida->getSize().Width;
	c_vidaProtagonista = VIDA_INICIAL_PROTAGONISTA;

	c_equipado = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTextura("assets/imagenes/imagenEquipado2.png");
	c_mirilla = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTextura("assets/imagenes/mirillaRaton.png");
	c_mitadMirilla.Width = c_mirilla->getSize().Width / 2;
	c_mitadMirilla.Height = c_mirilla->getSize().Height / 2;

	FachadaMotorGrafico::dameFachadaMotorGrafico()->iniciaCursorRaton();
	c_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();
	c_posicionMirilla.Height = c_tamañoVentana.Height / 2 - c_mitadMirilla.Height;
	c_posicionMirilla.Width = c_tamañoVentana.Width / 2 - c_mitadMirilla.Width;
	
	c_fuente = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->getSkin()->getFont();
	c_nombreObjeto = "SIN ARMA";
	c_cantidadObjeto = "0/0";
	c_objetoEquipado = nullptr;
}

HUD::~HUD()
{
	//c_barraVida->drop();
	//c_mirilla->drop();
	//c_equipado->drop();
	//c_fuente->drop();
	FachadaMotorGrafico::dameFachadaMotorGrafico()->setHUD(nullptr);
}

void HUD::dibujaHUD()
{
	//DIBUJO BARRA DE VIDA
	c_driver->draw2DImage(
		//TEXTURA	
		c_barraVida,
		//POSICION DESTINO
		irr::core::position2di(0, c_tamañoVentana.Height - c_barraVida->getSize().Height),
		//SOURCE RECT
		irr::core::rect<irr::s32>(0,                            0, 
								  c_barraVida->getSize().Width, c_barraVida->getSize().Height),
		//CLIP RECT
		&irr::core::rect<irr::s32>(0,             c_tamañoVentana.Height - c_barraVida->getSize().Height,
								   c_pixelesVida, c_tamañoVentana.Height),
		//COLOR CON EL QUE SE DIBUJA LA IMAGEN
		irr::video::SColor(255, 255, 255, 255),
		//USAR CANAL ALPHA
		true
	);

	//DIBUJO EQUIPAMIENTO
	c_driver->draw2DImage(
		//TEXTURA	
		c_equipado,
		//POSICION DESTINO
		irr::core::position2di(c_tamañoVentana.Width - c_equipado->getSize().Width, c_tamañoVentana.Height - c_equipado->getSize().Height),
		//SOURCE RECT
		irr::core::rect<irr::s32>(0,                           0, 
								  c_equipado->getSize().Width, c_equipado->getSize().Height),
		//CLIP RECT
		0,
		//COLOR CON EL QUE SE DIBUJA LA IMAGEN
		irr::video::SColor(255, 255, 255, 255),
		//USAR CANAL ALPHA
		true
	);

	///DIBUJO MIRILLA
	if (c_mirillaVisible)
	{
		c_driver->draw2DImage(
			//TEXTURA	
			c_mirilla,
			//POSICION DESTINO
			irr::core::position2di(c_posicionMirilla.Width
			, c_posicionMirilla.Height),
			//SOURCE RECT
			irr::core::rect<irr::s32>(0, 0,
			c_mirilla->getSize().Width, c_mirilla->getSize().Height),
			//CLIP RECT
			0,
			//COLOR CON EL QUE SE DIBUJA LA IMAGEN
			irr::video::SColor(255, 255, 255, 255),
			//USAR CANAL ALPHA
			true
			);
	}
	
	irr::s32 posy = c_tamañoVentana.Height - c_barraVida->getSize().Height / 2;
	irr::core::stringw t_textoVidaProtagonista = L"";
	t_textoVidaProtagonista += c_vidaProtagonista;

	//ESCRIBO LOS PUNTOS DE VIDA EN LA BARRA DE VIDA
	c_fuente->draw(
		//TEXTO	
		t_textoVidaProtagonista,
		//POSICION
		irr::core::rect<irr::s32>(60, posy,
								  60, posy),
		//COLOR
		irr::video::SColor(255, 0, 0, 0)
	);
		if (c_objetoEquipado)
	{
		if (c_armaEquipada)
		{
			c_cantidadObjeto = "";
			c_cantidadObjeto += c_armaEquipada->dameCargadorActual();
			c_cantidadObjeto += "/";
			c_cantidadObjeto += c_armaEquipada->dameTamañoMaximoCargador();
		}
		else
		{
			c_cantidadObjeto = "1/";
			c_cantidadObjeto += c_objetoEquipado->dameCantidad();
		}
	}
		//ESCRIBO EL NOMBRE DEL OBJETO EQUIPADO SI LO HAY
	c_fuente->draw(
		//TEXTO	
		c_nombreObjeto.c_str(),
		//POSICION
		irr::core::rect<irr::s32>(c_tamañoVentana.Width - c_equipado->getSize().Width + 15, c_tamañoVentana.Height - c_equipado->getSize().Height + 7,
		60, 60),
		//COLOR
		irr::video::SColor(255, 0, 0, 0)
	);

	c_fuente->draw(
		//TEXTO	
		c_cantidadObjeto,
		//POSICION
		irr::core::rect<irr::s32>(c_tamañoVentana.Width - c_equipado->getSize().Width + 15, c_tamañoVentana.Height - c_equipado->getSize().Height / 2,
		60, 60),
		//COLOR
		irr::video::SColor(255, 0, 0, 0)
	);
}

void HUD::pierdeVida(char p_dano)
{
	c_vidaProtagonista -= p_dano;
	float t_porcentajeVida = c_vidaProtagonista / (float)VIDA_INICIAL_PROTAGONISTA;
	c_pixelesVida = short(c_tamañoCruzBarraVida + c_tamañoBarraVida * t_porcentajeVida);
}

void HUD::ganaVida(char p_ganancia)
{
	if (c_vidaProtagonista + p_ganancia >= VIDA_INICIAL_PROTAGONISTA)
		c_vidaProtagonista = VIDA_INICIAL_PROTAGONISTA;
	else
		c_vidaProtagonista += p_ganancia;

	float t_porcentajeVida = c_vidaProtagonista / (float)VIDA_INICIAL_PROTAGONISTA;
	c_pixelesVida = short(c_tamañoCruzBarraVida + c_tamañoBarraVida * t_porcentajeVida);
}

void HUD::equipaObjeto(Objeto* p_objeto)
{
	c_objetoEquipado = p_objeto;
	c_nombreObjeto = c_objetoEquipado->dameNombre();
	c_armaEquipada = dynamic_cast<Arma*>(c_objetoEquipado);
}

void HUD::eliminaObjetoEquipado()
{
	c_nombreObjeto = "SIN ARMA";
	c_cantidadObjeto = "0/0";
	c_objetoEquipado = nullptr;
}
