#ifndef SISTEMALABORAL_H_
#define SISTEMALABORAL_H_

#include "Gremio.h"
#include "Tipos.h"

class SistemaLaboral {
public:
	SistemaLaboral();
	Nat agregarGremio(const Conj<Empresa>& es, const Nat cantAfiliados);
	void aliarGremios(const Nat idGr1, const Nat idGr2);
	Conj<Nat> obtenerAliados(const Nat idGremio) const;
	Conj<Gremio> obtenerGremios() const;
	Nat obtenerCantidadGrupos() const;
	~SistemaLaboral();

	//agregados por driver
	void agregarEmpresa(const Nat &idG, const Empresa &e);
	Gremio obtenerGremio(Nat idG);
private:
	//atributos
	Vector<Gremio> sl;

	//metodos
	Nat maximoIdGrupo() const;
};

#endif /* SISTEMALABORAL_H_ */
