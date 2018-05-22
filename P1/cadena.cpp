
#include "cadena.hpp"

using namespace std;

Cadena::Cadena( unsigned tam,const char c): s_(new char[tam+1]),tam_(tam)
{
	for (unsigned i = 0; i < tam; i++)
            s_[i]=c;

	s_[tam_]='\0';
}

Cadena::Cadena(const Cadena &cad): s_(new char[cad.tam_+1]),tam_(cad.tam_)
{
	strcpy(s_,cad.s_);
}

Cadena::Cadena(Cadena&& cad): s_(cad.s_),tam_(cad.tam_)
{
	cad.s_ = nullptr;
	cad.tam_ = 0;
}

Cadena::Cadena(const char* s): s_(new char[strlen(s)+1]),tam_(strlen(s))
{
	strcpy(s_,s);
}

Cadena::~Cadena()
{
	delete[] s_;
}


Cadena& Cadena::operator =(const Cadena& a)
{
	Cadena aux(*this);

	this->tam_ = a.tam_;

	delete[] this->s_;

	this->s_ = new char[this->tam_ + 1];

	strcpy(this->s_,a.s_);

	return *this;
}

Cadena& Cadena::operator =(const char* a)
{
	Cadena aux(*this);

	this->tam_ = strlen(a);

	delete[] this->s_;

	this->s_ = new char[this->tam_ + 1];

	strcpy(this->s_,a);

	return *this;
}

Cadena& Cadena::operator =(Cadena&& a) noexcept
{
	Cadena aux(*this);

	this->tam_ = a.tam_;

	delete[] this->s_;

	this->s_ = new char[this->tam_ + 1];

	strcpy(this->s_,a.s_);

	a.s_ = nullptr;
	a.tam_ = 0;

	return *this;
}

const char* Cadena::c_str() const noexcept
{
	return s_;
}

Cadena& Cadena::operator +=(const Cadena& a)
{
	Cadena aux(*this);

	this->tam_ += a.tam_;

	delete[] this->s_;

	this->s_ = new char[this->tam_ + 1];

	strcpy(this->s_,aux.s_);

	strcat(this->s_,a.s_);

	return *this;
}

Cadena& Cadena::operator +=(const char* a)
{
	Cadena aux(a);
	return *this += aux;
}

Cadena operator +(const Cadena& a,const Cadena& b)
{
	return Cadena(a) += b;
}

bool operator <(const Cadena& a, const Cadena& b)
{
	return (strcmp(a.c_str(),b.c_str()) < 0);
}


bool operator >(const Cadena& a, const Cadena& b)
{
	return (strcmp(a.c_str(),b.c_str()) > 0);
}

bool operator ==(const Cadena& a, const Cadena& b)
{
	return (strcmp(a.c_str(),b.c_str()) == 0);
}

bool operator !=(const Cadena& a, const Cadena& b)
{
	return !(strcmp(a.c_str(),b.c_str()) == 0);
}


bool operator <=(const Cadena& a, const Cadena& b)
{
	return (strcmp(a.c_str(),b.c_str()) <= 0);
}


bool operator >=(const Cadena& a, const Cadena& b)
{
	return (strcmp(a.c_str(),b.c_str()) >= 0);
}



char& Cadena::at (size_t i)
{
	if ( i < tam_)
		return this->s_[i];

	throw out_of_range{"Error. Índice fuera del rango de la cadena"};		
}

char Cadena::at (size_t i) const
{
	if ( i < tam_)
		return this->s_[i];

	throw out_of_range{"Error. Índice fuera del rango de la cadena"};
}

Cadena Cadena::substr(size_t i, unsigned tam) const
{

	if(i >= this->length() || i+tam > this->length() || i+tam < i)
		throw out_of_range{"Error de tamaño"};
	
		char* aux = new char[tam+1];
		strncpy(aux,s_ + i,tam);
		aux[tam]='\0';
		Cadena cad(aux);
		delete[] aux;
		return cad;
	
}

 std::istream& operator >>(std::istream &i,Cadena& cad)
{
	char aux[33];
	int j = 0;

	while(isspace(i.get()) && i.good()) {}
	i.unget();
	
	while(!isspace(i.peek()) && j < 32 && i.good())
	{
		aux[j] = i.get();
		j++;
	}
	aux[j] = '\0';

 	if(j == 0) cad = Cadena();
 	else
 	{
 	cad = Cadena(aux);		
 	} 

	return i;
}

 std::ostream& operator <<(std::ostream &o,const Cadena& cad)
{
	o << cad.c_str();
	return o;
}
