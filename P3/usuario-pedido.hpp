#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_
#include <set>
#include "pedido.hpp"

using namespace std;

class Usuario_Pedido{
public:
	typedef set<Pedido*> Pedidos;

	void asocia(Usuario& us, Pedido& ped) { us_ped[&us].insert(&ped); ped_us[&ped] = &us; }
	void asocia(Pedido& ped, Usuario& us) { asocia(us,ped); }

	Pedidos pedidos( Usuario& us){return us_ped[&us];}

	Usuario* cliente( Pedido& ped) {return ped_us[&ped];}

private:
	std::map<Usuario*, Pedidos> us_ped;
	std::map<Pedido*, Usuario* > ped_us;
};


#endif