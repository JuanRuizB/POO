#include "articulo.hpp"

std::ostream& operator <<(std::ostream &o,const Articulo& art){
	o << "[" << art.referencia() << "]" << art.titulo() << "," << art.f_publi() << "." << art.stock() << endl;
	return o;
}

