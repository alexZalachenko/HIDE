#include "Infectado.h"
#include "Constantes.h"
#include "FachadaMotorGrafico.h"
#include "GestorEntidadesJuego.h"
#include "Protagonista.h"
#include "Nodo.h"
#include <time.h>
#include "Estado_Global.h"
#include "Estado_Exploracion.h"
#include "Estado_Alerta.h"
#include "Estado_Huir.h"
#include "Estado_Ataque.h"
#include "RaycastVeoJugador.h"
#include "Publicador.h"

Infectado::Infectado(float p_posicionX, float p_posicionZ, char p_tipoInfectado, Grafo* p_grafoMapa, Protagonista* p_protagonista, GestorEntidadesJuego* p_gestorEntidadesJuego)
	: EntidadInteractuable()
	, EntidadInterpolable(p_posicionX, p_posicionZ, "assets/enemigos/shurmano.3ds")
	, c_maquinaEstados(this)
	, c_planificadorCaminos(this, p_grafoMapa)
	, c_protagonista(p_protagonista)
	, c_gestorEntidadesJuego(p_gestorEntidadesJuego)
	, c_movimientoRestringido(false)
	, c_eliminarEntidad(false)
{
	switch (p_tipoInfectado)
	{
	case 0:
		c_vidaActual = c_vidaInicial = VIDA_INICIAL_CIVIL;
		c_daño = DANO_CIVIL;
		//poner texturas del enemigo civil
		break;
	case 1:
		c_vidaActual = c_vidaInicial = VIDA_INICIAL_MEDICO;
		c_daño = DANO_MEDICO;
		//poner texturas del enemigo medico
		break;
	case 2:
		c_vidaActual = c_vidaInicial = VIDA_INICIAL_MILITAR;
		c_daño = DANO_MILITAR;
		//poner texturas del enemigo militar
		break;
	}
	c_maquinaEstados.SetEstadoGlobal(Estado_Global::GetInstancia());
	c_maquinaEstados.CambiarEstado(Estado_Exploracion::GetInstancia());
}

Infectado::~Infectado()
{
	Publicador::damePublicador()->eliminaSuscriptor(this);
}

bool Infectado::estaElJugadorVisible()
{
	//CALCULO ROTACION DEL ENEMIGO
	int t_rotacionEnemigo = (int)dameRotacionMallaGrafica().Y;
	//t_rotacionEnemigo = t_rotacionEnemigo % 360;
	//SI LA DISTANCIA DEL PERSONAJE AL ENEMIGO ES MAYOR QUE LA VISION NO VE NADA
	b2Vec2 t_vectorInfectadoProtagonista = c_protagonista->dameCuerpoFisicoEntidad()->GetPosition() - dameCuerpoFisicoEntidad()->GetPosition();
	float aux = t_vectorInfectadoProtagonista.x;
	t_vectorInfectadoProtagonista.x = t_vectorInfectadoProtagonista.y;
	t_vectorInfectadoProtagonista.y = aux;
	
	float t_distanciaInfectadoProtagonista = sqrt(pow(t_vectorInfectadoProtagonista.x, 2) + pow(t_vectorInfectadoProtagonista.y, 2));
	if (t_distanciaInfectadoProtagonista > RANGO_MAXIMO_VISION)
		return false;

	//SI EL PERSONAJE ESTA FUERA DEL ANGULO DE VISION NO VE NADA
	//b2Vec2 t_vectorRotacionEnemigo(sin(t_rotacionEnemigo), cos(t_rotacionEnemigo));
	float rotVerProta = abs(atan2(t_vectorInfectadoProtagonista.x, t_vectorInfectadoProtagonista.y) * RADTODEG);
	int dif = abs(t_rotacionEnemigo - rotVerProta);
	//dif = dif % 360;
	if (dif > 180)
		dif = 360 - dif;
	if (dif > ANGULO_MAXIMO_VISION)
		return false;

	/*float anguloVec;
	float t_anguloHorario =     atan2(t_vectorRotacionEnemigo.y - t_vectorInfectadoProtagonista.y, t_vectorRotacionEnemigo.x - t_vectorInfectadoProtagonista.x) * RADTODEG;
	float t_anguloAntihorario = atan2(t_vectorInfectadoProtagonista.y - t_vectorRotacionEnemigo.y, t_vectorInfectadoProtagonista.x - t_vectorRotacionEnemigo.x) * RADTODEG;

	if (t_anguloHorario < t_anguloAntihorario)
		anguloVec = t_anguloHorario;
	else
		anguloVec = t_anguloAntihorario;

	if (anguloVec*RADTODEG > ANGULO_MAXIMO_VISION / 2)
		return false;*/
	//EL PERSONAJE ESTA EN EL RANGO DE VISION
	float distRayo = (float)sqrt(pow(ALTURA_ENEMIGOS, 2) + pow(t_distanciaInfectadoProtagonista, 2));
	float anguloRayo = acos(t_distanciaInfectadoProtagonista / distRayo);
	RaycastVeoJugador callback(this);
	if (callback.veoJugador())
		return true;
	else
		return false;
}

//RECIBE DIRECCION IRRLICHT
void Infectado::mueveInfectado(b2Vec2 p_direccionMovimiento, float p_velocidadMovimiento)
{
	if (!c_movimientoRestringido)
	{
		b2Vec2 direccion(p_direccionMovimiento.y * p_velocidadMovimiento, p_direccionMovimiento.x * p_velocidadMovimiento);
		dameCuerpoFisicoEntidad()->SetLinearVelocity(direccion);
		giraInfectado(p_direccionMovimiento);
	}
}

void Infectado::actualizaEntidadJuego()
{
	//PARA CUANDO LA MUERTE SE PRODUCE DENTRO DEL STEP DEL MOTOR FISICO
	if (c_eliminarEntidad)
	{
		c_gestorEntidadesJuego->eliminaEntidad(this);
		return;
	}
	c_maquinaEstados.ActualizarMEF();
}

void Infectado::interactua(Protagonista* p_protagonista)
{
	char t_ataqueProtagonista = p_protagonista->ataca();
	if (t_ataqueProtagonista > 0)
		recibeDaño(t_ataqueProtagonista);
}

void Infectado::recibeDaño(char p_daño)
{
	c_vidaActual -= p_daño;
	if (c_vidaActual <= 0)
		c_gestorEntidadesJuego->eliminaEntidad(this);
	else
	{
		Publicador::damePublicador()->notificaSuscriptores(dameCuerpoFisicoEntidad()->GetPosition().y, dameCuerpoFisicoEntidad()->GetPosition().x, MEDIO);
		if (c_vidaActual <= PORCENTAJE_VIDA_HUIR)
		{
			c_posicionAlerta = b2Vec2(c_protagonista->dameCuerpoFisicoEntidad()->GetPosition().y, c_protagonista->dameCuerpoFisicoEntidad()->GetPosition().x);
			c_maquinaEstados.CambiarEstado(Estado_Huir::GetInstancia());
		}
	}
}

void Infectado::recibeDañoUsandoFisicas(char p_daño)
{
	c_vidaActual -= p_daño;
	if (c_vidaActual <= 0)
		c_eliminarEntidad = true;
	else
	{
		Publicador::damePublicador()->notificaSuscriptores(dameCuerpoFisicoEntidad()->GetPosition().y, dameCuerpoFisicoEntidad()->GetPosition().x, MEDIO);
		if (c_vidaActual < PORCENTAJE_VIDA_HUIR)
			c_maquinaEstados.CambiarEstado(Estado_Huir::GetInstancia());
	}
}

void Infectado::setColorMalla(char p_color)
{
	// 0 verde,  1 rojo
	if (p_color == 0){
		FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->getMeshManipulator()
			->setVertexColors(dameMallaGrafica()->getMesh(),
			irr::video::SColor(100, 100, 100, 0));
	}
	else
	{
		FachadaMotorGrafico::dameFachadaMotorGrafico()->dameSceneManager()->getMeshManipulator()
			->setVertexColors(dameMallaGrafica()->getMesh(),
			irr::video::SColor(100, 250, 100, 0));
	}
}

void Infectado::aullar()
{
	Publicador::damePublicador()->notificaSuscriptores(dameCuerpoFisicoEntidad()->GetPosition().y, dameCuerpoFisicoEntidad()->GetPosition().x, ALTO);
}

b2Vec2 Infectado::calculaDireccionMovimiento()
{
	b2Vec2 posInf(dameCuerpoFisicoEntidad()->GetPosition().y, dameCuerpoFisicoEntidad()->GetPosition().x);
	b2Vec2 dir = c_planificadorCaminos.GetNodoDestino()->GetPosicion() - posInf;
	dir.Normalize();
	return dir;
}

void Infectado::mueveInfectadoHaciaPersonaje()
{
	if (!c_movimientoRestringido)
	{
		b2Vec2 dir = c_protagonista->dameCuerpoFisicoEntidad()->GetPosition() - dameCuerpoFisicoEntidad()->GetPosition();
		dir.Normalize();
		float t_direccionX = dir.x;
		dir.x = dir.y;
		dir.y = t_direccionX;
		mueveInfectado(dir, VELOCIDAD_ATAQUE_INFECTADO);
	}
}

void Infectado::ataca()
{
	time_t  timev;
	int tiempoAhora = (int)time(&timev);
	if (tiempoAhora - c_ultimoTiempoAtaque > TIEMPO_ENTRE_ATAQUES)
	{
		c_ultimoTiempoAtaque = tiempoAhora;
		c_protagonista->recibeDaño(c_daño);
	}
}

bool Infectado::protagonistaEnRangoAtaque()
{
	b2Vec2 posEne;
	posEne.x = c_protagonista->dameCuerpoFisicoEntidad()->GetPosition().y;
	posEne.y = c_protagonista->dameCuerpoFisicoEntidad()->GetPosition().x;
	b2Vec2 posInf;
	posInf.x = dameCuerpoFisicoEntidad()->GetPosition().y;
	posInf.y = dameCuerpoFisicoEntidad()->GetPosition().x;

	b2Vec2 vecdist = posEne - posInf;
	float dist = vecdist.Length();
	if (dist<3)
		return true;
	return false;
}

void Infectado::giraInfectado(b2Vec2 dir)
{
	/*
	//COMPRUEBO SI LA POSICION OBJETIVO ESTA SOBRE LOS EJES PQ LOS CALCULOS FALLAN EN ESE CASO.
	float rotObj;
	if (trunc(dir.x * 10) == 0)//X SOBRE EL EJE
	{
		if (dir.y<0)
		{
			rotObj = 180;
			dir.y = 1;//PARA QUE NO HAGA EL CALCULO DE LOS CUADRANTES
		}
		else
			rotObj = 0;
	}
	else if (trunc(dir.y * 10) == 0)//Y SOBRE EL EJE
	{
		dir.y = 1;//PARA QUE NO HAGA EL CALCULO DE LOS CUADRANTES
		if (dir.x<0)
			rotObj = 270;
		else
			rotObj = 90;
	}
	else
		rotObj = atan(dir.x / dir.y)*RADTODEG;
	//CALCULO CUADRANTE DE LA POSICION OBJETIVO PARA MODIFICAR EL ANGULO
	if (dir.y < 0)
	{
		if (dir.x < 0)//CUADRANTE 3
			rotObj = 180 + rotObj;/////////////-0.9,-0.3 TOCA SUMAR!!!! CAMBIAR!!
		else//CUADRANTE 4
			rotObj = 180 - rotObj;
	}
	if (rotObj < 0)
		rotObj += 360;
	int rotMaya = (int)dameMallaGrafica()->getRotation().Y % 360;
	if (round(rotObj) != rotMaya)
	{
		//CALCULO EL ANGULO MENOR
		short difRot = (short)rotObj - rotMaya;
		if (abs(difRot) >(rotMaya + 180) % 360)
		{
			if (difRot < 0)
				difRot += 360;
			else
				difRot -= 360;
		}
		//APLICO LA ROTACION
		setRotacionNueva(irr::core::vector3df(0, rotObj, 0));
	}*/
	int rotacionNueva = (int)(atan2(dir.x, dir.y) * RADTODEG);
	rotacionNueva = rotacionNueva % 360;
	if (rotacionNueva < 0)
		rotacionNueva += 360;
	//APLICO LA ROTACION
	setRotacionNueva(irr::core::vector3df(0.f, rotacionNueva, 0.f));
}

//SI LA DISTANCIA ES MENOR QE EL VOLUMEN OIGO EL SONIDO
void Infectado::recibeNotificacion(float p_posicionSonidox, float p_posicionSonidoy, VolumenSonidos p_volumen)
{
	b2Vec2 t_distancia = b2Vec2(p_posicionSonidoy, p_posicionSonidox) - dameCuerpoFisicoEntidad()->GetPosition();
	if (t_distancia.Length() < (float)p_volumen)
	{
		if (c_maquinaEstados.GetEstadoActual() == Estado_Ataque::GetInstancia())
			return;
		// si estado == grupo -> notificar
		if (c_maquinaEstados.GetEstadoActual() == Estado_Huir::GetInstancia())
		{
			c_posicionAlerta = b2Vec2(p_posicionSonidox, p_posicionSonidoy);
			c_maquinaEstados.CambiarEstado(Estado_Huir::GetInstancia());
			return;
		}
		c_posicionAlerta = b2Vec2(p_posicionSonidox, p_posicionSonidoy);
		c_maquinaEstados.CambiarEstado(Estado_Alerta::GetInstancia());
	}
}


