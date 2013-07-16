#include "../include/Driver.h"
#include "../include/Utils.h"

#include <iostream>
#include <sstream>

#define     GREMIO_INEXISTENTE(g)       ("El gremio " + g + " no existe en el sistema.")
#define     GREMIO_YA_EXISTE(g)     ("El gremio " + g + " ya existe.")

Driver::Driver()
{
    sistema = new SistemaLaboral();
    temporada = NULL;
}

Driver::~Driver()
{
    if (sistema != NULL)
        delete sistema;

    if (temporada != NULL)
        delete temporada;
}

void Driver::agregarGremio(const NombreGremio &g, Nat cantAfiliados)
{
    if (puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_YA_EXISTE(g));

    Conj<Empresa> empresas;
    Nat idG = sistema->agregarGremio(empresas, cantAfiliados);

    puenteNombreId.Definir(g, idG);
    puenteIdNombre.Definir(idG, g);
}

void Driver::aliar(const NombreGremio &g1, const NombreGremio &g2)
{
    if (!puenteNombreId.Definido(g1))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g1));

    if (!puenteNombreId.Definido(g2))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g2));

    Nat idG1 = puenteNombreId.Significado(g1);
    Nat idG2 = puenteNombreId.Significado(g2);

    sistema->aliarGremios(idG1, idG2);
}

void Driver::agregarEmpresa(const NombreGremio &g, const Empresa &e)
{
    if (!puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g));

    Nat idG = puenteNombreId.Significado(g);

    sistema->agregarEmpresa(idG, e);
}

Conj<Empresa> Driver::empresas(const NombreGremio &g) const
{
    if (!puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g));

    Nat idG = puenteNombreId.Significado(g);

    Conj<Empresa> ret;
    Conj<Empresa>::Iterador it = sistema->obtenerEmpresas(idG).CrearIt();
    while (it.HaySiguiente())
    {
        ret.Agregar(it.Siguiente());
        it.Avanzar();
    }

    return ret;
}

Conj<NombreGremio> Driver::aliados(const NombreGremio &g) const
{
    if (!puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g));

    Nat idG = puenteNombreId.Significado(g);
    Conj<Nat> aliados = sistema->obtenerAliados(idG);

    Conj<NombreGremio> ret;
    Conj<Nat>::Iterador it = aliados.CrearIt();
    while (it.HaySiguiente())
    {
        ret.Agregar(puenteIdNombre.Significado(it.Siguiente()));
        it.Avanzar();
    }

    return ret;
}

void Driver::iniciar()
{
    temporada = new Temporada(*sistema);
}

void Driver::abrirParitaria(const NombreGremio &g, Nat piso, Nat tope)
{
    if (!puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g));

    Nat idG = puenteNombreId.Significado(g);

    Gremio gremio = sistema->obtenerGremio(idG);
    temporada->abrirParitaria(gremio, piso, tope, gremio.obtenerEmpresas());
}

void Driver::cerrarAcuerdo(const NombreGremio &g, Nat valor)
{
    if (!puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g));

    Nat idG = puenteNombreId.Significado(g);

    Gremio gremio = sistema->obtenerGremio(idG);
    temporada->cerrarAcuerdo(gremio, valor);
}

Conj<NombreGremio> Driver::paritarias() const
{
    Conj<NombreGremio> ret;
    Conj<Paritaria>::const_Iterador it = temporada->obtenerParitariasAbiertas().CrearIt();
    while (it.HaySiguiente())
    {
        Paritaria pa = it.Siguiente();
        ret.Agregar(puenteIdNombre.Significado(pa.obtenerGremio().obtenerIdGremio()));
        it.Avanzar();
    }

    return ret;
}

Conj<NombreGremio> Driver::acuerdos() const
{
    Conj<Nat> conj = temporada->obtenerGremiosConAcuerdos();

    Conj<NombreGremio> res;
    Conj<Nat>::Iterador acuerdos = conj.CrearIt();
    while (acuerdos.HaySiguiente())
    {
        res.AgregarRapido(puenteIdNombre.Significado(acuerdos.Siguiente()));
        acuerdos.Avanzar();
    }

    return res;
}

Nat Driver::piso(const NombreGremio &g) const
{
    if (!puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g));

    Nat idG = puenteNombreId.Significado(g);

    Conj<Paritaria>::const_Iterador it = temporada->obtenerParitariasAbiertas().CrearIt();
    Paritaria pa = it.Siguiente();
    while (pa.obtenerGremio().obtenerIdGremio() != idG)
    {
        it.Avanzar();
    }

    return it.Siguiente().obtenerPiso();
}

Nat Driver::tope(const NombreGremio &g) const
{
    if (!puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g));

    Nat idG = puenteNombreId.Significado(g);

    Conj<Paritaria>::const_Iterador it = temporada->obtenerParitariasAbiertas().CrearIt();
    Paritaria pa = it.Siguiente();
    while (pa.obtenerGremio().obtenerIdGremio() != idG)
    {
        it.Avanzar();
    }

    return it.Siguiente().obtenerTope();
}

Nat Driver::valor(const NombreGremio &g) const
{
    if (!puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g));

    Nat idG = puenteNombreId.Significado(g);

    Gremio gremio = sistema->obtenerGremio(idG);
    Lista<Acuerdo>::Iterador it = temporada->obtenerAcuerdosDeAliados(gremio).CrearIt();
    while (it.Siguiente().obtenerGremio().obtenerIdGrupo() != idG)
    {
        it.Avanzar();
    }

    return it.Siguiente().obtenerPorcentaje();
}

Nat Driver::acuerdosPrevios(const NombreGremio &g) const
{
    if (!puenteNombreId.Definido(g))
        TERMINAR_CON_ERROR(GREMIO_INEXISTENTE(g));

    Nat idG = puenteNombreId.Significado(g);

    Gremio gremio = sistema->obtenerGremio(idG);

    return temporada->obtenerCantAcuerdosPrevios(gremio);
}
