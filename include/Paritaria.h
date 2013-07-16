#ifndef PARITARIA_H_
#define PARITARIA_H_

#include "Gremio.h"

class Paritaria {
public:
	Paritaria();
	Paritaria(const Gremio& gr, const Nat piso, const Nat tope);
	Paritaria(const Paritaria& otra);
	Gremio& obtenerGremio();
	Nat obtenerPiso() const;
	Nat obtenerTope() const;
	~Paritaria();
	bool operator !=(const Paritaria &p) const;
private:
	Gremio gremio;
	Nat piso;
	Nat tope;
};

#endif /* PARITARIA_H_ */
