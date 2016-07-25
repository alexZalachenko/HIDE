#pragma once
#include "Objeto.h"
class ObjetoSimple : public Objeto
{
public:
	ObjetoSimple(float p_posicionX, float p_posicionZ, char* p_modelo3D, float p_peso,
				 char* p_nombre, char* p_descripcion, char* p_nombreImagenObjeto);
	~ObjetoSimple();
	//IMPLEMENTA FUNCION VIRTUAL DE OBJETO
	char usar();
};

