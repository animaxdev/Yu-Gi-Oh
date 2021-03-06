#include "Marco.h"
#include "Imagenes.h"
#include "Mapas.h"
#include "Objetos.h"
#include "Cartas.h"
#include "Dialogo.h"

namespace YuGiOh {

	Marco::Marco(Posicion ^p) {
		sprite = gcnew Sprite(IMAGENES::MARCO_SPRITE);
		sprite->indice = 0;
		sprite->ancho = 48;
		sprite->alto = 72;
		sprite->frecuencia = 2;
		sprite->numero_de_columnas = 7;
		sprite->numero_de_filas = 4;

		direccion = Direccion::Abajo;
		baraja = Baraja::crearBaraja(1);
		dinero = 10;
		velocidad = 8;
		posicion = p;
		ancho = RESOLUCION_X;
		alto = RESOLUCION_Y;
		debe_avanzar = false;
	}

	void Marco::mostrarloEn(Graphics ^graphics)	{
		Marco ^marco = Marco::marco;
		Sprite ^marco_sprite = marco->sprite;

		marco_sprite->cambiarSubindice((int)marco->direccion);

		graphics->DrawImage(
			marco_sprite->imagen,
			Rectangle(
				marco->ancho - marco->sprite->ancho + marco->posicion->x,
				marco->alto - marco->sprite->alto + marco->posicion->y,
				marco->sprite->ancho, 
				marco->sprite->alto
			),
			Rectangle(
				marco_sprite->indice / marco_sprite->frecuencia * marco_sprite->ancho,
				marco_sprite->subindice * marco_sprite->alto,
				marco_sprite->ancho - 1, // Normalemnte no se deberia quitar uno
				marco_sprite->alto - 1 // Pero, se pinta un pixel mas
			),
			GraphicsUnit::Pixel
		);
	}

	void Marco::intentarAvanzar(Direccion direccion) {

		sprite->siguienteIndice();
		redondearMovimiento(direccion);

		Posicion ^siguiente_posicion = posicion->getSiguientePosicion(direccion, velocidad);
		

		// Colision para los bloques
		if (marco->colisionaConMapaActual(siguiente_posicion, direccion))
			return; // No avanza 
		
		// Colision para los objetos
		Objeto ^siguiente_bloque = Mapa::mapa_actual->getObjeto(siguiente_posicion);
		
		// Colision para los profesor
		Profesor ^siguiente_profesor = dynamic_cast<Profesor ^>(Mapa::mapa_actual->getProfesor(siguiente_posicion));

		if (noHayONoExsite(siguiente_bloque)) {
			if (noHayONoExsite(siguiente_profesor))
				marco->avanzarUnPaso();
			else {
				// COLISION CON UN PROFESOR
				Profesor ^profesor = siguiente_profesor;
				marco->Detener();

				if (baraja->estaVacia()) {
					Dialogo::pausarYMostarMensaje("No tienes cartas para luchar!!");
					return;
				}

				if (profesor->ha_sido_derrotado) {
					Dialogo::pausarYMostarMensaje("Ya derrotaste a este profesor");
					return;
				}
				
				if (profesor->nivel != 1 && !profesor->anteriorProfesor()->ha_sido_derrotado) {
					String ^mapa_profe = Mapa::getNombre(profesor->anteriorProfesor()->mapa);
					Dialogo::pausarYMostarMensaje("Primero, derrota al anterior profe(" + mapa_profe + ")");
					return;
				}

				Escena::CambiarEscena(ESCENAS::batalla);
				ESCENAS::batalla->enemigo = profesor;
				ESCENAS::batalla->empezarBatalla();
				EscenaDeMapa ^escena_de_mapa = ESCENAS::batalla;

				escena_de_mapa->escena_a_mostrar = Batalla;
				escena_de_mapa->pabellon_de_regreso = Mapa::obtenerMapaTipo(profesor->mapa);
				escena_de_mapa->posicion_de_regreso = Marco::marco->posicion;
				escena_de_mapa->direccion_de_regreso = Marco::marco->direccion;
			}

		}
		else {
			// COLISION DE UN OBJETO
			//Se choca con un objeto y se interactua con este
			Objeto ^objeto_dinamico = siguiente_bloque;
			bool debe_dar_un_paso_mas = objeto_dinamico->interactuarConMarco();
			
			//Algunos objetos detienen a marco por completo y otros no...
			if (debe_dar_un_paso_mas) {
				marco->avanzarUnPaso();
			}
		}
	}

	void Marco::avanzarUnPaso() {
		posicion->Aumentar(this->direccion, this->velocidad);
	}

	void Marco::Detener() {
		sprite->indice = 0;
		debe_avanzar = false;
	}
}