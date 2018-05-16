extern "C" {
#include <unistd.h>
}
#include <cstring>
#include <random>
#include <iomanip>
#include <ctime> 
#include "usuario.hpp"

//***************************************CLAVE*******************************

Clave::Clave (const char* pass)
{
	static const char *const seedchars ="./0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";

	if(strlen(pass) < 5) throw Incorrecta(CORTA);

	static std::random_device r;
	static std::uniform_int_distribution<size_t> distribucion(0,63);

	const char salt[] = {seedchars[distribucion(r)], seedchars[distribucion(r)]};

	if (const char* const pcc = crypt(pass,salt))
		password_ = pcc;
	else
		throw Incorrecta(ERROR_CRYPT);
}

bool Clave::verifica(const char* ver) const
{
	if (const char* const pcc = crypt(ver,password_.c_str()))
		return password_ == pcc;
	throw Incorrecta(ERROR_CRYPT);

};



//**************************************USUARIO******************************

	Usuario::Usuarios Usuario::usuario_;


	Usuario::Usuario(const Cadena& id,const Cadena& nom,const Cadena& apell,const Cadena& dir, const Clave& pw)
	:id_(id),nom_(nom), apell_(apell), dir_us(dir), pass_(pw)
	{
		if(!usuario_.insert(id).second) 
			throw Id_duplicado(id_);
	}

	Usuario::~Usuario()
	{
		auto iter = tar_.begin();
    	
    	while(iter != tar_.end()) {
    		iter->second->anula_titular();
    		iter++;
	}
		usuario_.erase(id_);
	}

	//***METODOS***

	void Usuario::es_titular_de(Tarjeta& A)
	{
		if(this == A.titular())
			tar_.insert(std::make_pair(A.numero(),&A));
	}

	void Usuario::no_es_titular_de( Tarjeta& A)
	{
		A.anula_titular();
		tar_.erase(A.numero());
	}

	void Usuario::compra( Articulo& art,unsigned cant )
	{
		
			if(cant == 0)
			{
				art_.erase(&art);
			} else
			{
				art_[&art] = cant;
			}

	}

	std::ostream& operator <<(std::ostream& o, const Usuario& U)
	{
		o << U.id_ << "[" << U.pass_.clave().c_str() << "]" << U.nom_ << " " << U.apell_ << endl;
		o << U.dir_us << endl;
		o << "Tarjetas:" << endl;
		auto pos = U.tarjetas().begin();
		while(pos != U.tarjetas().end())
		{
			o << *pos->second << endl;
			pos++;
		}
		return o;
	}

	std::ostream& mostrar_carro(std::ostream& o, const Usuario& U)
	{
		o << "Carrito de compra de " << U.id() << "[Artículos: " << U.n_articulos() << "]" << endl;
		o << "Cant. Artículo" << endl
		<< setw(95) << setfill('=') << '\n' << setfill(' ');
		int aux = U.n_articulos();
		while(aux > 0)
		{
			for (auto const& pos : U.compra())
			{
			o << setw(4) << pos.second << "   "
			 << "[" << (*pos.first).referencia() << "] \""
			 << (*pos.first).titulo() << "\", " 
			 << (*pos.first).f_publi().anno()
			 << ". " << fixed << setprecision(2) << (*pos.first).precio() << " €" << endl;
			--aux;
			}
		}
		return o;
	}


