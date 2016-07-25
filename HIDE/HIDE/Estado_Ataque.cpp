#include "Estado_Ataque.h"
#include "Estado_Alerta.h"
#include "Constantes.h"
#include "Estado_Huir.h"
#include "Protagonista.h"


Estado_Ataque::Estado_Ataque()
{
}

Estado_Ataque* Estado_Ataque::GetInstancia()
{
	static Estado_Ataque instancia;
	return &instancia;
}

Estado_Ataque::~Estado_Ataque()
{
}

void Estado_Ataque::Execute(Infectado* infectado)
{
	if (infectado->protagonistaEnRangoAtaque())
		infectado->ataca();
	else
		infectado->mueveInfectadoHaciaPersonaje();
}

void Estado_Ataque::EntrarEstado(Infectado* infectado)
{
	infectado->setColorMalla(1);
}

void Estado_Ataque::SalirEstado(Infectado* infectado)
{
	infectado->setColorMalla(0);
	infectado->setPosicionAlerta(infectado->dameProtagonista()->dameCuerpoFisicoEntidad()->GetPosition());
}