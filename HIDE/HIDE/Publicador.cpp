#include "Publicador.h"
#include "Suscriptor.h"
#include "Constantes.h"

Publicador* Publicador::ptrPublicador = 0;

Publicador* Publicador::damePublicador()
{
	if (ptrPublicador == 0)
		ptrPublicador = new Publicador();
	return ptrPublicador;
}

Publicador::Publicador()
{
}

Publicador::~Publicador()
{
}

void Publicador::añadeSuscriptor(Suscriptor* p_suscriptor)
{
	bool t_encontrado = false;
	for each (Suscriptor* t_suscriptor in c_suscriptores)
	{
		if (t_suscriptor == p_suscriptor)
			t_encontrado = true;
	}
	if (t_encontrado == false)
		c_suscriptores.push_back(p_suscriptor);
}

void Publicador::eliminaSuscriptor(Suscriptor* p_suscriptor)
{
	std::vector<Suscriptor*>::iterator t_iterador = c_suscriptores.begin();
	for each (Suscriptor* t_suscriptor in c_suscriptores)
	{
		if (t_suscriptor==p_suscriptor)
		{
			c_suscriptores.erase(t_iterador);
			break;
		}
		t_iterador++;
	}
}

void Publicador::notificaSuscriptores(float p_posicionSonidox, float p_posicionSonidoy, VolumenSonidos p_volumen)
{
	for each (Suscriptor* t_suscriptor in c_suscriptores)
		t_suscriptor->recibeNotificacion(p_posicionSonidox, p_posicionSonidoy, p_volumen);
}
