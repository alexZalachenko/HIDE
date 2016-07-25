#include "MenuConstruccion.h"
#include "FachadaMotorGrafico.h"
#include "Protagonista.h"
#include "Objeto.h"
#include "EscritorFicheros.h"
#include <string>
#include "Constantes.h"
#include "Crafteos.h"
#include "GestorEventosEntrada.h"

const short ID_OBJETO1 = 288;
const short ID_OBJETO2 = 289;
const short ID_OBJETO3 = 290;
const short ID_HERRAMIENTA = 291;
const short ID_LISTA = 292;

using namespace irr;
using namespace gui;

MenuConstruccion::MenuConstruccion(GestorEntidadesJuego* p_gestorEntidadesJuego)
	: Menu(p_gestorEntidadesJuego)
	, c_guiElement_hovered(nullptr)
{
	c_mochila = p_gestorEntidadesJuego->dameProtagonista()->dameMochila();
	irr::gui::IGUIEnvironment* t_GUIEnviroment = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameGUIEnviroment();
	irr::core::dimension2d<irr::u32> t_tamañoVentana = FachadaMotorGrafico::dameFachadaMotorGrafico()->dameTamanoVentana();

	c_ventanaMenu = t_GUIEnviroment->addWindow(
		irr::core::rect<irr::s32>(t_tamañoVentana.Width / 6, (t_tamañoVentana.Height / 6)
		, (t_tamañoVentana.Width / 6) * 5, (t_tamañoVentana.Height / 6) * 5),
		false, L"MOCHILA", 0, 1);
	c_ventanaMenu->setDrawTitlebar(false);
	c_ventanaMenu->getCloseButton()->remove();
	c_ventanaMenu->setDraggable(false);

	short t_margenIzquierdo = c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 20;
	short t_margenArriba = c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 20;
	short t_huecoPequeño = c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 15;

	c_listaObjetos = t_GUIEnviroment->addListBox(
		irr::core::rect<irr::s32>((c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 6) * 5, c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 15,
		c_ventanaMenu->getAbsoluteClippingRect().getWidth() - 1, c_ventanaMenu->getAbsoluteClippingRect().getHeight() - 1)
		, c_ventanaMenu, ID_LISTA);

	t_GUIEnviroment->addStaticText(L"MOCHILA"
		, irr::core::rect<irr::s32>((c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 6) * 5, 0
		, (c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 5) * 4 + 100, ALTO_BOTON)
		, false, false, c_ventanaMenu);

	t_GUIEnviroment->addButton(irr::core::rect<irr::s32>(t_margenIzquierdo, irr::s32((t_tamañoVentana.Height / 6) * 3.5)
													   , t_margenIzquierdo + ANCHO_BOTON, irr::s32((t_tamañoVentana.Height / 6) * 3.5 + ALTO_BOTON))
		, c_ventanaMenu, ID_BOTON_MENU_CONSTRUCCION_VOLVER, L"VOLVER", L"VOLVER");

	irr::video::ITexture* t_imagenDefault = FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png");

	c_imagenObjetoResultado = t_GUIEnviroment->addImage(t_imagenDefault,
		irr::core::position2d<irr::s32>((c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 5) * 2 - t_imagenDefault->getSize().Width,
										c_ventanaMenu->getAbsoluteClippingRect().getHeight() - t_imagenDefault->getSize().Height - t_huecoPequeño)
		, true, c_ventanaMenu, -1, L"Objeto resultado");

	c_imagenObjeto1 = t_GUIEnviroment->addImage(t_imagenDefault,
		irr::core::position2d<irr::s32>((c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 5) - t_imagenDefault->getSize().Width, t_margenArriba)
		, true, c_ventanaMenu, ID_OBJETO1, L"Objeto 1");

	c_imagenObjeto2 = t_GUIEnviroment->addImage(t_imagenDefault,
		irr::core::position2d<irr::s32>((c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 5) * 2 - t_imagenDefault->getSize().Width, t_margenArriba)
		, true, c_ventanaMenu, ID_OBJETO2, L"Objeto 2");

	c_imagenObjeto3 = t_GUIEnviroment->addImage(t_imagenDefault,
		irr::core::position2d<irr::s32>((c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 5) * 3 - t_imagenDefault->getSize().Width, t_margenArriba)
		, true, c_ventanaMenu, ID_OBJETO3, L"Objeto 3");

	c_imagenHerramienta = t_GUIEnviroment->addImage(t_imagenDefault,
		irr::core::position2d<irr::s32>((c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 5) * 2 - t_imagenDefault->getSize().Width,
										c_ventanaMenu->getAbsoluteClippingRect().getHeight() / 2 - t_imagenDefault->getSize().Height / 2)
										, true, c_ventanaMenu, ID_HERRAMIENTA, L"Objeto 3");

	t_GUIEnviroment->addButton(irr::core::rect<irr::s32>(c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 2 + t_imagenDefault->getSize().Width / 2 + t_huecoPequeño,
														 irr::s32((t_tamañoVentana.Height / 6) * 3.5),
														 c_ventanaMenu->getAbsoluteClippingRect().getWidth() / 2 + t_imagenDefault->getSize().Width / 2 + t_huecoPequeño + ANCHO_BOTON,
														 irr::s32((t_tamañoVentana.Height / 6) * 3.5 + ALTO_BOTON))
		, c_ventanaMenu, ID_BOTON_MENU_CONSTRUCCION_CREAR, L"CREAR", L"CREAR");

	c_ventanaMenu->setVisible(false);
}

MenuConstruccion::~MenuConstruccion()
{
}

void MenuConstruccion::cambiaEstadoMenu()
{
	Menu::cambiaEstadoMenu();
	if (c_ventanaMenu->isVisible())
	{
		iniciaMenuConstruccion();
		GestorEventosEntrada::dameGestorEventosEntrada()->setNotificaEscenaConEntidad(true);
	}
	else
		GestorEventosEntrada::dameGestorEventosEntrada()->setNotificaEscenaConEntidad(false);
}

void MenuConstruccion::iniciaMenuConstruccion()
{
	c_copiaMochila.clear();
	c_copiaMochila.resize(0);
	for each (Objeto* t_objetoEnMochila in c_mochila->dameObjetosMochila())
		c_copiaMochila.push_back(ObjetoSimplificado{ t_objetoEnMochila->dameNombre() , t_objetoEnMochila->dameNombreImagen(),
													 t_objetoEnMochila->dameCantidad(), t_objetoEnMochila->esApilable()});
	actualizaListaObjetos();
	c_draggado.cantidad = -1;
	c_objetosEnImagenes.resize(0);
	for (char t_objetoEnImagen = 0; t_objetoEnImagen < 4; t_objetoEnImagen++)
		c_objetosEnImagenes.push_back(ObjetoSimplificado{ "", "", -1, false });

	c_guiElement_hovered = nullptr;
	c_draggado.cantidad = -1;
	c_padre = nullptr;
	
	c_imagenObjetoResultado->setImage(FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png"));
	c_imagenObjeto1->setImage(FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png"));
	c_imagenObjeto2->setImage(FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png"));
	c_imagenObjeto3->setImage(FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png"));
	c_imagenHerramienta->setImage(FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png"));
}

void MenuConstruccion::actualizaMochilaOriginal()
{
	short t_posicionMochilaCopia = 0 , t_posicionMochila = 0;
	for (size_t t_posicion = 0; t_posicion < c_copiaMochila.size(); t_posicionMochilaCopia++, t_posicionMochila++, t_posicion++)
	{
		while (c_copiaMochila[t_posicionMochilaCopia].cantidad != c_mochila->dameObjetosMochila()[t_posicionMochila]->dameCantidad())
		{
			if (c_copiaMochila[t_posicionMochilaCopia].cantidad < c_mochila->dameObjetosMochila()[t_posicionMochila]->dameCantidad())
			{
				if (c_mochila->eliminaObjetoDeMochila(c_mochila->dameObjetosMochila().at(t_posicionMochila)))
				{
					t_posicionMochila--;
					break;
				}
			}
			else
			c_mochila->añadeObjetoAMochila(c_mochila->dameObjetosMochila().at(t_posicionMochila));
		}
	}
}

void MenuConstruccion::actualizaListaObjetos()
{
	c_listaObjetos->clear();
	for each (ObjetoSimplificado t_objetoCopiaMochila in c_copiaMochila)
	{
		if (t_objetoCopiaMochila.cantidad > 0)
		{
			//HAY QUE GUARDAR EL NOMBRE EN UN STRING AUXILIAR, NO SE PUEDE USAR t_objetoEnMochila->dameNombre().begin()
			//NI IDEA DE PQ
			std::string t_stringNombreObjetoMochila = t_objetoCopiaMochila.nombre + " " + std::to_string(t_objetoCopiaMochila.cantidad);
			std::wstring t_nombreObjetoWide(t_stringNombreObjetoMochila.begin(),
				t_stringNombreObjetoMochila.end());
			c_listaObjetos->addItem(t_nombreObjetoWide.c_str());
		}
	}
}

ObjetoSimplificado MenuConstruccion::dameObjetoSeleccionado(short p_id)
{
	if (ID_OBJETO1 <= p_id && p_id <= ID_OBJETO3)
		return c_objetosEnImagenes[p_id - ID_OBJETO1];
	else if (p_id == ID_LISTA)
	{
		char t_idListItem = c_listaObjetos->getSelected();

		if (t_idListItem != -1)
		{
			ObjetoSimplificado t_objetoRetorno = c_copiaMochila.at(t_idListItem);
			char t_incrementoMochila = 0;
			while (t_objetoRetorno.cantidad == 0)
			{
				t_incrementoMochila++;
				t_objetoRetorno = c_copiaMochila.at(t_idListItem + t_incrementoMochila);
			}
			return t_objetoRetorno;
		}
	}
	return ObjetoSimplificado{ "", "", -1 };
}

void MenuConstruccion::actualizaObjetoResultado()
{
	std::vector<std::string> t_nombresObjetos;
	for each (ObjetoSimplificado t_objetoSimple in c_objetosEnImagenes)
		t_nombresObjetos.push_back(t_objetoSimple.nombre);
	Crafteo t_resultado = esCrafteable(t_nombresObjetos);
	if (t_resultado.esCrafteoValido())
		c_imagenObjetoResultado->setImage(FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena(t_resultado.dameImagenResultado()));
}

void MenuConstruccion::añadeObjetoACasilla()
{
	if (ID_OBJETO1 <= c_guiElement_hovered->getID() && c_guiElement_hovered->getID() <= ID_OBJETO3)
	{
		if (c_objetosEnImagenes[c_guiElement_hovered->getID() - ID_OBJETO1].cantidad == -1)
		{
			c_objetosEnImagenes[c_guiElement_hovered->getID() - ID_OBJETO1] = c_draggado;
			((IGUIImage*)c_guiElement_hovered)->setImage(
				FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena(c_draggado.nombreImagen));

			//QUITO EL OBJETO DEL PADRE
			if (ID_OBJETO1 <= c_padre->getID() && c_padre->getID() <= ID_OBJETO3)
			{
				c_objetosEnImagenes[c_padre->getID() - ID_OBJETO1].cantidad = -1;
				c_objetosEnImagenes[c_padre->getID() - ID_OBJETO1].nombre = "";
				((IGUIImage*)c_padre)->setImage(
					FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png"));
			}
			else if (c_padre->getID() == ID_LISTA)
			{
				for (size_t t_posicionObjetoCopiaMochila = 0; t_posicionObjetoCopiaMochila < c_copiaMochila.size(); t_posicionObjetoCopiaMochila++)
				{
					if (c_copiaMochila.at(t_posicionObjetoCopiaMochila).cantidad > 0 && c_copiaMochila.at(t_posicionObjetoCopiaMochila).nombre == c_draggado.nombre)
					{
						c_copiaMochila.at(t_posicionObjetoCopiaMochila).cantidad--;
						break;
					}
				}
				actualizaListaObjetos();
			}
		}
	}
	else if (c_guiElement_hovered->getID() == ID_LISTA)
	{
		if (c_padre->getID() != ID_LISTA)
		{
			for (size_t t_posicionObjetoCopiaMochila = 0; t_posicionObjetoCopiaMochila < c_copiaMochila.size(); t_posicionObjetoCopiaMochila++)
			{
				if (c_copiaMochila.at(t_posicionObjetoCopiaMochila).nombre == c_draggado.nombre)
				{
					if (c_copiaMochila.at(t_posicionObjetoCopiaMochila).cantidad == 0)
						c_copiaMochila.at(t_posicionObjetoCopiaMochila).cantidad++;
					else if (c_copiaMochila.at(t_posicionObjetoCopiaMochila).cantidad > 0 && c_copiaMochila.at(t_posicionObjetoCopiaMochila).esApilable)
						c_copiaMochila.at(t_posicionObjetoCopiaMochila).cantidad++;
				}
			}
			actualizaListaObjetos();
			//QUITO EL OBJETO DEL PADRE
			if (ID_OBJETO1 <= c_padre->getID() && c_padre->getID() <= ID_OBJETO3)
			{
				c_objetosEnImagenes[c_padre->getID() - ID_OBJETO1].cantidad = -1;
				c_objetosEnImagenes[c_padre->getID() - ID_OBJETO1].nombre= "";
				((IGUIImage*)c_padre)->setImage(
					FachadaMotorGrafico::dameFachadaMotorGrafico()->anadirImagenAEscena("assets/imagenes/iconosObjetos/sinObjeto.png"));
			}
		}
		else
		{
			c_guiElement_hovered = nullptr;
			c_draggado.cantidad = -1;
			c_padre = nullptr;
		}
	}
	actualizaObjetoResultado();
}

void MenuConstruccion::eliminaObjetoMochilaCopia(std::string p_objeto)
{
	if (p_objeto != "")
	{
		for each (ObjetoSimplificado t_objetoMochilaCopia in c_copiaMochila)
		{
			if (p_objeto == t_objetoMochilaCopia.nombre && t_objetoMochilaCopia.cantidad > 0)
			{
				t_objetoMochilaCopia.cantidad--;
				break;
			}
		}
	}
}

void MenuConstruccion::RecibeEvento(const SEvent* event)
{
	/*if (c_ventanaMenu->isVisible())
	{*/
	if (event->EventType == EET_GUI_EVENT)
	{
		std::string t_stringDescripcion;
		std::wstring  t_texto;
		switch (event->GUIEvent.EventType)
		{
		case EGET_LISTBOX_CHANGED:
			c_draggado = dameObjetoSeleccionado(event->GUIEvent.Caller->getID());
			if (c_draggado.cantidad != -1)
				c_padre = event->GUIEvent.Caller;
			break;

		case EGET_ELEMENT_FOCUSED:
			c_draggado = dameObjetoSeleccionado(event->GUIEvent.Caller->getID());
			if (c_draggado.cantidad != -1)
				c_padre = event->GUIEvent.Caller;
			break;

		case EGET_ELEMENT_HOVERED:
			if (ID_OBJETO1 <= event->GUIEvent.Caller->getID() && event->GUIEvent.Caller->getID() <= ID_LISTA)
				c_guiElement_hovered = event->GUIEvent.Caller;
			else
				c_guiElement_hovered = nullptr;
			break;

		case EGET_ELEMENT_LEFT:
			c_guiElement_hovered = nullptr;
			break;
		case EGET_BUTTON_CLICKED:
			if (event->GUIEvent.Caller->getID() == ID_BOTON_MENU_CONSTRUCCION_CREAR)
			{
				std::vector<std::string> t_nombresObjetos;
				for each (ObjetoSimplificado t_objetoSimple in c_objetosEnImagenes)
					t_nombresObjetos.push_back(t_objetoSimple.nombre);
				std::string t_resultado = esCrafteable(t_nombresObjetos).dameObjetoResultado();
				if (t_resultado != "")
				{
					Objeto* t_objetoCreado = c_gestorEntidadesJuego->creaEntidadPorNombre(t_resultado);
					if (!c_mochila->añadeObjetoAMochila(t_objetoCreado))
						c_gestorEntidadesJuego->eliminaEntidad(t_objetoCreado);
					else
					{
						for each (std::string t_nombreObjetoUsado in t_nombresObjetos)
							eliminaObjetoMochilaCopia(t_nombreObjetoUsado);
					}
					actualizaMochilaOriginal();
					actualizaListaObjetos();
					iniciaMenuConstruccion();
				}
			}
			break;
		}
	}
	else if (event->EventType == EET_MOUSE_INPUT_EVENT && event->MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
	{
		if (c_guiElement_hovered != nullptr && c_draggado.cantidad != -1)
			añadeObjetoACasilla();
		c_guiElement_hovered = nullptr;
		c_draggado.cantidad = -1;
		c_padre = nullptr;
	}
	//}
}

