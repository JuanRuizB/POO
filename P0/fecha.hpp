#ifndef FECHA_HPP_
#define FECHA_HPP_

class Fecha {
public:

	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;

	explicit Fecha(int =0, int =0, int =0);

	Fecha(const char* c);

	int dia() const;
	int mes() const { return mes_; }
	int anno(void) const;

	// Operadores sobrecargados.
	Fecha& operator +=(int x);
	Fecha& operator -=(int x);
	Fecha operator +(int x) const;
	Fecha operator -(int x) const;
	Fecha operator ++(int );
	Fecha& operator ++();
	Fecha operator --(int );
	Fecha& operator --();
	operator const char*() const;


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

inline int Fecha::anno() const { return anno_; }

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

