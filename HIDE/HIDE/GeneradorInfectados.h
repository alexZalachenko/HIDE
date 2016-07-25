#pragma once
#include "Grafo.h"
#include "Reloj.h"
class Protagonista;
class GestorEntidadesJuego;
const short TIEMPO_ENTRE_GENERACION_PARCIAL = 1000;
const short	MAXIMO_INFECTADOS_SIMULTANEOS = 5;

class GeneradorInfectados
{
public:
	GeneradorInfectados(GestorEntidadesJuego* p_gestorEntidades);
	~GeneradorInfectados();
	Grafo* dameGrafoMapa(){ return c_grafoMapa; }
	void añadePuntoGeneracion(b2Vec2 p_puntoGeneracion){ t_puntosGeneracion.push_back(p_puntoGeneracion); }
	void setGrafoMapa(Grafo* p_grafoMapa){ c_grafoMapa = p_grafoMapa; }
	void actualizaGeneradorInfectados();
	void setProtagonista(Protagonista* p_protagonista){ c_protagonista = p_protagonista; }

private:
	Grafo* c_grafoMapa;
	GestorEntidadesJuego* c_gestorEntidades;
	std::vector<b2Vec2> t_puntosGeneracion;
	Reloj c_relojGeneracion;
	Protagonista* c_protagonista;
	short c_infectadosPorGeneracion;
	short c_infectadosPorGeneracionParcial;
	void generaEnemigos();
};

