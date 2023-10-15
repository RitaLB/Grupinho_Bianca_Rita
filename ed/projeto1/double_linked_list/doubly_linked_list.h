//! Copyright [2023] Rita Louro Barbosa

namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
            explicit Node(const T& data) {
                data_ = data;
            }
            Node(const T& data, Node* next) {
                data_ = data;
                next_ = next;
            }
            Node(const T& data, Node* prev, Node* next) {
                data_ = data;
                next_ = next;
                prev_ = prev;
            }
            T& data() {  // getter: dado
                return data_;
            }
            const T& data() const {  // getter const: dado
                return data_;
            }
            Node* prev() {
                return prev_;
            }
            const Node* prev() const {
                return prev_;
            }
            void prev(Node* node) {
                prev_ = node;
            }
             Node* next() {  // getter: próximo
                return next_;
            }
            const Node* next() const {  // getter const: próximo
                return next_;
            }
            void next(Node* node) {  // setter: próximo
                next_ = node;
            }

     private:
            T data_;
            Node* prev_;
            Node* next_;
    };

    Node * posicao(std::size_t pos) {
     Node *p;
     if (pos < size()/2) {  // 1º metade
         p = head;
         for (std::size_t i = 0; i < pos; i++) {
             p = p->next();
         }
     } else {  // 2º metade
         p = tail;
         for (std::size_t i = size() - 1; i > pos; i--) {
             p = p->prev();
         }
     }
     return p;
    }

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures

// construtor
template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

// destrutor
template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList()  {
    clear();
}

// limpar lista
template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

// inserir no fim
template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    Node *novo = new Node(data, nullptr, nullptr);
    if (empty()) {
        head = novo;
    } else {
        novo->prev(tail);  // 1º
        tail->next(novo);  // 2º
    }
    tail = novo;  // 3º
    size_++;
}

// inserir no início
template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Memória cheia");
    }
    if (empty()) {
        head = novo;
        tail = novo;
        size_++;
    } else {
        novo->next(head);
        novo->prev(nullptr);
        head->prev(novo);
        head = novo;
        size_++;
    }
}

// inserir na posição
template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("index inválido");
        // Se estiver na frente
    } else if (index == 0) {
        return push_front(data);
        // se estiver atrás
    } else if (index == size_) {
        return push_back(data);
    } else {
        Node* novo = new Node(data);
        Node* p = posicao(index);
        p->prev()->next(novo);
        novo->next(p);
        novo->prev(p->prev());
        p->prev(novo);
        size_++;
    }
}

// inserir em ordem
template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    size_t i = 0;
    Node *p = head;
    while (i < size_ && p->data() < data) {
        p = p->next();
        i++;
    }
    return insert(data, i);
}

// retirar da posição
template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (index < 0 || index > size_ - 1) {
        throw std::out_of_range("index inválido");
    } else if (index == 0) {
        return pop_front();
    } else if (index == size_ - 1) {
        return pop_back();
    } else {
        Node *sai = posicao(index);
        sai->prev()->next(sai->next());
        sai->next()->prev(sai->prev());
        T aux = sai->data();
        delete sai;
        size_--;
        return aux;
    }
}

// retirar do fim
template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        Node *sai = tail;
        if (size_ == 1)
            head = nullptr;
        else
            sai->prev()->next(nullptr);
        tail = sai->prev();
        T aux = sai->data();
        delete sai;
        size_--;
        return aux;
    }
}

// retirar do início
template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        Node *sai = head;
        if (size_ == 1)
            tail = nullptr;
        else
            sai->next()->prev(nullptr);
        head = sai->next();
        T aux = sai->data();
        delete sai;
        size_--;
        return aux;
    }
}

// retira específico
template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    size_t i = 0;
    Node* p = head;
    while (p->data() != data && i < size_) {
        p = p->next();
        i++;
    }
    pop(i);
}

// lista vazia
template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return (size_ == 0);
}

// contém
template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    Node *temp = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (temp->data() == data) {
            return true;
        }
        temp = temp->next();
    }
    return false;
}

// posição do dado
template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    int i = 0;
    Node *temp = head;
    while (i < static_cast<int>(size_) && temp->data() != data) {
        temp = temp->next();
        i++;
    }
    return i;
}

// tamanho da lista
template<typename T>
size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}
// at
template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("index invalido");
    } else {
        Node *p = posicao(index);
        T& aux = p->data();
        return aux;
    }
}

// at const
template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("index invalido");
    } else {
        Node *p = posicao(index);
        const T& aux = p->data();
        return aux;
    }
}
