#include "LanzadorRayCast.h"
#include "Protagonista.h"
#include "EntidadInteractuable.h"
#include "EntidadJuego.h"
#include "FachadaMotorFisico.h"
#include "Arma.h"
#include "Infectado.h"
#include "Constantes.h"


LanzadorRayCast::LanzadorRayCast(Protagonista* p_protagonista, float p_alcanceArmaEquipada)
	: c_protagonista(p_protagonista)
	, c_entidadEncontrada(nullptr)
	, c_distanciaParedMasCercana(300.f)
{
	c_alturaRayo = p_protagonista->damePosicionMallaGrafica().Y;
	c_anguloRayo = p_protagonista->dameRotacionMallaGrafica().X;
	//BUSCA OBJETOS
	if (p_alcanceArmaEquipada < RANGO_MAXIMO_INTERACCION)
		c_longitudRayo = RANGO_MAXIMO_INTERACCION;
	else
		c_longitudRayo = p_alcanceArmaEquipada;
}

LanzadorRayCast::~LanzadorRayCast()
{
}

EntidadInteractuable* LanzadorRayCast::lanzaRayoYDameEntidad()
{
	b2Vec2 t_punto1 = c_protagonista->dameCuerpoFisicoEntidad()->GetPosition();
	b2Vec2 t_punto2 = calculaPunto2(t_punto1);
	FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->RayCast(this, t_punto1, t_punto2);
	if (c_entidadEncontrada != nullptr)
	{
		if (c_distanciaEntidadEncontrada > c_distanciaParedMasCercana)
			c_entidadEncontrada = nullptr;
		else
		{
			if (dynamic_cast<Objeto*>(c_entidadEncontrada) != 0 && c_distanciaEntidadEncontrada > RANGO_MAXIMO_INTERACCION)
				c_entidadEncontrada = nullptr;
			/*else if (dynamic_cast<Infectado*>(c_entidadEncontrada) != 0 && c_protagonista->dameArmaEquipada() == nullptr)
				c_entidadEncontrada = nullptr;*/
		}
		//TIRO RAYO DE VUELTA PARA ASEGURAME QUE NO HAY COLISIONES
		if (c_entidadEncontrada != nullptr)
		{
			//PQ CON EL RAYO DE VUELTA SE SOBREESCRIBE Y EL PROTAGONISTA (SI EL RAYO NO IMPACTA EN PARED) ES LA NUEVA ENTIDADENCONTRADA
			EntidadJuego* t_entidadEncontradaAuxiliar = c_entidadEncontrada;
			c_entidadEncontrada = nullptr;
			c_alturaRayo = c_alturaColision;
			c_anguloRayo = c_protagonista->dameRotacionMallaGrafica().X*-1;
			c_longitudRayo = c_distanciaEntidadEncontrada;
			FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->RayCast(this, t_punto2, t_punto1);
			if (c_entidadEncontrada != nullptr)
				return  dynamic_cast<EntidadInteractuable*>(t_entidadEncontradaAuxiliar);
		}
	}
	return nullptr;
}

b2Vec2 LanzadorRayCast::calculaPunto2(b2Vec2 p_punto1)
{
	float t_rotacionProtagonistaY = c_protagonista->dameRotacionMallaGrafica().Y;
	b2Vec2 r_punto2;
	if (c_anguloRayo < 0 && c_alturaRayo == AGACHADO)
	{
		r_punto2.x = p_punto1.x + (float)cos(t_rotacionProtagonistaY * DEGTORAD) * c_longitudRayo;
		r_punto2.y = p_punto1.y + (float)sin(t_rotacionProtagonistaY * DEGTORAD) * c_longitudRayo;
	}

	if (c_anguloRayo < 0)
		r_punto2.Set(p_punto1.x + 0.001f, p_punto1.y + 0.001f);
	else
	{
		float dist = (c_alturaRayo / sin(c_anguloRayo*DEGTORAD)*cos(c_anguloRayo*DEGTORAD));
		if (dist < c_longitudRayo)
			c_longitudRayo = dist;
		r_punto2.x = p_punto1.x + (float)cos(t_rotacionProtagonistaY * DEGTORAD) * c_longitudRayo;
		r_punto2.y = p_punto1.y + (float)sin(t_rotacionProtagonistaY * DEGTORAD) * c_longitudRayo;
	}
	return r_punto2;
}

float32 LanzadorRayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	b2Body* body = fixture->GetBody();
	if (body->GetType() == b2_staticBody)//EL RAYCAST HA CHOCADO CON UNA PARED
	{
		//COMPRUEBO LA ALTURA DEL OBJETO
		if (body->GetUserData() == "ALTA"){
			c_distanciaParedMasCercana = c_longitudRayo*fraction;
			return 1.f;//CONTINUA EL RAYCAST
		}
		else//EL OBJETO ES DE ALTURA MEDIA, COMPRUEBO SI EL RAYO IMPACTA CON EL OBJETO
		{
			if (TestAltura(c_longitudRayo * fraction, ALTURA_OBJETOS_ALTURA_MEDIA))//NO HAY IMPACTO CON EL OBSTACULO
				return -1.f;//IGNORA ESTA INTERSECCION Y CONTINUA RAYCAST          
			else{//HAY IMPACTO CON EL OBJETO
				c_distanciaParedMasCercana = c_longitudRayo*fraction;
				return 1.f;//CONTINUA EL RAYCAST
			}
		}
	}
	else //EL RAYCAST HA CHOCADO CONTRA UN ENEMIGO, EL PERSONAJE O UN OBJETO
	{
		EntidadJuego* t_entidadInteractuableImpactada = (EntidadJuego*)body->GetUserData();
		float t_alturaEntidad;
		if (dynamic_cast<Infectado*>(t_entidadInteractuableImpactada) != nullptr)
			t_alturaEntidad = ALTURA_ENEMIGOS;
		else if (dynamic_cast<Objeto*>(t_entidadInteractuableImpactada) != nullptr)
			t_alturaEntidad = ALTURAITEMS;
		else
			t_alturaEntidad = ((Protagonista*)body->GetUserData())->damePosicionMallaGrafica().Y;

		if (!TestAltura(c_longitudRayo * fraction, t_alturaEntidad))
		{
			c_entidadEncontrada = t_entidadInteractuableImpactada;
			c_posicionColision = body->GetPosition();
			c_distanciaEntidadEncontrada = c_longitudRayo*fraction;
			c_alturaColision = (float)c_alturaRayo - c_longitudRayo*fraction * tan(c_anguloRayo*DEGTORAD);
			return fraction;//RECORTO EL RAYO PARA OBTENER LA ENTIDAD MAS CERCANA
		}
		return 1.f;//CONTINUA RAYCAST
	}
}

bool LanzadorRayCast::TestAltura(float p_longitudRayo, float p_alturaMaxima)
{
	float t_alturaImpacto = (float)c_alturaRayo - p_longitudRayo * tan(c_anguloRayo*DEGTORAD);
	if (t_alturaImpacto > p_alturaMaxima)
		return true;//NO HAY IMPACTO CON EL OBJETO, EL TIRO VA MUY ALTO
	return false;//EL DISPASTO IMPACTA EN EL OBJETO
}