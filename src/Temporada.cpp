#include "../include/Temporada.h"

Temporada::Temporada(SistemaLaboral &sl): sistema(sl)
{
    inicializarAcuerdosPorGrupos();
    inicializarCantAcuerdosPrevios();
}

void Temporada::inicializarAcuerdosPorGrupos()
{
    Nat indice = 0;
    Nat cantGrupos = this->sistema.obtenerCantidadGrupos();
    while (indice < cantGrupos)
    {
        this->acuerdosPorGrupo.AgregarAtras(Lista<Acuerdo>());
        indice++;
    }
}

void Temporada::inicializarCantAcuerdosPrevios()
{
    Nat indice = 0;
    Nat cantGrupos = this->sistema.obtenerGremios().Cardinal();
    while (indice < cantGrupos)
    {
        this->cantAcuerdosPrevios.AgregarAtras(0);
        indice++;
    }
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
    {
        removerAcuerdo(gr);
    }
    agregarParitaria(Paritaria(gr, piso, techo));
}

void Temporada::cerrarAcuerdo(const Gremio gr, const Nat porcentaje)
{
    Lista<Acuerdo>::Iterador it = obtenerAcuerdosDeAliados(gr).CrearIt();
    while ( (it.HaySiguiente()) && (it.Siguiente().obtenerPorcentaje() < porcentaje) )
    {
        agregarParitaria(it.Siguiente().obtenerParitaria());
        it.EliminarSiguiente();
        if (it.HaySiguiente()) //agregue esto por las moscas. si borro el ultimo nos vimos en disney basicamente, no?(avanzar tiene assert hay siguiente, ver impl soporte)
        {
            it.Avanzar();//TODO ver que pasa si borramos el ultimo , esto no vuela sangrientamente porque no vale HaySiguiente? SI. Fixed con if.
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
    Paritaria pa = it.Siguiente();
    while ((it.HaySiguiente()) && (pa.obtenerGremio().obtenerIdGremio() != gr.obtenerIdGremio()))
    {
        it.Avanzar();
        pa = it.Siguiente();
    }
    return it.HaySiguiente();
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
    Paritaria pa = it.Siguiente();
    while (pa.obtenerGremio().obtenerIdGremio() != gr.obtenerIdGremio())
    {
        it.Avanzar();
        pa = it.Siguiente();
    }
    res = it.Siguiente();
    it.EliminarSiguiente();
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

