#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_
#include <iostream>
#include <iomanip>
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

ostream& operator <<(ostream& os,const LineaPedido& lin_ped);


	struct OrdenaArticulos : public std::binary_function<const Articulo*,const Articulo*,bool>
	{
 		bool operator () (const Articulo* a, const Articulo* b)const;
	};

	struct OrdenaPedidos : public std::binary_function<const Pedido*,const Pedido*,bool>
	{
 		bool operator () (const Pedido* x, const Pedido* y)const;
	};

class Pedido_Articulo{
public:
	typedef std::map<Articulo*,LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*,LineaPedido, OrdenaPedidos> Pedidos;


	void pedir(Pedido& ped, Articulo& art, double pre, unsigned cant = 1);
	void pedir(Articulo& art,Pedido& ped, double pre, unsigned cant = 1);

	ItemsPedido& detalle(Pedido& ped);

	Pedidos ventas(Articulo& art);

	std::ostream& mostrarDetallePedidos(std::ostream& os);
	std::ostream& mostrarVentasArticulos(std::ostream& os);

private:
	std::map<Pedido*, ItemsPedido, OrdenaPedidos> directa_;
	std::map<Articulo*, Pedidos, OrdenaArticulos> inversa_;
};

std::ostream& operator <<(std::ostream& os, Pedido_Articulo::ItemsPedido x);

std::ostream& operator <<(std::ostream& os, Pedido_Articulo::Pedidos x );



#endif