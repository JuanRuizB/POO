#include <iostream>
#include <stdexcept>
#include <cstring>
#include "cadena.hpp"

using namespace std;

Cadena::Cadena( size_t tam,const char c): s_(new char[tam+1]),tam_(tam)
{
	for (unsigned i = 0; i < tam; i++)
            s_[i]=c;

	s_[tam_]='\0';
}

Cadena::Cadena(const Cadena& cad): s_(new char[cad.tam_+1]),tam_(cad.tam_)
{
	strcpy(s_,cad.s_);
}

Cadena::Cadena(const char* s): s_(new char[strlen(s)+1]),tam_(strlen(s))
{
	strcpy(s_,s);
}

Cadena::~Cadena() noexcept
{
	delete[] s_;
}


Cadena& Cadena::operator =(const Cadena& a)
{
	Cadena aux(*this);

	this->tam_ += a.tam_;

	delete[] this->s_;

	this->s_ = new char[this->tam_ + 1];

	strcat(this->s_,a.s_);

	return *this;
}


Cadena::operator const char*() const 
{
	char* c = new char[this->tam_];

	strcpy(c,this->s_);

return (const char*)c;
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



Cadena operator +(const Cadena& a,const Cadena& b)
{
	return Cadena(a) += b;
}

bool operator <(const Cadena& a, const Cadena& b)
{
	return strcmp(a,b) < 0;
}

bool operator <(const Cadena& a, const char* b)
{
	return strcmp(a,b) < 0;
}

bool operator >(const Cadena& a, const Cadena& b)
{
	return strcmp(b,a) < 0;
}

bool operator >(const Cadena& a, const char* b)
{
	return strcmp(b,a) < 0;
}

bool operator ==(const Cadena& a, const Cadena& b)
{
		if (strcmp(a,b) == 0) return true;
	else return false;
}

bool operator !=(const Cadena& a, const Cadena& b)
{
	if (strcmp(a,b) == 0) return false;
	else return true;
}

bool operator !=(const Cadena& a, char* b)
{
	if (strcmp(a,b) == 0) return false;
	else return false;
}

bool operator <=(const Cadena& a, const Cadena& b)
{
	if (strcmp(a,b) <= 0) return true;
	else return false;
}

bool operator <=(const Cadena& a, const char* b)
{
	if (strcmp(a,b) <= 0) return true;
	else return false;
}

bool operator >=(const Cadena& a, const Cadena& b)
{
	if (strcmp(a,b) >= 0) return true;
	else return false;
}

bool operator >=(const Cadena& a, const char* b)
{
	if (strcmp(a,b) >= 0) return true;
	else return false;
}


char& Cadena::at (size_t i)
{
	if ( i < tam_)
		return (*this)[i];

	throw out_of_range("Error. Índice fuera del rango de la cadena");		
}

char Cadena::at (size_t i) const
{
	if ( i < tam_)
		return (*this)[i];

	throw out_of_range("Error. Índice fuera del rango de la cadena");
}

Cadena Cadena::substr(size_t i, size_t tam) const
{

	if(i >= this->length() || i+tam > this->length() || i+tam < i)
		throw out_of_range("Error de tamaño");
	else{
		Cadena A(tam+1);
		for (unsigned j = 0; j < tam; j++)
		{
			A.s_[j] = this->s_[i+j];
		}
		A.s_[tam] = '\0';
		return A;
	}
}