// Copyright [2023] <Rita Louro>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <stdexcept>

namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

} //  namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
  max_size_ = DEFAULT_MAX;
  contents = new T[max_size_];
  size_ = 0;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
  max_size_ = DEFAULT_MAX;
  contents = new T[max_size];
  size_ = 0;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
  delete [] contents;
}

// método limpar lista (voltar fim para -1)
template<typename T>
void structures::ArrayList<T>::clear() {
  size_= 0;
}

//! metodo insere dado no fim da lista
template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
	if (this->full()) throw std::out_of_range("Lista cheia");

	contents[size_] = data;
	size_++;
}
    // não deveria incrementar end_ também? não tem end nesse modelo
    // qual a diferença de end_ para size_ ??
    // end_ cumpriria a msm função do size

//! metodo insere item no início da fila
template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
	if (this->full()) throw std::out_of_range("Lista cheia");

	size_++;
	// mover ítens do início para o fim
	for (size_t i = (size_-1); i > 0; i--) {
		contents[i] = contents[i-1];
	}
	// add dadp
	contents[0] = data;
}

//! metodo insere ítem em posição escolhida (index)
template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
  if (this->full()) throw std::out_of_range("Lista Cheia");

	if ((static_cast<int>(index) < 0) || (index > size_))
	    throw std::out_of_range("passou do range maximo da lista");

	size_++;
	for (size_t i = (size_-1); i > index; i--) {
		contents[i] = contents[i-1];
	}
	contents[index] = data;
}

//! metodo insere ordenado
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
	if (this->full()) throw std::out_of_range("Lista Cheia");

	if (static_cast<int>(size_) > 0) {
		for (size_t i = 0; i < size_; i++) {
			if (contents[i] > data) {
				insert(data, i);
				return;
			}
		}
		this->push_back(data);

	} else {
		this->insert(data, 0);
	}
}

//! metodo retira de posição específica
template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
	if (this->empty()) throw std::out_of_range("lista vazia");

	if ((static_cast<int>(index) < 0) || (index >= size_))
	    throw std::out_of_range("Index fora do rage");

	T dado = contents[index];
	size_--;
	for (size_t i = index; i < size_; i++) {
		contents[i] = contents[i+1];
	}

	return dado;
}

// metodo retira do final
template<typename T>
T structures::ArrayList<T>::pop_back() {
	if (this->empty()) throw std::out_of_range("lista vazia");

	size_--;

	return contents[size_];
}

// metodo retira da frente
template<typename T>
T structures::ArrayList<T>::pop_front() {
	if (this->empty()) throw std::out_of_range("lista vazia");

	T dado = contents[0];

	size_--;
	for (size_t i = 0; i < size_; i++) {
		contents[i] = contents[i+1];
	}

	return dado;
}

// metodo remove primeiro ítem igual ao fornecido
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
	if (this->empty()) throw std::out_of_range("Lista vazia");

	for (size_t i = 0; i < size_; i++) {
		if (contents[i] == data) {
			this->pop(i);
			return;
		}
	}
}

// metodo verifica se está cheio
template<typename T>
bool structures::ArrayList<T>::full() const {
	if (size_ == max_size_)
	    return true;
	else
	    return false;
}

//  metodo verifica se está vazio

template<typename T>
bool structures::ArrayList<T>::empty() const {
	if (size_ == 0)
	    return true;
	else
	    return false;
}

// metodo verifica se ítem existe na lista
template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
	if (this->empty()) throw std::out_of_range("lista vazia");

	for (size_t i = 0; i < size_; i++) {
		if (contents[i] == data) {
			return true;
		}
	}
	return false;
}
// metodo verifica posição de ítem em uma fila
template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
	if (this->empty()) throw std::out_of_range("lista vazia:");

	for (size_t i = 0; i < size_; i++) {
		if (contents[i] == data) {
			return i;
		}
	}
	return size_;
}

// verifica tamanho da lista
template<typename T>
std::size_t structures::ArrayList<T>::size() const {
	return size_;
}

// verifica variável max_size
template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
	return max_size_;
}

// verifica se index fornecido está no range da lista
template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
	if (this->empty()) throw std::out_of_range("lista vazia");
	if (index >= size_) throw std::out_of_range("index fora do range");
	return contents[index];
}

// descrição da disciplina
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
	if (static_cast<int>(index) < 0) {
		return contents[0];
	}
	return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
	if (this->empty()) throw std::out_of_range("lista vazia");
	if (index >= size_) throw std::out_of_range("index fora do range");
	return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
	if (static_cast<int>(index) < 0) {
		return contents[0];
	}
	return contents[index];
}
