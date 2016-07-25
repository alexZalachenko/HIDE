#include "Consumible.h"


Consumible::Consumible(float p_posicionX, float p_posicionZ, char* p_modelo3D, float p_peso, 
					   char* p_nombre, char* p_descripcion, char* p_nombreImagenObjeto)
	: Objeto(p_posicionX, p_posicionZ, p_modelo3D, true, p_peso, p_nombre, p_descripcion, p_nombreImagenObjeto, CONSUMIBLE)
{
}

Consumible::~Consumible()
{
}

char Consumible::usar()
{
	if (c_nombre == "ANTIBIOTICO")
		return -3;
	else if (c_nombre == "MORFINA")
		return -4;
	//PARA QUE NO SE QUEJE EL COMPILADOR
	return -1;
}
