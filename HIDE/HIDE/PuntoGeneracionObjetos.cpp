#include "PuntoGeneracionObjetos.h"
#include "Objeto.h"
#include "GeneradorObjetos.h"
const long TIEMPO_REGENERACION_OBJETOS = 60 * 1000;

PuntoGeneracionObjetos::PuntoGeneracionObjetos(float p_posicionX, float p_posicionY)
	: c_objetoGenerado(nullptr)
{
	c_posicionPuntoGeneracion.x = p_posicionX;
	c_posicionPuntoGeneracion.y = p_posicionY;
	c_reloj.setTiempoTranscurrido(-TIEMPO_REGENERACION_OBJETOS);
}

PuntoGeneracionObjetos::~PuntoGeneracionObjetos()
{
}

bool PuntoGeneracionObjetos::actualizaPuntoGeneracion()
{
	if (c_objetoGenerado == nullptr && c_reloj.dameTiempoTranscurridoMilisegundos() > TIEMPO_REGENERACION_OBJETOS)
		return true;
	else
		return false;
}

void PuntoGeneracionObjetos::eliminaObjeto()
{
	c_objetoGenerado = nullptr;
	c_reloj.dameTiempoTranscurridoMilisegundosYReinicia();
}

void PuntoGeneracionObjetos::setObjeto(Objeto* p_objeto)
{ 
	if (p_objeto == nullptr)
		exit(1);
	c_objetoGenerado = p_objeto; 
	c_objetoGenerado->setPuntoGeneracionObjetos(this);
}