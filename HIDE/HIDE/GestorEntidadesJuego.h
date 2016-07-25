#pragma once
#include <vector>
#include "GeneradorInfectados.h"
#include "Constantes.h"
#include "GeneradorObjetos.h"
class EntidadInterpolable;
class EntidadJuego;
class Protagonista;
class Grafo;
class Objeto;

class GestorEntidadesJuego
{
public:
	GestorEntidadesJuego();
	~GestorEntidadesJuego();
	std::vector<EntidadInterpolable*> getEntidadesInterpolables();
	void guardaEstadoNuevoEnEstadoAntiguo();
	void calculaEstadoNuevo(long p_tiempoTranscurridoUltimaActualizacion);
	void creaProtagonista(float p_posicionX, float p_posicionZ);
	void creaInfectado(float p_posicionX, float p_posicionZ, char p_tipoInfectado);
	Objeto* creaArma(float p_posicionX, float p_posicionZ, TiposArma p_tipoArma);
	//0 = ANTIBIOTICO 1 = MORFINA
	Objeto* creaConsumible(float p_posicionX, float p_posicionZ, char p_tipoConsumible);
	Objeto* creaTrampa(float p_posicionX, float p_posicionZ, TipoTrampa p_tipoTrampa);
	Objeto* creaObjetoSimple(float p_posicionX, float p_posicionZ, TiposObjetoSimple p_tipoObjetoSimple);
	Objeto* creaEntidadPorNombre(std::string p_nombre);
	void actualizaGeneradorInfectados();
	GeneradorInfectados* dameGeneradorInfectados(){ return &c_generadorInfectados; }
	short dameCantidadInfectadosActual(){ return c_cantidadInfectadosActual; }
	Protagonista* dameProtagonista(){ return c_protagonista; }
	GeneradorObjetos* dameGeneradorObjetos(){ return &c_generadorObjetos; }
	void actualizaGeneradorObjetos();
	void eliminaTodasEntidades();
	//ELIMINA LA ENTIDAD Y TODOS SUS ATRIBUTOS DE MEMORIA
	void eliminaEntidad(EntidadJuego* p_entidadEliminar);
	void convierteObjetoEnActualizable(Objeto* p_objeto);

private:
	//LAS ENTIDADES QUE TIENEN QUE INTERPOLAR SU POSICION PQ SE MUEVEN
	std::vector<EntidadInterpolable*> c_entidadesInterpolables;
	//LAS ENTIDADES QUE TIENEN QUE ACTUALIZAR SU COMPORTAMIENTO CADA ITERACION DEL JUEGO (INFECTADO, TRAMPA..)
	std::vector<EntidadJuego*> c_entidadesActualizables;
	//OBJETOS Y TRAMPAS INACTIVAS
	std::vector<Objeto*> c_objetos;
	Protagonista* c_protagonista;
	GeneradorInfectados c_generadorInfectados;
	short c_cantidadInfectadosActual;
	//SON LLAMADOS POR ELIMINA ENTIDAD. NO USAR DIRECTAMENTE
	void eliminaEntidadInterpolable(EntidadInterpolable* p_EntidadInterpolable);
	void eliminaEntidadActualizable(EntidadJuego* p_EntidadJuego);
	bool eliminaObjeto(EntidadJuego* p_entidadEliminar);
	GeneradorObjetos c_generadorObjetos;
};

