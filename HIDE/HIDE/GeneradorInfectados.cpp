#include "GeneradorInfectados.h"
#include "Constantes.h"
#include "Protagonista.h"
#include "GestorEntidadesJuego.h"

GeneradorInfectados::GeneradorInfectados(GestorEntidadesJuego* p_gestorEntidades)
	: c_infectadosPorGeneracion(1)
	, c_gestorEntidades(p_gestorEntidades)
{
}

GeneradorInfectados::~GeneradorInfectados()
{
	delete c_grafoMapa;
}

void GeneradorInfectados::actualizaGeneradorInfectados()
{
	//SI HAY INFECTADOS EN LA PARTE PARCIAL Y HA PASADO EL INTERVALO DE GENERACION DE LA PARTE PARCIAL O SI HA PASADO EL IN
	if ((c_infectadosPorGeneracionParcial != 0 && c_relojGeneracion.dameTiempoTranscurridoMilisegundos() > TIEMPO_ENTRE_GENERACION_PARCIAL)
		|| (c_relojGeneracion.dameTiempoTranscurridoMilisegundos() > INTERVALO_GENERACION_ENEMIGOS))
		generaEnemigos();
}

void GeneradorInfectados::generaEnemigos()
{
	char t_tipoInfectado;
	//PILLO LAS POSICIONES QUE SON VALIDAS PARA GENERAR A UN INFECTADO
	b2Vec2 t_posicionProtagonista(c_protagonista->dameCuerpoFisicoEntidad()->GetPosition().y, c_protagonista->dameCuerpoFisicoEntidad()->GetPosition().x);
	std::vector<b2Vec2> t_posicionesGeneracionValidas;
	b2Vec2 t_posicionGeneracion;
	for each (b2Vec2 t_posicionGeneracion in t_puntosGeneracion)
	{
		b2Vec2 distVec = t_posicionProtagonista - t_posicionGeneracion;
		float dist = sqrt(pow(distVec.x, 2) + pow(distVec.y, 2));
		if (dist > DISTANCIA_JUGADOR_GENERACION)
			t_posicionesGeneracionValidas.push_back(t_posicionGeneracion);
	}
	if (t_posicionesGeneracionValidas.size()>0)
	{
		//LE PEGO UNA VUELTA A LAS POSICIONES VALIDAS Y SI CUANDO LE DE LA VUELTA TODAVIA QUEDAN INFECTADOS POR GENERAR LOS METO A LA GENERACION PARCIAL
		char t_posGeneracion = 0;
		//CALCULO LOS INFECTADOS QUE HAY QUE CREAR ESTA GENERACION.SI HAY QUE CREAR MAS DE LAS POSICIONES QUE TENGO VALIDAS METO LAS RESTANTES A LA GENERACION PARCIAL
		unsigned short t_infectadosAGenerar;
		t_infectadosAGenerar = MAXIMO_INFECTADOS_SIMULTANEOS - c_gestorEntidades->dameCantidadInfectadosActual();
		if (c_infectadosPorGeneracionParcial != 0)
			t_infectadosAGenerar = c_infectadosPorGeneracionParcial;

		if (c_infectadosPorGeneracion < t_infectadosAGenerar)
			t_infectadosAGenerar = c_infectadosPorGeneracion;

		if (t_infectadosAGenerar > t_posicionesGeneracionValidas.size())
		{
			c_infectadosPorGeneracionParcial = t_infectadosAGenerar - t_posicionesGeneracionValidas.size();
			t_infectadosAGenerar -= c_infectadosPorGeneracionParcial;
		}
		//RECORRO LAS POSICIONES DE GENERACION
		for (char a = 0; a < t_infectadosAGenerar; a++)
		{
			t_tipoInfectado = rand() % CANTIDAD_TIPOS_ENEMIGO;
			//CALCULO LA POSICION DE GENERACION QUE VOY A USAR PARA CREAR AL INFECTADO Y LA ELIMINO DE LA LISTA
			char t_posGen = rand() % t_posicionesGeneracionValidas.size();
			t_posicionGeneracion = t_posicionesGeneracionValidas.at(t_posGen); 
			t_posicionesGeneracionValidas.erase(t_posicionesGeneracionValidas.begin() + t_posGen);

			//CREO EL INFECTADO
			c_gestorEntidades->creaInfectado(t_posicionGeneracion.x, t_posicionGeneracion.y, t_tipoInfectado);
		}
		//SI NO SE VAN A GENERAR INFECTADOS EN LA PARTE PARCIAL INCREMENTO EL NUMERO DE INF PARA LA SIGUIENTE GENERACION
		if (c_infectadosPorGeneracionParcial == 0)
			c_infectadosPorGeneracion += INCREMENTO_ENEMIGOS_GENERADOS;
		c_relojGeneracion.dameTiempoTranscurridoMilisegundosYReinicia();
	}
}