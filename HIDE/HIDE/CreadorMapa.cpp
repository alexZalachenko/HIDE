#include "CreadorMapa.h"
#include "FachadaMotorFisico.h"
#include <vector>
using namespace std;
using namespace irr;
using namespace scene;

CreadorMapa::CreadorMapa(b2World* world)
	: mundo(world)
{
}

CreadorMapa::~CreadorMapa()
{
}

void CreadorMapa::AnadePared(b2Body** ground, b2Vec2 p1, b2Vec2 p2, b2Vec2 posCasilla, irr::scene::IDummyTransformationSceneNode* padre){
	//PARTE FISICA
	b2EdgeShape shape;
	b2FixtureDef sd;
	sd.shape = &shape;		
	sd.density = 0.f;
	b2Vec2 p1aux(p1.y, p1.x); b2Vec2 p2aux(p2.y, p2.x); 
	shape.Set(p1aux, p2aux);
	(*ground)->CreateFixture(&sd);
	
	//PARTE GRAFICA
	/*b2Vec2 dist = p2 - p1;
	dist.x = abs(dist.x);	dist.y = abs(dist.y);
	irr::scene::IMeshSceneNode* nodo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addCubeSceneNode(1.f, padre);
	nodo->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->getMeshManipulator()->setVertexColors(nodo->getMesh(), irr::video::SColor(112, 122, 112, 112));
	if (dist.x != 0)
	{//PASILLO HORIZONTAL

		if (p1.x > p2.x)
			nodo->setPosition(irr::core::vector3df(p2.x + dist.x / 2.f, 0, p1.y));
		else
			nodo->setPosition(irr::core::vector3df(p1.x + dist.x / 2.f, 0, p1.y));
		nodo->setScale(irr::core::vector3df(dist.x, 1, 0.5));
	}
	else
	{//PASILLO VERTICAL
		if (p1.y>p2.y)
			nodo->setPosition(irr::core::vector3df(p1.x, 0, p2.y + dist.y / 2.f));
		else
			nodo->setPosition(irr::core::vector3df(p1.x, 0, p1.y + dist.y / 2.f ));
		nodo->setScale(irr::core::vector3df(0.5, 1, dist.y));
	}*/
}

//LA POSICION HAY QUE DARLA EN COORDENADAS CASILLA
IDummyTransformationSceneNode* CreadorMapa::CreaPasillo(b2Vec2 posCasilla, char orientacion, Grafo* g)
{
	//0=horizontal 1=vertical
	irr::scene::IDummyTransformationSceneNode* grupo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addDummyTransformationSceneNode();
	grupo->getRelativeTransformationMatrix().setTranslation(irr::core::vector3df(posCasilla.x*TAMANO_CASILLA_MAPA, 0, posCasilla.y*TAMANO_CASILLA_MAPA));
	
	b2BodyDef bd;
	b2Vec2 posPixel(posCasilla.x * TAMANO_CASILLA_MAPA, posCasilla.y * TAMANO_CASILLA_MAPA);
	bd.position.Set(posPixel.y, posPixel.x);
	b2Body* estancia = mundo->CreateBody(&bd);
	estancia->SetUserData("ALTA");
	b2Vec2 p1, p2;
	p1.x = 0.f;					p1.y = -3.f;
	p2.x = 16.f;				p2.y = -3.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.y -= 10;
	p2.y -= 10;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);

	//AÑADO LA MALLA 
	irr::scene::IMeshSceneNode* malla = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena("assets/escenario/pasillo.3ds");
	malla->setPosition(malla->getPosition() + irr::core::vector3df(posCasilla.x * TAMANO_CASILLA_MAPA, 0, posCasilla.y * TAMANO_CASILLA_MAPA));

	if (orientacion == 1)
	{
		RotaEstancia(90.f, estancia, grupo);
		malla->setRotation(irr::core::vector3df(0, 90, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA, 0, 0));
	}
	short x = 8 + (short)posPixel.x;
	short y = -8 + (short)posPixel.y;
	g->AnadeNodo(b2Vec2(x, y));
	FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x,3,y));
	return grupo;
}

IDummyTransformationSceneNode* CreadorMapa::CreaPasilloConPuerta(b2Vec2 posCasilla, char orientacion, Grafo* g)
{
	//0=PUERTA ARRIBA 1=PUERTA DCHA 2=PUERTA ABAJO 3=PUERTA IZDA
	irr::scene::IDummyTransformationSceneNode* grupo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addDummyTransformationSceneNode();
	grupo->getRelativeTransformationMatrix().setTranslation(irr::core::vector3df(posCasilla.x*TAMANO_CASILLA_MAPA, 0, posCasilla.y*TAMANO_CASILLA_MAPA));

	b2BodyDef bd;
	b2Vec2 posPixel(posCasilla.x * TAMANO_CASILLA_MAPA, posCasilla.y * TAMANO_CASILLA_MAPA);
	bd.position.Set(posPixel.y, posPixel.x);
	b2Body* estancia = mundo->CreateBody(&bd);
	estancia->SetUserData("ALTA");
	b2Vec2 p1, p2;
	p1.x = 0.f;	p1.y = -3.f;
	p2.x = 6.f; p2.y = -3.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x += 6; p1.y += 3;	
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x += 4;
	p2.x += 4;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x += 6; p1.y -= 3;		
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f;	p1.y = -13.f;
	p2.x = 16.f; p2.y = -13.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);

	irr::scene::IMeshSceneNode* malla = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena("assets/escenario/pasilloPuerta.3ds");
	//FachadaMotorGrafico::dameFachadaMotorGrafico()->aplicaTexturas(malla, "pasillo.png");
	malla->setPosition(malla->getPosition() + irr::core::vector3df(posCasilla.x * TAMANO_CASILLA_MAPA, 0, posCasilla.y * TAMANO_CASILLA_MAPA));

	switch (orientacion)
	{
	case 1:
		RotaEstancia(90.f, estancia, grupo);
		malla->setRotation(irr::core::vector3df(0, 90, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA, 0, 0));
		break;
	case 2:
		RotaEstancia(180.f, estancia, grupo);
		malla->setRotation(irr::core::vector3df(0, 180, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA, 0, -TAMANO_CASILLA_MAPA));
		break;
	case 3:
		RotaEstancia(270.f, estancia, grupo);
		malla->setRotation(irr::core::vector3df(0, 270, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(0, 0, -TAMANO_CASILLA_MAPA));
		b2Vec2 posf = estancia->GetPosition();
		irr::core::vector3df pos = grupo->getRelativeTransformationMatrix().getTranslation();
		//PARTE FISICA
		posf.x -= 1 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.Z -= 1 * TAMANO_CASILLA_MAPA;
		estancia->SetTransform(posf, estancia->GetAngle());
		grupo->getRelativeTransformationMatrix().setTranslation(pos);
		break;
	}
	//ANADO NODO AL GRAFO
	short x = 8 + (short)posPixel.x;
	short y = -8 + (short)posPixel.y;
	FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
	g->AnadeNodo(b2Vec2(x, y));
	return grupo;
}

IDummyTransformationSceneNode* CreadorMapa::CreaPasilloConCurva(b2Vec2 posCasilla, char orientacion, Grafo* g)
{
	//FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena("assets/escenario/pasilloCurva.3ds");
	//                     __                       __                
	//0== |__          1==   |       2==  __|  3== |            
	irr::scene::IDummyTransformationSceneNode* grupo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addDummyTransformationSceneNode();
	grupo->getRelativeTransformationMatrix().setTranslation(irr::core::vector3df(posCasilla.x*TAMANO_CASILLA_MAPA, 0, posCasilla.y*TAMANO_CASILLA_MAPA));
	b2BodyDef bd;
	b2Vec2 posPixel(posCasilla.x * TAMANO_CASILLA_MAPA, posCasilla.y * TAMANO_CASILLA_MAPA);
	bd.position.Set(posPixel.y, posPixel.x);
	b2Body* estancia = mundo->CreateBody(&bd);
	estancia->SetUserData("ALTA");
	b2Vec2 p1, p2;
	p1.x = 0.f; p1.y = -3.f;		
	p2.x = 29.f; p2.y = -3.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.y -= 10;
	p2.y -= 10;
	p2.x -= 10;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.y -= 19;
	p1.x += 19;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x += 10;
	p2.x += 10;
	p2.y += 10;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);

	//AÑADO LA MALLA 
	irr::scene::IMeshSceneNode* malla = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena("assets/escenario/pasilloCurva.3ds");
	malla->setPosition(malla->getPosition() + irr::core::vector3df(posCasilla.x * TAMANO_CASILLA_MAPA, 0, posCasilla.y * TAMANO_CASILLA_MAPA));

	b2Vec2 posf = estancia->GetPosition();
	irr::core::vector3df pos = grupo->getRelativeTransformationMatrix().getTranslation();
	short x, y;
	switch (orientacion)
	{
		case 0:
			RotaEstancia(180.f, estancia, grupo);
			malla->setPosition(malla->getPosition() + irr::core::vector3df(0, 0, -TAMANO_CASILLA_MAPA*2));
			malla->setRotation(irr::core::vector3df(0, -90, 0));
			//PARTE FISICA
			posf.y += 2*TAMANO_CASILLA_MAPA;
			posf.x -= 2*TAMANO_CASILLA_MAPA;
			//PARTE GRAFICA
			pos.Z -= 2*TAMANO_CASILLA_MAPA;
			pos.X += 2*TAMANO_CASILLA_MAPA;
			//ANADO NODO AL GRAFO
			x = 8 + (short)posPixel.x;
			y = -24 + (short)posPixel.y;
			break;
		case 1:
			malla->setRotation(irr::core::vector3df(0, 90, 0));
			malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA * 2, 0, 0));
			//ANADO NODO AL GRAFO
			x = 24 + (short)posPixel.x;
			y = -8 + (short)posPixel.y;
			break;
		case 2:
			RotaEstancia(90.f, estancia, grupo); 
			malla->setRotation(irr::core::vector3df(0, 180, 0));
			malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA * 2, 0, -TAMANO_CASILLA_MAPA * 2));
			//PARTE FISICA
			posf.y += 2*TAMANO_CASILLA_MAPA;
			//PARTE GRAFICA
			pos.X += 2*TAMANO_CASILLA_MAPA;
			//ANADO NODO AL GRAFO
			x = 24 + (short)posPixel.x;
			y = -24 + (short)posPixel.y;
			break;
		case 3:
			RotaEstancia(-90.f, estancia, grupo);
			malla->setRotation(irr::core::vector3df(0, 0, 0));
			//PARTE FISICA
			posf.x -= 2*TAMANO_CASILLA_MAPA;
			//PARTE GRAFICA
			pos.Z -= 2*TAMANO_CASILLA_MAPA;
			//ANADO NODO AL GRAFO
			x = 8 + (short)posPixel.x;
			y = -8 + (short)posPixel.y;
			break;
	}
	estancia->SetTransform(posf, estancia->GetAngle());
	grupo->getRelativeTransformationMatrix().setTranslation(pos);
	g->AnadeNodo(b2Vec2(x, y));
	FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
	return grupo;
}

IDummyTransformationSceneNode* CreadorMapa::CreaPasilloConPasillo(b2Vec2 posCasilla, char orientacion, Grafo* g)
{
	//                        ___				                
	//0==  _|_            1==  |              2==  -|           3== |-   
	irr::scene::IDummyTransformationSceneNode* grupo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addDummyTransformationSceneNode();
	grupo->getRelativeTransformationMatrix().setTranslation(irr::core::vector3df(posCasilla.x*TAMANO_CASILLA_MAPA, 0, posCasilla.y*TAMANO_CASILLA_MAPA));
	                                                     
	b2BodyDef bd;
	b2Vec2 posPixel(posCasilla.x * TAMANO_CASILLA_MAPA, posCasilla.y * TAMANO_CASILLA_MAPA);
	bd.position.Set(posPixel.y, posPixel.x);
	b2Body* estancia = mundo->CreateBody(&bd);
	estancia->SetUserData("ALTA");
	b2Vec2 p1, p2;
	p1.x = 0.f; p1.y = -3.f;
	p2.x = 48.f; p2.y = -3.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f; p1.y = -13.f;
	p2.x = 19.f; p2.y = -13.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x += 29.f; 
	p2.x += 29.f; 
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 19.f; p1.y = -32.f;
	p2.x = 19.f; p2.y = -13.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x += 10.f;
	p2.x += 10.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);

	irr::scene::IMeshSceneNode* malla = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena("assets/escenario/pasilloInterseccion.3ds");
	malla->setPosition(malla->getPosition() + irr::core::vector3df(posCasilla.x * TAMANO_CASILLA_MAPA, 0, posCasilla.y * TAMANO_CASILLA_MAPA));

	b2Vec2 posf = estancia->GetPosition();
	irr::core::vector3df pos = grupo->getRelativeTransformationMatrix().getTranslation();
	short x, y;
	switch (orientacion)
	{
	case 0:
		RotaEstancia(180, estancia, grupo);
		//PARTE FISICA
		posf.y += 3 * TAMANO_CASILLA_MAPA;
		posf.x -= 2 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.Z -= 2 * TAMANO_CASILLA_MAPA;
		pos.X += 3 * TAMANO_CASILLA_MAPA;
		//ANADO NODO AL GRAFO
		x = 24 + (short)posPixel.x;
		y = -24 + (short)posPixel.y;
		break;
	case 1:
		malla->setRotation(irr::core::vector3df(0, 180, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA*3, 0, -TAMANO_CASILLA_MAPA*2));
		//ANADO NODO AL GRAFO
		x = 24 + (short)posPixel.x;
		y = -8 + (short)posPixel.y;
		break;
	case 2:
		RotaEstancia(90, estancia, grupo);
		malla->setRotation(irr::core::vector3df(0, -90, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(0, 0, -TAMANO_CASILLA_MAPA*3));
		//PARTE FISICA
		posf.y += 2 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.X += 2 * TAMANO_CASILLA_MAPA;
		//ANADO NODO AL GRAFO
		x = 24 + (short)posPixel.x;
		y = -24 + (short)posPixel.y;
		break;
	case 3:
		RotaEstancia(-90, estancia, grupo);
		malla->setRotation(irr::core::vector3df(0, 90, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA*2, 0, 0));
		//PARTE FISICA
		posf.x -= 3 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.Z -= 3 * TAMANO_CASILLA_MAPA;
		//ANADO NODO AL GRAFO
		x = 8 + (short)posPixel.x;
		y = -24 + (short)posPixel.y;
		break;
	}
	estancia->SetTransform(posf, estancia->GetAngle());
	grupo->getRelativeTransformationMatrix().setTranslation(pos);
	g->AnadeNodo(b2Vec2(x, y));
	FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
	return grupo;
}

IDummyTransformationSceneNode* CreadorMapa::CreaPasilloCallejonSinSalida(b2Vec2 posCasilla, char orientacion, Grafo* g)
{
	//   __                          __             __             
	// 0 __|         1   |__|    2  |__         3  |  |           
	irr::scene::IDummyTransformationSceneNode* grupo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addDummyTransformationSceneNode();
	grupo->getRelativeTransformationMatrix().setTranslation(irr::core::vector3df(posCasilla.x*TAMANO_CASILLA_MAPA, 0, posCasilla.y*TAMANO_CASILLA_MAPA));

	b2BodyDef bd;
	b2Vec2 posPixel(posCasilla.x * TAMANO_CASILLA_MAPA, posCasilla.y * TAMANO_CASILLA_MAPA);
	bd.position.Set(posPixel.y, posPixel.x);
	b2Body* estancia = mundo->CreateBody(&bd);
	estancia->SetUserData("ALTA");
	b2Vec2 p1, p2;
	p1.x = 0.f;					p1.y = -3.f;
	p2.x = 16.f ;				p2.y = -3.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.y -= 10;
	p2.y -= 10;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x += 16;
	p1.y += 10;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);

	irr::scene::IMeshSceneNode* malla = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena("assets/escenario/pasilloCortado.3ds");
	malla->setPosition(malla->getPosition() + irr::core::vector3df(posCasilla.x * TAMANO_CASILLA_MAPA, 0, posCasilla.y * TAMANO_CASILLA_MAPA));

	switch (orientacion)
	{
	case 1:
		RotaEstancia(90.f, estancia, grupo);
		malla->setRotation(irr::core::vector3df(0, 90, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA, 0, 0));
		break;
	case 2:
		RotaEstancia(180.f, estancia, grupo);
		malla->setRotation(irr::core::vector3df(0, 180, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA, 0, -TAMANO_CASILLA_MAPA));
		break;
	case 3:
		RotaEstancia(270.f, estancia, grupo);
		malla->setRotation(irr::core::vector3df(0, -90, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(0, 0, -TAMANO_CASILLA_MAPA));
		b2Vec2 posf = estancia->GetPosition();
		irr::core::vector3df pos = grupo->getRelativeTransformationMatrix().getTranslation();
		//PARTE FISICA
		posf.x -= 1 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.Z -= 1 * TAMANO_CASILLA_MAPA;
		estancia->SetTransform(posf, estancia->GetAngle());
		grupo->getRelativeTransformationMatrix().setTranslation(pos);
		break;
	}
	//ANADO NODO AL GRAFO
	short x = 8 + (short)posPixel.x;
	short y = -8 + (short)posPixel.y;
	g->AnadeNodo(b2Vec2(x, y));
	FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
	return grupo;
}

IDummyTransformationSceneNode* CreadorMapa::CreaMesa(b2Body** ground, b2Vec2 posCasilla, b2Vec2 p1, b2Vec2 p2, irr::scene::IDummyTransformationSceneNode* padre)
{
	//PARTE GRAFICA
	AnadePared(ground, b2Vec2(p1.x, p1.y), b2Vec2(p2.x, p1.y), posCasilla, padre);
	AnadePared(ground, b2Vec2(p1.x, p1.y), b2Vec2(p1.x, p2.y), posCasilla, padre);
	AnadePared(ground, b2Vec2(p1.x, p2.y), b2Vec2(p2.x, p2.y), posCasilla, padre);
	AnadePared(ground, b2Vec2(p2.x, p1.y), b2Vec2(p2.x, p2.y), posCasilla, padre);
	return nullptr;
}

IDummyTransformationSceneNode* CreadorMapa::CreaBano(b2Vec2 posCasilla, char orientacion, Grafo* g)
{
	// 0=PUERTA ABAJO		1=PUERTA IZQUIERDA		2=PUERTA ARRIBA		3=PUERTA DERECHA
	irr::scene::IDummyTransformationSceneNode* grupo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addDummyTransformationSceneNode();
	grupo->getRelativeTransformationMatrix().setTranslation(irr::core::vector3df(posCasilla.x*TAMANO_CASILLA_MAPA, 0, posCasilla.y*TAMANO_CASILLA_MAPA));

	b2BodyDef bd;
	b2Vec2 posPixel(posCasilla.x * TAMANO_CASILLA_MAPA, posCasilla.y * TAMANO_CASILLA_MAPA);
	bd.position.Set(posPixel.y, posPixel.x);
	b2Body* estancia = mundo->CreateBody(&bd);
	estancia->SetUserData("ALTA");
	b2Vec2 p1, p2;
	p1.x = 0.f;			p1.y = 0.f;
	p2.x = 16.f ;		p2.y = 0.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 16;			p1.y = -16;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p2.x = 10;			p2.y = -16;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f;			p1.y = -16.f;
	p2.x = 6.f;		p2.y = -16.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p2.x = 0.f;		p2.y = 0.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);

	irr::scene::IMeshSceneNode* malla = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena("assets/escenario/baño.3ds");
	malla->setPosition(malla->getPosition() + irr::core::vector3df(posCasilla.x * TAMANO_CASILLA_MAPA, 0, posCasilla.y * TAMANO_CASILLA_MAPA));

	switch (orientacion)
	{
	case 1:
		malla->setRotation(irr::core::vector3df(0, 90, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA, 0, 0));
		RotaEstancia(90.f, estancia, grupo);
		break;
	case 2:
		malla->setRotation(irr::core::vector3df(0, 180, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA, 0, -TAMANO_CASILLA_MAPA));
		RotaEstancia(180.f, estancia, grupo);
		break;
	case 3:
		malla->setRotation(irr::core::vector3df(0, 270, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(0, 0, -TAMANO_CASILLA_MAPA ));
		RotaEstancia(270.f, estancia, grupo);
		b2Vec2 posf = estancia->GetPosition();
		irr::core::vector3df pos = grupo->getRelativeTransformationMatrix().getTranslation();
		//PARTE FISICA
		//posf.y += 3 * TAMANO_CASILLA_MAPA;
		posf.x -= 1 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.Z -= 1 * TAMANO_CASILLA_MAPA;
		//pos.X += 3 * TAMANO_CASILLA_MAPA;
		estancia->SetTransform(posf, estancia->GetAngle());
		grupo->getRelativeTransformationMatrix().setTranslation(pos);
		break;
	}
	//ANADO NODO AL GRAFO
	short x = 8 + (short)posPixel.x;
	short y = -8 + (short)posPixel.y;
	g->AnadeNodo(b2Vec2(x, y));
	FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
	return grupo;
}

IDummyTransformationSceneNode* CreadorMapa::CreaLaboratorio(b2Vec2 posCasilla, char orientacion, Grafo* g)
{
	// 0=SILOS ABAJO		1=SILOS IZQUIERDA		2=SILOS ARRIBA		3=SILOS DERECHA
	irr::scene::IDummyTransformationSceneNode* grupo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addDummyTransformationSceneNode();
	grupo->getRelativeTransformationMatrix().setTranslation(irr::core::vector3df(posCasilla.x*TAMANO_CASILLA_MAPA, 0, posCasilla.y*TAMANO_CASILLA_MAPA));

	b2BodyDef bd;
	b2Vec2 posPixel(posCasilla.x * TAMANO_CASILLA_MAPA, posCasilla.y * TAMANO_CASILLA_MAPA);
	bd.position.Set(posPixel.y, posPixel.x);
	b2Body* estancia = mundo->CreateBody(&bd);
	estancia->SetUserData("ALTA");
	b2Vec2 p1, p2;
	p1.x = 0.f;			p1.y = 0.f;
	p2.x = 32.f;		p2.y = 0.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 32.f;		p1.y = -6.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 32.f;		p1.y = -10.f;
	p2.x = 32.f;		p2.y = -22.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 32.f;		p1.y = -26.f;
	p2.x = 32.f;		p2.y = -32.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f;		p1.y = -32.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p2.x = 0.f;		p2.y = -26.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f;		p1.y = -10.f;
	p2.x = 0.f;		p2.y = -22.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f;		p1.y = 0.f;
	p2.x = 0.f;		p2.y = -6.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);

	irr::scene::IMeshSceneNode* malla = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena("assets/escenario/laboratorio.3ds");
	malla->setPosition(malla->getPosition() + irr::core::vector3df(posCasilla.x * TAMANO_CASILLA_MAPA, 0, posCasilla.y * TAMANO_CASILLA_MAPA));

	//CREO MOBILIARIO
	CreaMesa(&estancia, posCasilla, b2Vec2(2, 0), b2Vec2(8, -3), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(11, 0), b2Vec2(13, -5), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(16, 0), b2Vec2(22, -3), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(25, 0), b2Vec2(27, -5), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(0, -12), b2Vec2(2, -15), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(6, -12), b2Vec2(8, -20), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(12, -12), b2Vec2(14, -15), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(19, -11), b2Vec2(22, -15), grupo);

	CreaMesa(&estancia, posCasilla, b2Vec2(30, -12), b2Vec2(32, -15), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(30, -17), b2Vec2(32, -20), grupo);

	CreaMesa(&estancia, posCasilla, b2Vec2(12, -17), b2Vec2(14, -20), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(19, -17), b2Vec2(22, -21), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(2, -28), b2Vec2(5, -31), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(8, -28), b2Vec2(11, -31), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(14, -28), b2Vec2(18, -31), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(21, -28), b2Vec2(24, -31), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(27, -28), b2Vec2(30, -31), grupo);
	CreaMesa(&estancia, posCasilla, b2Vec2(0, -17), b2Vec2(2, -20), grupo);

	b2Vec2 posf = estancia->GetPosition();
	irr::core::vector3df pos = grupo->getRelativeTransformationMatrix().getTranslation();
	short x, y;
	switch (orientacion)
	{
	case 0:
		//ANADO NODO AL GRAFO
		x = 16 + (short)posPixel.x;
		y = -8 + (short)posPixel.y;
		g->AnadeNodo(b2Vec2(x, y));
		FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
		x = 16 + (short)posPixel.x;
		y = -24 + (short)posPixel.y;
		g->AnadeNodo(b2Vec2(x, y));
		FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
		break;
	case 1:
		malla->setRotation(irr::core::vector3df(0, 90, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA*2, 0, 0));
		RotaEstancia(90.f, estancia, grupo);
		//PARTE FISICA
		posf.y += 2 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.X += 2 * TAMANO_CASILLA_MAPA;
		//ANADO NODO AL GRAFO
		x = 8 + (short)posPixel.x;
		y = -16 + (short)posPixel.y;
		g->AnadeNodo(b2Vec2(x, y));
		FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
		x = 24 + (short)posPixel.x;
		y = -16 + (short)posPixel.y;
		g->AnadeNodo(b2Vec2(x, y));
		FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
		break;
	case 2:
		malla->setRotation(irr::core::vector3df(0, 180, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA * 2, 0, -TAMANO_CASILLA_MAPA * 2));
		RotaEstancia(180.f, estancia, grupo);
		//PARTE FISICA
		posf.y += 2 * TAMANO_CASILLA_MAPA;
		posf.x -= 2 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.Z -= 2 * TAMANO_CASILLA_MAPA;
		pos.X += 2 * TAMANO_CASILLA_MAPA;
		//ANADO NODO AL GRAFO
		x = 16 + (short)posPixel.x;
		y = -8 + (short)posPixel.y;
		g->AnadeNodo(b2Vec2(x, y));
		FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
		x = 16 + (short)posPixel.x;
		y = -24 + (short)posPixel.y;
		g->AnadeNodo(b2Vec2(x, y));
		FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
		break;
	case 3:
		malla->setRotation(irr::core::vector3df(0, 270, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(0, 0, -TAMANO_CASILLA_MAPA*2));
		RotaEstancia(270.f, estancia, grupo);
		//PARTE FISICA
		//posf.y -= 1 * TAMANO_CASILLA_MAPA;//x grafica
		posf.x -= 2 * TAMANO_CASILLA_MAPA;//z grafica
		//PARTE GRAFICA
		pos.Z -= 2 * TAMANO_CASILLA_MAPA;
		//pos.X -= 1 * TAMANO_CASILLA_MAPA;
		//ANADO NODO AL GRAFO
		x = 8 + (short)posPixel.x;
		y = -16 + (short)posPixel.y;
		g->AnadeNodo(b2Vec2(x, y));
		FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
		x = 24 + (short)posPixel.x;
		y = -16 + (short)posPixel.y;
		g->AnadeNodo(b2Vec2(x, y));
		FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
		break;
	}
	estancia->SetTransform(posf, estancia->GetAngle());
	grupo->getRelativeTransformationMatrix().setTranslation(pos);
	return grupo;
}

IDummyTransformationSceneNode* CreadorMapa::CreaSalaJuntas(b2Vec2 posCasilla, char orientacion, Grafo* g)
{
	//EL GIRO ES EN SENIDO HORARIO
	// 0=PUERTA ABAJO		1=PUERTA IZQUIERDA		2=PUERTA ARRIBA		3=PUERTA DERECHA
	irr::scene::IDummyTransformationSceneNode* grupo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addDummyTransformationSceneNode();
	grupo->getRelativeTransformationMatrix().setTranslation(irr::core::vector3df(posCasilla.x*TAMANO_CASILLA_MAPA, 0, posCasilla.y*TAMANO_CASILLA_MAPA));

	b2BodyDef bd;
	b2Vec2 posPixel(posCasilla.x * TAMANO_CASILLA_MAPA, posCasilla.y * TAMANO_CASILLA_MAPA);
	bd.position.Set(posPixel.y, posPixel.x);
	b2Body* estancia = mundo->CreateBody(&bd);
	estancia->SetUserData("ALTA");
	b2Vec2 p1, p2;
	p1.x = 0.f;			p1.y = 0.f;
	p2.x = 32.f;		p2.y = 0.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 32.f;		p1.y = -32.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p2.x = 18.f;		p2.y = -32.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f;			p1.y = -32.f;
	p2.x = 14.f;		p2.y = -32.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p2.x = 0.f;			p2.y = -18.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f;			p1.y = -14.f;
	p2.x = 0.f;			p2.y = 0.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	

	switch (orientacion)
	{
	case 1:
		RotaEstancia(90.f, estancia, grupo);
		break;
	case 2:
		RotaEstancia(180.f, estancia, grupo);
		break;
	case 3:
		RotaEstancia(270.f, estancia, grupo);
		break;
	}
	return grupo;
}

IDummyTransformationSceneNode* CreadorMapa::CreaAlmacen(b2Vec2 posCasilla, char orientacion, Grafo* g)
{
	//EL GIRO ES EN SENIDO HORARIO
	// 0=PUERTA ABAJO		1=PUERTA IZQUIERDA		2=PUERTA ARRIBA		3=PUERTA DERECHA
	irr::scene::IDummyTransformationSceneNode* grupo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addDummyTransformationSceneNode();
	grupo->getRelativeTransformationMatrix().setTranslation(irr::core::vector3df(posCasilla.x*TAMANO_CASILLA_MAPA, 0, posCasilla.y*TAMANO_CASILLA_MAPA));

	b2BodyDef bd;
	b2Vec2 posPixel(posCasilla.x * TAMANO_CASILLA_MAPA, posCasilla.y * TAMANO_CASILLA_MAPA);
	bd.position.Set(posPixel.y, posPixel.x);
	b2Body* estancia = mundo->CreateBody(&bd);
	estancia->SetUserData("ALTA");
	b2Vec2 p1, p2;

	p1.x = 0.f;			p1.y = 0.f;
	p2.x = 48.f;		p2.y = 0.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 48.f;		p1.y = -6.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p2.x = 0.f;		p2.y = -6.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f;		p1.y = 0.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 22.f;		p1.y = -10.f;
	p2.x = 0.f;		p2.y = -10.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p2.x = 22.f;		p2.y = -32.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 0.f;		p1.y = -32.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p2.x = 0.f;		p2.y = -10.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 26.f;		p1.y = -10.f;
	p2.x = 48.f;		p2.y = -10.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 48.f;		p1.y = -32.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p2.x = 26.f;		p2.y = -32.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);
	p1.x = 26.f;		p1.y = -10.f;
	AnadePared(&estancia, p1, p2, posCasilla, grupo);

	irr::scene::IMeshSceneNode* malla = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirMallaAEscena("assets/escenario/almacen.3ds");
	malla->setPosition(malla->getPosition() + irr::core::vector3df(posCasilla.x * TAMANO_CASILLA_MAPA, 0, posCasilla.y * TAMANO_CASILLA_MAPA));

	b2Vec2 posf = estancia->GetPosition();
	irr::core::vector3df pos = grupo->getRelativeTransformationMatrix().getTranslation();
	short x, y;
	switch (orientacion)
	{
	case 0:
		//ANADO NODO AL GRAFO
		x = 24 + (short)posPixel.x;
		y = -8 + (short)posPixel.y;
		break;
	case 1:
		malla->setRotation(irr::core::vector3df(0, 90, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA * 2 , 0, 0));
		RotaEstancia(90.f, estancia, grupo);
		//PARTE FISICA
		posf.y += 2 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.X += 2 * TAMANO_CASILLA_MAPA;
		//ANADO NODO AL GRAFO
		x = 24 + (short)posPixel.x;
		y = -24 + (short)posPixel.y;
		break;
	case 2:
		malla->setRotation(irr::core::vector3df(0, 180, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(TAMANO_CASILLA_MAPA *3, 0, -TAMANO_CASILLA_MAPA*2));
		RotaEstancia(180.f, estancia, grupo);
		//PARTE FISICA
		posf.y += 3 * TAMANO_CASILLA_MAPA;
		posf.x -= 2 * TAMANO_CASILLA_MAPA;
		//PARTE GRAFICA
		pos.Z -= 2 * TAMANO_CASILLA_MAPA;
		pos.X += 3 * TAMANO_CASILLA_MAPA;
		//ANADO NODO AL GRAFO
		x = 24 + (short)posPixel.x;
		y = -24 + (short)posPixel.y;
		break;
	case 3:
		malla->setRotation(irr::core::vector3df(0, 270, 0));
		malla->setPosition(malla->getPosition() + irr::core::vector3df(0 , 0, -TAMANO_CASILLA_MAPA *3));
		RotaEstancia(270.f, estancia, grupo);
		//PARTE FISICA
		//posf.y -= 1 * TAMANO_CASILLA_MAPA;//x grafica
		posf.x -= 3 * TAMANO_CASILLA_MAPA;//z grafica
		//PARTE GRAFICA
		pos.Z -= 3 * TAMANO_CASILLA_MAPA;
		//pos.X -= 1 * TAMANO_CASILLA_MAPA;
		//ANADO NODO AL GRAFO
		x = 8 + (short)posPixel.x;
		y = -24 + (short)posPixel.y;
		break;
	}
	estancia->SetTransform(posf, estancia->GetAngle());
	grupo->getRelativeTransformationMatrix().setTranslation(pos);
	g->AnadeNodo(b2Vec2(x, y));
	FachadaMotorGrafico::dameFachadaMotorGrafico()->creaLuz(irr::core::vector3df(x, 3, y));
	return grupo;
}

void CreadorMapa::RotaEstancia(float grados, b2Body* estancia, irr::scene::IDummyTransformationSceneNode* grupo)
{
	b2Vec2 posf = estancia->GetPosition();
	irr::core::vector3df pos = grupo->getRelativeTransformationMatrix().getTranslation();
	estancia->SetTransform(posf, grados * DEGTORAD);
	grupo->getRelativeTransformationMatrix().setRotationDegrees(irr::core::vector3df(0.f, grados, 0.f));
	switch ((int)grados)
	{
	case 180:
		//PARTE FISICA
		posf.y += 16;
		posf.x -= 16;
		//PARTE GRAFICA
		pos.Z -= 16;
		pos.X += 16;
		break;
	case 90:
		//PARTE FISICA
		posf.y += 16;
		//PARTE GRAFICA
		pos.X += 16;
		break;
	case -90:
		//PARTE FISICA
		posf.x -= 16;
		//PARTE GRAFICA
		pos.Z -= 16;
		break;
	}
	estancia->SetTransform(posf, estancia->GetAngle());
	grupo->getRelativeTransformationMatrix().setTranslation(pos);
}

void CreadorMapa::LeeFicheroMapa(char* fich, GestorEntidadesJuego* p_gestorEntidades)
{
	//pintaEjes();
	const int TAMANOMAXLINEA = 10;
	const int TAMANOMAXNUMERO = 3;
	const int PARAMETROSPORLINEA = 4;
	const char* SEPARADOR = ",";

	char linea[TAMANOMAXLINEA];
	int valores[4];
	char *next_token = NULL;
	Grafo* grafo=new Grafo;
	vector<IDummyTransformationSceneNode*> t_mapaJuego;

	ifstream fichero(fich, ifstream::in);
	if (!fichero)
		exit(-1);

	//LEO LAS LINEAS DE FICHERO
	while (fichero.getline(linea, TAMANOMAXLINEA)){
		if (linea[0]=='G')//GENERACION DE INFECTADOS
		{
			atoi(strtok_s(linea, SEPARADOR, &next_token));
			valores[0] = atoi(strtok_s(NULL, SEPARADOR, &next_token));
			valores[1] = atoi(strtok_s(NULL, SEPARADOR, &next_token));
			p_gestorEntidades->dameGeneradorInfectados()->añadePuntoGeneracion(b2Vec2((float)valores[0], (float)valores[1]));
			continue;
		}
		else if (linea[0] == 'P')//SPAWN DEL PROTAGONISTA
		{
			atoi(strtok_s(linea, SEPARADOR, &next_token));
			valores[0] = atoi(strtok_s(NULL, SEPARADOR, &next_token));
			valores[1] = atoi(strtok_s(NULL, SEPARADOR, &next_token));
			p_gestorEntidades->creaProtagonista((float)valores[0], (float)valores[1]);
			continue;
		}
		else if (linea[0] == 'O')//GENERACION DE OBJETOS
		{
			atoi(strtok_s(linea, SEPARADOR, &next_token));
			valores[0] = atoi(strtok_s(NULL, SEPARADOR, &next_token));
			valores[1] = atoi(strtok_s(NULL, SEPARADOR, &next_token));
			p_gestorEntidades->dameGeneradorObjetos()->añadePuntoGeneracionObjetos((float)valores[0], (float)valores[1]);
			continue;
		}
		//LEO CADA NUMERO DE LA LINEA
		for (int  i = 0; i < PARAMETROSPORLINEA; i++)
		{
			if (i == 0)
				valores[i] = atoi(strtok_s(linea, SEPARADOR, &next_token));
			else
				valores[i] = atoi(strtok_s(NULL, SEPARADOR, &next_token));
		}
		//CREO LA ESTANCIA EN CUESTION
		switch (valores[0])
		{
			case 0:
				t_mapaJuego.push_back(CreaPasillo(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;
			case 1:
				t_mapaJuego.push_back(CreaPasilloCallejonSinSalida(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;
			case 2:
				t_mapaJuego.push_back(CreaPasilloConPuerta(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;
			case 3:
				t_mapaJuego.push_back(CreaPasilloConCurva(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;
			case 4:
				t_mapaJuego.push_back(CreaPasilloConPasillo(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;
			case 5:
				t_mapaJuego.push_back(CreaBano(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;
			case 6:
				t_mapaJuego.push_back(CreaAlmacen(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;
			case 7:
				t_mapaJuego.push_back(CreaLaboratorio(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;
			case 8:
				t_mapaJuego.push_back(CreaSalaJuntas(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;
			/*case 9:
				t_mapaJuego.push_back(CreaPasilloPuertaImpar(b2Vec2((float)valores[1], (float)valores[2]), (char)valores[3], grafo));
				break;*/
		}
	}
	FachadaMotorGrafico::dameFachadaMotorGrafico()->setMapaJuego(t_mapaJuego);
	fichero.close();
	p_gestorEntidades->dameGeneradorInfectados()->setGrafoMapa(grafo);
}

void CreadorMapa::pintaEjes(){
	b2Vec2 p2(100, 0);
	b2Vec2 p1(-100, 0);
	b2Vec2 dist = p2 - p1;
	dist.x = abs(dist.x);	dist.y = abs(dist.y);
	irr::scene::IMeshSceneNode* nodo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addCubeSceneNode(1.f, 0);
	nodo->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->getMeshManipulator()->setVertexColors(nodo->getMesh(), irr::video::SColor(0, 255, 0, 0));
	if (dist.x != 0)
	{//PASILLO HORIZONTAL

		if (p1.x > p2.x)
			nodo->setPosition(irr::core::vector3df(p2.x + dist.x / 2.f, 0, p1.y));
		else
			nodo->setPosition(irr::core::vector3df(p1.x + dist.x / 2.f, 0, p1.y));
		nodo->setScale(irr::core::vector3df(dist.x, 0.25, 0.05));
	}

	p2.Set(0, 100);
	p1.Set(0,-100);
	dist = p2 - p1;
	dist.x = abs(dist.x);	dist.y = abs(dist.y);
	nodo = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->addCubeSceneNode(1.f, 0);
	nodo->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->getMeshManipulator()->setVertexColors(nodo->getMesh(), irr::video::SColor(0, 0, 0, 255));
	//PASILLO VERTICAL
		if (p1.y>p2.y)
			nodo->setPosition(irr::core::vector3df(p1.x, 0, p2.y + dist.y / 2.f));
		else
			nodo->setPosition(irr::core::vector3df(p1.x, 0, p1.y + dist.y / 2.f));
		nodo->setScale(irr::core::vector3df(0.05, 0.25, dist.y));
}