#include "Protagonista.h"
#include "EntidadInteractuable.h"
#include "GestorEventosEntrada.h"
#include "Constantes.h"
#include "FachadaMotorGrafico.h"
#include "Arma.h"
#include "LanzadorRayCast.h"
#include "HUD.h"
#include "GestorEntidadesJuego.h"
#include "Publicador.h"
#include "GestorEscenas.h"
#include "EscenaMenuPrincipal.h"

const short TIEMPO_ENTRE_USOS_OBJETO = 350;

Protagonista::Protagonista(float p_posicionX, float p_posicionZ, GestorEntidadesJuego* p_gestorEntidades)
	: EntidadInterpolable(p_posicionX, p_posicionZ, "assets/protagonista/patasProta.obj")
	, c_auraObjetoApuntado(nullptr)
	, c_vidaActual(VIDA_INICIAL_PROTAGONISTA)
	, c_gestorEntidades(p_gestorEntidades)
	, c_mochila(p_gestorEntidades)
	, c_objetoEquipado(nullptr)
	, c_morfinaActiva(false)
	, c_muerto(false)
{
	c_camaraProtagonista = FachadaMotorGrafico::dameFachadaMotorGrafico()->añadeCamara(p_posicionX, p_posicionZ);
	c_HUD = new HUD();
}

Protagonista::~Protagonista()
{
	c_camaraProtagonista->remove();
	if (c_auraObjetoApuntado != nullptr)
		c_auraObjetoApuntado->remove();
	delete c_HUD;
}

void Protagonista::actualizaEntidadJuego()
{
	calculaMovimiento();
	EntidadInteractuable* t_entidadEnCruceta = dameEntidadEnCruceta();
	if (t_entidadEnCruceta != nullptr)
	{
		if (GestorEventosEntrada::dameGestorEventosEntrada()->hayClicIzquierdo())
			t_entidadEnCruceta->interactua(this);
		else if (c_auraObjetoApuntado == nullptr)
		{
			Objeto* t_objetoEnCruceta = dynamic_cast<Objeto*>(t_entidadEnCruceta);
			if (t_objetoEnCruceta != 0)
				c_auraObjetoApuntado = t_objetoEnCruceta->dibujaAura();
		}
	}
	else
	{
		if (c_auraObjetoApuntado != nullptr)
		{
			c_auraObjetoApuntado->remove();
			c_auraObjetoApuntado = nullptr;
		}
		if (GestorEventosEntrada::dameGestorEventosEntrada()->hayClicIzquierdo() && c_objetoEquipado != nullptr)
			usaObjetoEquipado();
	}
	if (c_morfinaActiva && c_relojMorfina.dameTiempoTranscurridoMilisegundos() > TIEMPO_INVULNERABILIDAD_MORFINA)
		c_morfinaActiva = false;
}

void Protagonista::calculaMovimiento()
{
	/*************************************************
	*     CALCULO DE LA ESTATURA Y VELOCIDAD         *
	*************************************************/
	float t_nuevaVelocidad;
	EnumEstaturaPersonaje t_nuevaEstatura;
	VolumenSonidos t_volumen;
	if (GestorEventosEntrada::dameGestorEventosEntrada()->estaPresionadaTecla(irr::EKEY_CODE::KEY_SPACE))
	{
		t_nuevaVelocidad = VELOCIDAD_ANDAR_PROTAGONISTA;
		t_nuevaEstatura = ERGUIDO;
		t_volumen = BAJO;
	}
	else if (GestorEventosEntrada::dameGestorEventosEntrada()->estaPresionadaTecla(irr::EKEY_CODE::KEY_LSHIFT))
	{
		t_nuevaVelocidad = VELOCIDAD_GATEAR_PROTAGONISTA;
		t_nuevaEstatura = AGACHADO;
		t_volumen = SINSONIDO;
	}
	else
	{
		t_nuevaVelocidad = VELOCIDAD_CORRER_PROTAGONISTA;
		t_nuevaEstatura = ERGUIDO;
		t_volumen = MEDIO;
	}
	if (t_nuevaEstatura != c_estaturaActual)
	{
		irr::core::vector3df t_posicionNueva = damePosicionNueva();
		t_posicionNueva.Y = (float)t_nuevaEstatura;
		c_estaturaActual = t_nuevaEstatura;
		setPosicionNueva(t_posicionNueva);
	}

	/*************************************************
	*       CALCULO DE ROTACION DE LA CAMARA         *
	*************************************************/
	float t_rotacionCamaraY = c_camaraProtagonista->getRotation().Y;
	float t_rotacionCamaraX = c_camaraProtagonista->getRotation().X;
	if (GestorEventosEntrada::dameGestorEventosEntrada()->hayMovimientoRaton())
	{
		irr::core::vector2di t_desplazamientoRaton = GestorEventosEntrada::dameGestorEventosEntrada()->dameDesplazamientoRaton();
		t_rotacionCamaraY += (float)t_desplazamientoRaton.X * VELOCIDAD_GIRO_PROTAGONISTA;
		t_rotacionCamaraX += (float)t_desplazamientoRaton.Y * VELOCIDAD_GIRO_PROTAGONISTA;
		if (t_rotacionCamaraX < -89)
			t_rotacionCamaraX = -89;
		else if (t_rotacionCamaraX > 89)
			t_rotacionCamaraX = 89;
		setRotacionNueva(irr::core::vector3df(t_rotacionCamaraX, t_rotacionCamaraY, 0));
	}

	/*************************************************
	*        CALCULO DIRECCION DE MOVIMIENTO         *
	*************************************************/
	b2Vec2 t_direccionMovimiento(0, 0); 
	irr::core::vector3df t_rotacionCamara = c_camaraProtagonista->getRotation();
	if (GestorEventosEntrada::dameGestorEventosEntrada()->estaPresionadaTecla(irr::EKEY_CODE::KEY_KEY_W))
	{
		t_direccionMovimiento.x += (float)cos(t_rotacionCamara.Y * DEGTORAD) * t_nuevaVelocidad;
		t_direccionMovimiento.y += (float)sin(t_rotacionCamara.Y * DEGTORAD) * t_nuevaVelocidad;
	}
	else if (GestorEventosEntrada::dameGestorEventosEntrada()->estaPresionadaTecla(irr::EKEY_CODE::KEY_KEY_S))
	{
		t_direccionMovimiento.x += (float)cos(t_rotacionCamara.Y * DEGTORAD) * -t_nuevaVelocidad;
		t_direccionMovimiento.y += (float)sin(t_rotacionCamara.Y * DEGTORAD) * -t_nuevaVelocidad;
	}
	if (GestorEventosEntrada::dameGestorEventosEntrada()->estaPresionadaTecla(irr::EKEY_CODE::KEY_KEY_A))
	{
		t_direccionMovimiento.x += (float)sin(t_rotacionCamara.Y * DEGTORAD) * t_nuevaVelocidad;
		t_direccionMovimiento.y += (float)cos(t_rotacionCamara.Y * DEGTORAD) * -t_nuevaVelocidad;
	}
	else if (GestorEventosEntrada::dameGestorEventosEntrada()->estaPresionadaTecla(irr::EKEY_CODE::KEY_KEY_D))
	{
		t_direccionMovimiento.x += (float)sin(t_rotacionCamara.Y * DEGTORAD) * -t_nuevaVelocidad;
		t_direccionMovimiento.y += (float)cos(t_rotacionCamara.Y * DEGTORAD) * t_nuevaVelocidad;
	}
	dameCuerpoFisicoEntidad()->SetLinearVelocity(t_direccionMovimiento);
	if (t_direccionMovimiento.x != 0 || t_direccionMovimiento.y != 0)
		Publicador::damePublicador()->notificaSuscriptores(dameCuerpoFisicoEntidad()->GetPosition().y, dameCuerpoFisicoEntidad()->GetPosition().x, t_volumen);
}

EntidadInteractuable* Protagonista::dameEntidadEnCruceta()
{
	if (c_objetoEquipado != nullptr && c_objetoEquipado->dameTipoObjeto() == ARMA)
	{
		LanzadorRayCast t_lanzadorRayCast(this, dynamic_cast<Arma*>(c_objetoEquipado)->dameAlcance());
		return t_lanzadorRayCast.lanzaRayoYDameEntidad();
	}
	else
	{
		LanzadorRayCast t_lanzadorRayCast(this, 0);
		return t_lanzadorRayCast.lanzaRayoYDameEntidad();
	}
}

void Protagonista::usaObjetoEquipado()
{
	if (c_objetoEquipado != nullptr)
	{
		if (c_relojUsoObjeto.dameTiempoTranscurridoMilisegundos() > TIEMPO_ENTRE_USOS_OBJETO )
		{
			c_relojUsoObjeto.dameTiempoTranscurridoMilisegundosYReinicia();
			char t_codigoUsoObjeto = c_objetoEquipado->usar();
			switch (t_codigoUsoObjeto)
			{
				//TRAMPA NO COLOCADA
			case -5:
				break;
				//MORFINA
			case -4:
				c_morfinaActiva = true;
				c_relojMorfina.dameTiempoTranscurridoMilisegundosYReinicia();
				eliminaObjetoEquipado();
				break;
				//ANTIBIOTICO
			case -3:
				if (c_vidaActual + CURACION_ANTIBIOTICO >= VIDA_INICIAL_PROTAGONISTA)
					c_vidaActual = VIDA_INICIAL_PROTAGONISTA;
				else
					c_vidaActual += CURACION_ANTIBIOTICO;
				c_HUD->ganaVida(CURACION_ANTIBIOTICO);
				eliminaObjetoEquipado();
				break;
			case -2:
				recargaArmaEquipada();
				break;
			case -1:
				eliminaObjetoEquipado();
				break;
			}
			Arma* t_armaEquipada = dynamic_cast<Arma*>(c_objetoEquipado);
			if (t_codigoUsoObjeto > 0 && t_armaEquipada->dameHaceRuido())
				Publicador::damePublicador()->notificaSuscriptores(dameCuerpoFisicoEntidad()->GetPosition().y, dameCuerpoFisicoEntidad()->GetPosition().x, ALTO);
		}
	}
}

void Protagonista::recargaArmaEquipada()
{
	std::string t_tipoBalasNecesarias;
	Arma* t_armaEquipada = dynamic_cast<Arma*>(c_objetoEquipado);
	if (t_armaEquipada->dameNombre() == "REVOLVER")
		t_tipoBalasNecesarias = "BALAS REVOLVER";
	else if (t_armaEquipada->dameNombre() == "PISTOLA")
		t_tipoBalasNecesarias = "BALAS PISTOLA";

	for each (Objeto* t_objetoEnMochila in c_mochila.dameObjetosMochila())
	{
		if (t_objetoEnMochila->dameTipoObjeto() == OBJETO_SIMPLE && t_objetoEnMochila->dameNombre() == t_tipoBalasNecesarias)
		{
 			char t_balasSacadasMochila;
			if (t_armaEquipada->dameTamañoMaximoCargador() >= t_objetoEnMochila->dameCantidad())
				t_balasSacadasMochila = t_objetoEnMochila->dameCantidad();
			else
				t_balasSacadasMochila = t_armaEquipada->dameTamañoMaximoCargador();
			t_armaEquipada->recarga(t_balasSacadasMochila);
			for (char t_balasSacarMochila = t_balasSacadasMochila; t_balasSacarMochila > 0; t_balasSacarMochila--)
				c_mochila.eliminaObjetoDeMochila(t_objetoEnMochila);
			break;
		}
	}
}

char Protagonista::ataca()
{
	char t_daño = 0;
	if (c_objetoEquipado)
	{
		if (c_objetoEquipado->dameTipoObjeto() == ARMA)
		{
			Arma* t_armaEquipada = dynamic_cast<Arma*>(c_objetoEquipado);
			t_daño = t_armaEquipada->usar();
			if (t_daño == -1)
				eliminaObjetoEquipado();
			else if (t_daño == -2)
				recargaArmaEquipada();
			else if (t_armaEquipada->dameHaceRuido())
				Publicador::damePublicador()->notificaSuscriptores(dameCuerpoFisicoEntidad()->GetPosition().y, dameCuerpoFisicoEntidad()->GetPosition().x, ALTO);
		}
	}
	return t_daño;
}

Mochila* Protagonista::dameMochila()
{
	return &c_mochila;
}

void Protagonista::recibeDaño(char p_dano)
{
	if (!c_morfinaActiva)
	{
		c_vidaActual -= p_dano;
		c_HUD->pierdeVida(p_dano);

		if (c_vidaActual <= 0)
		{
			c_muerto = true;
		}
	}
}

char Protagonista::damePeligrosidadArma()
{
	if (c_objetoEquipado!=nullptr)
	{
		if (c_objetoEquipado->dameTipoObjeto() == ARMA)
			return dynamic_cast<Arma*>(c_objetoEquipado)->damePeligrosidadArma();
	}
	return 0;
}

void Protagonista::interpolaPosicion(float p_cantidadFrameTranscurrido)
{
	EntidadInterpolable::interpolaPosicion(p_cantidadFrameTranscurrido);
	
	c_camaraProtagonista->setPosition(damePosicionMallaGrafica());
	c_camaraProtagonista->updateAbsolutePosition();
	c_camaraProtagonista->setRotation(dameRotacionMallaGrafica());
}

void Protagonista::equipaObjeto(Objeto* p_objeto)
{
	if (c_objetoEquipado != nullptr)
	{
		c_objetoEquipado->dameMallaGrafica()->setVisible(false);
		c_HUD->eliminaObjetoEquipado();
		c_objetoEquipado = nullptr;
	}
	if (p_objeto != nullptr)
	{
		p_objeto->dameMallaGrafica()->setVisible(true);
		p_objeto->dameMallaGrafica()->setParent(c_camaraProtagonista);
		p_objeto->dameMallaGrafica()->setPosition(irr::core::vector3df(0.5, -0.5, 1.5));
		c_HUD->equipaObjeto(p_objeto);
		c_objetoEquipado = p_objeto;
	}
}

void Protagonista::eliminaObjetoEquipado()
{
	if (c_mochila.eliminaObjetoDeMochila(c_objetoEquipado))
	{
		c_HUD->eliminaObjetoEquipado();
		c_objetoEquipado = nullptr;
	}
}

void Protagonista::setJuegoPausado(bool p_juegoPausado)
{ 
	c_HUD->setMirillaVisible(!p_juegoPausado); 
}