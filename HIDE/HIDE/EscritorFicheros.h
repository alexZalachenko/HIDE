#pragma once
#include <irrlicht.h>
#include <string>

class EscritorFicheros
{
public:
	static EscritorFicheros* dameEscritorFicheros();
	//A�ADE P_TEXTO AL FICHERO
	void escribe(std::string p_texto);
	//A�ADE P_TEXTO AL FICHERO Y UN SALTO DE LINEA
	void escribenl(std::string p_texto);
	void escribe(irr::core::vector3df p_vector);
	void escribenl(irr::core::vector3df p_vector);
private:
	static EscritorFicheros* ptrInstanciaEscritorFicheros;
	EscritorFicheros();
	~EscritorFicheros();
};

