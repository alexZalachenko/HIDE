#include "Suscriptor.h"
#include "Publicador.h"


Suscriptor::Suscriptor()
{
	Publicador::damePublicador()->a�adeSuscriptor(this);
}


Suscriptor::~Suscriptor()
{
}
