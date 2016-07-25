#include "ObjetoSimple.h"


ObjetoSimple::ObjetoSimple(float p_posicionX, float p_posicionZ, char* p_modelo3D, float p_peso,
						   char* p_nombre, char* p_descripcion, char* p_nombreImagenObjeto)
	: Objeto(p_posicionX, p_posicionZ, p_modelo3D, true, p_peso, p_nombre, p_descripcion, p_nombreImagenObjeto, OBJETO_SIMPLE)
{
}


ObjetoSimple::~ObjetoSimple()
{
}

char ObjetoSimple::usar()
{
	return 0;
}
