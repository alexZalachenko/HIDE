#pragma once
class Infectado2
{
public:
	Infectado2();
	~Infectado2();
	float dameVida(){ return vida; }
	char dameDaño(){ return daño; }
	bool dameVeJugador(){ return veJugador; }

private:
	float vida;
	char daño;
	bool veJugador;
};

