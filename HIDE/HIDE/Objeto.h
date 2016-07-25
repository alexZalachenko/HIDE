#pragma once
#include "EntidadInteractuable.h"
#include "EntidadJuego.h"
#include <string>
#include "Constantes.h"
class Protagonista;
class PuntoGeneracionObjetos;

class Objeto : public EntidadJuego, public EntidadInteractuable
{
public:
	Objeto(float p_posicionX, float p_posicionZ, char* p_modelo3D, bool p_esApilable,
		   float p_peso, char* p_nombre, char* p_descripcion, char* p_imagenObjeto, TiposObjeto p_tipoObjeto);
	virtual ~Objeto();
	bool esApilable(){ return c_esApilable; }
	float damePeso(){ return c_peso; }
	char dameCantidad(){ return c_cantidad; }
	void aumentaCantidad(){c_cantidad++; }
	void disminuyeCantidad(){ c_cantidad--; }
	void interactua(Protagonista* p_protagonista);
	virtual void actualizaEntidadJuego();
	irr::scene::IMeshSceneNode* dibujaAura();
	std::string dameNombre(){ return c_nombre; }
	std::string dameDescripcion(){ return c_descripcion; }
	std::string dameNombreImagen(){ return c_imagenObjeto; }
	//-1 EL OBJETO SE HA ROTO AL USARLO. -2 SI ES UN ARMA QUE REQUIERE RECARGA. 0 EN OTRO CASO. DAÑO SI ES UN ARMA.
	virtual char usar();
	TiposObjeto dameTipoObjeto(){ return c_tipoObjeto; }
	void setPuntoGeneracionObjetos(PuntoGeneracionObjetos* p_puntoGeneracionObjetos){ c_puntoGeneracionObjetos = p_puntoGeneracionObjetos; }

protected:
	TiposObjeto c_tipoObjeto;
	bool c_esApilable;
	float c_peso;
	char c_cantidad;
	std::string c_descripcion;
	std::string c_nombre;
	std::string c_imagenObjeto;

private:
	PuntoGeneracionObjetos* c_puntoGeneracionObjetos;
};

