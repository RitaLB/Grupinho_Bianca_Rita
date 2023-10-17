// Copyright [2018] <CRita Louro Barbosa>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    std::size_t size();
    //! metodo retorna tamanho maximo
    std::size_t max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular)
    int end_;  // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    end_  = -1;
    begin_ = 0;
    size_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    end_  = -1;
    begin_ = 0;
    size_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

// método enfileirar ( inserir dado )
template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw std::out_of_range("Fila cheia");
    } else {
        size_++;
        end_ = (end_ +1) % max_size_;
        contents[end_] = data;
    }
}

//! metodo desenfileirar ( remover ítem da fila)
// ? não funcionou com alternativa
template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Fila vazia");
    } else {
        size_--;
        int i2 = begin_;
        begin_ = (begin_ +1) % max_size_;
        return contents[i2];
    }
}

//! metodo retorna o ultimo (ítem de trás) da fila
template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("Fila vazia");
    } else {
       return contents[end_];
    }
}

//! metodo limpa a fila
template<typename T>
void structures::ArrayQueue<T>::clear() {
    end_  = -1;
    // ## ???? está certo?
    begin_ = 0;
    size_ = 0;
}

//! metodo retorna tamanho atual
template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

//! metodo retorna tamanho maximo
template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

//! metodo verifica se vazio
// está errado?
template<typename T>
bool structures::ArrayQueue<T>::empty() {
    if (size_ == 0) {
        return true;
    } else {
       return false;
    }
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    if (size_ == (max_size_)) {
        return true;
    } else {
       return false;
    }
}
