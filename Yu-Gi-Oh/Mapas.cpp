#include "Constantes.h"
#include "Mapas.h"
#include "Juego.h"
#include "Objetos.h"

namespace YuGiOh {

	Mapa::Mapa() {
		capa_terreno = Juego::context->Allocate(Juego::graphics, Juego::myform->ClientRectangle);
	}

	void Mapa::generarCapaTerreno() {
		for (int y = 0; y < MYFORM_HEIGHT; y++) {
			for (int x = 0; x < MYFORM_WIDTH; x++) {

				Image^ imagen_terreno;
				float coordenada_x = x * RESOLUCION_X;
				float coordenada_y = y * RESOLUCION_Y;

				switch (matriz_terreno[y,x]) {
				case Loceta:
					imagen_terreno = IMAGENES::LOCETA;
					break;
				case Pasto:
					imagen_terreno = IMAGENES::PASTO;
					break;
				case Agua:
					imagen_terreno = IMAGENES::AGUA;
					break;
				case Maceta:
					imagen_terreno = IMAGENES::MACETA;
					break;
				}

				capa_terreno->Graphics->DrawImage(imagen_terreno, Rectangle(coordenada_x, coordenada_y, RESOLUCION_X, RESOLUCION_Y));
				
				if (DEBUG_MODE)
					capa_terreno->Graphics->DrawString(
						coordenada_x + "," + coordenada_y,
						gcnew Font("Arial", 8.0f),
						gcnew SolidBrush(Color::Black),
						coordenada_x,
						coordenada_y
					);
			}
		}
	}

	Objeto^ Mapa::getObjeto(Posicion^ posicion) {

		int numero_de_objetos = this->objetos->Count;
		
		for (int i = 0; i < numero_de_objetos; i++) {
			if (objetos[i]->posicion == posicion) {
				return objetos[i];
			}
		}

		return nullptr;
	}

	Terreno Mapa::getTerrenoEnCoordenada(Posicion^ posicion) {
		
		// Se invierte, porque los mapas se guardan en forma x,y
		int x = posicion->y;
		int	y = posicion->x;

		if (posicion->x < 0 || posicion->x >= matriz_terreno->GetLength(0))
			x = 0;
		if (posicion->y < 0 || posicion->y >= matriz_terreno->GetLength(1))
			y = 0;

		return matriz_terreno[x, y];
	}

	void Mapa::mostrarTerreno(Graphics^ graphics) {
		capa_terreno->Render(graphics);
	}

	void Mapa::mostrarObjetos(Graphics^ graphics) {

		int numero_de_objetos = this->objetos->Count;

		for (int i = 0; i < numero_de_objetos; i++)
			objetos[i]->mostrar(graphics);
	}

	PlazuelaMapa::PlazuelaMapa() : Mapa() {
		this->matriz_terreno = gcnew array<Terreno,2> {
			{ Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Loceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta},
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Loceta, Loceta, Loceta, Loceta, Loceta, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Agua, Agua, Agua, Agua, Agua, Agua, Agua, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Pasto, Pasto, Pasto, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Pasto, Pasto, Pasto, Loceta, Loceta, Maceta },
			{ Maceta, Maceta, Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Pasto, Pasto, Pasto, Loceta, Loceta, Maceta },
			{ Loceta, Pasto, Pasto, Pasto, Pasto, Pasto, Pasto, Pasto, Pasto, Pasto, Pasto, Loceta, Loceta, Loceta, Pasto, Pasto, Pasto, Loceta, Loceta, Maceta },
			{ Maceta, Maceta, Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Pasto, Pasto, Pasto, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Pasto, Pasto, Pasto, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Loceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta }
		};

		this->objetos = gcnew List<Objeto^>();
		this->objetos->AddRange(gcnew array<Objeto^>{
			gcnew PuertaObjeto(gcnew Posicion(-1, 3, true), PabellonA, gcnew Posicion(19, 3, true), Izquierda),
			gcnew PuertaObjeto(gcnew Posicion(8, 14, true), PabellonB, gcnew Posicion(8, 0, true), Abajo),
			gcnew PuertaEscenaObjeto(Tienda, gcnew Posicion(0, 9, true), Plazuela, gcnew Posicion(1, 9, true), Derecha),
			gcnew MonedaObjeto(gcnew Posicion(1, 1, true)),
			gcnew MonedaObjeto(gcnew Posicion(1, 12, true)),
			gcnew MonedaObjeto(gcnew Posicion(11, 9, true)),
			gcnew MonedaObjeto(gcnew Posicion(12, 11, true)),
			gcnew MonedaObjeto(gcnew Posicion(17, 2, true)),
			gcnew MonedaObjeto(gcnew Posicion(18, 7, true)),
			gcnew MonedaObjeto(gcnew Posicion(18, 12, true))
		});

		generarCapaTerreno();
	}

	PabellonAMapa::PabellonAMapa() : Mapa() {
		this->matriz_terreno = gcnew array<Terreno, 2> {
			{ Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta},
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta }
		};

		this->objetos = gcnew List<Objeto^>();
		this->objetos->AddRange(gcnew array<Objeto^>{
			gcnew PuertaObjeto(gcnew Posicion(20, 3, true), Plazuela, gcnew Posicion(0, 3, true), Derecha)
		});

		generarCapaTerreno();
	}

	PabellonBMapa::PabellonBMapa() : Mapa() {
		this->matriz_terreno = gcnew array<Terreno, 2> {
			{ Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Loceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta},
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Loceta, Maceta },
			{ Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta, Maceta }
		};

		this->objetos = gcnew List<Objeto^>();
		this->objetos->AddRange(gcnew array<Objeto^>{
			gcnew PuertaObjeto(gcnew Posicion(8, -1, true), Plazuela, gcnew Posicion(8, 13, true), Arriba)
		});

		generarCapaTerreno();
	}

	Mapa^ Mapa::obtenerMapa(Pabellon pabellon) {
		
		switch (pabellon)
		{
		case Plazuela:
			return Mapas::plazuela_mapa;
			break;
		case PabellonA:
			return Mapas::pabellonA_mapa;
			break;
		case PabellonB:
			return Mapas::pabellonB_mapa;
			break;
		default:
			return nullptr;
		}
	}

}
