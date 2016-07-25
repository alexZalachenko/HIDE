#pragma once
#include "NodoArbolDecision.h"
#include "EscritorFicheros.h"

class AccionDecirHola : public NodoArbolDecision
{
public:
	AccionDecirHola(){}
	~AccionDecirHola(){}
	void tomaDecision()
	{
		EscritorFicheros::dameEscritorFicheros()->escribe("Hola! \n");
	}
};

class AccionAtaqueSuicida : public NodoArbolDecision
{
public:
	AccionAtaqueSuicida(){}
	~AccionAtaqueSuicida(){}
	void tomaDecision()
	{
		EscritorFicheros::dameEscritorFicheros()->escribe("Ataco con vida baja! \n");
	}
};

class AccionHuir : public NodoArbolDecision
{
public:
	AccionHuir(){}
	~AccionHuir(){}
	void tomaDecision()
	{
		EscritorFicheros::dameEscritorFicheros()->escribe("Huyo! \n");
	}
};

class AccionAtaqueSeguro : public NodoArbolDecision
{
public:
	AccionAtaqueSeguro(){}
	~AccionAtaqueSeguro(){}
	void tomaDecision()
	{
		EscritorFicheros::dameEscritorFicheros()->escribe("Ataco xq tengo vida! \n");
	}
};

class AccionBuscarCurar : public NodoArbolDecision
{
public:
	AccionBuscarCurar(){}
	~AccionBuscarCurar(){}
	void tomaDecision()
	{
		EscritorFicheros::dameEscritorFicheros()->escribe("Busco Curar! \n");
	}
};

class AccionBuscarJugador : public NodoArbolDecision
{
public:
	AccionBuscarJugador(){}
	~AccionBuscarJugador(){}
	void tomaDecision()
	{
		EscritorFicheros::dameEscritorFicheros()->escribe("Busco Jugador! \n");
	}
};