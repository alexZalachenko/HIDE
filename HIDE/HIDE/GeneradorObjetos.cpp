#include "GeneradorObjetos.h"
#include "GestorEntidadesJuego.h"
#include "Constantes.h"

GeneradorObjetos::GeneradorObjetos(GestorEntidadesJuego* p_gestorEntidadesJuego)
	: c_gestorEntidadesJuego(p_gestorEntidadesJuego)
{
}

GeneradorObjetos::~GeneradorObjetos()
{
}

void GeneradorObjetos::actualizaGeneradorObjetos()
{
	for (size_t t_punto = 0; t_punto < c_puntosGeneracionObjetos.size(); t_punto++)
	{
		if (c_puntosGeneracionObjetos[t_punto].actualizaPuntoGeneracion())
			c_puntosGeneracionObjetos[t_punto].setObjeto(generaObjeto(c_puntosGeneracionObjetos[t_punto].damePosicion()));
	}
}

void GeneradorObjetos::añadePuntoGeneracionObjetos(float p_posicionX, float p_posicionY)
{
	c_puntosGeneracionObjetos.push_back(PuntoGeneracionObjetos(p_posicionX, p_posicionY));
}

Objeto* GeneradorObjetos::generaObjeto(b2Vec2 p_posicion)
{
	int t_tipoObjeto = rand() % 4;
	char t_objetoConcreto;
	switch (t_tipoObjeto)
	{
		//ARMA
		case 0:
			t_objetoConcreto = rand() % 6;
			switch (t_objetoConcreto)
			{
				case 0:
					return c_gestorEntidadesJuego->creaArma(p_posicion.x, p_posicion.y, PISTOLA);
					break;
				case 1:
					return c_gestorEntidadesJuego->creaArma(p_posicion.x, p_posicion.y, ARCO);
					break;
				case 2:
					return c_gestorEntidadesJuego->creaArma(p_posicion.x, p_posicion.y, REVOLVER);
					break;
				case 3:
					return c_gestorEntidadesJuego->creaArma(p_posicion.x, p_posicion.y, MACHETE);
					break;
				case 4:
					return c_gestorEntidadesJuego->creaArma(p_posicion.x, p_posicion.y, CUCHILLO);
					break;
				case 5:
					return c_gestorEntidadesJuego->creaArma(p_posicion.x, p_posicion.y, BATEBEISBOL);
					break;
			}
			break;
		//CONSUMIBLE
		case 1:
			t_objetoConcreto = rand() % 2;
			if (t_objetoConcreto == 0)
				return c_gestorEntidadesJuego->creaConsumible(p_posicion.x, p_posicion.y, 0);
			else
				return c_gestorEntidadesJuego->creaConsumible(p_posicion.x, p_posicion.y, 1);
			break;
		//TRAMPA
		case 2:
			t_objetoConcreto = rand() % 5;
			switch (t_objetoConcreto)
			{
				case 0:
					return c_gestorEntidadesJuego->creaTrampa(p_posicion.x, p_posicion.y, TRAMPA_BOMBA);
					break;
				case 1:
					return c_gestorEntidadesJuego->creaTrampa(p_posicion.x, p_posicion.y, TRAMPA_CLAVOS);
					break;
				case 2:
					return c_gestorEntidadesJuego->creaTrampa(p_posicion.x, p_posicion.y, TRAMPA_FUEGO);
					break;
				case 3:
					return c_gestorEntidadesJuego->creaTrampa(p_posicion.x, p_posicion.y, TRAMPA_SOGA);
					break;
				case 4:
					return c_gestorEntidadesJuego->creaTrampa(p_posicion.x, p_posicion.y, TRAMPA_SONORA);
					break;
			}
			break;
		//SIMPLE
		case 3:
			t_objetoConcreto = rand() % 19;
			switch (t_objetoConcreto)
			{
				case 0:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, POLVORA);
					break;
				case 1:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, CUERDA);
					break;
				case 2:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, HIERRO_DIMINUTO);
					break;
				case 3:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, HIERRO_GRANDE);
					break;
				case 4:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, HIERRO_PEQUEÑO);
					break;
				case 5:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, LISTON_MADERA);
					break;
				case 6:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, TABLON_MADERA);
					break;
				case 7:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, CLAVOS);
					break;
				case 8:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, MARTILLO);
					break;
				case 9:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, MECHERO);
					break;
				case 10:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, PIEDRA_AFILAR);
					break;
				case 11:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, SIERRA);
					break;
				case 12:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, HOJA_CUCHILLO);
					break;
				case 13:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, HOJA_MACHETE);
					break;
				case 14:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, MANGO_CUCHILLO);
					break;
				case 15:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, MANGO_MACHETE);
					break;
				case 16:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, BALAS_PISTOLA);
					break;
				case 17:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, BALAS_REVOLVER);
					break;
				case 18:
					return c_gestorEntidadesJuego->creaObjetoSimple(p_posicion.x, p_posicion.y, FLECHAS);
					break;
			}
			break;
	}
	return nullptr;
}
