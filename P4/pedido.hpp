#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include <iostream>

#include "../P1/fecha.hpp"
#include "../P2/tarjeta.hpp"

using namespace std;

class Usuario_Pedido;
class Pedido_Articulo;


class Pedido {
public:
	Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& us, const Tarjeta& tj,const Fecha& = Fecha() );

	class Vacio{
	public:
		Vacio( Usuario const* usu):vac(usu) { }
		const Usuario& usuario() const { return *vac;}
	private:
		 Usuario const* vac;
	};

	class Impostor{
	public:
		Impostor( Usuario const* usu):im(usu) { }
		const Usuario& usuario() const { return *im;}
	private:
		 Usuario const* im;
	};

	class SinStock{
	public:
		SinStock( Articulo const* ar):art(ar) { }
		const Articulo& articulo() const { return *art;}
	private:
		 Articulo const* art;
	};

	int numero() const {return num_;}

	Tarjeta const* tarjeta() const {return tarjeta_;}

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