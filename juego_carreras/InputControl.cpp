#include <iostream>

char controladorInput() {
	char input;

	do
	{
		std::cout << "Escriba su respuesta:" << std::endl;
		std::cin >> input;

		input = toupper(input); //Aumentamos el tamaño del input a mayúsculas.
	} while (input != 'S' && input != 'N'); //Hasta que no se introduzca una S o N.

	return input;
}