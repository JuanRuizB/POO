#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_
#include <iostream>
#include <set>
#include <map>
class Pedido;
using namespace std;

class Usuario_Pedido{
public:
	typedef set<Pedido*> Pedidos;

	void asocia(Usuario& us, Pedido& ped) { us_ped[&us].insert(&ped); ped_us[&ped] = &us; }
	void asocia(Pedido& ped, Usuario& us) { asocia(us,ped); }

	Pedidos& pedidos( Usuario& us){return us_ped.at(&us);}

	Usuario* cliente( Pedido& ped) {return ped_us.find(&ped)->second;}

private:
	map<Usuario*, Pedidos> us_ped;
	map<Pedido*, Usuario* > ped_us;
};


#endif