//! Copyright [2023] Bianca Mazzuco Verzola e Rita Louro Barbosa

#include <cstring>
#include <vector>
#include <string>

namespace structures {

class Trie {
 public:
    Trie();

    void insert(char chave[], unsigned long pos, unsigned long c);
    std::vector<std::string> keysWithPrefix(char prefix[]);

 private:
    class NoTrie {  // Elemento
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
        
        NoTrie(char l, unsigned long p, unsigned long c) {
            letra_ = l;
            for (int i = 0; i < 26; ++i) {
                filhos_[i] = nullptr;
            }
            pos_ = p;
            comprimento_ = c;
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

    NoTrie* insert(char chave[], unsigned long pos, unsigned long c, NoTrie* node, int num);
    void collect(char chave[], NoTrie* node, std::vector<std::string>& vetor);
    NoTrie* get(char chave[], int num, NoTrie* node);

    NoTrie* root;
};

}  // namespace structures

// construtor
structures::Trie::Trie() {
    root = new NoTrie();
}

// insert
void structures::Trie::insert(char chave[], unsigned long pos, unsigned long c) {
    root = insert(chave, pos, c, root, 0);
}

// insert privado
structures::Trie::NoTrie* structures::Trie::insert(char chave[], unsigned long p, unsigned long c, NoTrie* node, int num) {
    if (node == nullptr)
        node = new NoTrie(chave[num-1]);
    if (num == std::strlen(chave)) { 
        node->pos(p);
        node->comprimento(c);
        return node; 
    }
    node->filhos()[chave[num]-97] = insert(chave, p, c, node->filhos()[chave[num]-97], num+1);
    return node;
}

// get (busca)
structures::Trie::NoTrie* structures::Trie::get(char chave[], int num, NoTrie* node) {
    if (node == nullptr) 
        return nullptr;
    if (num == std::strlen(chave))
        return node;

    return get(chave, num+1, node->filhos()[chave[num]-97]);
}

// keys with prefix
std::vector<std::string> structures::Trie::keysWithPrefix(char prefix[]) {
    std::vector<std::string> vetor;
    collect(prefix, get(prefix, 0, root), vetor);
    return vetor;
}

// collect
void structures::Trie::collect(char chave[], NoTrie* node, std::vector<std::string>& vetor) {
    size_t len = std::strlen(chave);
    if (node->comprimento())
        vetor.push_back(chave);

    for (int i = 0; i < 26; i++) {
        if (node->filhos()[i] != nullptr) {
            char* novaChave = new char[len + 2];  // +2 para a letra e o caractere nulo
            std::strcpy(novaChave, chave);
            novaChave[len] = node->filhos()[i]->letra();
            novaChave[len + 1] = '\0';  // Garante que a string tenha terminação nula
            collect(novaChave, node->filhos()[i], vetor);
            delete[] novaChave;  // Libera a memória alocada dinamicamente
        }
    }
}