#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>

using namespace std;

class Cadena {
public:

explicit Cadena( size_t tam = 0,char c = ' ');
Cadena(const Cadena& cad);
Cadena(const char* s);

~Cadena() noexcept;


Cadena& operator =(const Cadena& a);
operator const char*() const;
Cadena& operator +=(const Cadena& a);
char& operator [](size_t i);
char operator [](size_t i) const;

char& at (size_t i);
char at (size_t i) const;

Cadena substr(size_t i, size_t tam) const;

size_t length() const;

private:
	char* s_;
	size_t tam_;
};

Cadena operator +(const Cadena& a, const Cadena& b);
bool operator <(const Cadena& a, const Cadena& b);

bool operator >(const Cadena& a, const Cadena& b);

bool operator ==(const Cadena& a, const Cadena& b);
bool operator !=(const Cadena& a, const Cadena& b);

bool operator <=(const Cadena& a, const Cadena& b);

bool operator >=(const Cadena& a, const Cadena& b);


inline size_t Cadena::length() const { return tam_; }

inline char& Cadena::operator [](size_t i)
{
	return s_[i];
}

inline char Cadena::operator [](size_t i) const
{
	return s_[i];
}


#endif