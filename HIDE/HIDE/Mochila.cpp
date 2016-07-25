#include "Mochila.h"
#include "Objeto.h"
#include "Trampa.h"


Mochila::Mochila(GestorEntidadesJuego* p_gestorEntidades)
	: c_pesoDisponible(PESO_MAXIMO_MOCHILA)
	, c_gestorEntidades(p_gestorEntidades)
{
	c_objetosEnMochila.reserve(TAMAÑO_MAXIMO_MOCHILA);
	for each (Objeto* t_objetoEnMochila in c_objetosEnMochila)
		t_objetoEnMochila = nullptr;
}

Mochila::~Mochila()
{
}

bool Mochila::añadeObjetoAMochila(Objeto* p_objetoParaAñadir)
{
	if (c_pesoDisponible >= p_objetoParaAñadir->damePeso())
	{
		for each (Objeto* t_objetoEnMochila in c_objetosEnMochila)
		{
			if (t_objetoEnMochila->dameNombre() == p_objetoParaAñadir->dameNombre())
			{
				if (t_objetoEnMochila->esApilable())
				{
					t_objetoEnMochila->aumentaCantidad();
					c_gestorEntidades->eliminaEntidad(p_objetoParaAñadir);
					c_pesoDisponible -= p_objetoParaAñadir->damePeso();
					return true;
				}
			}
		}
		if (c_objetosEnMochila.size() < TAMAÑO_MAXIMO_MOCHILA)
		{
			c_objetosEnMochila.push_back(p_objetoParaAñadir);
			p_objetoParaAñadir->destruyeEntidad();
			c_pesoDisponible -= p_objetoParaAñadir->damePeso();
			return true;
		}
	}
	return false;
}

//DEVUELVE TRUE SI SE ELIMINA EL OBJETO DE MEMORIA. FALSE SI SOLO SE DECREMENTA SU CANTIDAD
bool Mochila::eliminaObjetoDeMochila(Objeto* p_objetoParaEliminar)
{
	int t_posicionEnMochila = 0;
	for each (Objeto* t_objetoEnMochila in c_objetosEnMochila)
	{
		if (t_objetoEnMochila == p_objetoParaEliminar)
		{
			t_objetoEnMochila->disminuyeCantidad();
			c_pesoDisponible += p_objetoParaEliminar->damePeso();
			if (t_objetoEnMochila->dameCantidad() <= 0)
			{
				if (p_objetoParaEliminar->dameTipoObjeto() == TRAMPA)
					c_gestorEntidades->convierteObjetoEnActualizable(p_objetoParaEliminar);
				else
					c_gestorEntidades->eliminaEntidad(c_objetosEnMochila.at(t_posicionEnMochila));
				c_objetosEnMochila.erase(c_objetosEnMochila.begin() + t_posicionEnMochila);
				return true;
			}
		}
		t_posicionEnMochila++;
	}
	return false;
}

bool Mochila::hayHuecoDisponible()
{
	if (c_objetosEnMochila.size() < TAMAÑO_MAXIMO_MOCHILA)
		return true;
	else
		return false;
}

Objeto* Mochila::dameSiguienteObjeto(Objeto* p_objeto)
{
	if (p_objeto == nullptr)
	{
		if (c_objetosEnMochila.size() == 0)
			return nullptr;
		else
			return c_objetosEnMochila.at(0);
	}
	
	for (size_t t_posicionMochila = 0; t_posicionMochila < c_objetosEnMochila.size(); t_posicionMochila++)
	{
		if (c_objetosEnMochila.at(t_posicionMochila) == p_objeto)
		{
			if (t_posicionMochila == c_objetosEnMochila.size() - 1)
				return nullptr;
			else
				return c_objetosEnMochila.at(++t_posicionMochila);
		}
	}
	return nullptr;
}

Objeto* Mochila::dameAnteriorObjeto(Objeto* p_objeto)
{
	if (p_objeto == nullptr)
	{
		if (c_objetosEnMochila.size() == 0)
			return nullptr;
		else
			return c_objetosEnMochila.at(c_objetosEnMochila.size() - 1);
	}

	for (size_t t_posicionMochila = c_objetosEnMochila.size() - 1; t_posicionMochila >= 0; t_posicionMochila--)
	{
		if (c_objetosEnMochila.at(t_posicionMochila) == p_objeto)
		{
			if (t_posicionMochila == 0)
				return nullptr;
			else
				return c_objetosEnMochila.at(--t_posicionMochila);
		}
	}
	return nullptr;
}

