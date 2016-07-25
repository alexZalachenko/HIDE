#include "MenuMochila.h"
#include "FachadaMotorGrafico.h"
#include "Constantes.h"
#include "Protagonista.h"
#include "Objeto.h"
#include "Protagonista.h"
#include <string>
#include <sstream>
#include <iomanip>

MenuMochila::MenuMochila(GestorEntidadesJuego* p_gestorEntidadesJuego)
	: Menu(p_gestorEntidadesJuego)
{
	c_mochila = p_gestorEntidadesJuego->dameProtagonista()->dameMochila();
	c_protagonista = p_gestorEntidadesJuego->dameProtagonista();
	irr::gui::IGUIEnvironment* t_GUIEnviroment = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment();
	irr::core::dimension2d<irr::u32> t_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();

	c_ventanaMenu = t_GUIEnviroment->addWindow(
		irr::core::rect<irr::s32>(t_tamañoVentana.Width / 6,	  (t_tamañoVentana.Height / 6)
							   , (t_tamañoVentana.Width / 6) * 5, (t_tamañoVentana.Height / 6) * 5),
		false, L"MOCHILA", 0, 1);

	c_ventanaMenu->setDrawTitlebar(false);
	c_ventanaMenu->getCloseButton()->remove();
	c_ventanaMenu->setDraggable(false);

	short t_margenIzquierdo = c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 20;
	short t_margenArriba = c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 20;

	c_imagenObjeto = t_GUIEnviroment->addImage(FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png"),
												irr::core::position2d<irr::s32>(t_margenIzquierdo, t_margenArriba)
												, true, c_ventanaMenu, -1, L"Objeto seleccionado");
	
	c_textoPeso = t_GUIEnviroment->addStaticText(L"", 
		irr::core::rect<irr::s32>(t_margenIzquierdo,				 (t_tamañoVentana.Height/6) * 1.25, 
								  t_margenIzquierdo + 100,			  t_tamañoVentana.Height / 6 + 100),
								  false, false, c_ventanaMenu);

	c_textoCantidad = t_GUIEnviroment->addStaticText(L"", 
		irr::core::rect<irr::s32>(t_tamañoVentana.Height / 6,		 (t_tamañoVentana.Height / 6) * 1.25,
								  t_tamañoVentana.Height / 6 + 100,   t_tamañoVentana.Height / 6 + 100),
								  false, false, c_ventanaMenu);

	c_textoDescripcion = t_GUIEnviroment->addStaticText(L""
		, irr::core::rect<irr::s32>(t_margenIzquierdo,							 (t_tamañoVentana.Height/6) * 1.5
								  , t_margenIzquierdo + t_tamañoVentana.Width/5, (t_tamañoVentana.Height/6) * 1.5 + t_tamañoVentana.Height/5)
								  , false, true, c_ventanaMenu);

	t_GUIEnviroment->addButton(irr::core::rect<irr::s32>(t_margenIzquierdo,				  (t_tamañoVentana.Height/6) * 3
													   , t_margenIzquierdo + ANCHO_BOTON, (t_tamañoVentana.Height / 6) * 3 + ALTO_BOTON)
													   , c_ventanaMenu, ID_BOTON_MENU_MOCHILA_EQUIPA, L"EQUIPA", L"EQUIPA");

	t_GUIEnviroment->addButton(irr::core::rect<irr::s32>(t_margenIzquierdo + 2 * ANCHO_BOTON, (t_tamañoVentana.Height / 6) * 3
													   , t_margenIzquierdo + 3 * ANCHO_BOTON, (t_tamañoVentana.Height / 6) * 3 + ALTO_BOTON)
													   , c_ventanaMenu, ID_BOTON_MENU_MOCHILA_ELIMINA, L"ELIMINA", L"ELIMINA");
		
	t_GUIEnviroment->addButton(irr::core::rect<irr::s32>(t_margenIzquierdo,				  (t_tamañoVentana.Height / 6) * 3.5
													   , t_margenIzquierdo + ANCHO_BOTON, (t_tamañoVentana.Height / 6) * 3.5 + ALTO_BOTON)
													   , c_ventanaMenu, ID_BOTON_MENU_MOCHILA_VOLVER, L"VOLVER", L"VOLVER");

	c_textoPesoMochila = t_GUIEnviroment->addStaticText(L""
		, irr::core::rect<irr::s32>(t_tamañoVentana.Width / 6,		 (t_tamañoVentana.Height / 6) * 3.5
								  , t_tamañoVentana.Width / 6 + 400, (t_tamañoVentana.Height / 6) * 3.5 + 50)
								  , false, false, c_ventanaMenu);
	
	c_listaObjetos = t_GUIEnviroment->addListBox(
		irr::core::rect<irr::s32>((c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 6) * 5, c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 15,
								  c_ventanaMenu->getAbsoluteClippingRect().getWidth() - 1, c_ventanaMenu->getAbsoluteClippingRect().getHeight() - 1)
		, c_ventanaMenu);

	c_ventanaMenu->setVisible(false);
}

MenuMochila::~MenuMochila()
{
}

void MenuMochila::iniciaMenuMochila()
{
	setItemGenericoInterfaz();
	c_listaObjetos->clear();

	for each (Objeto* t_objetoEnMochila in c_mochila->dameObjetosMochila())
	{
		//HAY QUE GUARDAR EL NOMBRE EN UN STRING AUXILIAR, NO SE PUEDE USAR t_objetoEnMochila->dameNombre().begin()
		//NI IDEA DE PQ
		std::string t_stringNombreObjetoMochila = t_objetoEnMochila->dameNombre();
		std::wstring t_nombreObjetoWide(t_stringNombreObjetoMochila.begin(), 
										t_stringNombreObjetoMochila.end());
		c_listaObjetos->addItem(t_nombreObjetoWide.c_str());
	}
}

void MenuMochila::cambiaEstadoMenu()
{
	Menu::cambiaEstadoMenu();
	if (c_ventanaMenu->isVisible())
		iniciaMenuMochila();
}

void MenuMochila::actualizaObjetoSeleccionado()
{
	char t_idListItem = c_listaObjetos->getSelected();
	if (t_idListItem != -1)
	{
		std::stringstream stream;
		std::string string;
		std::wstring ws;

		Objeto* t_objeto = c_mochila->dameObjetosMochila().at(t_idListItem);

		std::wstring t_texto = L"PESO: ";
		stream << std::fixed << std::setprecision(1) << t_objeto->damePeso();
		string = stream.str();
		ws = std::wstring(string.begin(), string.end());
		t_texto += ws;
		t_texto += L" KG";
		c_textoPeso->setText(t_texto.c_str());

		t_texto = L" CANTIDAD: ";
		t_texto += std::to_wstring(t_objeto->dameCantidad());
		c_textoCantidad->setText(t_texto.c_str());

		t_texto = L"DESCRIPCION: ";
		std::string t_stringDescripcion = t_objeto->dameDescripcion();
		t_texto += std::wstring(t_stringDescripcion.begin(), t_stringDescripcion.end());
		c_textoDescripcion->setText(t_texto.c_str());


		short t_margenIzquierdo = c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 20;
		short t_margenArriba = c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 20;


		c_imagenObjeto->remove();
		c_imagenObjeto = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment()->addImage(
			FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena(t_objeto->dameNombreImagen()),
			irr::core::position2d<irr::s32>(
			c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 20,
			c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 20)
			, true, c_ventanaMenu, -1, L"Objeto seleccionado");
	}
}

void MenuMochila::equipaObjetoSeleccionado()
{
	char t_idListItem = c_listaObjetos->getSelected();
	if (t_idListItem != -1)
	{
		Objeto* t_objeto = c_mochila->dameObjetosMochila().at(t_idListItem);
		c_protagonista->equipaObjeto(t_objeto);
	}
}

void MenuMochila::eliminaObjetoSeleccionado()
{
	char t_idListItem = c_listaObjetos->getSelected();
	if (t_idListItem != -1)
	{
		Objeto* t_objeto = c_mochila->dameObjetosMochila().at(t_idListItem);
		c_protagonista->equipaObjeto(t_objeto);
		if (t_objeto == c_protagonista->dameObjetoEquipado())
			c_protagonista->eliminaObjetoEquipado();
		else
			c_mochila->eliminaObjetoDeMochila(t_objeto);
		c_listaObjetos->removeItem(t_idListItem);
		setItemGenericoInterfaz();
	}
}

void MenuMochila::setItemGenericoInterfaz()
{
	std::stringstream stream;
	std::string string;
	std::wstring ws;

	c_imagenObjeto->setImage(FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png"));
	c_textoPeso->setText(L"PESO: 0 KG");
	c_textoCantidad->setText(L" CANTIDAD: 0");
	c_textoDescripcion->setText(L"DESCRIPCION:");
	std::wstring  t_textoPesoMochila = L"PESO MOCHILA: ";

	stream << std::fixed << std::setprecision(1) << PESO_MAXIMO_MOCHILA - c_mochila->damePesoDisponible();
	string = stream.str();
	ws = std::wstring(string.begin(), string.end());
	t_textoPesoMochila += ws;

	t_textoPesoMochila += L" KG. PESO MAXIMO: ";
	t_textoPesoMochila += std::to_wstring(PESO_MAXIMO_MOCHILA);
	t_textoPesoMochila += L" KG.";
	c_textoPesoMochila->setText(t_textoPesoMochila.c_str());
}

