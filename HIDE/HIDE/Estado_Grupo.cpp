#include "Estado_Grupo.h"


Estado_Grupo::Estado_Grupo()
{
}

Estado_Grupo* Estado_Grupo::GetInstancia()
{
	static Estado_Grupo instancia;
	return &instancia;
}

Estado_Grupo::~Estado_Grupo()
{
}

void Estado_Grupo::Execute(Infectado* infectado)
{

}

void Estado_Grupo::EntrarEstado(Infectado* infectado)
{

}

void Estado_Grupo::SalirEstado(Infectado* infectado)
{

}
