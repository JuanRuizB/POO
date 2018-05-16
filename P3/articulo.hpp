#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"

class Articulo{

public:

	Articulo(const char* ref,const char* tit, Fecha fech, double pre, int sto):referencia_(ref), titulo_(tit), fecha_(fech), precio_(pre), existencias_(sto){};


	Cadena referencia() const {return referencia_;}
	Cadena titulo() const {return titulo_; }
	Fecha f_publi() const {return fecha_; }
	double precio() const {return precio_; }
	unsigned stock() const {return existencias_; }

	double& precio() {return precio_; }
	unsigned& stock() {return existencias_; }


private:
	Cadena referencia_;
	Cadena titulo_;
	Fecha fecha_;
	double precio_;
	unsigned existencias_;
};

std::ostream& operator <<(std::ostream &o,const Articulo& art);


#endif