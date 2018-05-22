#include <iostream>
#include <iomanip>
#include "pedido-articulo.hpp"


LineaPedido::LineaPedido(double pre , unsigned cant ):precio_venta_(pre), cantidad_(cant){};


std::ostream& operator <<(std::ostream& os,const LineaPedido& lin_ped)
{
	os << std::fixed << std::setprecision(2) << lin_ped.precio_venta() << " €" << '\t' << lin_ped.cantidad();
	return os;
}

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double pre, unsigned cant)
	{
		directa_[&ped].insert(std::make_pair(&art,LineaPedido(pre,cant)));
		inversa_[&art].insert(std::make_pair(&ped,LineaPedido(pre,cant)));
	}

void Pedido_Articulo::pedir(Articulo& art,Pedido& ped, double pre, unsigned cant)
	{
		Pedido_Articulo::pedir(ped,art,pre,cant);
	}

bool OrdenaArticulos::operator () (const Articulo* a, const Articulo* b)const {return a->referencia() < b->referencia();};

bool OrdenaPedidos::operator () (const Pedido* x, const Pedido* y)const {return x->numero() < y->numero();};



Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& ped)
{
 	return directa_[&ped];
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& art)
{
	return inversa_[&art];
}

std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::ItemsPedido IP)
{

	os << "PVP\tCantidad\t\tArticulo\n";
	os << "==================================================================\n";

	double total = 0.;

		for(auto const& pos : IP)
		{
			total = total + pos.second.precio_venta()*pos.second.cantidad();
			
			os << pos.second << "\t\t" 
			<< "[" << (*pos.first).referencia() << "] \""
			<< (*pos.first).titulo() << "\", " << "\n";

		}
	os << "==================================================================\n";
	os << "Total\t" << total;
	return os;
}

std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::Pedidos ped )
{
	os << "[Pedidos: " << ped.size() << "]\n";
	os << "==================================================================\n";

	os << "PVP\tCantidad\t\tFecha de venta\n";
	os << "==================================================================\n";

	int cant = 0;
	double total = 0.;

		for(auto const& pos : ped)
		{
			os << pos.second << "\t\t" << pos.first->fecha() << "\n";

			total +=pos.second.precio_venta() * pos.second.cantidad();
			cant += pos.second.cantidad();
		}
		os << "==================================================================\n";
		os << std::setprecision(2) << total << " €" << "\t" << cant << "\n";
		return os;
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
	double total = 0.;
	Fecha hoy;
	for(auto pos : directa_)
	{
		if(pos.first->fecha() <= hoy)
		{
		os << "Pedido num. " << pos.first->numero() << "\n";
		os << "Cliente: " << pos.first->tarjeta()->titular()->nombre() 
		<< "\t\t" << "Fecha: " << pos.first->fecha() << pos.second ;
		}
	total += pos.first->total();
	}
	os << std::fixed;
	os << "TOTAL VENTAS " << std::setprecision(2) << total << " €" << "\n";
	return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{

	for(auto pos : inversa_)
	{
		os << "Ventas de " << "[" << pos.first->referencia() << "] \"" 
		<< pos.first->titulo() << "\"\n" << pos.second << "\n";
	}
	return os;
}
