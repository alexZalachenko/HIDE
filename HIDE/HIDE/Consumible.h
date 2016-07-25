#pragma once
#include "Objeto.h"
class Consumible : public Objeto
{
public:
	Consumible(float p_posicionX, float p_posicionZ, char* p_modelo3D, float p_peso,
			   char* p_nombre, char* p_descripcion, char* p_nombreImagenObjeto);
	~Consumible();
	char usar();
};

