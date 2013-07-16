#include "../include/SistemaLaboral.h"

SistemaLaboral::SistemaLaboral(){

}

void SistemaLaboral::agregarEmpresa(const Nat &idG, const Empresa &e){
	this->sl[idG].agregarEmpresa(e);
}

Nat SistemaLaboral::agregarGremio(const Conj<Empresa>& es, const Nat cantAfiliados){
	//idgrupo fixes
	//+1 fix
	//gremios vacios fix
	Nat idGremio=sl.Longitud();//siempre es uno mas que el ultimo, ok.
	Nat idGrupo=maximoIdGrupo();
	if(idGremio==0){
		//sl esta vacio...
		//entonces el idGrupo tambien es 0...porque arrancan a numerarse asi.
	}else{
		//hay al menos otro gremio en el sistema
		//si pongo siempre maximoIdGrupo me quedan el nuevo aliado implicitamente con los del ultimo grupo. +1 Fix, esto hace que cada nuevo gremio tenga su "particion" unica implicitamente.
		idGrupo++;
	}

	Gremio nuevoGremio(es, cantAfiliados);
	nuevoGremio.guardarIdGremio(idGremio);
	nuevoGremio.guardarIdGrupo(idGrupo);

	sl.AgregarAtras(nuevoGremio);

	return idGremio;
}

Conj<Empresa>& SistemaLaboral::obtenerEmpresas(const Nat &idG){
	return this->sl[idG].obtenerEmpresas();
}

Gremio SistemaLaboral::obtenerGremio(Nat idG){
	return this->sl[idG];
}

void SistemaLaboral::aliarGremios(const Nat idGr1, const Nat idGr2){
	Nat idGrupo1 = sl[idGr1].obtenerIdGrupo();
	Nat idGrupo2 = sl[idGr2].obtenerIdGrupo();

	if(idGrupo1!=idGrupo2){
		Nat idMenor = min(idGrupo1, idGrupo2);
		Nat idMayor = max(idGrupo1, idGrupo2);
		Nat indice=0;
		while(indice<sl.Longitud()){
			Nat idGrupoActual = sl[indice].obtenerIdGrupo();
			if(idMayor == idGrupoActual){
				sl[indice].guardarIdGrupo(idMenor);
			}else{
				if(idMayor<idGrupoActual){
					sl[indice].guardarIdGrupo(idGrupoActual-1);
				}
			}
			indice++;
		}
	}
}

Conj<Gremio> SistemaLaboral::obtenerGremios() const{
	Conj<Gremio> result;
	for(Nat i=0;i<sl.Longitud();i++){
		result.AgregarRapido(sl[i]);
	}
	return result;
}

Conj<Nat> SistemaLaboral::obtenerAliados(const Nat idGremio) const{
	// condicion de while a if fix
	Conj<Nat> result;
	Nat indice=0;
	Nat idGrupoTarget=sl[idGremio].obtenerIdGrupo();
	while(indice < sl.Longitud()){
		if((indice!=idGremio) && (sl[indice].obtenerIdGrupo()==idGrupoTarget)){
			result.AgregarRapido(indice);
		}
		indice++;
	}
	return result;
}

Nat SistemaLaboral::obtenerCantidadGrupos() const{
	//* gremios vacios fix
	//* plus one fix.
	return (sl.Longitud()>0)? this->maximoIdGrupo() + 1 : 0;
}

Nat SistemaLaboral::maximoIdGrupo() const {
	Nat max=0;
	for(Nat j=0; j<sl.Longitud(); j++)
	{
	    if(max<sl[j].obtenerIdGrupo()){
	    	max=sl[j].obtenerIdGrupo();
	    }
	}
	return max;
}

SistemaLaboral::~SistemaLaboral() {

}
