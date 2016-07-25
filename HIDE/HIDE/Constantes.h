#ifndef INC_CONSTANTES
#define INC_CONSTANTES

/************************************************************************************
*                                    MATEMATICAS                                    *
************************************************************************************/
const float PI = 3.141592653589793f;
const float DEGTORAD = 0.0174532925199432957f;
const float RADTODEG = 57.295779513082320876f;


/************************************************************************************
*                                    MOTOR FISICO                                   *
************************************************************************************/
const unsigned char VELOCITYITERATIONS = 6;
const unsigned char POSITIONITERATIONS = 2;


/************************************************************************************
*                                        JUEGO                                      *
************************************************************************************/
const float TIEMPO_ACTUALIZACION_JUEGO = 1000 / 15.f;


/************************************************************************************
*                                      PROTAGONISTA                                 *
************************************************************************************/
enum EnumEstaturaPersonaje
{
	ERGUIDO = 2,
	AGACHADO = 1
};
const char	TAMAÑO_MAXIMO_MOCHILA = 10;
const char	PESO_MAXIMO_MOCHILA = 22;
const float VELOCIDAD_CORRER_PROTAGONISTA = 0.008f;
const float VELOCIDAD_ANDAR_PROTAGONISTA = 0.003f;
const float VELOCIDAD_GATEAR_PROTAGONISTA = 0.001f;
const float VELOCIDAD_GIRO_PROTAGONISTA = 0.07f;
const char VIDA_INICIAL_PROTAGONISTA = 100;
const unsigned char RANGO_MAXIMO_INTERACCION = 3;


/************************************************************************************
*                              GENERACION ENEMIGOS                                  *
************************************************************************************/
const short			INTERVALO_GENERACION_ENEMIGOS = 5000;//milisegundos
const short			INCREMENTO_ENEMIGOS_GENERADOS = 2;
const short			DISTANCIA_JUGADOR_GENERACION = 80; 

/************************************************************************************
*                                      INFECTADO                                    *
************************************************************************************/
const float			TIEMPO_ENTRE_ATAQUES = 0.5f;
const unsigned char RANGO_MAXIMO_VISION = 25;
const unsigned char ANGULO_MAXIMO_VISION = 65;//PARA CADA LADO. EN TOTAL JUSTO EL DOBLE
const unsigned char RANGO_MAXIMO_AUDICION = 30;
const unsigned char VIDA_INICIAL_CIVIL = 20;
const unsigned char DANO_CIVIL = 10;
const unsigned char VIDA_INICIAL_MEDICO = 35;
const unsigned char DANO_MEDICO = 10;
const unsigned char VIDA_INICIAL_MILITAR = 20;
const unsigned char DANO_MILITAR = 25;
const unsigned char ALTURA_ENEMIGOS = 2;
const unsigned char CANTIDAD_TIPOS_ENEMIGO = 3;
const char			PORCENTAJE_VIDA_HUIR = 10;


/************************************************************************************
*                                    CREACION MAPA                                  *
************************************************************************************/
const unsigned char ANCHO_MAPA = 10;
const unsigned char ALTO_MAPA = 10;
const unsigned char TAMANO_CASILLA_MAPA = 16;
const unsigned char ALTURA_OBJETOS_ALTURA_MEDIA = 1;


/************************************************************************************
*                                        ARMAS                                      *
************************************************************************************/
enum TiposArma
{
	PISTOLA,
	REVOLVER,
	ARCO,
	CUCHILLO,
	MACHETE,
	BATEBEISBOL
};
//////////////////////PISTOLA/////////////////////
const char  PISTOLADANO = 5;
const float  PISTOLAALCANCE = 25.f;
const char  PISTOLAUSOS = -1;
const char  PISTOLACARGADOR = 12;
/////////////////////REVOLVER////////////////////
const char  REVOLVERDANO = 7;
const float  REVOLVERALCANCE = 25.f;
const char  REVOLVERUSOS = -1;
const char  REVOLVERCARGADOR = 6;
/////////////////////ARCO////////////////////////
const char  ARCODANO = 5;
const float  ARCOALCANCE = 25.f;
const char  ARCOUSOS = -1;
const char  ARCOCARGADOR = 1;
//////////////////CUCHILLO///////////////////////
const char  CUCHILLODANO = 5;
const float  CUCHILLOALCANCE = 1.f;
const char  CUCHILLOUSOS = 30;
///////////////MACHETE//////////////////////////
const char  MACHETEDANO = 10;
const float  MACHETEALCANCE = 1.5f;
const char  MACHETEUSOS = 20;
//////////////BATEBEISBOL//////////////////////
const char  BATEBEISBOLDANO = 7;
const float  BATEBEISBOLALCANCE = 1.5f;
const char  BATEBEISBOLUSOS = 15;


/************************************************************************************
*                                      OBJETOS                                      *
************************************************************************************/
const char CURACION_ANTIBIOTICO = 30;
const long TIEMPO_INVULNERABILIDAD_MORFINA = 5000;
enum TiposObjeto
{
	ARMA,
	OBJETO_SIMPLE,
	TRAMPA,
	CONSUMIBLE
};

enum TiposObjetoSimple
{
	POLVORA, 
	CUERDA,
	HIERRO_DIMINUTO,
	HIERRO_PEQUEÑO,
	HIERRO_GRANDE,
	LISTON_MADERA,
	TABLON_MADERA,
	CLAVOS,
	MARTILLO,
	PIEDRA_AFILAR,
	SIERRA,
	MECHERO,
	HOJA_CUCHILLO,
	HOJA_MACHETE,
	MANGO_CUCHILLO,
	MANGO_MACHETE,
	BALAS_PISTOLA,
	BALAS_REVOLVER,
	FLECHAS
};

const float ALTURAITEMS = 1; 
const float PESOPOLVORA = 0.1f;
const float PESOCUERDA = 0.5f;
const float PESOHIERRODIMINUTO = 0.25f;
const float PESOHIERROPEQUENO = 0.5f;
const float PESOHIERROGRANDE = 1.f;
const float PESOLISTONMADERA = 0.5f;
const float PESOTABLONMADERA = 1.f;
const float PESOCLAVOS = 0.1f;
const float PESOMORFINA = 0.5f;
const float PESOANTIBIOTICOS = 0.5f;
const float PESOMARTILLO = 3.f;
const float PESOPIEDRAAFILAR = 2.f;
const float PESOSIERRA = 3.f;
const float PESOMECHERO = 2.f;
const float PESOBATEBEISBOL = 5.f;
const float PESOARCO = 5.f;
const float PESOPISTOLA = 5.f;
const float PESOREVOLVER = 5.f;
const float PESOCUCHILLO = 3.f;
const float PESOMACHETE = 5.f;
const float PESOHOJACUCHILLO = 1.f;
const float PESOHOJAMACHETE = 2.f;
const float PESOMANGOCUCHILLO = 1.f;
const float PESOMANGOMACHETE = 1.f;
const float PESOBALASPISTOLA = 0.1f;
const float PESOBALASREVOLVER = 0.1f;
const float PESOFLECHAS = 0.1f;
const float PESOTRAMPABOMBA = 3.f;
const float PESOTRAMPASOGA = 3.f;
const float PESOTRAMPASONORA = 3.f;
const float PESOTRAMPACLAVOS = 3.f;
const float PESOTRAMPAFUEGO = 3.f;


/************************************************************************************
*                                      TRAMPAS                                      *
************************************************************************************/
enum TipoTrampa
{
	TRAMPA_BOMBA, 
	TRAMPA_CLAVOS,
	TRAMPA_SOGA,
	TRAMPA_SONORA,
	TRAMPA_FUEGO
};

const int DELAY_TRAMPA_BOMBA = 5 * 1000;
const char DAÑO_TRAMPA_BOMBA = 40;
const char RADIO_TRAMPA_BOMBA = 6;

const int DELAY_TRAMPA_CLAVOS = 1 * 1000; //PARA NO PINCHARTE AL COLOCARLA
const char DAÑO_TRAMPA_CLAVOS = 10;
const int DURACION_TRAMPA_CLAVOS = 120 * 1000;
const char USOS_TRAMPA_CLAVOS = 5;

const int DURACION_TRAMPA_SOGA = 10 * 1000;

const int DELAY_TRAMPA_SONORA = 5 * 1000;
const int DURACION_TRAMPA_SONORA = 8 * 1000;

const int DELAY_TRAMPA_FUEGO = 5 * 1000;
const char DAÑO_TRAMPA_FUEGO = 10;
const int DURACION_TRAMPA_FUEGO = 6 * 1000;



/************************************************************************************
*                                      SONIDOS                                      *
************************************************************************************/
enum VolumenSonidos
{
	SINSONIDO = 0,
	BAJO =  30,
	MEDIO = 50,
	ALTO =  80
};
const char SONIDO_ABRIR_PUERTA = BAJO;
const char SONIDO_ANDAR = BAJO;
const char SONIDO_CORRER = MEDIO;
const char SONIDO_ATACAR_CQC = MEDIO;
const char SONIDO_DISPARAR = ALTO;
const char SONIDO_AULLIDO_INFECTADO = ALTO;
const char SONIDO_TRAMPA_SONORA = ALTO;



/************************************************************************************
*                                     INTERFAZ                                      *
************************************************************************************/
enum IDBotones
{
	ID_BOTON_MENU_PRINCIPAL_JUGAR = 0,
	ID_BOTON_MENU_PRINCIPAL_OPCIONES,
	ID_BOTON_MENU_PRINCIPAL_CREDITOS,
	ID_BOTON_MENU_PRINCIPAL_SALIR,

	ID_BOTON_MENU_PAUSA_OPCIONES,
	ID_BOTON_MENU_PAUSA_MENU_PRINCIPAL,
	ID_BOTON_MENU_PAUSA_VOLVER,
	 
	ID_BOTON_MENU_DURANTE_JUEGO_MOCHILA,
	ID_BOTON_MENU_DURANTE_JUEGO_CONSTRUCCION,
	ID_BOTON_MENU_DURANTE_JUEGO_VOLVER,

	ID_BOTON_MENU_MOCHILA_EQUIPA,
	ID_BOTON_MENU_MOCHILA_ELIMINA,
	ID_BOTON_MENU_MOCHILA_VOLVER,

	ID_BOTON_MENU_CONSTRUCCION_CREAR,
	ID_BOTON_MENU_CONSTRUCCION_VOLVER,

	ID_BOTON_MENU_CREDITOS_VOLVER,

	ID_MENU_OPCIONES_SCROLLBAR,
	ID_BOTON_MENU_OPCIONES_JUEGO_VOLVER
};

const char ANCHO_BOTON = 100;
const char ALTO_BOTON = 30;

#endif