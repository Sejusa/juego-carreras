#include <cstdlib> //Para srand() y rand()
#include <ctime> //Para time()
#include <iostream>
#include <string>
#include "InputControl.h"

#define maximoValorGenerado 6
#define minimoValorGenerado 1
#define multiplo5 5
#define residuo 0
#define casillaFinal 50
#define jugador1 1
#define jugador2 2 
#define maximoValorGeneradoObjetos 3
#define cantidadDeObjetos 4

std::string objetoJugador1 = "Inventario vacío."; //Se empieza con el inventario vacío.
std::string objetoJugador2 = "Inventario vacío.";
const std::string lista_Objetos[cantidadDeObjetos]{ "Error.", "Dado adicional.", "Haces retroceder al enemigo.", "Avanzas 1-3 casillas." };

short dado(short valorMaximo, short valorMinimo) { //Función de lanzamiento de dado.
	return (rand() % valorMaximo) + valorMinimo;
}

void usarObjeto(std::string& inventarioActual, short& posicionActual, short& posicionEnemigo, short& jugadorActual) { //Función de uso de objeto.
	short numeroAleatorio;

	if (inventarioActual == "Dado adicional.") {
		std::cout << "Usando el -dado adicional-." << std::endl;

		numeroAleatorio = dado(maximoValorGenerado, minimoValorGenerado); //Genera un número entre el 1 y el 6
		std::cout << "Has avanzado " << numeroAleatorio << " casillas." << std::endl;

		inventarioActual = "Inventario vacío."; //Después de usar el objeto el inventario vacía.

		posicionActual += numeroAleatorio; //Asigno la nueva posición.
	}

	else if (inventarioActual == "Haces retroceder al enemigo.") {
		std::cout << "Usando el -Haces retroceder al enemigo-." << std::endl;

		numeroAleatorio = dado(maximoValorGenerado, minimoValorGenerado);
		std::cout << "El enemigo retrocede " << numeroAleatorio << " casillas." << std::endl;

		inventarioActual = "Inventario vacío."; //Después de usar el objeto el inventario vacía.

		posicionEnemigo -= numeroAleatorio; //Asigno la nueva posición al enemigo.
	}

	else {
		std::cout << "Usando el -Avanzas 1-3 casillas-." << std::endl;

		numeroAleatorio = dado(maximoValorGeneradoObjetos, minimoValorGenerado); //Genera un número entre el 1 y el 3.
		std::cout << "Avanzas " << numeroAleatorio << " casillas." << std::endl;

		inventarioActual = "Inventario vacío."; //Después de usar el objeto el inventario vacía.

		posicionActual += numeroAleatorio; //Asigno la nueva posición.
	}
}

//Cambio clave : Recibe 'string&', NO un array.Recibe la referencia directa.
std::string guardarObjeto(short item, std::string& inventario) {
	inventario = lista_Objetos[item]; //Se le asigna al inventario el objeto que ha tocado según el item.

	std::cout << "Has obtenido: " << inventario << std::endl;

	return inventario;
}

void objeto(short jugadorActual, short& posicionActual, short& posicionEnemigo) {
	//Genera un valor entre el 1 y el 3. Lo genero al inicio, aunque el jugador no quiere coger el objeto. Así evito posteriormente en el código repetir esta linea.
	short objeto = dado(maximoValorGeneradoObjetos, minimoValorGenerado); //Número entre 1 y 3.
	char input;

	//inventarioActual es como un "apodo" para una variable que ya existe. Simplemente creo el apodo inventarioActual y apunto a la variable que necesito modificar.
	std::string& inventarioActual = (jugadorActual == jugador1) ? objetoJugador1 : objetoJugador2;

	if (inventarioActual == "Inventario vacío.") {
		inventarioActual = guardarObjeto(objeto, inventarioActual); //Asignamos al inventario del jugador que toca el objeto que le ha tocado.

		std::cout << "¿Quieres usar el objeto?" << std::endl;
		input = controladorInput();

		if (input == 'S') { //Si SI.
			usarObjeto(inventarioActual, posicionActual, posicionEnemigo, jugadorActual);
		}
	}

	else {
		std::cout << "Tu inventario está lleno, para almacenar el nuevo objeto debes usar el antiguo. ¿Usar? (s/n)." << std::endl;
		input = controladorInput();

		if (input == 'S') { //Si SI.
			usarObjeto(inventarioActual, posicionActual, posicionEnemigo, jugadorActual);
		}

		inventarioActual = guardarObjeto(objeto, inventarioActual);

		std::cout << "¿Quieres usar el objeto?" << std::endl;
		input = controladorInput();

		if (input == 'S') { //Si SI.
			usarObjeto(inventarioActual, posicionActual, posicionEnemigo, jugadorActual);
		}
	}
}

short lanzamientoDado(short& posicionActual, short& posicionEnemigo, short turno) {
	short numeroAleatorio = dado(maximoValorGenerado, minimoValorGenerado); //Genera un número entre el 1 y el 6

	posicionActual += numeroAleatorio;

	std::cout << "Has avanzado " << numeroAleatorio << " casillas." << std::endl;

	while (posicionActual % multiplo5 == residuo && posicionActual != casillaFinal) { //Mientras la casilla actual no sea múltiple de 5.
		std::cout << "Has sacado un número múltiple de 5. Lanzando dado de nuevo: " << std::endl;
		numeroAleatorio = dado(maximoValorGenerado, minimoValorGenerado);
		posicionActual += numeroAleatorio;
		std::cout << "Has avanzado " << numeroAleatorio << " casillas." << std::endl;
	}

	switch (posicionActual) {
	case 7:
		posicionActual = 12;
		std::cout << "Avanzas a " << posicionActual << std::endl;
		break;

	case 12:
		posicionActual = 7;
		std::cout << "Retrocedes a " << posicionActual << std::endl;
		break;

	case 19:
		posicionActual = 24;
		std::cout << "Avanzas a " << posicionActual << std::endl;
		break;

	case 24:
		posicionActual = 19;
		std::cout << "Retrocedes a " << posicionActual << std::endl;
		break;

	case 31:
		posicionActual = 40;
		std::cout << "Avanzas a " << posicionActual << std::endl;
		break;

	case 40:
		posicionActual = 31;
		std::cout << "Retrocedes a " << posicionActual << std::endl;
		break;

	case 3:
	case 13:
	case 23:
	case 33:
	case 43: //Para todos estos caso, ejecuto objeto();
		objeto(turno, posicionActual, posicionEnemigo);
		break;
	}

	return posicionActual;
}

void reiniciarInventarios() {
	objetoJugador1 = "Inventario vacío.";
	objetoJugador2 = "Inventario vacío.";
}