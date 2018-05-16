#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_
#include <iostream>
#include <map>
#include <functional>   // std::greater
#include "pedido.hpp"
#include "articulo.hpp"
class Pedido;
class Articulo;

using namespace std;

class LineaPedido {

public:
	explicit LineaPedido(double pre , unsigned cant = 1);

	double precio_venta() const {return precio_venta_;}
	unsigned cantidad() const {return cantidad_;}

private:
	double precio_venta_;
	unsigned cantidad_;
};

std::ostream& operator <<(std::ostream& os,const LineaPedido& lin_ped)
{
	os << lin_ped.precio_venta() << " €" << setw(4) << lin_ped.cantidad() << endl;
	return os;
}

struct OrdenaPedidos : public std::binary_function<const Articulo*,const Articulo*,bool>
	{
 		bool operator() (const Articulo* a, const Articulo* b)const;
	};

	struct OrdenaArticulos : public std::binary_function<const Pedido*,const Pedido*,bool>
	{
 		bool operator() (const Pedido* a, const Pedido* b)const;
	};

class Pedido_Articulo{
public:
	typedef map<Articulo*,LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef map<Pedido*,LineaPedido, OrdenaPedidos> Pedidos;

	//typedef sort (auto ini = ped_art.begin(),auto fini = ped_art.end() , greater<int>() ) OrdenaPedidos;
	//typedef sort (auto ini = art_ped.begin(),auto fini = art_ped.end() , greater<Cadena>()) OrdenaArticulos;

	void pedir(Pedido& ped, Articulo& art, double pre, unsigned cant = 1);
	void pedir(Articulo& art,Pedido& ped, double pre, unsigned cant = 1);

	ItemsPedido& detalle(Pedido& ped);

	Pedidos& ventas(Articulo& art);

	ostream& mostrarDetallePedidos(ostream& os);
	ostream& mostrarVentasArticulos(ostream& os);

private:
	map<Pedido*, ItemsPedido, OrdenaPedidos> directa_;
	map<Articulo*, Pedidos, OrdenaArticulos> inversa_;
};

ostream& operator <<(ostream& os, Pedido_Articulo::ItemsPedido x);

ostream& operator <<(ostream& os, Pedido_Articulo::Pedidos x );



#endif