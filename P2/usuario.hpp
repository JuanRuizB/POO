#ifndef USUARIO_HPP_
#define USUARIO_HPP_
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "tarjeta.hpp"
#include "articulo.hpp"
class Tarjeta;
class Numero;

using namespace std;


//****************************************CLAVE**************************************

class Clave{
public:
	enum Razon {CORTA, ERROR_CRYPT};
	
	Clave (const char* pass);
	bool verifica(const char* ver) const;

	const Cadena& clave() const {return password_;}


class Incorrecta{
public:
	Razon razon() const{return raz;}
	Incorrecta(const Razon error): raz(error){}
private:
	Razon raz;
};

private:
	Cadena password_;
};

//****************************************USUARIO************************************	

class Usuario{
public:

	typedef std::map< Numero , Tarjeta* > Tarjetas;
	typedef std::unordered_map< Articulo*, unsigned > Articulos;
	typedef std::unordered_set<Cadena> Usuarios;

	//***CONSTRUCTORES***

	Usuario(const Cadena& id,const Cadena& nom,const Cadena& apell,const Cadena& dir, const Clave& pw);

	Usuario(const Usuario& tar) = delete;

	//***OPERADORES***

	Usuario& operator =(const Usuario& tar) = delete;

	//***METODOS***

	void es_titular_de(Tarjeta& A);

	void no_es_titular_de( Tarjeta& A);

	void compra( Articulo& art,unsigned cant = 1);

	//***OBSERVADORES***

	Cadena id() const {return id_;}

	Cadena nombre() const {return nom_;}

	Cadena apellidos() const {return apell_;}

	Cadena direccion() const {return dir_us;}

	const Tarjetas& tarjetas() const {return tar_;}

	const Articulos& compra() const {return art_;}

	size_t n_articulos() const {return art_.size();}


	friend std::ostream& operator <<(std::ostream& o, const Usuario& U);

	~Usuario();

		//***CLASE ID_DUPLICADO***

	class Id_duplicado{
	public:
		Id_duplicado(const Cadena& cad):id_repe(cad){}
		const Cadena& idd() const {return id_repe; }
	private:
		Cadena id_repe;
	};

private:
	Cadena id_,nom_,apell_,dir_us;
	Clave pass_;
	Tarjetas tar_;
	Articulos art_;
	static Usuarios usuario_;

};

	std::ostream& mostrar_carro(std::ostream& o, const Usuario& U);



#endif