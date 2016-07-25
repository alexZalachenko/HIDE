#pragma once
#include "Constantes.h"
#include "GestorEntidadesJuego.h"
#include <vector>
class Objeto;

class Mochila
{
public:
	Mochila(GestorEntidadesJuego* p_gestorEntidades);
	~Mochila();
	bool añadeObjetoAMochila(Objeto* p_objetoParaAñadir);
	//DEVUELVE TRUE SI EL OBJETO SE ELIMINA Y FALSE SI SOLO SE DECREMENTA SU CANTIDAD
	bool eliminaObjetoDeMochila(Objeto* p_objetoParaEliminar);
	std::vector<Objeto*>& dameObjetosMochila(){ return c_objetosEnMochila; }
	float damePesoDisponible(){ return c_pesoDisponible; }
	bool hayHuecoDisponible();
	Objeto* dameSiguienteObjeto(Objeto* p_objeto);
	Objeto* dameAnteriorObjeto(Objeto* p_objeto);

private:
	float c_pesoDisponible;
	std::vector<Objeto*> c_objetosEnMochila;
	GestorEntidadesJuego* c_gestorEntidades;
};

