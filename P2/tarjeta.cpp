#include <algorithm>
#include <cctype>
#include <iomanip>
#include "tarjeta.hpp"

bool luhn(const Cadena& numero);

//******************************NUMERO**************************

Numero::Numero(const Cadena& num)
{
	Cadena aux = quitarEspacios(num);

	if(aux.length() < 13 || aux.length() > 19)
		throw Incorrecto(Razon::LONGITUD);
	if( count_if(aux.begin(), aux.end(), static_cast<int(*)(int)>(isdigit)) != aux.length())
	 throw Incorrecto(Razon::DIGITOS);

	if(!luhn(aux)) throw Incorrecto(Razon::NO_VALIDO);
	tarjeta_ = aux;
}

Cadena Numero::quitarEspacios(const Cadena& cad)
{
	Cadena str(cad);

	remove_if(str.begin(),str.end()+1,[](unsigned char x){return isspace(x);});

	return Cadena(str.c_str());
}	

bool Numero::deteccionCaracteres(const Cadena& cad)
{
	Cadena str(cad);

	return find_if(str.begin(),str.end()+1,[](unsigned char x){return isdigit(x);});

}

bool operator <(const Numero& A,const Numero& B)
{
	return (A.tarjeta_ < B.tarjeta_);
}

//*****************************TARJETA******************************

Tarjeta::Tarjeta(Tipo tip,const Numero& num, Usuario& us,const Fecha& fe):
tipo_(tip), num_tar(num), titular_(&us), caducidad_(fe)
{
	Fecha aux(0,0,0);
	if(aux > fe) throw Caducada(caducidad_);

	us.es_titular_de(*this);
	titular_facial_ = us.nombre() + " " + us.apellidos();
	
}

//***DESTRUCTOR***

Tarjeta::~Tarjeta() 
{
	if(Usuario* us = const_cast<Usuario*>(titular_))
	us->no_es_titular_de(*this);

}

//***OPERADORES***

ostream& operator <<(ostream& os,const Tarjeta::Tipo& t)
{
	switch(t)
	{
		case Tarjeta::Tipo::VISA:
			os << " VISA ";
		break;

		case Tarjeta::Tipo::Mastercard:
			os << " Mastercard ";
		break;

		case Tarjeta::Tipo::Maestro:
			os << " Maestro ";
		break;

		case Tarjeta::Tipo::JCB:
			os << " JCB ";
		break;

		case Tarjeta::Tipo::AmericanExpress:
			os << " AmericanExpress ";
		break;
	}
	return os;
}

ostream& operator <<(ostream& o,const Tarjeta& tar)
{

	o << tar.tipo() << endl;
	o << tar.numero() << endl;
	o << tar.titular_facial() << endl;
	o << "Caduca: " << setfill('0') << setw(2) << tar.caducidad().mes() << "/" << tar.caducidad().anno() % 100 << endl;

	return o;
}


bool operator <(const Tarjeta& A, const Tarjeta& B)
{
	return (A.numero() < B.numero());
}


