#include "Trampa.h"
#include "GestorEntidadesJuego.h"
#include "RaycastColocaTrampa.h"
#include "EscenaConEntidad.h"
#include "FachadaMotorGrafico.h"
#include "GestorEntidadesJuego.h"
#include "Publicador.h"
#include "FachadaMotorFisico.h"
#include "Protagonista.h"
#include "Infectado.h"

Trampa::Trampa(float p_posicionX, float p_posicionZ, char* p_modelo3D, float p_peso,
			   char* p_nombre, char* p_descripcion, char* p_imagenObjeto, TipoTrampa p_tipoTrampa, GestorEntidadesJuego* p_gestorEntidades)

			   : Objeto(p_posicionX, p_posicionZ, p_modelo3D, false, p_peso, p_nombre, p_descripcion, p_imagenObjeto, TRAMPA)
			   , c_enEstadoDelay(true)
			   , c_gestorEntidades(p_gestorEntidades)
			   , c_tipoTrampa(p_tipoTrampa)
			   , c_infectadoCapturado(nullptr)
{
	switch (c_tipoTrampa)
	{
	case TRAMPA_BOMBA:
		c_delay = DELAY_TRAMPA_BOMBA;
		c_duracion = 0;
		c_daño = DAÑO_TRAMPA_BOMBA;
		c_radio = RADIO_TRAMPA_BOMBA;
		break;
	case TRAMPA_CLAVOS:
		c_delay = DELAY_TRAMPA_CLAVOS;
		c_duracion = 10 * 1000;// DURACION_TRAMPA_CLAVOS;
		c_usosTrampaClavos = USOS_TRAMPA_CLAVOS;
		c_daño = DAÑO_TRAMPA_CLAVOS;
		c_radio = 0;
		break;
	case TRAMPA_SOGA:
		c_delay = 0;
		c_duracion = DURACION_TRAMPA_SOGA;
		c_daño = 0;
		c_radio = 0;
		break;
	case TRAMPA_SONORA:
		c_delay = DELAY_TRAMPA_SONORA;
		c_duracion = DURACION_TRAMPA_SONORA;
		c_daño = 0;
		c_radio = 0;
		break;
	case TRAMPA_FUEGO:
		c_delay = DELAY_TRAMPA_FUEGO;
		c_duracion = DURACION_TRAMPA_FUEGO;
		c_daño = DAÑO_TRAMPA_FUEGO;
		c_radio = 0;
		break;
	}
}

Trampa::~Trampa()
{
}

char Trampa::usar()
{
	RaycastColocaTrampa raycast(EscenaConEntidad::dameEscenaConEntidad()->dameGestorEntidadesJuego()->dameProtagonista());
	if (raycast.sePuedeColocarTrampa())
	{
		dameMallaGrafica()->setParent(FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->getRootSceneNode());
		reanimaEntidad(raycast.damePosicionColocacionTrampa(), b2_kinematicBody);
		setSensor(true);
		FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->SetContactListener(this);
		dameCuerpoFisicoEntidad()->SetActive(false);
		c_reloj.dameTiempoTranscurridoMilisegundosYReinicia();
		return -1;
	}
	else
		return -5;
}

void Trampa::actualizaEntidadJuego()
{
	if (c_enEstadoDelay)
	{
		if (c_reloj.dameTiempoTranscurridoMilisegundos() > c_delay)
		{
			c_enEstadoDelay = false;
			dameCuerpoFisicoEntidad()->SetActive(true);
			c_reloj.dameTiempoTranscurridoMilisegundosYReinicia();
		}
		else
			return;
	}
	else if ( c_duracion == 0 || c_duracion > c_reloj.dameTiempoTranscurridoMilisegundos())
	{
		switch (c_tipoTrampa)
		{
			case TRAMPA_BOMBA:
				actualizaTrampaBomba();
				break;
			case TRAMPA_SONORA:
				actualizaTrampaSonora();
				break;
		}
	}
	else
	{
		if (c_tipoTrampa == TRAMPA_SOGA && c_infectadoCapturado != nullptr)
			c_infectadoCapturado->setMovimientoRestringido(false);
		//PARA TODAS LAS TRAMPAS
		//FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->SetDestructionListener(this);
		c_gestorEntidades->eliminaEntidad(this);
	}	
}

void Trampa::actualizaTrampaBomba()
{
	//hacer radio mas grande y en la colision quitar vida
	b2CircleShape t_formaCirculo;
	t_formaCirculo.m_radius = RADIO_TRAMPA_BOMBA ;
	b2FixtureDef t_boxFixtureDef;
	t_boxFixtureDef.shape = &t_formaCirculo;
	t_boxFixtureDef.density = 1;

	b2BodyDef t_myBodyDef;
	t_myBodyDef.type = b2_kinematicBody;
	t_myBodyDef.position.Set(dameCuerpoFisicoEntidad()->GetPosition().x, dameCuerpoFisicoEntidad()->GetPosition().x);
	dameCuerpoFisicoEntidad()->CreateFixture(&t_boxFixtureDef);

	Publicador::damePublicador()->notificaSuscriptores(
		dameCuerpoFisicoEntidad()->GetPosition().y, dameCuerpoFisicoEntidad()->GetPosition().x, MEDIO);

	c_duracion = -1;
}

void Trampa::actualizaTrampaClavos(b2Contact* contact)
{
	if (contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody)
	{
		EntidadJuego* t_entidadColisionada;
		Infectado* t_infectadoColisionado;
		Protagonista* t_protagonistaColisionado;

		//QUITO VIDA A LAS ENTIDADES COLISIONADAS
		t_entidadColisionada = (EntidadJuego*)contact->GetFixtureA()->GetBody()->GetUserData();
		t_infectadoColisionado = dynamic_cast<Infectado*>(t_entidadColisionada);
		t_protagonistaColisionado = dynamic_cast<Protagonista*>(t_entidadColisionada);

		if (t_infectadoColisionado)
		{
			t_infectadoColisionado->recibeDañoUsandoFisicas(c_daño);
			c_duracion--;
		}

		else if (t_protagonistaColisionado)
		{
			t_protagonistaColisionado->recibeDaño(c_daño);
			c_duracion--;
		}
		c_usosTrampaClavos--;
		if (c_usosTrampaClavos == 0)
		{
			c_duracion = -1;
		}
	}
}

void Trampa::actualizaTrampaFuego(b2Contact* contact)
{
	if (contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody)
	{
		EntidadJuego* t_entidadColisionada;
		Infectado* t_infectadoColisionado;
		Protagonista* t_protagonistaColisionado;

		//QUITO VIDA A LAS ENTIDADES COLISIONADAS
		t_entidadColisionada = (EntidadJuego*)contact->GetFixtureA()->GetBody()->GetUserData();
		t_infectadoColisionado = dynamic_cast<Infectado*>(t_entidadColisionada);
		t_protagonistaColisionado = dynamic_cast<Protagonista*>(t_entidadColisionada);

		if (t_infectadoColisionado)
			t_infectadoColisionado->recibeDañoUsandoFisicas(c_daño);
		else if (t_protagonistaColisionado)
			t_protagonistaColisionado->recibeDaño(c_daño);
	}
}

void Trampa::actualizaTrampaSoga(b2Contact* contact)
{
	if (contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody)
	{
		EntidadJuego* t_entidadColisionada;
		Infectado* t_infectadoColisionado;

		//PARALIZO A LOS INFECTADOS COLISIONADOS
		t_entidadColisionada = (EntidadJuego*)contact->GetFixtureA()->GetBody()->GetUserData();
		t_infectadoColisionado = dynamic_cast<Infectado*>(t_entidadColisionada);

		if (t_infectadoColisionado)
			t_infectadoColisionado->setMovimientoRestringido(true);
	}
}

void Trampa::actualizaTrampaSonora()
{
	Publicador::damePublicador()->notificaSuscriptores(
		dameCuerpoFisicoEntidad()->GetPosition().y, dameCuerpoFisicoEntidad()->GetPosition().x, ALTO);
	c_duracion = -1;
}

void Trampa::colisionTrampaBomba(b2Contact* contact)
{
	EntidadJuego* t_entidadColisionada;
	Infectado* t_infectadoColisionado;
	Protagonista* t_protagonistaColisionado;

	//QUITO VIDA A LAS ENTIDADES COLISIONADAS
	t_entidadColisionada = (EntidadJuego*)contact->GetFixtureA()->GetBody()->GetUserData();
	t_infectadoColisionado = dynamic_cast<Infectado*>(t_entidadColisionada);
	t_protagonistaColisionado = dynamic_cast<Protagonista*>(t_entidadColisionada);

	if (t_infectadoColisionado)
		t_infectadoColisionado->recibeDañoUsandoFisicas(c_daño);
	else if (t_protagonistaColisionado)
		t_protagonistaColisionado->recibeDaño(c_daño);
}

void Trampa::BeginContact(b2Contact* contact)
{
	switch (c_tipoTrampa)
	{
		/*case TRAMPA_BOMBA:
			colisionTrampaBomba(contact);
			break;*/
		case TRAMPA_CLAVOS:
			actualizaTrampaClavos(contact);
			break;
		case TRAMPA_SOGA:
			actualizaTrampaSoga(contact);
			break;
		case TRAMPA_FUEGO:
			actualizaTrampaFuego(contact);
			break;
	}
}