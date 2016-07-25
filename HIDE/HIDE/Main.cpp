#include <irrlicht.h>
#include <irrKlang\irrKlang.h>
#include "EscenaMenuPrincipal.h"
#include "GestorEscenas.h"
#include "EscenaConEntidad.h"

#pragma comment(lib, "lib/irrKlang.lib")
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

using namespace irrklang;

int main()
{
	/*ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
	{
		printf("Could not startup engine\n");
		return 0; // error starting up the engine
	}
	return 0;*/

	//GestorEscenas::dameGestorEscenas()->cambiaEscena(EscenaConEntidad::dameEscenaConEntidad()); 
	GestorEscenas::dameGestorEscenas()->cambiaEscena(EscenaMenuPrincipal::dameEscenaMenuPrincipal());
	GestorEscenas::dameGestorEscenas()->bucleEscena();
	return 0;
}