#include "GestorEntidadesJuego.h"
#include "FachadaMotorFisico.h"
#include "Protagonista.h"
#include "Infectado.h"
#include "Grafo.h"
#include "GeneradorInfectados.h"
#include "EntidadInterpolable.h"
#include "EntidadJuego.h"
#include "Arma.h"
#include "Objeto.h"
#include "Consumible.h"
#include "Trampa.h"
#include "ObjetoSimple.h"

GestorEntidadesJuego::GestorEntidadesJuego()
	: c_generadorInfectados(this)
	, c_cantidadInfectadosActual(0)
	, c_generadorObjetos(this)
{
}

GestorEntidadesJuego::~GestorEntidadesJuego()
{
	eliminaTodasEntidades();
}

std::vector<EntidadInterpolable*> GestorEntidadesJuego::getEntidadesInterpolables()
{
	return c_entidadesInterpolables;
}

void GestorEntidadesJuego::eliminaEntidadInterpolable(EntidadInterpolable* p_EntidadInterpolable)
{
	if (dynamic_cast<Infectado*>(p_EntidadInterpolable))
		c_cantidadInfectadosActual--;
	std::vector<EntidadInterpolable*>::iterator t_iterador = c_entidadesInterpolables.begin();
	for each (EntidadInterpolable* t_EntidadInterpolable in c_entidadesInterpolables)
	{
		if (t_EntidadInterpolable == p_EntidadInterpolable)
		{
			c_entidadesInterpolables.erase(t_iterador);
			break;
		}
		t_iterador++;
	}
}

void GestorEntidadesJuego::eliminaEntidadActualizable(EntidadJuego* p_EntidadActualizable)
{
	std::vector<EntidadJuego*>::iterator t_iterador = c_entidadesActualizables.begin();
	for each (EntidadJuego* t_EntidadActualizable in c_entidadesActualizables)
	{
		if (t_EntidadActualizable == p_EntidadActualizable)
		{
			c_entidadesActualizables.erase(t_iterador);
			break;
		}
		t_iterador++;
	}
}

bool GestorEntidadesJuego::eliminaObjeto(EntidadJuego* p_entidadEliminar)
{
	std::vector<Objeto*>::iterator t_iterador = c_objetos.begin();
	for each (Objeto* t_objeto in c_objetos)
	{
		if (t_objeto == p_entidadEliminar)
		{
			c_objetos.erase(t_iterador);
			return true;
		}
		t_iterador++;
	}
	return false;
}

void GestorEntidadesJuego::eliminaEntidad(EntidadJuego* p_entidadEliminar)
{
	if (!eliminaObjeto(p_entidadEliminar))
	{
		eliminaEntidadActualizable(p_entidadEliminar);
		EntidadInterpolable* t_entidadInterpolableEliminar = dynamic_cast<EntidadInterpolable*>(p_entidadEliminar);
		if (t_entidadInterpolableEliminar)
			eliminaEntidadInterpolable(t_entidadInterpolableEliminar);
	}
	delete p_entidadEliminar;/////////////LAS TRAMPAS ACTIVADAS SE DESTRUYEN AQUI
}

void GestorEntidadesJuego::guardaEstadoNuevoEnEstadoAntiguo()
{
	for each (EntidadInterpolable* t_entidadInterpolable in c_entidadesInterpolables)
		t_entidadInterpolable->guardaEstadoNuevoEnEstadoAntiguo();
}

void GestorEntidadesJuego::calculaEstadoNuevo(long p_tiempoTranscurridoUltimaActualizacion)
{
	//NO SE PUEDE USAR FOR EACH PQ SI EL PROTA DICE DE ELIMINAR UNA TRAMPA PETA
	for (size_t t_entidadParaActualizar = 0; t_entidadParaActualizar < c_entidadesActualizables.size(); t_entidadParaActualizar++)
		c_entidadesActualizables[t_entidadParaActualizar]->actualizaEntidadJuego();

	FachadaMotorFisico::dameFachadaMotorFisico()->actualizaMundoFisico(p_tiempoTranscurridoUltimaActualizacion);
	for each (EntidadInterpolable* t_entidadParaInterpolar in c_entidadesInterpolables)
	{
		b2Vec2 t_posicionCuerpoFisico = t_entidadParaInterpolar->dameCuerpoFisicoEntidad()->GetPosition();
		irr::core::vector3df t_nuevaPosicion = t_entidadParaInterpolar->damePosicionNueva();
		t_nuevaPosicion.Z = t_posicionCuerpoFisico.x;
		t_nuevaPosicion.X = t_posicionCuerpoFisico.y;
		t_entidadParaInterpolar->setPosicionNueva(t_nuevaPosicion);
	}
}

void GestorEntidadesJuego::actualizaGeneradorInfectados()
{
	if (!(c_cantidadInfectadosActual > MAXIMO_INFECTADOS_SIMULTANEOS))
		c_generadorInfectados.actualizaGeneradorInfectados();
}

void GestorEntidadesJuego::actualizaGeneradorObjetos()
{
	c_generadorObjetos.actualizaGeneradorObjetos();
}

void GestorEntidadesJuego::creaProtagonista(float p_posicionX, float p_posicionZ)
{
	c_protagonista = new Protagonista(p_posicionX, p_posicionZ, this);
	c_entidadesInterpolables.push_back(c_protagonista);
	c_entidadesActualizables.push_back(c_protagonista);
	c_generadorInfectados.setProtagonista(c_protagonista);
}

void GestorEntidadesJuego::creaInfectado(float p_posicionX, float p_posicionZ, char p_tipoInfectado)
{
	if (c_protagonista == nullptr)
		exit(1);

	Infectado* t_infectadoCreado = new Infectado(p_posicionX, p_posicionZ, p_tipoInfectado,
		c_generadorInfectados.dameGrafoMapa(), c_protagonista, this);
	c_entidadesInterpolables.push_back(t_infectadoCreado);
	c_entidadesActualizables.push_back(t_infectadoCreado);
	c_cantidadInfectadosActual++;
}

Objeto* GestorEntidadesJuego::creaArma(float p_posicionX, float p_posicionZ, TiposArma p_tipoArma)
{
	char* t_modelo3D = "";
	char* t_nombre = "";
	char* t_descripcion = "";
	char* t_nombreImagenObjeto = "";
	char  t_daño, t_cargadorActual, t_tamañoMaximoCargador = 0, t_peligrosidad;
	float t_peso;
	float t_maximoAlcance;
	bool t_haceRuido, t_esRompible;
	switch (p_tipoArma)
	{
	case ARCO:
		t_maximoAlcance = ARCOALCANCE;
		t_haceRuido = false;
		t_daño = ARCODANO;
		t_cargadorActual = 0;
		t_esRompible = false;
		t_tamañoMaximoCargador = ARCOCARGADOR;
		t_peligrosidad = 1;
		t_peso = PESOARCO;
		t_modelo3D = "assets/objetos/armas/arco.3ds";
		t_nombre = "ARCO";
		t_descripcion = "ARMA A DISTANCIA CON UN ATAQUE MODERADO Y SILENCIOSO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/armas/arco.png";
		break;
	case PISTOLA:
		t_maximoAlcance = PISTOLAALCANCE;
		t_haceRuido = true;
		t_daño = PISTOLADANO;
		t_cargadorActual = 0;
		t_esRompible = false;
		t_tamañoMaximoCargador = PISTOLACARGADOR;
		t_peligrosidad = 2;
		t_peso = PESOPISTOLA;
		t_modelo3D = "assets/objetos/armas/pistola.3ds";
		t_nombre = "PISTOLA";
		t_descripcion = "ARMA DE FUEGO A DISTANCIA DE ATAQUE MODERADO. LOS DISPAROS PUEDEN SER OIDOS POR LOS INFECTADOS. CUENTA CON UN CARGADOR DE 12 BALAS";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/armas/pistola.png";
		break;
	case REVOLVER:
		t_maximoAlcance = REVOLVERALCANCE;
		t_haceRuido = true;
		t_daño = REVOLVERDANO;
		t_cargadorActual = 0;
		t_esRompible = false;
		t_tamañoMaximoCargador = REVOLVERCARGADOR;
		t_peligrosidad = 2;
		t_peso = PESOREVOLVER;
		t_modelo3D = "assets/objetos/armas/revolver.3ds";
		t_nombre = "REVOLVER";
		t_descripcion = "ARMA DE FUEGO A DISTANCIA DE ATAQUE ALTO. CUENTA CON UN CARGADOR REDUCIDO PERO ES COMPENSADO POR LAS HERIDAS QUE PRODUCE";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/armas/revolver.png";
		break;
	case CUCHILLO:
		t_maximoAlcance = CUCHILLOALCANCE;
		t_haceRuido = false;
		t_daño = CUCHILLODANO;
		t_cargadorActual = CUCHILLOUSOS;
		t_esRompible = true;
		t_peligrosidad = 0;
		t_peso = PESOCUCHILLO;
		t_modelo3D = "assets/objetos/armas/cuchillo.3ds";
		t_nombre = "CUCHILLO";
		t_descripcion = "ARMA DE MUY CORTO ALCANCE Y DE ATAQUE BAJO. SE ROMPE CON EL USO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/armas/cuchillo.png";
		break;
	case MACHETE:
		t_maximoAlcance = MACHETEALCANCE;
		t_haceRuido = false;
		t_daño = MACHETEDANO;
		t_cargadorActual = MACHETEUSOS;
		t_esRompible = true;
		t_peligrosidad = 0;
		t_peso = PESOMACHETE;
		t_modelo3D = "assets/objetos/armas/machete.3ds";
		t_nombre = "MACHETE";
		t_descripcion = "ARMA CUERPO A CUERPO DE CORTO ALCANCE. SE ROMPE CON EL USO. CAUSA MAYORES HERIDAS QUE EL CUCHILLO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/armas/machete.png";
		break;
	case BATEBEISBOL:
		t_maximoAlcance = BATEBEISBOLALCANCE;
		t_haceRuido = false;
		t_daño = BATEBEISBOLDANO;
		t_cargadorActual = BATEBEISBOLUSOS;
		t_esRompible = true;
		t_peligrosidad = 0;
		t_peso = PESOBATEBEISBOL;
		t_modelo3D = "assets/objetos/armas/bateBeisbol.3ds";
		t_nombre = "BATE DE BEISBOL";
		t_descripcion = "ARMA CUERPO A CUERPO DE CORTO ALCANTE Y POCO ATAQUE. SE ROMPE CON EL USO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/armas/batebeisbol.png";
		break;
	}
	Objeto* t_objetoCreado = new Arma(p_posicionX, p_posicionZ, t_modelo3D, t_peso, t_maximoAlcance, t_haceRuido,
		t_daño, t_cargadorActual, t_esRompible, t_tamañoMaximoCargador, t_peligrosidad,
		t_nombre, t_descripcion, t_nombreImagenObjeto, p_tipoArma);
	c_objetos.push_back(t_objetoCreado);
	return t_objetoCreado;
}

Objeto* GestorEntidadesJuego::creaConsumible(float p_posicionX, float p_posicionZ, char p_tipoConsumible)
{
	char* t_modelo3D = "";
	char* t_nombre = "";
	char* t_descripcion = "";
	char* t_nombreImagenObjeto = "";
	float t_peso = 0;
	switch (p_tipoConsumible)
	{
	case 0:
		t_modelo3D = "assets/objetos/consumibles/antibiotico.3ds";
		t_nombre = "ANTIBIOTICO";
		t_descripcion = "CURA LAS HERIDAS Y RESTABLECE LA SALUD AL USARLO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/consumibles/antibiotico.png";
		t_peso = PESOANTIBIOTICOS;
		break;
	case 1:
		t_modelo3D = "assets/objetos/consumibles/morfina.3ds";
		t_nombre = "MORFINA";
		t_descripcion = "AL CONSUMIRSE PRODUCE INMUNIDAD A LOS ATAQUES DE INFECTADOS";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/consumibles/morfina.png";
		t_peso = PESOMORFINA;
		break;
	}
	Objeto* t_objetoCreado = new Consumible(p_posicionX, p_posicionZ, t_modelo3D, t_peso, t_nombre, t_descripcion, t_nombreImagenObjeto);
	c_objetos.push_back(t_objetoCreado);
	return t_objetoCreado;
}

Objeto* GestorEntidadesJuego::creaTrampa(float p_posicionX, float p_posicionZ, TipoTrampa p_tipoTrampa)
{
	char* t_modelo3D = "";
	char* t_nombre = "";
	char* t_descripcion = "";
	char* t_nombreImagenObjeto = "";
	float t_peso = 0;
	TipoTrampa t_tipoTrampa;
	switch (p_tipoTrampa)
	{
	case TRAMPA_BOMBA:
		t_modelo3D = "assets/objetos/trampas/trampaBomba.3ds";
		t_nombre = "TRAMPA BOMBA";
		t_descripcion = "EXPLOTA PASADOS UNOS SEGUNDOS Y QUITA VIDA A LOS PERSONAJES EN UN AREA";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/trampas/trampaBomba.png";
		t_peso = PESOTRAMPABOMBA;
		t_tipoTrampa = TRAMPA_BOMBA;
		break;
	case TRAMPA_CLAVOS:
		t_modelo3D = "assets/objetos/trampas/trampaClavos.3ds";
		t_nombre = "TRAMPA CLAVOS";
		t_descripcion = "QUITA VIDA A LOS INFECTADOS QUE LA PISAN. SE ROMPE TRAS SER PISADA VARIAS VECES";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/trampas/trampaClavos.png";
		t_peso = PESOTRAMPACLAVOS;
		t_tipoTrampa = TRAMPA_CLAVOS;
		break;
	case TRAMPA_SOGA:
		t_modelo3D = "assets/objetos/trampas/trampaSoga.3ds";
		t_nombre = "TRAMPA SOGA";
		t_descripcion = "CAPTURA AL PRIMER INFECTADO QUE LA PISE Y LO INMOVILIZA.";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/trampas/trampaSoga.png";
		t_peso = PESOTRAMPASOGA;
		t_tipoTrampa = TRAMPA_SOGA;
		break;
	case TRAMPA_SONORA:
		t_modelo3D = "assets/objetos/trampas/trampaSonora.3ds";
		t_nombre = "TRAMPA SONORA";
		t_descripcion = "PROVOCA UN FUERTE RUIDO QUE ATRAE A LOS INFECTADOS CERCANOS.";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/trampas/trampaSonora.png";
		t_peso = PESOTRAMPASONORA;
		t_tipoTrampa = TRAMPA_SONORA;
		break;
	case TRAMPA_FUEGO:
		t_modelo3D = "assets/objetos/trampas/trampaFuego.3ds";
		t_nombre = "TRAMPA FUEGO";
		t_descripcion = "UNA TRAMPA QUE ARDE Y QUE QUEMA A LOS INFECTADOS QUE PASEN POR ENCIMA. EL FUEGO SE APAGA PASADOS UNOS SEGUNDOS";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/trampas/trampaFuego.png";
		t_peso = PESOTRAMPAFUEGO;
		t_tipoTrampa = TRAMPA_FUEGO;
		break;
	}
	Objeto* t_objetoCreado = new Trampa(p_posicionX, p_posicionZ, t_modelo3D, t_peso, t_nombre, t_descripcion, t_nombreImagenObjeto, t_tipoTrampa, this);
	c_objetos.push_back(t_objetoCreado);
	return t_objetoCreado;
}

Objeto* GestorEntidadesJuego::creaEntidadPorNombre(std::string p_nombre)
{
	if (p_nombre == "ARCO")
	{
		return creaArma(0, 0, ARCO);
	} 
	else if (p_nombre == "CUCHILLO")
	{
		return creaArma(0, 0, CUCHILLO);
	}
	else if (p_nombre == "MACHETE")
	{
		return creaArma(0, 0, MACHETE);
	}
	else if (p_nombre == "BATE BEISBOL")
	{
		return creaArma(0, 0, BATEBEISBOL);
	}
	else if (p_nombre == "HOJA CUCHILLO")
	{
		return creaObjetoSimple(0, 0, HOJA_CUCHILLO);
	}
	else if (p_nombre == "HOJA MACHETE")
	{
		return creaObjetoSimple(0, 0, HOJA_MACHETE);
	}
	else if (p_nombre == "MANGO CUCHILLO")
	{
		return creaObjetoSimple(0, 0, MANGO_CUCHILLO);
	}
	else if (p_nombre == "MANGO MACHETE")
	{
		return creaObjetoSimple(0, 0, MANGO_MACHETE);
	}
	else if (p_nombre == "BALAS REVOLVER")
	{
		return creaObjetoSimple(0, 0, BALAS_REVOLVER);
	}
	else if (p_nombre == "BALAS PISTOLA")
	{
		return creaObjetoSimple(0, 0, BALAS_PISTOLA);
	}
	else if (p_nombre == "FLECHAS")
	{
		return creaObjetoSimple(0, 0, FLECHAS);
	}
	else if (p_nombre == "CLAVOS")
	{
		return creaObjetoSimple(0, 0, CLAVOS);
	}
	else if (p_nombre == "HIERRO DIMINUTO")
	{
		return creaObjetoSimple(0, 0, HIERRO_DIMINUTO);
	}
	else if (p_nombre == "HIERRO PEQUEÑO")
	{
		return creaObjetoSimple(0, 0, HIERRO_PEQUEÑO);
	}
	else if (p_nombre == "HIERRO GRANDE")
	{
		return creaObjetoSimple(0, 0, HIERRO_GRANDE);
	}
	else if (p_nombre == "LISTON MADERA")
	{
		return creaObjetoSimple(0, 0, LISTON_MADERA);
	}
	else if (p_nombre == "TABLON MADERA")
	{
		return creaObjetoSimple(0, 0, TABLON_MADERA);
	}
	else if (p_nombre == "TRAMPA BOMBA")
	{
		return creaTrampa(0, 0, TRAMPA_BOMBA);
	}
	else if (p_nombre == "TRAMPA CLAVOS")
	{
		return creaTrampa(0, 0, TRAMPA_CLAVOS);
	}
	else if (p_nombre == "TRAMPA SOGA")
	{
		return creaTrampa(0, 0, TRAMPA_SOGA);
	}
	else if (p_nombre == "TRAMPA SONORA")
	{
		return creaTrampa(0, 0, TRAMPA_SONORA);
	}
	else if (p_nombre == "TRAMPA FUEGO")
	{
		return creaTrampa(0, 0,TRAMPA_FUEGO);
	}
	return nullptr;
}

Objeto* GestorEntidadesJuego::creaObjetoSimple(float p_posicionX, float p_posicionZ, TiposObjetoSimple p_tipoObjetoSimple)
{
	char* t_modelo3D = "";
	char* t_nombre = "";
	char* t_descripcion = "";
	char* t_nombreImagenObjeto = "";
	float t_peso = 0;
	switch (p_tipoObjetoSimple)
	{
	case POLVORA:
		t_modelo3D = "assets/objetos/objetosSimples/polvora.3ds";
		t_nombre = "POLVORA";
		t_descripcion = "SI VAS A QUEMARLA INTENTA ESTAR LEJOS";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/polvora.png";
		t_peso = PESOPOLVORA;
		break;
	case CUERDA:
		t_modelo3D = "assets/objetos/objetosSimples/cuerda.3ds";
		t_nombre = "CUERDA";
		t_descripcion = "UNA CUERDA SIEMPRE ES UN BUEN SUSTITUTO DE UNA CORREA";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/cuerda.png";
		t_peso = PESOCUERDA;
		break;
	case HIERRO_DIMINUTO:
		t_modelo3D = "assets/objetos/objetosSimples/hierroDiminuto.3ds";
		t_nombre = "HIERRO DIMINUTO";
		t_descripcion = "AH! SE ME HA METIDO UNA ESQUIRLA EN EL OJO!";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/hierroDiminuto.png";
		t_peso = PESOHIERRODIMINUTO;
		break;
	case HIERRO_PEQUEÑO:
		t_modelo3D = "assets/objetos/objetosSimples/hierroPequeño.3ds";
		t_nombre = "HIERRO PEQUEÑO";
		t_descripcion = "PODRIA SER UN TENEDOR RARO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/hierroPequeño.png";
		t_peso = PESOHIERROPEQUENO;
		break;
	case HIERRO_GRANDE:
		t_modelo3D = "assets/objetos/objetosSimples/hierroGrande.3ds";
		t_nombre = "HIERRO GRANDE";
		t_descripcion = "PUEDE SER PERJUDICIAL PARA LA SALUD QUE TE CAIGA ENCIMA";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/hierroGrande.png";
		t_peso = PESOHIERROGRANDE;
		break;
	case LISTON_MADERA:
		t_modelo3D = "assets/objetos/objetosSimples/listonMadera.3ds";
		t_nombre = "LISTON MADERA";
		t_descripcion = "DICEN QUE UNA ESTACA ES LA UNICA FORMA DE MATAR A UN VAMPIRO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/listonMadera.png";
		t_peso = PESOLISTONMADERA;
		break;
	case TABLON_MADERA:
		t_modelo3D = "assets/objetos/objetosSimples/tablonMadera.3ds";
		t_nombre = "TABLON MADERA";
		t_descripcion = "CON UN PAR MAS PODRIAS CONSTRUIR UN BONITO BARCO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/tablonMadera.png";
		t_peso = PESOTABLONMADERA;
		break;
	case CLAVOS:
		t_modelo3D = "assets/objetos/objetosSimples/clavos.3ds";
		t_nombre = "CLAVOS";
		t_descripcion = "INTENTA NO PISARLO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/clavos.png";
		t_peso = PESOCLAVOS;
		break;
	case MARTILLO:
		t_modelo3D = "assets/objetos/herramientas/martillo.3ds";
		t_nombre = "MARTILLO";
		t_descripcion = "CUIDADO CON LOS DEDOS AL SUJETAR LOS CLAVOS!";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/martillo.png";
		t_peso = PESOMARTILLO;
		break;
	case PIEDRA_AFILAR:
		t_modelo3D = "assets/objetos/herramientas/piedraAfilar.3ds";
		t_nombre = "PIEDRA AFILAR";
		t_descripcion = "PORQUE AFILAR CUCHILLOS ES DEMASIADO MAINSTREAM";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/piedraAfilar.png";
		t_peso = PESOPIEDRAAFILAR;
		break;
	case SIERRA:
		t_modelo3D = "assets/objetos/herramientas/sierra.3ds";
		t_nombre = "SIERRA";
		t_descripcion = "PUEDE CORTAR MADERAS PERO TAMBIEN BOCADILLOS";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/sierra.png";
		t_peso = PESOSIERRA;
		break;
	case MECHERO:
		t_modelo3D = "assets/objetos/herramientas/mechero.3ds";
		t_nombre = "MECHERO";
		t_descripcion = "¡CUIDADO, QUEMA!";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/mechero.png";
		t_peso = PESOMECHERO;
		break;
	case HOJA_CUCHILLO:
		t_modelo3D = "assets/objetos/objetosSimples/hojaCuchillo.3ds";
		t_nombre = "HOJA CUCHILLO";
		t_descripcion = "¿Y QUE ES UN CUCHILLO SIN SU HOJA?";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/hojaCuchillo.png";
		t_peso = PESOHOJACUCHILLO;
		break;
	case HOJA_MACHETE:
		t_modelo3D = "assets/objetos/objetosSimples/hojaMachete.3ds";
		t_nombre = "HOJA MACHETE";
		t_descripcion = "GRANDE COMO ALGO GRANDE, AFILADA COMO ALGO AFILADO";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/hojaMachete.png";
		t_peso = PESOHOJAMACHETE;
		break;
	case MANGO_CUCHILLO:
		t_modelo3D = "assets/objetos/objetosSimples/mangoCuchillo.3ds";
		t_nombre = "MANGO CUCHILLO";
		t_descripcion = "¿DE ALGUN SITIO HABIA QUE COGERLO NO?";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/mangoCuchillo.png";
		t_peso = PESOMANGOCUCHILLO;
		break;
	case MANGO_MACHETE:
		t_modelo3D = "assets/objetos/objetosSimples/mangoMachete.3ds";
		t_nombre = "MANGO MACHETE";
		t_descripcion = "COGER EL MACHETE POR LA HOJA NO PARECE UNA BUENA IDEA";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/mangoMachete.png";
		t_peso = PESOMANGOMACHETE;
		break;
	case BALAS_PISTOLA:
		t_modelo3D = "assets/objetos/objetosSimples/balasPistola.3ds";
		t_nombre = "BALAS PISTOLA";
		t_descripcion = "BANG BANG!";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/balasPistola.png";
		t_peso = PESOBALASPISTOLA;
		break;
	case BALAS_REVOLVER:
		t_modelo3D = "assets/objetos/objetosSimples/balasRevolver.3ds";
		t_nombre = "BALAS REVOLVER";
		t_descripcion = "BIENVENIDO AL SALVAJE OESTE";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/balasRevolver.png";
		t_peso = PESOBALASREVOLVER;
		break;
	case FLECHAS:
		t_modelo3D = "assets/objetos/objetosSimples/flechas.3ds";
		t_nombre = "FLECHAS";
		t_descripcion = "PORQUE LAS ARMAS DE FUEGO ESTAN SOBREVALORADAS";
		t_nombreImagenObjeto = "assets/imagenes/iconosObjetos/objetosSimples/flechas.png";
		t_peso = PESOFLECHAS;
		break;
	}
	Objeto* t_objetoCreado = new ObjetoSimple(p_posicionX, p_posicionZ, t_modelo3D, t_peso, t_nombre, t_descripcion, t_nombreImagenObjeto);
	c_objetos.push_back(t_objetoCreado);
	return t_objetoCreado;
}

void GestorEntidadesJuego::eliminaTodasEntidades()
{
	for each (EntidadJuego* t_EntidadActualizable in c_entidadesActualizables)
		delete t_EntidadActualizable;
	c_entidadesActualizables.clear();
	c_entidadesInterpolables.clear();
	
	for each (Objeto* t_objeto in c_objetos)
		delete t_objeto;
	c_objetos.clear();
}

void GestorEntidadesJuego::convierteObjetoEnActualizable(Objeto* p_objeto)
{
	eliminaObjeto(p_objeto);
	c_entidadesActualizables.push_back(p_objeto);
}




