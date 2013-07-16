#include "../include/Gremio.h"

Gremio::Gremio(){

}

bool Gremio::operator != (const Gremio &p) const
{
    return this->idGremio!=p.idGremio;
}

void Gremio::guardarCantAfiliados(Nat cantidadAfiliados){
	this->cantAfiliados=cantidadAfiliados;
}

void Gremio::guardarEmpresas(Conj<String>& empresas){
	this->empresas=empresas;
}

void Gremio::agregarEmpresa(const Empresa &e){
	this->empresas.Agregar(e);
}

Gremio::Gremio(const Conj<Empresa>& es, const Nat cantidadAfiliados):empresas(es), cantAfiliados(cantidadAfiliados), idGremio(0), idGrupo(0) {

}

Conj<Empresa>& Gremio::obtenerEmpresas(){
	return this->empresas;
}

Gremio::Gremio(const Gremio& otro): empresas(otro.empresas), cantAfiliados(otro.cantAfiliados), idGremio(otro.idGremio), idGrupo(otro.idGrupo){

}

Nat Gremio::obtenerCantAfiliados() const{
	return this->cantAfiliados;
}

Nat Gremio::obtenerIdGremio() const{
	return this->idGremio;
}

Nat Gremio::obtenerIdGrupo() const{
	return this->idGrupo;
}

void Gremio::guardarIdGremio(const Nat nuevoId){
	this->idGremio=nuevoId;
}

void Gremio::guardarIdGrupo(const Nat nuevoId){
	this->idGrupo=nuevoId;
}

Gremio::~Gremio() {
	//no hay nada que liberar...
}

