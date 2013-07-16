#include "../Utils.h"
#include "../implementaciones/List.h"
#ifndef CONJUNTO_H_
#define CONJUNTO_H_

using namespace std;

template<typename T>
class Conjunto{
public:
	Conjunto();
	Conjunto(const Conjunto<T>& otro);
	void add(T& value);
	bool belongs(T& value);
	void remove(T& value);
	~Conjunto();
private:
	List<T> listaSuby;
	nat cardinal;
};

template<typename T>
Conjunto<T>::Conjunto() {
	//se inicializa sola la lista Subyacente
	this->cardinal=0;
}

template<typename T>
Conjunto<T>::Conjunto(const Conjunto<T>& otro) {
	this->cardinal=otro.cardinal;
	//copiar lista, si lista tiene constructor por copia el = las copia?
}

template<typename T>
void Conjunto<T>::add(T& value) {
	this->listaSuby.addBack(value);
	this->cardinal++;
}

template<typename T>
bool Conjunto<T>::belongs(T& target) {
	if(this->listaSuby.getSize()>0){
		this->listaSuby.resetFirst();
		bool flag=false;
		while((this->listaSuby.hasNext()) && (!flag)){
			T& elem = this->listaSuby.getNext();
			flag = flag && (elem==target);
		}
		return flag;
	}else{
		return false;
	}
}

template<typename T>
void Conjunto<T>::remove(T& value) {
	//si esta, cardinal--;
	if(this->listaSuby.getSize()>0){
			this->listaSuby.resetFirst();
			bool flag=false;
			while((this->listaSuby.hasNext()) && (!flag)){
				T& elem = this->listaSuby.getNext();
				flag = flag && (elem==target);
			}
			if(flag){
				this->
				this->cardinal--;
			}
		}else{
			return false;
		}

}

template<typename T>
Conjunto<T>::~Conjunto() {
	//nada que liberar, el destructor de la lista se llama solo, no?
}

#endif /* CONJUNTO_H_ */
