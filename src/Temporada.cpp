#include "../include/Temporada.h"

Temporada::Temporada(SistemaLaboral &sl): sistema(sl)
{
    inicializarAcuerdosPorGrupos();
    inicializarCantAcuerdosPrevios();
}

void Temporada::inicializarAcuerdosPorGrupos()
{
    Nat cantGrupos = this->sistema.obtenerCantidadGrupos();

    for (Nat indice = 0; indice < cantGrupos; indice++)
        this->acuerdosPorGrupo.AgregarAtras(Lista<Acuerdo>());
}

void Temporada::inicializarCantAcuerdosPrevios()
{
    Nat cantGremios = this->sistema.obtenerGremios().Cardinal();

    for (Nat indice = 0; indice < cantGremios; indice++)
        this->cantAcuerdosPrevios.AgregarAtras(0);
}

Conj<Gremio> Temporada::gremios() const
{
    return this->sistema.obtenerGremios();
}

const Conj<Paritaria> &Temporada::obtenerParitariasAbiertas() const
{
    return this->paritariasAbiertas;
}

void Temporada::abrirParitaria(const Gremio gr, const Nat piso, const Nat techo, const Conj<Empresa> es)
{
    if (obtenerCantAcuerdosPrevios(gr) > 0)
        removerAcuerdo(gr);

    agregarParitaria(Paritaria(gr, piso, techo));
}

void Temporada::cerrarAcuerdo(const Gremio gr, const Nat porcentaje)
{
    Lista<Acuerdo>::Iterador it = obtenerAcuerdosDeAliados(gr).CrearIt();
    while ( (it.HaySiguiente()) && (it.Siguiente().obtenerPorcentaje() < porcentaje) )
    {
        agregarParitaria(it.Siguiente().obtenerParitaria());
        it.EliminarSiguiente();
        //TODO ver que pasa si borramos el ultimo , esto no vuela sangrientamente porque no vale HaySiguiente? SI. Fixed con if.
        if (it.HaySiguiente()) //agregue esto por las moscas. si borro el ultimo nos vimos en disney basicamente, no?(avanzar tiene assert hay siguiente, ver impl soporte)
        {
            it.Avanzar();
        }
    }
    Paritaria pa;
    removerParitaria(gr, pa);
    this->cantAcuerdosPrevios[gr.obtenerIdGremio()]++;
    it.AgregarComoSiguiente(Acuerdo(pa, porcentaje, obtenerCantAcuerdosPrevios(gr)));
}

Nat Temporada::obtenerCantAcuerdosPrevios(const Gremio &gr) const
{
    Nat idGremio = gr.obtenerIdGremio();
    return this->cantAcuerdosPrevios[idGremio];
}

void Temporada::reabrir(const Gremio gr)
{
    Paritaria pa = removerAcuerdo(gr);
    agregarParitaria(pa);
}

void Temporada::agregarParitaria(Paritaria pa)
{
    this->paritariasAbiertas.AgregarRapido(pa);
}

Lista<Acuerdo> &Temporada::obtenerAcuerdosDeAliados(const Gremio &gr)
{
    Nat idGrupo = gr.obtenerIdGrupo();
    return this->acuerdosPorGrupo[idGrupo];
}

bool Temporada::enParitarias(const Gremio gr) const
{
    Conj<Paritaria>::const_Iterador it = this->paritariasAbiertas.CrearIt();
    bool flag = false;
    while ((it.HaySiguiente()) && (!flag))
    {
        Paritaria pa = it.Siguiente();
    	flag = (pa.obtenerGremio().obtenerIdGremio() == gr.obtenerIdGremio());
		it.Avanzar();
    }
    return flag;
}


Conj<Gremio> Temporada::gremiosNegociando() const
{
    Conj<Gremio> res;
    Conj<Paritaria>::const_Iterador it = this->paritariasAbiertas.CrearIt();
    while (it.HaySiguiente())
    {
        Paritaria pa = it.Siguiente();
        res.AgregarRapido(pa.obtenerGremio());
        it.Avanzar();
    }

    return res;
}

Conj<Empresa> Temporada::empresasNegociando() const
{
    Conj<Empresa> res;
    Conj<Paritaria>::const_Iterador it = this->paritariasAbiertas.CrearIt();
    while (it.HaySiguiente())
    {
        Paritaria pa = it.Siguiente();
        Conj<Empresa> empresasParitaria = pa.obtenerGremio().obtenerEmpresas();
        Conj<Empresa>::const_Iterador itEmpresas = empresasParitaria.CrearIt();
        while (itEmpresas.HaySiguiente())
        {
            res.AgregarRapido(itEmpresas.Siguiente());
            itEmpresas.Avanzar();
        }
        it.Avanzar();
    }

    return res;
}

Nat Temporada::trabajadoresNegociando() const
{
    Nat res = 0;
    Conj<Paritaria>::const_Iterador it = this->paritariasAbiertas.CrearIt();
    while (it.HaySiguiente())
    {
        Paritaria pa = it.Siguiente();
        Nat cantAfiliadosParitaria = pa.obtenerGremio().obtenerCantAfiliados();
        res += cantAfiliadosParitaria;
        it.Avanzar();
    }

    return res;
}

/**
 * res sale por parametro in/out
 * devolverlo era un dolor digamos de cabeza...
 */
void Temporada::removerParitaria(const Gremio &gr, Paritaria &res)
{
    Conj<Paritaria>::Iterador it = this->paritariasAbiertas.CrearIt();
    bool flag = false;
    while( (it.HaySiguiente()) && (!flag) ){
    	Paritaria prox = it.Siguiente();
    	flag = prox.obtenerGremio().obtenerIdGremio() == gr.obtenerIdGremio();
    	if(flag){//encontre el elemento, lo borro y si hay siguiente avanzo, al borrarlo puede no valer mas haySiguiente, flag va a ser true y corta el ciclo
    		res = it.Siguiente();
    		it.EliminarSiguiente();
    		if(it.HaySiguiente()){
    			it.Avanzar();//podria haber estado borrando el ultimo! por eso el if.
    		}
    	}else{//no es lo que busco, segui buscando ( valia la guarda , haySiguiente)
    		it.Avanzar();
    	}
    }
}

/**
 * resultado sale por parametro in/out
 * devolverlo era un dolor digamos de cabeza...
 */
void Temporada::gremioConflictivo(Gremio &gremioConflictivo) const
{
    Conj<Gremio>::const_Iterador itGremios = this->gremios().CrearIt();
    gremioConflictivo = itGremios.Siguiente();
    Nat mCantAcuerdosPrevios = obtenerCantAcuerdosPrevios(gremioConflictivo);
    itGremios.Avanzar();

    while (itGremios.HaySiguiente())
    {
        Nat cantAcuerdosPrevios = obtenerCantAcuerdosPrevios(itGremios.Siguiente());
        if (mCantAcuerdosPrevios < cantAcuerdosPrevios)
        {
            mCantAcuerdosPrevios = cantAcuerdosPrevios;
            gremioConflictivo = itGremios.Siguiente();
        }
        itGremios.Avanzar();
    }
}

Conj<Nat> Temporada::obtenerGremiosConAcuerdos() const
{
    Conj<Nat> res;
    for (Nat j = 0; j < this->acuerdosPorGrupo.Longitud(); j++)
    {
        Lista<Acuerdo>::const_Iterador acuerdosDeGrupo = this->acuerdosPorGrupo[j].CrearIt();
        while (acuerdosDeGrupo.HaySiguiente())
        {
            Acuerdo ac = acuerdosDeGrupo.Siguiente();
            res.AgregarRapido(ac.obtenerGremio().obtenerIdGremio());
            acuerdosDeGrupo.Avanzar();
        }
    }
    return res;
}

Paritaria &Temporada::removerAcuerdo(const Gremio &gr)
{
    Lista<Acuerdo>::Iterador it = this->obtenerAcuerdosDeAliados(gr).CrearIt();
    while (it.Siguiente().obtenerGremio().obtenerIdGremio() != gr.obtenerIdGremio())
    {
        it.Avanzar();
    }
    Paritaria &res = it.Siguiente().obtenerParitaria();
    it.EliminarSiguiente();
    return res;
}

Temporada::~Temporada()
{

}

