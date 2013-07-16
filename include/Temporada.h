#ifndef TEMPORADA_H_
#define TEMPORADA_H_

#include "SistemaLaboral.h"
#include "Paritaria.h"
#include "Acuerdo.h"

class Temporada {
public:
	Temporada(SistemaLaboral& sl);
	void abrirParitaria(const Gremio gr, const Nat piso, const Nat techo, const Conj<Empresa> es);
	void cerrarAcuerdo(const Gremio gr, const Nat porcentaje);
	void reabrir(const Gremio gr);
	Conj<Gremio> gremios() const;
	bool enParitarias(const Gremio gr) const;
	Conj<Gremio> gremiosNegociando() const;
	Conj<Empresa> empresasNegociando() const;
	Nat trabajadoresNegociando() const;
	void gremioConflictivo(Gremio& gremioConflictivo) const;
	~Temporada();

	//necesarias por driver(nuevas o hechas publicas)
	const Conj<Paritaria>& obtenerParitariasAbiertas() const;
	Nat obtenerCantAcuerdosPrevios(const Gremio& gr) const;
	Conj<Nat> obtenerGremiosConAcuerdos() const;
	Lista<Acuerdo>& obtenerAcuerdosDeAliados(const Gremio& gr);
private:
	//atributos
	SistemaLaboral sistema;
	Conj<Paritaria> paritariasAbiertas;
	Vector<Lista<Acuerdo> > acuerdosPorGrupo;
	Vector<Nat> cantAcuerdosPrevios;

	//metodos
	void inicializarAcuerdosPorGrupos();
	void inicializarCantAcuerdosPrevios();
	Paritaria& removerAcuerdo(const Gremio& gr);
	void agregarParitaria(Paritaria pa);
	void removerParitaria(const Gremio& gr, Paritaria& res);
};

#endif /* TEMPORADA_H_ */
