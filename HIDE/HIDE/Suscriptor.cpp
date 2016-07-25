#include "Suscriptor.h"
#include "Publicador.h"


Suscriptor::Suscriptor()
{
	Publicador::damePublicador()->añadeSuscriptor(this);
}


Suscriptor::~Suscriptor()
{
}
