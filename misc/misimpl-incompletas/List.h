#include "../Utils.h"
#ifndef LIST_H_
#define LIST_H_

using namespace std;

template<typename T>
class List {
public:
	List();
	void addBack(T& value);
	nat getSize();
	void resetFirst();
	void deleteNext();//pre hasNext
	T& getNext();//pre hasNext
	bool hasNext();
	~List();
private:
	struct Nodo{
		T data;
		Nodo* nextPtr;
	};

	Nodo* current;
	Nodo* first;
	nat size;
};

template<typename T>
List<T>::List() {
	this->first=NULL;
	this->current=this->first;
	this->size=0;
}

template<typename T>
void List<T>::addBack(T& value) {

}

template<typename T>
nat List<T>::getSize() {
	return this->size;
}

template<typename T>
void List<T>::resetFirst() {
	this->current=this->first;
}

template<typename T>
void List<T>::deleteNext() {

}

template<typename T>
T& List<T>::getNext() {
	return current->data;
	current=current->nextPtr;
}

template<typename T>
bool List<T>::hasNext() {
	if(this->size>0){
		return (this->current->nextPtr!=NULL);
	}else{
		return false;
	}
}

template<typename T>
List<T>::~List() {
	//TODO eliminar nodos.
}

#endif /* LIST_H_ */
