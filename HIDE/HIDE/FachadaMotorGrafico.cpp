#include "FachadaMotorGrafico.h"
#include "Constantes.h"
#include "GestorEventosEntrada.h"
#include "HUD.h"
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

FachadaMotorGrafico* FachadaMotorGrafico::ptrInstanciaFachadaMotorGrafico = 0;

FachadaMotorGrafico* FachadaMotorGrafico::dameFachadaMotorGrafico()
{
	if (ptrInstanciaFachadaMotorGrafico == 0)
		ptrInstanciaFachadaMotorGrafico = new FachadaMotorGrafico();
	return ptrInstanciaFachadaMotorGrafico;
}

FachadaMotorGrafico::FachadaMotorGrafico()
	: c_HUD(nullptr)
{
	IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
	c_tamañoVentana = nulldevice->getVideoModeList()->getDesktopResolution();
	nulldevice->drop();
	c_device = createDevice(EDT_OPENGL, c_tamañoVentana, 32, true, false, false, GestorEventosEntrada::dameGestorEventosEntrada());

	if (!c_device)
		exit(1);
	c_driver = c_device->getVideoDriver();//SE ENCARGA DE RENDERIZAR
	c_smgr = c_device->getSceneManager();//SE ENCARGA DE LA GESTION DE LA ESCENA: ANADIR NODOS AL ARBOL DE LA ESCENA, MODIFICALO, ETC
	c_guienv = c_device->getGUIEnvironment();//CREAR UNA GUI
	c_guienv->getSkin()->setFont(c_guienv->getFont("assets/tipografias/myfont.xml"));
	iniciaLuces();
}

FachadaMotorGrafico::~FachadaMotorGrafico()
{
	delete ptrInstanciaFachadaMotorGrafico;
	delete c_device;
	delete c_driver;
	delete c_smgr;
	delete c_guienv;
	ptrInstanciaFachadaMotorGrafico = 0;
	c_device = 0;
	c_driver = 0;
	c_smgr = 0;
	c_guienv = 0;
}

void FachadaMotorGrafico::dibuja()
{
	c_device->run();
	c_driver->beginScene(true, true, SColor(255, 100, 101, 140));
	c_smgr->drawAll();
	c_guienv->drawAll();
	if (c_HUD != nullptr)
		c_HUD->dibujaHUD();
	c_driver->endScene();
}

void FachadaMotorGrafico::termina()
{
	c_device->drop();
}

ICameraSceneNode* FachadaMotorGrafico::añadeCamara(float p_posicionX, float p_posicionZ)
{
	ICameraSceneNode* r_camara = c_smgr->addCameraSceneNode(0, vector3df(p_posicionX,     ERGUIDO, p_posicionZ), 
															   vector3df(p_posicionX + 5, ERGUIDO, p_posicionZ));
	r_camara->bindTargetAndRotation(true);
	return r_camara;
}

void FachadaMotorGrafico::escribeTituloVentana(irr::core::stringw p_texto)
{
	/*
	CODIGO PARA CREAR EL MENSAJE Y MANDAR A ESCRIBIR
	irr::core::stringw t_mensaje = L"";
	t_mensaje += a;
	FachadaMotorGrafico::dameFachadaMotorGrafico()->escribeTituloVentana(t_mensaje);
	*/
	c_device->setWindowCaption(p_texto.c_str());
}

irr::core::dimension2d<irr::u32> FachadaMotorGrafico::dameTamanoVentana()
{
	return c_tamañoVentana;
}

irr::scene::IMeshSceneNode* FachadaMotorGrafico::anadirMallaAEscena(std::string p_modelo3D)
{
	/*IMesh* mesh = c_smgr->getMesh(p_modelo3D);
	if (!mesh)
	{
		c_device->drop();
		exit(1);
	}
	mesh->setHardwareMappingHint(EHM_STATIC);
	IMeshSceneNode* node = c_smgr->addMeshSceneNode(mesh);
	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);
		c_smgr->getMeshManipulator()->setVertexColors(node->getMesh(), SColor(255, 76, 76, 76));
		node->setAutomaticCulling(1);///////////////////////////////////////////////////////////////////////////////////////////////
	}
	return node;*/
	
	IMesh* mesh = c_smgr->getMeshCache()->getMeshByName(p_modelo3D.c_str());
	if (!mesh)
	{
		mesh = c_smgr->getMesh(p_modelo3D.c_str());
		if (!mesh)
		{
			c_device->drop();
			exit(1);
		}
	}
	mesh->setHardwareMappingHint(EHM_STATIC);
	IMeshSceneNode* node = c_smgr->addMeshSceneNode(mesh); 
	
	if (node) {
		p_modelo3D.replace(p_modelo3D.length() - 3, 3, "png");
		irr::video::ITexture* t_textura = c_driver->findTexture(p_modelo3D.c_str());
		if (!t_textura)
		{
			t_textura = c_driver->getTexture(p_modelo3D.c_str());
			node->setMaterialTexture(0, t_textura); 
		}
		node->setMaterialFlag(EMF_LIGHTING, true);
		//c_smgr->getMeshManipulator()->setVertexColors(node->getMesh(), SColor(255, 76, 76, 76));
		node->setAutomaticCulling(1);
	}
	return node;
}

void FachadaMotorGrafico::aplicaTexturas(IMeshSceneNode* p_malla, std::vector<std::string> p_texturas)
{
	if (c_driver->findTexture(p_texturas[0].c_str()) == nullptr)
	{
		for (size_t textura = 0; textura < p_texturas.size(); textura++)
			p_malla->setMaterialTexture(0, c_driver->getTexture(p_texturas[textura].c_str()));
	}
	else
	{
		for (size_t textura = 0; textura < p_texturas.size(); textura++)
			p_malla->setMaterialTexture(0, c_driver->findTexture(p_texturas[textura].c_str()));
	}
}

void FachadaMotorGrafico::aplicaTexturas(IMeshSceneNode* p_malla, std::string p_texturas)
{
	if (c_driver->findTexture(p_texturas.c_str()) == nullptr)
		p_malla->setMaterialTexture(0, c_driver->getTexture(p_texturas.c_str()));
	else
		p_malla->setMaterialTexture(0, c_driver->findTexture(p_texturas.c_str()));
}

void FachadaMotorGrafico::iniciaCursorRaton()
{
	GestorEventosEntrada::dameGestorEventosEntrada()->iniciaCursorRaton(ptrInstanciaFachadaMotorGrafico->c_device->getCursorControl());
}

irr::scene::IMeshSceneNode* FachadaMotorGrafico::dibujaEsferaSemitransparente(float p_posicionX, float p_posicionZ)
{
	scene::IMeshSceneNode* r_esfera = c_smgr->addSphereSceneNode(0.7f);
	if (r_esfera) {
		r_esfera->setPosition(core::vector3df(p_posicionX, 0, p_posicionZ));
		r_esfera->setMaterialFlag(video::EMF_LIGHTING, false);
		r_esfera->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
		c_smgr->getMeshManipulator()->setVertexColors(r_esfera->getMesh(), SColor(100, 255, 255, 255));
	}
	return r_esfera;
}

irr::video::ITexture* FachadaMotorGrafico::anadirImagenAEscena(std::string p_nombreArchivo)
{
	return c_driver->getTexture(p_nombreArchivo.c_str());
}

void FachadaMotorGrafico::borraMapaJuego()
{
	for each (IDummyTransformationSceneNode* t_grupo in c_mapaJuego)
		t_grupo->remove();
	c_mapaJuego.clear();
}

void FachadaMotorGrafico::setHUD(HUD* p_HUD)
{ 
	c_HUD = p_HUD;
	if (p_HUD)
		c_HUD->setDriver(c_driver); 
}

void FachadaMotorGrafico::iniciaLuces()
{
	c_smgr->setAmbientLight(video::SColorf(0.5f, 0.5f, 0.5f, 1));
}

void FachadaMotorGrafico::creaLuz(irr::core::vector3df t_posicion)
{
	ILightSceneNode* light1 = c_smgr->addLightSceneNode(0, t_posicion, video::SColorf(0.7f, 0.7f, 0.7f), 15.0f, -1);
}