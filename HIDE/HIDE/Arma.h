#pragma once
#include "Objeto.h"
#include "Constantes.h"

class Arma : public Objeto
{
public:
	Arma(float p_posicionX, float p_posicionZ, char* p_modelo3D, float p_peso, float p_maximoAlcance, 
		 bool p_haceRuido, char p_da�o, char p_cargadorActual, bool p_esRompible, char p_tama�oMaximoCargador,
		 char p_peligrosidad, char* p_nombre, char* p_descripcion, char* p_nombreImagenObjeto, TiposArma p_tipoArma);
	~Arma();
	char usar();
	void recarga(char p_numeroProyectiles);
	char dameTama�oMaximoCargador(){ return c_tama�oMaximoCargador; }
	char dameCargadorActual(){ return c_cargadorActual; }
	char damePeligrosidadArma(){ return c_peligrosidad; }
	char dameDa�o(){ return c_da�o; }
	float dameAlcance(){ return c_maximoAlcance; }
	TiposArma dameTipoArma(){ return c_tipoArma; }
	bool dameHaceRuido(){ return c_haceRuido; }

private:
	TiposArma c_tipoArma;
	float c_maximoAlcance;
	bool c_haceRuido;
	char c_da�o;
	char c_cargadorActual;
	bool c_esRompible;
	char c_tama�oMaximoCargador;
	char c_peligrosidad;
};

