#pragma once
#include <vector>
#include "Constantes.h"
class Suscriptor;

class Publicador
{
public:
	static Publicador* damePublicador();
	~Publicador();
	void añadeSuscriptor(Suscriptor* p_suscriptor);
	void eliminaSuscriptor(Suscriptor* p_suscriptor);
	void notificaSuscriptores(float p_posicionSonidox, float p_posicionSonidoy, VolumenSonidos p_volumen);

private:
	static Publicador* ptrPublicador;
	Publicador();
	std::vector<Suscriptor*> c_suscriptores;
};

