//! Copyright [2023] Bianca Mazzuco Verzola e Rita Louro Barbosa

#include <vector>
#include <string>

namespace structures {

class Trie {
 public:
    Trie();
    ~Trie();
    void insert(std::string chave, unsigned long pos, unsigned long c);
    std::vector<std::string> keysWithPrefix(std::string prefix);

    class NoTrie {
     public:
        NoTrie() {
            letra_ = '\0';
            for (int i = 0; i < 26; ++i) {
                filhos_[i] = nullptr;
            }
        }

        NoTrie(char l) {
            letra_ = l;
            for (int i = 0; i < 26; ++i) {
                filhos_[i] = nullptr;
            }
        }

        char letra() {
            return letra_;
        }

        NoTrie** filhos() {
            return filhos_;
        }

        unsigned long pos() {
            return pos_;
        }

        void pos(unsigned long p) {
            pos_ = p;
        }

        unsigned long comprimento() {
            return comprimento_;
        }

        void comprimento(unsigned long c) {
            comprimento_ = c;
        }

        
     private:
        char letra_;        
        NoTrie *filhos_[26];
        unsigned long pos_;
        unsigned long comprimento_{0};  //se maior que zero, indica último caracter de uma palavra
    };

    NoTrie* get(std::string chave);

 private:
    NoTrie* insert(std::string chave, unsigned long pos, unsigned long c, NoTrie* node, int num);
    void collect(std::string chave, NoTrie* node, std::vector<std::string>& vetor);
    NoTrie* get(std::string chave, int num, NoTrie* node);

    void remove_all(NoTrie* node);  // nesse projeto, o método só foi usado no destrutor (para liberar a memória alocada)

    NoTrie* root;
};

}  // namespace structures

// construtor
structures::Trie::Trie() {
    root = new NoTrie();
}

// destrutor
structures::Trie::~Trie() {
    remove_all(root);
}

// remove o nó dado e todos seus filhos
void structures::Trie::remove_all(NoTrie* node) {
    for (int i = 0; i < 26; i++) {
        if (node->filhos()[i] != nullptr)
            remove_all(node->filhos()[i]);
    }

    delete node;
}

// insert
void structures::Trie::insert(std::string chave, unsigned long pos, unsigned long c) {
    insert(chave, pos, c, root, 0);
}

// insert privado
structures::Trie::NoTrie* structures::Trie::insert(std::string chave, unsigned long p, unsigned long c, NoTrie* node, int num) {
    if (node == nullptr)
        node = new NoTrie(chave[num-1]);
    if (num == chave.size()) { 
        node->pos(p);
        node->comprimento(c);
        return node; 
    }
    node->filhos()[chave[num]-97] = insert(chave, p, c, node->filhos()[chave[num]-97], num+1);
    return node;
}

// get --> busca o último nó da chave
structures::Trie::NoTrie* structures::Trie::get(std::string chave) {
    return get(chave, 0, root);
}

// get privado
structures::Trie::NoTrie* structures::Trie::get(std::string chave, int num, NoTrie* node) {
    if (node == nullptr)
        return nullptr;

    if (num == chave.size())
        return node;

    return get(chave, num+1, node->filhos()[chave[num]-97]);
}

// keys with prefix --> retorna vetor de strings das chaves que tem determinado prefixo
std::vector<std::string> structures::Trie::keysWithPrefix(std::string prefix) {
    std::vector<std::string> vetor;
    NoTrie* node = get(prefix, 0, root);
    if (node != nullptr)
        collect(prefix, node, vetor);
    return vetor;
}

/* collect (coleta a chave se seu nó for o nonódo que representa o fim de uma palavra,
            colocando-a no vetor, caso contrário, chama o método recursivamente para
            os filhos do nó --> dessa forma, são coletadas todas as chaves que um dos
            seus nós é o nó passado na primeira chamada do método)    
*/
void structures::Trie::collect(std::string chave, NoTrie* node, std::vector<std::string>& vetor) {
    if (node->comprimento())
        vetor.push_back(chave);

    for (int i = 0; i < 26; i++) {
        if (node->filhos()[i] != nullptr) {
            std::string nova_chave;
            nova_chave = chave + node->filhos()[i]->letra();
            collect(nova_chave, node->filhos()[i], vetor);
        }
    }
}
