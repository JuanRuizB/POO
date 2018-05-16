#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdio>

class Fecha {
public:

	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;

	explicit Fecha(int =0, int =0, int =0);

	Fecha(const char* c);

	int dia() const noexcept{return dia_; }
	int mes() const noexcept { return mes_; }
	int anno(void) const noexcept { return anno_; }

	// Operadores sobrecargados.
	Fecha& operator +=(int x);
	Fecha& operator -=(int x);
	Fecha operator +(int x) const;
	Fecha operator -(int x) const;
	Fecha operator ++(int );
	Fecha& operator ++();
	Fecha operator --(int );
	Fecha& operator --();

	const char* cadena() const noexcept;


	void comprobaciones();

	class Invalida{
	public:
		Invalida(const char* e);
		const char* por_que() const;
	private:
		const char* error;
	};

private:
	int dia_, mes_, anno_;
};

bool operator ==(const Fecha& a,const Fecha& b) noexcept;
bool operator !=(const Fecha& a,const Fecha& b) noexcept;
bool operator >(const Fecha& a, const Fecha& b) noexcept;
bool operator <(const Fecha& a, const Fecha& b) noexcept;
bool operator <=(const Fecha& a, const Fecha& b) noexcept;
bool operator >=(const Fecha& a,const Fecha& b) noexcept;

std::istream& operator >> (std::istream &i, Fecha& f);
std::ostream& operator << (std::ostream &o, const Fecha& f);


//Operador -=
inline Fecha& Fecha::operator -=(int x)
{
	return (*this += -x);
}

//Metodo lanzador de error.
 inline const char* Fecha::Invalida::por_que() const
{
	return error;
}

//Constructor de objeto invalida.
inline Fecha::Invalida::Invalida(const char* e):error(e){}

#endif

