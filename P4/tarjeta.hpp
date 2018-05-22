#ifndef TARJETA_HPP_
#define TARJETA_HPP_
#include <iostream>
#include <cctype>
#include "cadena.hpp"
#include "usuario.hpp"
#include "fecha.hpp"
class Usuario;

using namespace std;

struct EsBlanco: unary_function<char, bool>{
	bool operator()(unsigned char x) {return isspace(x);};
};


//*********************NUMERO******************************

class Numero{
public:

	enum Razon {LONGITUD,DIGITOS, NO_VALIDO};

	Numero(Cadena num);
	operator const char*() const { return tarjeta_.c_str(); }

	class Incorrecto{
	public:
		Razon razon() const{return raz;}
		Incorrecto(Razon error): raz(error){}
	private:
		Razon raz;
	};

	friend bool operator <(const Numero& A,const Numero& B);

private:
	Cadena tarjeta_;

};


//****************************TARJETA*******************************

class Tarjeta {
public:
	enum Tipo {VISA, Mastercard, Maestro, JCB, AmericanExpress};
	
	///***CONSTRUCTORES***

	Tarjeta(Tipo tip,const Numero& num, Usuario& us,const Fecha& fe);

	Tarjeta(const Tarjeta& tar) = delete;

	~Tarjeta();

	//***OBSERVADORES***

	Tipo tipo() const {return tipo_;}

	const Numero& numero() const {return num_tar;}

	const Usuario* titular() const {return titular_;}

	const Fecha& caducidad() const {return caducidad_;}

	const Cadena& titular_facial() const {return titular_facial_;}

	//***OPERADORES***

	Tarjeta& operator =(const Tarjeta& tar) = delete;

	//**CLASE CADUCADA***

	class Caducada{
	public:
		Caducada(Fecha cadu):f_caducada(cadu){}
		const Fecha& cuando()const {return f_caducada;}
	private:
		Fecha f_caducada;
	};

	//***METODOS***

	void anula_titular() {titular_ = nullptr;}


private:
	Tipo tipo_;
	Numero num_tar;
	const Usuario* titular_;
	Fecha caducidad_;
	Cadena titular_facial_;
};

ostream& operator <<(ostream& os,const Tarjeta::Tipo& t);
std::ostream& operator <<(std::ostream& o,const Tarjeta& tar);

bool operator <(const Tarjeta& A, const Tarjeta& B);



#endif