#include "Arma.h"
#include "Constantes.h"


Arma::Arma(float p_posicionX, float p_posicionZ, char* p_modelo3D, float p_peso, float p_maximoAlcance,
		   bool p_haceRuido, char p_daño, char p_cargadorActual, bool p_esRompible, char p_tamañoMaximoCargador, 
		   char p_peligrosidad, char* p_nombre, char* p_descripcion, char* p_nombreImagenObjeto, TiposArma p_tipoArma)
		   : Objeto(p_posicionX, p_posicionZ, p_modelo3D, false, p_peso, p_nombre, p_descripcion, p_nombreImagenObjeto, ARMA)
	, c_maximoAlcance(p_maximoAlcance)
	, c_haceRuido(p_haceRuido)
	, c_daño(p_daño)
	, c_cargadorActual(p_cargadorActual)
	, c_esRompible(p_esRompible)
	, c_tamañoMaximoCargador(p_tamañoMaximoCargador)
	, c_peligrosidad(p_peligrosidad)
	, c_tipoArma(p_tipoArma)
{
}

Arma::~Arma()
{
}

char Arma::usar()
{
	if (c_cargadorActual > 0)
	{
		c_cargadorActual--;
		return c_daño;
	}
	else
	{
		if (c_esRompible)
		{
			c_cantidad--;
			if (c_cantidad > 0)
				return 0;
			else
				return -1;
		}
		else
			return -2;
	}
}

void Arma::recarga(char p_numeroProyectiles)
{
	c_cargadorActual += p_numeroProyectiles;
	//hacer animacion y esperar un tiempo sin poder usar
}
