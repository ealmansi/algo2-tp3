#ifndef ACUERDO_H_
#define ACUERDO_H_

#include "Paritaria.h"

class Acuerdo {
public:
	Acuerdo(const Paritaria& pa, const Nat porcentaje, const Nat cantAcuerdosPrevios);
	Acuerdo(const Acuerdo& otro);
	Paritaria& obtenerParitaria();
	Gremio& obtenerGremio();
	Nat obtenerPorcentaje() const;
	Nat obtenerCantAcuerdosPrevios() const;
	~Acuerdo();
private:
	Paritaria paritaria;
	Nat cantAcuerdosPrevios;
	Nat porcentaje;
};

#endif /* ACUERDO_H_ */
