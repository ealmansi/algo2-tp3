#include "../include/Acuerdo.h"

Acuerdo::Acuerdo(const Paritaria& pa, const Nat porcentaje, const Nat cantAcuerdosPrevios):paritaria(pa), cantAcuerdosPrevios(cantAcuerdosPrevios), porcentaje(porcentaje){

}

Paritaria& Acuerdo::obtenerParitaria(){
	return this->paritaria;
}

Acuerdo::Acuerdo(const Acuerdo& otro):paritaria(otro.paritaria), cantAcuerdosPrevios(otro.cantAcuerdosPrevios), porcentaje(otro.porcentaje){

}

Gremio& Acuerdo::obtenerGremio(){
	return (this->paritaria).obtenerGremio();
}

Nat Acuerdo::obtenerPorcentaje() const{
	return this->porcentaje;
}

Nat Acuerdo::obtenerCantAcuerdosPrevios() const{
	return this->cantAcuerdosPrevios;
}

Acuerdo::~Acuerdo() {
	//no hay nada que liberar...
}

