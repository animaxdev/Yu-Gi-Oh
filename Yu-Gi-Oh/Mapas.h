#pragma once
#include "Objetos.h"

using namespace System::Collections::Generic;

namespace YuGiOh {
	public ref class Mapa
	{
	protected:
		void generarCapaTerreno();
	public:
		Mapa();
		array<Terreno, 2>^ matriz_terreno;
		List<Objeto^>^ objetos;
		BufferedGraphics^ capa_terreno;

		Objeto^ getObjeto(Posicion^ posicion);
		
		static Mapa^ mapa_actual;
		static Mapa^ obtenerMapa(Pabellon pabellon);
		
		void mostrarTerreno(Graphics^ graphics);
		void mostrarObjetos(Graphics^ graphics);
	};

	public ref class PlazuelaMapa : public Mapa{ public: PlazuelaMapa(); };
	public ref class PabellonAMapa : public Mapa{ public: PabellonAMapa(); };
	public ref class PabellonBMapa : public Mapa{ public: PabellonBMapa(); };

	public ref class Mapas abstract sealed {
	public:
		static PlazuelaMapa^ plazuela_mapa;
		static PabellonAMapa^ pabellonA_mapa;
		static PabellonBMapa^ pabellonB_mapa;
	};
}