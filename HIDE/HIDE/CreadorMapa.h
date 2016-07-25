#pragma once
#include <Box2D/Box2D.h>
#include "Constantes.h"
#include <irrlicht.h>
#include "FachadaMotorGrafico.h"
#include <fstream>
#include "Grafo.h"
#include "GestorEntidadesJuego.h"
class FactoriaPersonajes;

class CreadorMapa
{
private:
	b2World* mundo;
	void CreadorMapa::RotaEstancia(float grados, b2Body* estancia, irr::scene::IDummyTransformationSceneNode* grupo);
	void pintaEjes();

public:
	CreadorMapa(b2World* world);
	~CreadorMapa();
	void AnadePared(b2Body** ground, b2Vec2 p1, b2Vec2 p2, b2Vec2 posCasilla, irr::scene::IDummyTransformationSceneNode* padre);
	void LeeFicheroMapa(char* fich, GestorEntidadesJuego* p_gestorEntidades);
	//ESTANCIAS
	irr::scene::IDummyTransformationSceneNode* CreaPasillo(b2Vec2 posCasilla, char orientacion, Grafo* g);
	irr::scene::IDummyTransformationSceneNode* CreaPasilloCallejonSinSalida(b2Vec2 posCasilla, char orientacion, Grafo* g);
	irr::scene::IDummyTransformationSceneNode* CreaPasilloConPuerta(b2Vec2 posCasilla, char orientacion, Grafo* g);
	irr::scene::IDummyTransformationSceneNode* CreaPasilloConCurva(b2Vec2 posCasilla, char orientacion, Grafo* g);
	irr::scene::IDummyTransformationSceneNode* CreaPasilloConPasillo(b2Vec2 posCasilla, char orientacion, Grafo* g);
	irr::scene::IDummyTransformationSceneNode* CreaBano(b2Vec2 posCasilla, char orientacion, Grafo* g);
	irr::scene::IDummyTransformationSceneNode* CreaAlmacen(b2Vec2 posCasilla, char orientacion, Grafo* g);
	irr::scene::IDummyTransformationSceneNode* CreaLaboratorio(b2Vec2 posCasilla, char orientacion, Grafo* g);
	irr::scene::IDummyTransformationSceneNode* CreaSalaJuntas(b2Vec2 posCasilla, char orientacion, Grafo* g);
	//MOBILIARIO
	irr::scene::IDummyTransformationSceneNode* CreaMesa(b2Body** ground, b2Vec2 posCasilla, b2Vec2 punto1, b2Vec2 punto2, irr::scene::IDummyTransformationSceneNode* padre);
};


