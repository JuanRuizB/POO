#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <set>
#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"

class Articulo{

public:

	typedef set<autor*> Autores;

	class Autores_vacios{};

	Articulo(const Autores& au, const Cadena& ref,const Cadena& tit, Fecha fech, double pre):autores_(au),referencia_(ref), titulo_(tit), fecha_(fech), precio_(pre) 
	{
		if(au.empty()) throw Articulo::Autores_vacios;
	};

	Cadena referencia() const {return referencia_;}
	Cadena titulo() const {return titulo_; }
	Fecha f_publi() const {return fecha_; }
	double precio() const {return precio_; }

//	unsigned stock() const {return existencias_; }

	double& precio() {return precio_; }
//	unsigned& stock() {return existencias_; }

	virtual void impresion_especifica(ostream& )const = 0;


private:
	Cadena referencia_;
	Cadena titulo_;
	Fecha fecha_;
	double precio_;
//	unsigned existencias_;

	const Autores autores_;
};

std::ostream& operator <<(std::ostream &o,const Articulo& art);

class autor{
public:
	autor(const Cadena& nom,const Cadena& apel,const Cadena& dir):nombre_(nom),apellidos_(apel),direccion_(dir) {};

	Cadena nombre()const {return nombre_;}
	Cadena apellidos()const {return apellidos_;}
	Cadena direccion()const {return direccion_;}

private:
	Cadena nombre_;
	Cadena apellidos_;
	Cadena direccion_;

}


class ArticuloAlmacenable: public Articulo{
public:
	ArticuloAlmacenable(const Autores& au, const Cadena& ref,const Cadena& tit, Fecha fech, double pre,unsigned sto = 0):Articulo(au,ref,tit,fech,pre), stock_(sto){ }

	unsigned stock()const {return stock_; };
	unsigned& stock(){return stock_; };

private:
	unsigned stock_;
}

class Libro: public ArticuloAlmacenable{
public:

	Libro(const Autores& au, const Cadena& ref,const Cadena& tit, Fecha fech, double pre,unsigned pag,unsigned sto = 0):ArticuloAlmacenable(au,ref,tit,fech,pre,sto) n_pag_(pag) {}

	unsigned n_pag()const {return n_pag_;}

	void impresion_especifica(ostream& )const;

private:
	static unsigned n_pag_;
}

class Cederron: public ArticuloAlmacenable{
public:
	Cederron(const Autores& au, const Cadena& ref,const Cadena& tit, Fecha fech, double pre, unsigned MB, unsigned sto = 0): ArticuloAlmacenable(au,ref,tit,fech,pre,sto),MB_(MB) {}

	unsigned tam()const {return MB_;}

	void impresion_especifica(ostream& )const;

private:
	static unsigned MB_;
}

class LibroDigital: public Articulo{
public:
	LibroDigital(const Autores& au, const Cadena& ref,const Cadena& tit, Fecha fech, double pre, Fecha fe):Articulo(au,ref,tit,fech,pre), f_expir_(fe) {}

	Fecha f_expir()const {return f_expir_;}

	void impresion_especifica(ostream& )const;

private:
	static Fecha f_expir_;
}

#endif