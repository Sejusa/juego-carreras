short lanzamientoDado(short& posicionActual, short& posicionEnemigo, short turno);
void objeto(short jugadorActual, short& posicionActual, short& posicionEnemigo);
std::string guardarObjeto(short item, std::string inventario);
void usarObjeto(std::string item, short& posicionActual, short& posicionEnemigo);
short dado(short valorMaximo, short valorMinimo);