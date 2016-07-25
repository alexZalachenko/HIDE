#include "Nodo.h"

Nodo::Nodo(b2Vec2 pos)
	:peso(-1)
	, posicion(pos)
{
}

Nodo::~Nodo()
{
}

void Nodo::AnadeAdyacente(Nodo* n, bool replica)
{
	//LANZO UN RAYCAST PARA COMPROBAR QUE SON REALMENTE ADYACENTES
	if (replica)
	{
		if (RaycastNodoVisible(n))
			{
				adyacentes.push_back(n);
				n->AnadeAdyacente(this, false);
			}
	}
	else
		adyacentes.push_back(n);
}

b2Vec2 Nodo::GetPosicion()
{
	return posicion;
}

std::vector<Nodo*> Nodo::GetAdyacentes()
{
	return adyacentes;
}

//DEVUELVE TRUE SI LOS NODOS SON VISIBLES ENTRE ELLOS Y FALSE EN CASO CONTRARIO
bool Nodo::RaycastNodoVisible(Nodo* objetivo)
{
	class RayCastNodoAdyacente : public b2RayCastCallback
	{
	public:
		RayCastNodoAdyacente():adyacente(true){}
		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
		{
			b2Body* body = fixture->GetBody();
			if (body->GetType() == b2_staticBody)//EL RAYCAST HA CHOCADO CON UNA PARED
			{
				//COMPRUEBO LA ALTURA DEL OBJETO
				if (body->GetUserData() == "ALTA"){
					adyacente = false;
					return 0.f;//TERMINA EL RAYCAST
				}
				else//EL OBJETO ES DE ALTURA MEDIA, COMPRUEBO SI EL RAYO IMPACTA CON EL OBJETO
					return 1.f;//CONTINUA EL RAYCAST
			}
			else //EL RAYCAST HA CHOCADO CONTRA UN ENEMIGO, EL PERSONAJE O UN OBJETO
				return 1.f;//CONTINUA RAYCAST
		}
		bool adyacente;
	};
	b2Vec2 p1(posicion.y, posicion.x);
	b2Vec2 p2(objetivo->GetPosicion().y, objetivo->GetPosicion().x);
	RayCastNodoAdyacente callback;
	FachadaMotorFisico::dameFachadaMotorFisico()->dameMundoFisico()->RayCast(&callback, p1, p2);
	return callback.adyacente;
}

void Nodo::IncrementaPeso()
{
	peso++;
}

char Nodo::GetPeso()
{
	return peso;
}

void Nodo::ReiniciaPeso()
{
	peso = -1;
}