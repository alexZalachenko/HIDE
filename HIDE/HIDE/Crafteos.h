#include <vector>
#include <string>
#include "Objeto.h"
const char CANTIDAD_MAXIMA_OBJETOS = 3;

class Crafteo
{
public:
	Crafteo(std::string p_objeto1, std::string p_objeto2, std::string p_objeto3, std::string p_herramienta, std::string p_objetoResultado, std::string p_imagenResultado);
	~Crafteo();
	Crafteo esCrafteable(std::vector<std::string> t_objetosRecibidos);
	bool esCrafteoValido()
	{ 
		if (c_objetoResultado != "")
			return true;
		else
			return false;
	}
	std::string dameObjetoResultado(){ return c_objetoResultado; }
	std::string dameImagenResultado(){ return c_imagenResultado; }

private:
	std::string c_objetoResultado;
	std::string c_imagenResultado;
	std::vector<std::string> objetosNecesarios;
};

std::vector<Crafteo> crafteos{	
	Crafteo("LISTON MADERA",	 "LISTON MADERA",	"CUERDA",			"CUERDA",		"ARCO",					"assets/imagenes/iconosObjetos/armas/arco.png"),
	Crafteo("MANGO CUCHILLO",  "HOJA CUCHILLO",	"",					"",					"CUCHILLO",				"assets/imagenes/iconosObjetos/armas/cuchillo.png"),
	Crafteo("MANGO MACHETE",   "HOJA MACHETE",	"",					"",					"MACHETE",				"assets/imagenes/iconosObjetos/armas/machete.png"),
	Crafteo("LISTON MADERA",   "CLAVOS",			"",					"MARTILLO",			"BATE DE BEISBOL",	"assets/imagenes/iconosObjetos/armas/batebeisbol.png"),
	Crafteo("HIERRO PEQUEÑO",  "PIEDRA AFILAR",	"",					"",					"HOJA CUCHILLO",		"assets/imagenes/iconosObjetos/objetosSimples/hojacuchillo.png"),
	Crafteo("HIERRO GRANDE",   "PIEDRA AFILAR",	"",					"",					"HOJA MACHETE",			"assets/imagenes/iconosObjetos/objetosSimples/hojamachete.png"),
	Crafteo("LISTON MADERA",   "HIERRO PEQUEÑO",	"HIERROPEQUEÑO",	"",				"MANGO CUCHILLO",		"assets/imagenes/iconosObjetos/objetosSimples/mangocuchillo.png"),
	Crafteo("LISTON MADERA",   "LISTON MADERA",	"HIERROPEQUEÑO",	"HIERRO PEQUEÑO",	"MANGO MACHETE",		"assets/imagenes/iconosObjetos/objetosSimples/mangomachete.png"),
	Crafteo("HIERRO DIMINUTO", "HIERRO DIMINUTO", "POLVORA",			"POLVORA",		"BALAS REVOLVER",		"assets/imagenes/iconosObjetos/objetosSimples/balasrevolver.png"),
	Crafteo("HIERRO DIMINUTO", "HIERRO DIMINUTO", "HIERRO DIMINUTO",	"POLVORA",		"BALAS PISTOLA",		"assets/imagenes/iconosObjetos/objetosSimples/balaspistola.png"),
	Crafteo("LISTON MADERA",	  "CLAVOS",		    "",					"",				"FLECHAS",				"assets/imagenes/iconosObjetos/objetosSimples/flechas.png"),
	Crafteo("HIERRO DIMINUTO", "PIEDRA AFILAR",   "",					"",				"CLAVOS",				"assets/imagenes/iconosObjetos/objetosSimples/clavos.png"),
	Crafteo("HIERRO PEQUEÑO",  "SIERRA",		    "",					"",				"HIERRO DIMINUTO",		"assets/imagenes/iconosObjetos/objetosSimples/hierrodiminuto.png"),
	Crafteo("HIERRO GRANDE",   "SIERRA",         "",					"",				"HIERRO PEQUEÑO",		"assets/imagenes/iconosObjetos/objetosSimples/hierropequeño.png"),
	Crafteo("HIERROPEQUEÑO",  "HIERRO PEQUEÑO",  "MARTILLO",			"",				"HIERRO GRANDE",		"assets/imagenes/iconosObjetos/objetosSimples/hierrogrande.png"),
	Crafteo("TABLON MADERA",   "SIERRA",			"",					"",				"LISTON MADERA",		"assets/imagenes/iconosObjetos/objetosSimples/listonmadera.png"),
	Crafteo("LISTON MADERA",   "LISTON MADERA",   "MARTILLO",		"",				"TABLON MADERA",			"assets/imagenes/iconosObjetos/objetosSimples/tablonmadera.png"),
	Crafteo("POLVORA",        "POLVORA",		"CUERDA",			"MECHERO",			"TRAMPA BOMBA",			"assets/imagenes/iconosObjetos/trampas/trampabomba.png"),
	Crafteo("TABLON MADERA",   "CLAVOS",			"CLAVOS",			"MARTILLO",			"TRAMPA CLAVOS",	"assets/imagenes/iconosObjetos/trampas/trampaclavos.png"),
	Crafteo("CUERDA",		  "CUERDA",			"CUERDA",			"LISTON MADERA",	"TRAMPA SOGA",			"assets/imagenes/iconosObjetos/trampas/trampasoga.png"),
	Crafteo("CUERDA",         "HIERRO GRANDE",   "HIERRO DIMINUTO",	"MARTILLO",			"TRAMPA SONORA",		"assets/imagenes/iconosObjetos/trampas/trampasonora.png"),
	Crafteo("TABLON MADERA",   "POLVORA",		"CUERDA",			"MECHERO",			"TRAMPA FUEGO",			"assets/imagenes/iconosObjetos/trampas/trampafuego.png")
};

Crafteo::Crafteo(std::string p_objeto1, std::string p_objeto2, std::string p_objeto3, std::string p_herramienta, std::string p_objetoResultado, std::string p_imagenResultado)
	: c_objetoResultado(p_objetoResultado)
	, c_imagenResultado(p_imagenResultado)
{
	objetosNecesarios.push_back(p_objeto1);
	objetosNecesarios.push_back(p_objeto2);
	objetosNecesarios.push_back(p_objeto3);
	objetosNecesarios.push_back(p_herramienta);
}

Crafteo::~Crafteo()
{
}

//DEVUELVE EL NOMBRE DEL OBJETO RESULTANTE O UN STRING VACIO "" SI NO HAY NINGUNA COMBINACION CON ESOS ELEMENTOS
Crafteo Crafteo::esCrafteable(std::vector<std::string> t_objetosRecibidos)
{
	for (size_t t_objeto = 0; t_objeto < t_objetosRecibidos.size(); t_objeto++)
	{
		if (t_objetosRecibidos[t_objeto] != objetosNecesarios[t_objeto])
			return Crafteo("","","","","","");
	}	
	return Crafteo(objetosNecesarios[0], objetosNecesarios[1], objetosNecesarios[2], objetosNecesarios[3], c_objetoResultado, c_imagenResultado);
}

Crafteo esCrafteable(std::vector<std::string> t_objetosCrafteo)
{
	Crafteo t_crafteoRetorno("", "", "", "", "", "");
	for each (Crafteo t_crafteo in crafteos)
	{
		t_crafteoRetorno = t_crafteo.esCrafteable(t_objetosCrafteo);
		if (t_crafteoRetorno.esCrafteoValido())
			return t_crafteoRetorno;
	}
	return t_crafteoRetorno;
}