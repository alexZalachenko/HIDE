#pragma once
class Infectado2
{
public:
	Infectado2();
	~Infectado2();
	float dameVida(){ return vida; }
	char dameDa�o(){ return da�o; }
	bool dameVeJugador(){ return veJugador; }

private:
	float vida;
	char da�o;
	bool veJugador;
};

