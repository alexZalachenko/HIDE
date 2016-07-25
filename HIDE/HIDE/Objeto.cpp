#include "Objeto.h"
#include "Protagonista.h"
#include "FachadaMotorGrafico.h"
#include "PuntoGeneracionObjetos.h"


Objeto::Objeto(float p_posicionX, float p_posicionZ, char* p_modelo3D, bool p_esApilable, float p_peso,
			   char* p_nombre, char* p_descripcion, char* p_imagenObjeto, TiposObjeto p_tipoObjeto)
	: EntidadJuego(p_posicionX, p_posicionZ, p_modelo3D, true)
	, EntidadInteractuable()
	, c_cantidad(1)
	, c_esApilable(p_esApilable)
	, c_peso(p_peso)
	, c_nombre(p_nombre)
	, c_descripcion(p_descripcion)
	, c_imagenObjeto(p_imagenObjeto)
	, c_tipoObjeto(p_tipoObjeto)
	, c_puntoGeneracionObjetos(nullptr)
{
}

Objeto::~Objeto()
{
}

void Objeto::interactua(Protagonista* p_protagonista)
{
	PuntoGeneracionObjetos* t_puntoGeneracion = c_puntoGeneracionObjetos;
	if (p_protagonista->dameMochila()->añadeObjetoAMochila(this))
	{
		if (t_puntoGeneracion != nullptr)
			t_puntoGeneracion->eliminaObjeto();
	}
}

irr::scene::IMeshSceneNode* Objeto::dibujaAura()
{
	return FachadaMotorGrafico::dameFachadaMotorGrafico()->dibujaEsferaSemitransparente(damePosicionMallaGrafica().X, damePosicionMallaGrafica().Z);
}

char Objeto::usar()
{
	return 0; 
}

void Objeto::actualizaEntidadJuego()
{
}

