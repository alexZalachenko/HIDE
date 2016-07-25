#pragma once
class Escena;

class GestorEscenas
{
public:
	static GestorEscenas* dameGestorEscenas();
	~GestorEscenas();
	void bucleEscena();
	void cambiaEscena(Escena* p_escenaNueva);
	void termina();

private:
	static GestorEscenas* ptrInstanciaGestorEscenas;
	GestorEscenas();
	Escena* c_escenaActual;
	bool    c_terminar;
};

