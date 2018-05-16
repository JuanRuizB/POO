#include <iostream>
#include <ctime>
#include <string.h>
#include "fecha.hpp"

using namespace std;

//Comprueba si el año es bisiesto.
int bisiesto(int anno)
{
	return (anno % 4 == 0 && (anno % 400 == 0 || anno % 100 != 0));
}

inline int Fecha::dia() const {return dia_; }

//Metodo que comprueba si la fecha es valida.
void Fecha::comprobaciones()
{

	static const int diames[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

	if ((diames[mes_] + bisiesto(anno_) < dia_) || dia_ < 0)
		throw (Invalida("ERROR: El día introducido no es valido."));

	if (mes_ < 0 || mes_ > 12)
		throw (Invalida("ERROR: El mes introducido es incorrecto"));

	if (anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo)
		throw (Invalida("ERROR: El año introducido es incorrecto"));
}



// Constructor 
Fecha::Fecha(int d, int m, int a): dia_(d), mes_(m), anno_(a)
{
	// Fecha del sistema
time_t tiempo_calendario = time(nullptr);
tm* tiempo_descompuesto = localtime(&tiempo_calendario);
int dia_del_sistema = tiempo_descompuesto->tm_mday;
int mes_del_sistema = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
int anno_del_sistema = tiempo_descompuesto->tm_year + 1900; // tm_year: annos desde 1900

	if (dia_ == 0)
		dia_ = dia_del_sistema;
	if (mes_ == 0) 
		mes_= mes_del_sistema;	
	if (anno_ == 0) 
		anno_ = anno_del_sistema;	
	comprobaciones();
}

//Constructor de fecha dada una cadena.
Fecha::Fecha(const char* c)
{
	int dia,mes,anno;

	if(sscanf(c, "%02d/%02d/%04d",&dia,&mes,&anno) == 3)
	{

	Fecha aux(dia,mes,anno);

	dia_ = aux.dia_;
	mes_ = aux.mes_;
	anno_ = aux.anno_;
	
	}else throw Invalida("Error de formato");
}


//Operador +=
Fecha& Fecha::operator +=(int x)
{
	if(x != 0)
	{
		tm hoy={}; 

		hoy.tm_mday = this->dia_ + x;
		hoy.tm_mon = this->mes_ - 1;
		hoy.tm_year = this->anno_ - 1900;

		mktime(&hoy);

		this->dia_ = hoy.tm_mday;
		this->mes_ = hoy.tm_mon + 1;
		this->anno_ = hoy.tm_year + 1900;
	comprobaciones();
	}

	return *this;
}


Fecha Fecha::operator +(int x) const
{
	return Fecha (*this) += x;
}

Fecha Fecha::operator -( int x) const
{
	return Fecha(*this) += -x;
}

Fecha Fecha::operator ++(int )
{
	static 	Fecha t;
	t = *this;
	*this += 1;

	return (t);
}

Fecha& Fecha::operator ++()
{
	return (*this += 1);
}

Fecha Fecha::operator --(int )
{
	static 	Fecha t;
	t = *this;
	*this += -1;

	return (t);
}

Fecha& Fecha::operator --()
{
	return (*this += -1);
}

bool operator ==(const Fecha& a,const Fecha& b) noexcept
{
	return (a.dia() == b.dia() && a.mes() == b.mes() && a.anno() == b.anno());
}

bool operator !=(const Fecha& a, const Fecha& b) noexcept
{
	return !(a == b);
}

bool operator <(const Fecha& a, const Fecha& b) noexcept
{
	if(a.anno() < b.anno()) return true;
	else 
	{
		if(a.anno() > b.anno()) return false;
		else
		{
			if(a.mes() < b.mes()) return true;
			else
			{
				if(a.mes() > b.mes()) return false;
				else
				{
					if(a.dia() < b.dia()) return true;
					else return false;
				}
			}
		} 
	}
}

bool operator >(const Fecha& a, const Fecha& b) noexcept
{
	return (b < a);
}

bool operator <=(const Fecha& a, const Fecha& b) noexcept
{
	return !(b < a);
}

bool operator >=(const Fecha& a,const Fecha& b) noexcept
{
	return !(a < b);
}

Fecha::operator const char*() const
{
	 const char* meses[13]={"0","enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};
	 const char* diasem[7]={"domingo","lunes","martes","miércoles","jueves","viernes","sábado"};
	static char c[50];
	tm f = {0};

		f.tm_mday = this->dia_;
		f.tm_mon = this->mes_ - 1;
		f.tm_year = this->anno_ - 1900;

		mktime(&f);

		sprintf(c,"%s %i de %s de %i", diasem[f.tm_wday], f.tm_mday, meses[f.tm_mon + 1], f.tm_year + 1900);

		return (const char*)c;
}