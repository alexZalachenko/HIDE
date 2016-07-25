#include "RaycastVeoJugador.h"
#include "Protagonista.h"
#include "EntidadInteractuable.h"
#include "EntidadJuego.h"
#include "FachadaMotorFisico.h"
#include "Arma.h"
#include "Infectado.h"
#include "Constantes.h"


RaycastVeoJugador::RaycastVeoJugador(Infectado* p_infectado)
	: c_entidadEncontrada(nullptr)
	, c_distanciaParedMasCercana(300.f)
	, c_infectado(p_infectado)
{
	c_alturaRayo = ALTURA_ENEMIGOS ;

	b2Vec2 distVec = p_infectado->dameProtagonista()->dameCuerpoFisicoEntidad()->GetPosition() - p_infectado->dameCuerpoFisicoEntidad()->GetPosition();
	float dist = distVec.Length();
	//EL RAYO SE LANZA A LOS PIES DEL PROTA. CALCULO LA LONGITUD CON EL TEOREMA DE PITAGORAS
	c_longitudRayo = (float)sqrt(pow(ALTURA_ENEMIGOS, 2) + pow(dist, 2));
	c_anguloRayo = acos(dist / c_longitudRayo);
}

RaycastVeoJugador::~RaycastVeoJugador()
{
}

bool RaycastVeoJugador::veoJugador()
{
	b2Vec2 t_punto1 = c_infectado->dameCuerpoFisicoEntidad()->GetPosition();
	b2Vec2 t_punto2 = c_infectado->dameProtagonista()->dameCuerpoFisicoEntidad()->GetPosition();
	FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->RayCast(this, t_punto1, t_punto2);
	if (c_entidadEncontrada != nullptr)
	{
		if (c_distanciaEntidadEncontrada > c_distanciaParedMasCercana)
			c_entidadEncontrada = nullptr;
		else
		{
			if (dynamic_cast<Infectado*>(c_entidadEncontrada) != 0)
				c_entidadEncontrada = nullptr;
		}
		//TIRO RAYO DE VUELTA PARA ASEGURAME QUE NO HAY COLISIONES
		if (c_entidadEncontrada != nullptr)
		{
			//PQ CON EL RAYO DE VUELTA SE SOBREESCRIBE Y EL PROTAGONISTA (SI EL RAYO NO IMPACTA EN PARED) ES LA NUEVA ENTIDADENCONTRADA
			EntidadJuego* t_entidadEncontradaAuxiliar = c_entidadEncontrada;
			c_entidadEncontrada = nullptr;
			c_alturaRayo = c_alturaColision;
			c_anguloRayo = c_infectado->dameProtagonista()->dameRotacionMallaGrafica().X * DEGTORAD;
			c_longitudRayo = c_distanciaEntidadEncontrada;
			FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->RayCast(this, t_punto2, t_punto1);
			if (c_entidadEncontrada != nullptr)
				return  true;
		}
	}
	return false;
}

float32 RaycastVeoJugador::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
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
			c_alturaColision = (float)c_alturaRayo - c_longitudRayo*fraction * tan(c_anguloRayo);
			return fraction;//RECORTO EL RAYO PARA OBTENER LA ENTIDAD MAS CERCANA
		}
		return 1.f;//CONTINUA RAYCAST
	}
}

bool RaycastVeoJugador::TestAltura(float p_longitudRayo, float p_alturaMaxima)
{
	float t_alturaImpacto = (float)c_alturaRayo - p_longitudRayo * tan(c_anguloRayo);
	if (t_alturaImpacto > p_alturaMaxima)
		return true;//NO HAY IMPACTO CON EL OBJETO, EL TIRO VA MUY ALTO
	return false;//EL DISPASTO IMPACTA EN EL OBJETO
}