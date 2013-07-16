#include"../Utils.h"

#ifndef VECTOR_H_
#define VECTOR_H_

#define initialCapacity 10

using namespace std;

template<typename T>
class Vector{
public:
	Vector();
	Vector(const Vector<T>& otro);
	void set(nat index, T& value);
	void addBack(T& value);
	T& get(nat index) const;
	nat getCapacity() const;
	nat getLastUsedIndex() const;
	~Vector();
private:
	T* subyArray;
	nat capacity;
	nat lastUsedIndex;
	void resizeToDoubleCapacity();
};


//impl
template<typename T>
Vector<T>::Vector(){
	this->capacity=initialCapacity;
	this->lastUsedIndex=0;
	this->subyArray=new T[this->capacity];
}

template<typename T>
nat Vector<T>::getCapacity() const{
	return this->capacity;
}

template<typename T>
nat Vector<T>::getLastUsedIndex() const{
	return this->lastUsedIndex;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& otro){
	this();//inicializo todo normal y copio los elementos
	for(nat j=0;j<otro.getLastUsedIndex();j++){
		this->addBack(otro.get(j));
	}
}

/**
 * Pre: index en rango 0<index<getCapacity()
 */
template<typename T>
void Vector<T>::set(nat index, T& value){
	this->subyArray[index]=value;
}

/**
 * Pre: index en rango 0<index<getCapacity()
 */
template<typename T>
T& Vector<T>::get(nat index) const{
	return this->subyArray[index];
}

template<typename T>
void Vector<T>::addBack(T& value){
	//si no hay espacio, duplico la capacidad.
	if(this->lastUsedIndex+1>=this->capacity){
		resizeToDoubleCapacity();
	}
	//lo pongo atras en lastUsedIndex+1
	this->set(++this->lastUsedIndex, value);
}

template<typename T>
void Vector<T>::resizeToDoubleCapacity(){
	nat newCapacity= 2*this->getCapacity();
	T* newSubyArray=new T[newCapacity];
	//copiar lo viejo al nuevo arreglo mas grande
	for(nat j=0;j<this->getLastUsedIndex();j++){
		newSubyArray[j]=this->subyArray[j];
	}
	//guardo ref del viejo arreglo subyacente
	T* oldArrayToDelete = this->subyArray;
	//pongo el nuevo arreglo subyacente en su lugar
	this->subyArray=newSubyArray;
	//elimino el viejo arreglo
	delete[] oldArrayToDelete;
	this->capacity=newCapacity;
	//lastusedindex es el mismo...
}

template<typename T>
Vector<T>::~Vector(){
	delete[] this->subyArray;
}

#endif /* VECTOR_H_ */
