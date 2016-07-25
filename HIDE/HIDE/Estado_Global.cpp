#include "Estado_Global.h"
#include "Estado_Huir.h"
#include "Estado_Grupo.h"
#include "Protagonista.h"

Estado_Global::Estado_Global()
{
}

Estado_Global* Estado_Global::GetInstancia()
{
	static Estado_Global instancia;
	return &instancia;
}

Estado_Global::~Estado_Global()
{
}

void Estado_Global::Execute(Infectado* infectado)
{
	Estado* t_estadoActual = infectado->dameMEF()->GetEstadoActual();
	if (infectado->estaElJugadorVisible())
	{
		if (t_estadoActual == Estado_Huir::GetInstancia())
		{
			infectado->setPosicionAlerta(b2Vec2(infectado->dameProtagonista()->dameCuerpoFisicoEntidad()->GetPosition().y,
												infectado->dameProtagonista()->dameCuerpoFisicoEntidad()->GetPosition().y));
			infectado->dameMEF()->CambiarEstado(Estado_Huir::GetInstancia());
			return;
		}
		else
		{
			if (t_estadoActual == Estado_Grupo::GetInstancia())
			{
				//AVISAR GRUPO
			}
			else if (t_estadoActual != Estado_Ataque::GetInstancia())
			{
				infectado->dameMEF()->CambiarEstado(Estado_Ataque::GetInstancia());
			}
		}
	}
	else if (t_estadoActual == Estado_Ataque::GetInstancia())
	{
		infectado->dameMEF()->CambiarEstado(Estado_Alerta::GetInstancia());
	}
}

void Estado_Global::EntrarEstado(Infectado* infectado)
{

}

void Estado_Global::SalirEstado(Infectado* infectado)
{
}