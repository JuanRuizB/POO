
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"


int Pedido::N_pedidos = 0;


int Pedido::n_total_pedidos()
{
	return N_pedidos;
}

Pedido::Pedido(Usuario_Pedido& us_pe, Pedido_Articulo& pe_art, Usuario& u, const Tarjeta& t, const Fecha& fp)
	:num_(N_pedidos + 1), tarjeta_(&t), fecha_(fp), total_(0)
{
	if(u.n_articulos() == 0)
		throw Vacio(u); 							//Carrito vacio

	if(t.titular() != &u)
		throw Impostor(u); 							//Tarjeta robada

	if(t.caducidad() < fp)
		throw Tarjeta::Caducada(t.caducidad()); 	//Tarjeta caducada


	for(auto c : u.compra()) //c es pair<Articulo*, unisgned (cantidad)>   	Este for es para mirar si hay stock de todos los articulos 
	{
		if(c.first->stock() < c.second) //no hay bastante stock en el armasén
		{
			 const_cast<Usuario::Articulos&>(u.compra()).clear();//necesitamos quitar el const que nos devuelve u.compra()
			throw SinStock(c.first);				
		}
	}
		Usuario::Articulos carroAux = u.compra();
	 //Hacemos esto pq si leemos y borramos en el mismo contenedor, al borrar elementos
											  //Los iteradores fallan entonces nos creamos este carro auxiliar para leer y borramos
											  //En el nuestro

	for(auto c : carroAux) //												Este for es para restar la cantidad de articulos que nos llevamos
	{
		Articulo* pa = c.first;
		unsigned int cantidad = c.second;
		double precio = pa->precio();

		pa->stock() -= cantidad;


		pe_art.pedir(*this, *pa, precio, cantidad);
		total_ += precio * cantidad;
		u.compra(*pa, 0);
	}
	us_pe.asocia(u, *this);
	++N_pedidos;
}

ostream& operator << (ostream& os, const Pedido& ped)
{
	os << "Num. pedido: " << ped.numero() << endl;
	os << "Fecha:" << setw(7) << ped.fecha() << endl;
	os << "Pagado con:" << setw(2) << ped.tarjeta() << endl;
	os << "Importe:" << setw(5) << ped.total() << " €" << endl;
}