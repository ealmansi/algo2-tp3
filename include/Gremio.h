#ifndef GREMIO_H_
#define GREMIO_H_

#include "Tipos.h"
#include "../lib/aed2.h"

class Gremio {
	public:
		Gremio();
		Gremio(const Conj<Empresa>& es, const Nat cantidadAfiliados);
		Gremio(const Gremio& otro);
		Conj<Empresa>& obtenerEmpresas();
		Nat obtenerCantAfiliados() const;
		Nat obtenerIdGremio() const;
		Nat obtenerIdGrupo() const;
		void guardarIdGremio(const Nat nuevoId);
		void guardarIdGrupo(const Nat nuevoId);
		void guardarCantAfiliados(Nat cantidadAfiliados);
		void guardarEmpresas(Conj<String>& empresas);
		~Gremio();
		bool operator !=(const Gremio &p) const;

		//agregados por driver
		void agregarEmpresa(const Empresa &e);
	private:
		Conj<String> empresas;
		Nat cantAfiliados;
		Nat idGremio;
		Nat idGrupo;
};

#endif /* GREMIO_H_ */
