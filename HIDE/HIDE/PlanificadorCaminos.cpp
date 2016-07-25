#include "PlanificadorCaminos.h"
#include "Infectado.h"
#include "Nodo.h"
#include "Protagonista.h"

PlanificadorCaminos::PlanificadorCaminos(Infectado* i, Grafo* g)
	:propietario(i)
	, nodoActual(NULL)
	, nodoDestino(NULL)
{
	grafoMapa = new Grafo(*g);//HAGO UNA COPIA DEL GRAFO
}

PlanificadorCaminos::~PlanificadorCaminos()
{
}

Nodo* PlanificadorCaminos::BuscaNodoActual()
{
	b2Vec2 cuerFis = propietario->dameCuerpoFisicoEntidad()->GetPosition();
	b2Vec2 posInf(cuerFis.y, cuerFis.x);
	b2Vec2 vecDist;
	Nodo* nodoMasCercano=NULL;
	float dist = 10000;
	float nDist;

	for each (Nodo* n in grafoMapa->GetNodosGrafo())
	{
		vecDist = n->GetPosicion() - posInf;
		nDist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
		if (nDist < dist)
		{
			nodoMasCercano = n;
			dist = nDist;
		}
	}
	return nodoMasCercano;
}

void PlanificadorCaminos::SetNodoActual(Nodo* n)
{
	nodoActual = n;
	nodoActual->IncrementaPeso();
}

void PlanificadorCaminos::SetNodoActual()
{
	nodoActual = BuscaNodoActual();
	nodoActual->IncrementaPeso();
}

void PlanificadorCaminos::SetNodoDestino()
{
	if (nodoDestino == NULL)
	{
		nodoDestino = nodoActual->GetAdyacentes().at(0);
		return;
	}
	std::vector<Nodo*> menoresPesos;
	Nodo* menor;
	char peso = 100;
	//GUARDO EN UN VECTOR LOS NODOS ADYACENTES AL NODO ACTUAL CON LOS MENORES PESOS
	for each (Nodo* n in nodoDestino->GetAdyacentes())
	{
		if (n != nodoActual)
		{
			if (n->GetPeso() <= peso)
			{
				if (n->GetPeso() == peso)
					menoresPesos.push_back(n);
				else
				{
					peso = n->GetPeso();
					menor = n;
					menoresPesos.clear();
					menoresPesos.push_back(n);
				}
			}
		}
	}
	
	if (menoresPesos.size() == 0)
		menoresPesos.push_back(nodoActual);
	if (menoresPesos.size() == 1)
	{
		nodoActual = nodoDestino;
		nodoActual->IncrementaPeso();
		nodoDestino = menoresPesos.at(0);
		return;
	}
	else
	{
		//MIRO SI HAY ALGUN NODO EN LA DIRECCION EN LA QUE ME ESTABA MOVIENDO
		if (nodoActual->GetPosicion().y == nodoDestino->GetPosicion().y)//ME MOVIA HORIZONTAL
		{
			if (nodoActual->GetPosicion().x < nodoDestino->GetPosicion().x)//MOVIA HACIA LA DERECHA
			{
				for each (Nodo* n in menoresPesos)
				{
					if (n->GetPosicion().x>nodoDestino->GetPosicion().x)
					{
						nodoActual = nodoDestino;
						nodoActual->IncrementaPeso();
						nodoDestino = n;
						return;
					}
				}
			}
			else//MOVIA HACIA LA IZQUIERDA
			{
				for each (Nodo* n in menoresPesos)
				{
					if (n->GetPosicion().x<nodoDestino->GetPosicion().x)
					{
						nodoActual = nodoDestino;
						nodoActual->IncrementaPeso();
						nodoDestino = n;
						return;
					}
				}
			}
		}
		else//ME MOVIA VERTICAL
		{
			if (nodoActual->GetPosicion().y < nodoDestino->GetPosicion().y)//MOVIA HACIA ARRIBA
			{
				for each (Nodo* n in menoresPesos)
				{
					if (n->GetPosicion().y>nodoDestino->GetPosicion().y)
					{
						nodoActual = nodoDestino;
						nodoActual->IncrementaPeso();
						nodoDestino = n;
						return;
					}
				}

			}
			else//MOVIA HACIA ABAJO
			{
				for each (Nodo* n in menoresPesos)
				{
					if (n->GetPosicion().y<nodoDestino->GetPosicion().y)
					{
						nodoActual = nodoDestino;
						nodoActual->IncrementaPeso();
						nodoDestino = n;
						return;
					}
				}
			}
		}
		//NO HAY NINGUN NODO EN LA DIRECCION EN LA QUE ME ESTABA MOVIENDO. PILLO EL MAS LEJANO AL NODO EN EL QUE ESTOY
		b2Vec2 vecDist;
		float dist = -1;
		float nDist = -1;
		Nodo* lejano = NULL;
		//CALCULO EL NODO MAS LEJANO AL NODO ACTUAL
		for each (Nodo*  n in nodoDestino->GetAdyacentes())
		{
			vecDist = n->GetPosicion();
			nDist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
			if (dist < nDist)
			{
				if (n!=nodoActual)
				{
					dist = nDist;
					lejano = n;
				}
			}
		}
		nodoActual = nodoDestino;
		nodoActual->IncrementaPeso();
		nodoDestino = lejano;
		return;
	}
}

void PlanificadorCaminos::SetNodoDestinoAlerta()
{
	std::vector<Nodo*> t_nodosAdyacentes = nodoActual->GetAdyacentes();
	std::vector<Nodo*> t_menoresPesos;
	float t_pesoMenor = 10000.f;
	//PILLO LOS NODOS CON MENOR PESO
	for each (Nodo* t_nodoAdyacente in t_nodosAdyacentes)
	{
		if (t_nodoAdyacente->GetPeso() < t_pesoMenor)
		{
			t_menoresPesos.clear();
			t_menoresPesos.push_back(t_nodoAdyacente);
			t_pesoMenor = t_nodoAdyacente->GetPeso();
		}
		else if (t_nodoAdyacente->GetPeso() == t_pesoMenor)
			t_menoresPesos.push_back(t_nodoAdyacente);
	}
	//PILLO EL NODO MAS EN DIRECCION A LA POSICION DE ALERTA. PARA ELLO CALCULO EL VECTOR DESDE LA POSICION DEL INFECTADO A LA POSICION DE ALERTA Y 
	//LUEGO LO COMPARO CON LOS VECTORES DESDE LA POSICION DEL INFECTADO A LOS NODOS.
	float t_anguloMenor = 400.f;
	float t_anguloCalculado;
	Nodo* t_nodoObjetivo = nullptr;
	b2Vec2 t_posicionInfectado(propietario->dameCuerpoFisicoEntidad()->GetPosition().y, propietario->dameCuerpoFisicoEntidad()->GetPosition().x);
	b2Vec2 t_posicionAlerta = propietario->damePosicionAlerta() - t_posicionInfectado;
	b2Vec2 t_posicionNodo;
	for each (Nodo* t_nodoAdyacente in t_menoresPesos)
	{
		t_posicionNodo = t_nodoAdyacente->GetPosicion() - t_posicionInfectado;

		float t_anguloHorario = abs((atan2(t_posicionNodo.y, t_posicionNodo.x) - atan2(t_posicionAlerta.y, t_posicionAlerta.x)) * RADTODEG);
		float t_anguloAntihorario = abs((atan2(t_posicionAlerta.x, t_posicionAlerta.y) - atan2(t_posicionNodo.x, t_posicionNodo.y)) * RADTODEG);
		if (t_anguloHorario < t_anguloAntihorario)
			t_anguloCalculado = t_anguloHorario;
		else
			t_anguloCalculado = t_anguloAntihorario;

		if (t_anguloCalculado < t_anguloMenor)
		{
			t_anguloMenor = t_anguloCalculado;
			t_nodoObjetivo = t_nodoAdyacente;
		}
	}
	nodoDestino = t_nodoObjetivo;
}

void PlanificadorCaminos::SetNodoDestinoHuir()
{
	std::vector<Nodo*> t_nodosAdyacentes = nodoActual->GetAdyacentes();
	std::vector<Nodo*> t_menoresPesos;
	float t_pesoMenor = 10000.f;
	//PILLO LOS NODOS CON MENOR PESO
	for each (Nodo* t_nodoAdyacente in t_nodosAdyacentes)
	{
		if (t_nodoAdyacente->GetPeso() < t_pesoMenor)
		{
			t_menoresPesos.clear();
			t_menoresPesos.push_back(t_nodoAdyacente);
			t_pesoMenor = t_nodoAdyacente->GetPeso();
		}
		else if (t_nodoAdyacente->GetPeso() == t_pesoMenor)
			t_menoresPesos.push_back(t_nodoAdyacente);
	}
	//PILLO EL NODO CON LA DIRECCION MAS CONTRARIA A LA POSICION DEL PROTAGONISTA.
	float t_anguloMayor = 0.f;
	float t_anguloCalculado;
	Nodo* t_nodoObjetivo = nullptr;
	b2Vec2 t_posicionInfectado(propietario->dameCuerpoFisicoEntidad()->GetPosition().y, propietario->dameCuerpoFisicoEntidad()->GetPosition().x);
	propietario->dameProtagonista()->dameCuerpoFisicoEntidad();
	b2Vec2 t_posicionProta(propietario->dameProtagonista()->dameCuerpoFisicoEntidad()->GetPosition().y, 
						   propietario->dameProtagonista()->dameCuerpoFisicoEntidad()->GetPosition().x);
	b2Vec2 t_vectorPosicionAlertaInfectado = t_posicionProta - t_posicionInfectado;
	b2Vec2 t_posicionNodo;
	for each (Nodo* t_nodoAdyacente in t_menoresPesos)
	{
		t_posicionNodo = t_nodoAdyacente->GetPosicion() - t_posicionInfectado;

		float t_anguloHorario = abs((atan2(t_posicionNodo.y, t_posicionNodo.x) - atan2(t_vectorPosicionAlertaInfectado.y, t_vectorPosicionAlertaInfectado.x)) * RADTODEG);
		float t_anguloAntihorario = abs((atan2(t_vectorPosicionAlertaInfectado.x, t_vectorPosicionAlertaInfectado.y) - atan2(t_posicionNodo.x, t_posicionNodo.y)) * RADTODEG);
		if (t_anguloHorario < t_anguloAntihorario)
			t_anguloCalculado = t_anguloHorario;
		else
			t_anguloCalculado = t_anguloAntihorario;

		if (t_anguloCalculado > t_anguloMayor)
		{
			t_anguloMayor = t_anguloCalculado;
			t_nodoObjetivo = t_nodoAdyacente;
		}
	}

	//PILLO EL NODO MAS LEJANO A LA POSICION DE ALERTA
	/*char t_mayorDistancia = 0;
	char t_distancia;
	Nodo* t_nodoObjetivo = nullptr;
	b2Vec2 t_posicionAlerta = propietario->damePosicionAlerta();
	b2Vec2 t_posicionNodo;
	for each (Nodo* t_nodoAdyacente in t_menoresPesos)
	{
		t_posicionNodo = t_nodoAdyacente->GetPosicion() - t_posicionAlerta;
		t_distancia = t_posicionNodo.LengthSquared();

		if (t_mayorDistancia < t_distancia)
		{
			t_mayorDistancia = t_distancia;
			t_nodoObjetivo = t_nodoAdyacente;
		}
	}*/
	nodoDestino = t_nodoObjetivo;
}

void PlanificadorCaminos::SetNodoDestino(b2Vec2 pos)
{
	b2Vec2 vecDist;
	Nodo* nodoMasCercano = NULL;
	float dist = 10000;
	float nDist;

	for each (Nodo* n in grafoMapa->GetNodosGrafo())
	{
		vecDist = n->GetPosicion() - pos;
		nDist = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
		if (nDist < dist)
		{
			nodoMasCercano = n;
			dist = nDist;
		}
	}
	nodoDestino = nodoMasCercano;
}

Nodo* PlanificadorCaminos::GetNodoDestino()
{
	return nodoDestino;
}

Nodo* PlanificadorCaminos::GetNodoActual()
{
	return nodoActual;
}

void PlanificadorCaminos::CompruebaSiLlegadoDestino()
{
	b2Vec2 posInf(propietario->dameCuerpoFisicoEntidad()->GetPosition().y, propietario->dameCuerpoFisicoEntidad()->GetPosition().x);
	if ((posInf - nodoDestino->GetPosicion()).Length() < 3.f)
		SetNodoDestino();
}

void PlanificadorCaminos::CompruebaSiLlegadoDestinoAlerta()
{
	b2Vec2 posInf(propietario->dameCuerpoFisicoEntidad()->GetPosition().y, propietario->dameCuerpoFisicoEntidad()->GetPosition().x);
	if ((posInf - nodoDestino->GetPosicion()).Length() < 3.f)
	{
		nodoActual = nodoDestino;
		nodoActual->IncrementaPeso();
		SetNodoDestinoAlerta();
	}
}

void PlanificadorCaminos::CompruebaSiLlegadoDestinoHuir()
{
	b2Vec2 posInf(propietario->dameCuerpoFisicoEntidad()->GetPosition().y, propietario->dameCuerpoFisicoEntidad()->GetPosition().x);
	if ((posInf - nodoDestino->GetPosicion()).Length() < 3.f)
	{
		nodoActual = nodoDestino;
		nodoActual->IncrementaPeso();
		SetNodoDestinoHuir();
	}
}

void PlanificadorCaminos::ReiniciaPesosGrafo()
{
	for each (Nodo* n in grafoMapa->GetNodosGrafo())
		n->ReiniciaPeso();
}

