#include "Escenas.h"
#include "Juego.h"

namespace YuGiOh
{
	Escena::Escena()
	{
		buffer = Juego::context->Allocate(Juego::graphics, Juego::myform->ClientRectangle);
		activo = false;
		dibujado = false;
		contador = 0;
	}

	Escena^ Escena::getEscenaActual() {
		if (Juego::campus->activo)
			return Juego::campus;

		else if (Juego::introduccion->activo)
			return Juego::introduccion;

		else if (Juego::tienda->activo)
			return Juego::tienda;
		
		return nullptr;
	}

	void Escena::CambiarEscena(Escena^ escena)
	{
		Escena^ escena_actual = getEscenaActual();
		DesactivarEscena(escena_actual);

		ActivarEscena(escena);
	}

	void Escena::EmpezarConEscena(Escena^ escena)
	{
		ActivarEscena(escena);
	}


	void Escena::ActivarEscena(Escena^ escena)
	{
		escena->activo = true;

		if (escena->onTimerTick != nullptr)
			Juego::myform->timer->Tick += escena->onTimerTick;
		if (escena->onKeyDown != nullptr)
			Juego::myform->KeyDown += escena->onKeyDown;
		if (escena->onKeyUp != nullptr)
			Juego::myform->KeyUp += escena->onKeyUp;
		if (escena->onMouseClick != nullptr)
			Juego::myform->MouseClick += escena->onMouseClick;
	}

	void Escena::DesactivarEscena(Escena^ escena)
	{
		escena->activo = false;

		if (escena->onTimerTick != nullptr)
			Juego::myform->timer->Tick -= escena->onTimerTick;
		if (escena->onKeyDown != nullptr)
			Juego::myform->KeyDown -= escena->onKeyDown;
		if (escena->onKeyUp != nullptr)
			Juego::myform->KeyUp -= escena->onKeyUp;
		if (escena->onMouseClick != nullptr)
			Juego::myform->MouseClick -= escena->onMouseClick;

		escena->dibujado = false;
	}

	Escena^ Escena::getEscenaTipo(TipoEscena tipo) {
		switch (tipo)
		{
		case Introduccion:
			return Juego::introduccion;
			break;
		case Campus:
			return Juego::campus;
			break;
		case Tienda:
			return Juego::tienda;
			break;
		default:
			return nullptr;
		}
	}
}