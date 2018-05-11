#include <iomanip>
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

size_t Pedido::n_pedidos_ = 0;

Pedido::Pedido(Usuario_Pedido& u_p,
               Pedido_Articulo& p_a,
               Usuario& u,
               const Tarjeta& t,
               Fecha fecha)
:num_(n_pedidos_+1),card_(&t),date_(fecha),total_(0)
{
    if( u.n_articulos() == 0) throw Pedido::Vacio(&u);
    if(t.titular() != &u) throw Pedido::Impostor(&u);
    if(t.caducidad() < fecha) throw Tarjeta::Caducada(t.caducidad());
    for(auto c : u.compra())//c = pair<Articulo*,unsigned>(cantidad)
        if(c.first->stock()<c.second)
        {   //no hay articulos.
            const_cast<Usuario::Articulos&>(u.compra()).clear();
            throw Pedido::SinStock(c.first);
        }
    Usuario::Articulos carro = u.compra();
    for(auto c : carro)
    {
        Articulo* pa = c.first;
        unsigned int cantidad = c.second;
        double precio = pa->precio();
        pa->stock() -= cantidad;
        p_a.pedir(*this,*pa,precio,cantidad);
        total_+= precio * cantidad;
        u.compra(*pa,0);
    }
    u_p.asocia(u,*this);
    ++n_pedidos_;
}

size_t Pedido::n_total_pedidos() noexcept
{
	return n_pedidos_;
}

std::ostream& operator << (std::ostream& os ,const Pedido& pe)
{
    os << "Núm. pedido:" << pe.numero() << std::endl
       << "Fecha:" << pe.fecha() << std::endl
       << "Pagado con:" << *pe.tarjeta() << std::endl
       << "Importe:" << std::fixed << std::setprecision(2) << pe.total() << " \u20AC";
    return os;
}
