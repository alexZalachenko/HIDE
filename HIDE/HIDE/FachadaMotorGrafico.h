#pragma once
#include <irrlicht.h>
#include <vector>
class HUD;

class FachadaMotorGrafico
{
public:
	static FachadaMotorGrafico* dameFachadaMotorGrafico();
	void dibuja();
	void termina();
	void escribeTituloVentana(irr::core::stringw p_texto);
	irr::core::dimension2d<irr::u32> dameTamanoVentana();
	irr::scene::IMeshSceneNode* anadirMallaAEscena(std::string p_modelo3D);
	void aplicaTexturas(irr::scene::IMeshSceneNode* p_malla, std::vector<std::string> p_texturas);
	void aplicaTexturas(irr::scene::IMeshSceneNode* p_malla, std::string p_texturas);
	irr::video::ITexture* anadirImagenAEscena(std::string p_nombreArchivo);
	irr::scene::ISceneManager* dameSceneManager(){ return c_smgr; }
	irr::scene::ICameraSceneNode* añadeCamara(float p_posicionX, float p_posicionZ);
	void iniciaCursorRaton();
	irr::scene::IMeshSceneNode* dibujaEsferaSemitransparente(float p_posicionX, float p_posicionZ);
	irr::gui::IGUIEnvironment* dameGUIEnviroment(){ return c_guienv; }
	void borraGUI(){ c_guienv->clear(); }
	void setMapaJuego(std::vector<irr::scene::IDummyTransformationSceneNode*> p_mapaJuego){ c_mapaJuego = p_mapaJuego; }
	void borraMapaJuego();
	irr::video::ITexture* dameTextura(char* p_nombreTextura){ return c_driver->getTexture(p_nombreTextura); }
	void setHUD(HUD* p_HUD);
	void creaLuz(irr::core::vector3df t_posicion);

private:
	static FachadaMotorGrafico* ptrInstanciaFachadaMotorGrafico;
	irr::IrrlichtDevice* c_device;
	irr::video::IVideoDriver* c_driver;
	irr::scene::ISceneManager* c_smgr;
	irr::gui::IGUIEnvironment* c_guienv;
	FachadaMotorGrafico();
	~FachadaMotorGrafico();
	irr::core::dimension2d<irr::u32> c_tamañoVentana;
	std::vector<irr::scene::IDummyTransformationSceneNode*> c_mapaJuego;
	HUD* c_HUD;
	void iniciaLuces();
};

