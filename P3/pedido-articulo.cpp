#include <iostream>
#include <iomanip>
#include "pedido-articulo.hpp"


LineaPedido::LineaPedido(double pre , unsigned cant ):precio_venta_(pre), cantidad_(cant){}


bool OrdenaPedidos::operator() (const Articulo* a, const Articulo* b)const {return (a->referencia() < b->referencia());}

bool OrdenaArticulos::operator() (const Pedido* a, const Pedido* b)const {return (a->numero() < b->numero());}


void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double pre, unsigned cant)
	{
		directa_[&ped].insert(std::make_pair(&art,LineaPedido(pre,cant)));

		inversa_[&art].insert(std::make_pair(&ped,LineaPedido(pre,cant)));
	}

void Pedido_Articulo::pedir(Articulo& art,Pedido& ped, double pre, unsigned cant)
	{
		pedir(ped,art,pre,cant);
	}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& ped)
{
 	return directa_[&ped];
}

Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& art)
{
	return inversa_[&art];
}

ostream& operator <<(ostream& os,const Pedido_Articulo::ItemsPedido x)
{
	os << setw(2) << "PVP" << setw(3) << "Cantidad" << setw(8) << "Articulo" << endl
	<< setw(95) << setfill('=') << '\n' << setfill(' ');

	unsigned int aux = x.size();
	double total = 0.;

	while(aux > 0)
	{
		for(auto const& pos : x)
		{
			total = total + pos.second.precio_venta()*pos.second.cantidad();
			os << setw(4) << pos.second << setw(15) 
			<< "[" << (*pos.first).referencia() << "] \""
			<< (*pos.first).titulo() << "\", " << endl;
			--aux;
		}
	}
	os << setw(95) << setfill('=') << '\n' << setfill(' ');
	os << "Total" << setw(3) << total;
	return os;
}

ostream& operator <<(ostream& os,const Pedido_Articulo::Pedidos x )
{
	os << "[Pedidos: " << x.size() << "]" << endl
	<< setw(95) << setfill('=') << '\n' << setfill(' ');

	os << setw(2) << "PVP" << setw(3) << "Cantidad" << setw(11) << "Fecha de venta" 
	<< setw(95) << setfill('=') << '\n' << setfill(' ');

	int cant = 0;
	double total = 0.;

		for(auto const& pos : x)
		{
			os << pos.second.precio_venta() << "€\t";
			os << pos.second.cantidad() << "\t";
			os << pos.first->fecha() << std::endl;

			total +=pos.second.precio_venta() * pos.second.cantidad();
			cant += pos.second.cantidad();
		}
		os << setw(95) << setfill('=') << '\n' << setfill(' ');
		os << total << " €" << setw(8) << cant << endl;
		return os;
}

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os)
{
	double total = 0.;

	for(auto pos : directa_)
	{
	os << "Pedido num. " << pos.first->numero() << endl;
	os << "Cliente: " << pos.first->tarjeta().titular()->nombre() 
	<< setw(15) << "Fecha: " << pos.first->fecha() << endl;

	total += pos.first->total();
	}

	os << "TOTAL VENTAS " << setw(15) << total << " €" << endl;
	return os;
}

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os)
{

	for(auto pos : inversa_)
	{
		os << "Ventas de [" << pos.first->referencia() << "] \"" 
		<< pos.first->titulo() << "\"" << endl;
	}
	return os;
}
