#include <iostream>
#include "RaceLibrary.h"
#include <locale.h> //Para el setlocale();
#include <thread>   // Para std::this_thread
#include <chrono>   // Para std::chrono (milisegundos, segundos, etc.)

#define casillaInicial 1
#define casillaFinal 50
#define jugadorInicial 1
#define jugador1 1
#define jugador2 2

int main() {
	short casillaJugador1 = casillaInicial;
	short casillaJugador2 = casillaInicial;
	short turnoJugador = jugadorInicial;

	setlocale(LC_ALL, ""); //Para texto según el idioma del dispositivo.
	srand(time(NULL)); //Genera una semilla aleatoria. Solo lo ejecutamos al inicio del programa para evitar bugs.

	std::cout << "Bienvenido al juego de carreras, pulsa cualquier botón para continuar." << std::endl;

	while (casillaJugador1 < casillaFinal && casillaJugador2 < casillaFinal) { //Mientra no se haya llegado a la casilla final.
		std::cout << "Turno jugador " << turnoJugador << "." << std::endl;
		
		if (turnoJugador == jugador1) {
			lanzamientoDado(casillaJugador1, casillaJugador2, turnoJugador); //Como uso referencias no es necesario igualar la variable casillaJugador1 a esta función.
			std::cout << "El jugador " << turnoJugador << " se encuentra en la casilla: " << casillaJugador1 << ".\n" << std::endl;
			turnoJugador = jugador2; //Cambiamos el turno.
		}

		else {
			lanzamientoDado(casillaJugador2, casillaJugador1, turnoJugador); //Como uso referencias no es necesario igualar la variable casillaJugador2 a esta función.
			std::cout << "El jugador " << turnoJugador << " se encuentra en la casilla: " << casillaJugador2 << ".\n" << std::endl;
			turnoJugador = jugador1;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1500)); //Pausa el programa durante 1500 ms.
	}

	return 0;
}