#include "../include/SistemaLaboral.h"

#define     MIN(a,b)    (((a) < (b))?((a)):((b)))
#define     MAX(a,b)    (((a) < (b))?((a)):((b)))

SistemaLaboral::SistemaLaboral()
{

}

void SistemaLaboral::agregarEmpresa(const Nat &idG, const Empresa &e)
{
    this->sl[idG].agregarEmpresa(e);
}

Nat SistemaLaboral::agregarGremio(const Conj<Empresa> &es, const Nat cantAfiliados)
{
    Nat idGremio = sl.Longitud();
    Nat idGrupo = (sl.Longitud() == 0) ? 0 : (maximoIdGrupo() + 1);

    Gremio nuevoGremio(es, cantAfiliados);
    nuevoGremio.guardarIdGremio(idGremio);
    nuevoGremio.guardarIdGrupo(idGrupo);

    sl.AgregarAtras(nuevoGremio);

    return idGremio;
}

Conj<Empresa> &SistemaLaboral::obtenerEmpresas(const Nat &idG)
{
    return this->sl[idG].obtenerEmpresas();
}

Gremio SistemaLaboral::obtenerGremio(Nat idG)
{
    return this->sl[idG];
}

void SistemaLaboral::aliarGremios(const Nat idGr1, const Nat idGr2)
{
    Nat idGrupo1 = sl[idGr1].obtenerIdGrupo();
    Nat idGrupo2 = sl[idGr2].obtenerIdGrupo();

    if (idGrupo1 != idGrupo2)
    {
        Nat idMenor = MIN(idGrupo1, idGrupo2);
        Nat idMayor = MAX(idGrupo1, idGrupo2);

        for (Nat i = 0; i < sl.Longitud(); i++)
        {
            Nat idGrupoActual = sl[i].obtenerIdGrupo();

            if (idMayor == idGrupoActual)
                sl[i].guardarIdGrupo(idMenor);

            else if (idMayor < idGrupoActual)
                sl[i].guardarIdGrupo(idGrupoActual - 1);
        }
    }
}

Conj<Gremio> SistemaLaboral::obtenerGremios() const
{
    Conj<Gremio> result;
    for (Nat i = 0; i < sl.Longitud(); i++)
        result.AgregarRapido(sl[i]);

    return result;
}

Conj<Nat> SistemaLaboral::obtenerAliados(const Nat idGremio) const
{
    Nat idGrupoTarget = sl[idGremio].obtenerIdGrupo();

    Conj<Nat> result;
    for (Nat i = 0; i < sl.Longitud(); i++)
        if ((i != idGremio) && (sl[i].obtenerIdGrupo() == idGrupoTarget))
            result.AgregarRapido(i);

    return result;
}

Nat SistemaLaboral::obtenerCantidadGrupos() const
{
    return (sl.Longitud() == 0) ? 0 : (maximoIdGrupo() + 1);
}

Nat SistemaLaboral::maximoIdGrupo() const
{
    Nat max = 0;
    for (Nat i = 0; i < sl.Longitud(); i++)
        max = MAX(max, sl[i].obtenerIdGrupo());

    return max;
}

SistemaLaboral::~SistemaLaboral()
{

}
