#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace YuGiOh {

	extern const bool DEBUG_MODE;
	// Dimensiones del Windows Form(cuantas coordenadas tendra), en unidades
	extern const int MYFORM_WIDTH;
	extern const int MYFORM_HEIGHT;

	// Dimensiones de cada coordenada(el personaje), en pixeles
	extern const int RESOLUCION_X;
	extern const int RESOLUCION_Y;

	extern const int MYFORM_SIZE_WIDTH;
	extern const int MYFORM_SIZE_HEIGHT;

	extern const int CARTAS_WIDTH;
	extern const int CARTAS_HEIGHT;

	extern const int CARTAS_WIDTH_LINE;
	extern const int CARTAS_HEIGHT_LINE;

	extern const float TAMANIO_LETRAS;

	// Velocidad con la que Marco corre en pixeles
	extern const int VELOCIDAD_TIMER;
	extern const int NUMERO_DE_CARTAS;

	// Enums
	public enum TipoEscena { Introduccion, Campus, Tienda, Batalla };
	public enum Direccion { Arriba, Abajo, Izquierda, Derecha };
	public enum TiposDeCarta { Criticos, Basicos, Extra, Electivos };
	public enum Pertenencia { Vendedor, DeMarco, DeProfesor };
	public enum ModoBatalla { Ataque, Defensa };
	public enum Objetos { Puerta, PuertaEscena, Moneda };
	public enum Terreno { Loceta, Agua, Arena, Granito, Hielo, Lava, Lodo, Maceta, Pasto, Roca, Tejado, Tierra };
	public enum MapaTipo { Plazuela, PabellonA, PabellonB, Jardin, Sotano };

	extern Terreno TERRENOS_COLISIONANTES[];
	// Funciones Utiles
	Direccion obtenerDireccionInvertida(Direccion direccion);
	bool Colisiona(Terreno terreno);
	bool noHayONoExsite(Object^ objeto);

	public ref class CONTROLES abstract sealed {
	public:
		static Keys SALIR;
		static Keys MOVER_ARRIBA_1;
		static Keys MOVER_ABAJO_1;
		static Keys MOVER_IZQUIERDA_1;
		static Keys MOVER_DERECHA_1;
		static Keys MOVER_ARRIBA_2;
		static Keys MOVER_ABAJO_2;
		static Keys MOVER_IZQUIERDA_2;
		static Keys MOVER_DERECHA_2;
		static Keys ACTIVAR_TRAMPA;
	};

	public ref class FUENTES abstract sealed {
	public:
		static Font ^SUBTITULOS;
		static Font ^DIALOGOS;
		static Font ^DINERO;
		static Font ^NIVEL;
	};
}