#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <stdexcept>
#include <cstring>


using namespace std;

class Cadena {
public:

typedef char* iterator;
typedef const char* const_iterator;
typedef std::reverse_iterator<iterator> reverse_iterator;
typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

 iterator begin() noexcept {	return s_; }

 iterator end() noexcept{	return s_+tam_; }

 const_iterator begin() const noexcept{ return s_; }

 const_iterator cbegin() const noexcept{ return s_; }

 const_iterator end() const noexcept{	return s_+tam_;}

 const_iterator cend() const noexcept{	return s_+tam_;}

 reverse_iterator rbegin() noexcept{return reverse_iterator(end());}

 reverse_iterator rend() noexcept{return reverse_iterator(begin());}

 const_reverse_iterator rbegin()const noexcept{	return const_reverse_iterator(end());}

 const_reverse_iterator crbegin()const noexcept{	return const_reverse_iterator(end());}

 const_reverse_iterator rend()const  noexcept{return const_reverse_iterator(begin());}

 const_reverse_iterator crend()const noexcept{return const_reverse_iterator(begin());}


explicit Cadena( size_t tam = 0,char c = ' ')noexcept;
Cadena(const Cadena& cad)noexcept;
Cadena(Cadena&& cad)noexcept;
Cadena(const char* s)noexcept;

~Cadena() noexcept;


Cadena& operator =(const Cadena& a);
Cadena& operator =(const char* a);
Cadena& operator =(Cadena&& a)noexcept;
const char* c_str() const noexcept;
Cadena& operator +=(const Cadena& a);
Cadena& operator +=(const char* a);
char& operator [](size_t i);
char operator [](size_t i) const;

char& at (size_t i);
char at (size_t i) const;

Cadena substr(size_t i, size_t tam) const;

size_t length() const noexcept;

private:
	char* s_;
	size_t tam_;
};

 std::istream& operator >>(std::istream &i,Cadena& cad);
 std::ostream& operator <<(std::ostream &o,const Cadena& cad);

Cadena operator +(const Cadena& a, const Cadena& b);
bool operator <(const Cadena& a, const Cadena& b);

bool operator >(const Cadena& a, const Cadena& b);

bool operator ==(const Cadena& a, const Cadena& b);
bool operator !=(const Cadena& a, const Cadena& b);

bool operator <=(const Cadena& a, const Cadena& b);

bool operator >=(const Cadena& a, const Cadena& b);


namespace std { // Estaremos dentro del espacio de nombres std
	template <> // Es una especialización de una plantilla para Cadena
	struct hash<Cadena> { // Es una clase con solo un operador publico
		size_t operator() (const Cadena& cad) const // el operador función
		{
			hash<string> hs;	// creamos un objeto hash de string
			const char * p = cad.c_str(); // obtenemos la cadena de la Cadena
			string s(p);	// creamos un string desde una cadena
			size_t res = hs(s);	// el hash del string. Como hs.operator()(s);
			return res;		// devolvemos el hash del string
		}
	};
}


inline size_t Cadena::length() const noexcept { return tam_; }

inline char& Cadena::operator [](size_t i)
{
	return s_[i];
}

inline char Cadena::operator [](size_t i) const
{
	return s_[i];
}


#endif