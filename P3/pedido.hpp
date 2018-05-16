#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include <iomanip>
#include <iostream>
#include "../P2/usuario.hpp"
#include "../P1/fecha.hpp"
#include "../P2/tarjeta.hpp"
class Usuario_Pedido;
class Pedido_Articulo;


using namespace std;

class Pedido {
public:
	Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& us, const Tarjeta& tj,const Fecha& fch = "0/0/0" );

	class Vacio{
	public:
		Vacio(const Usuario& usu):us(&usu) { }
		const Usuario& usuario() const { return *us;}
	private:
		const Usuario* us;
	};

	class Impostor{
	public:
		Impostor(const Usuario& usu):us(&usu) { }
		const Usuario& usuario() const { return *us;}
	private:
		const Usuario* us;
	};

	class SinStock{
	public:
		SinStock(const Articulo& ar):art(&ar) { }
		const Articulo& articulo() const { return *art;}
	private:
		const Articulo* art;
	};

	int numero() const {return num_;}

	const Tarjeta& tarjeta() const {return *tarjeta_;}

	const Fecha& fecha() const {return fecha_;}

	double total() const {return total_;}

	static int n_total_pedidos() {return N_pedidos;}

private:
	static int N_pedidos;
	int num_;
	const Tarjeta* tarjeta_;
	Fecha fecha_;
	double total_;

};

ostream& operator << (ostream& os, const Pedido& ped);


#endif