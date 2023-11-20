//! Copyright [2023] Bianca Mazzuco Verzola e Rita Louro Barbosa

#include <vector>
#include <string>

namespace structures {

class Trie {
 public:
    Trie();

    void insert(std::string chave, unsigned long pos, unsigned long c);
    std::vector<std::string> keysWithPrefix(std::string prefix);

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
    NoTrie* get(std::string chave);

 private:
    NoTrie* insert(std::string chave, unsigned long pos, unsigned long c, NoTrie* node, int num);
    void collect(std::string chave, NoTrie* node, std::vector<std::string>& vetor);
    NoTrie* get(std::string chave, int num, NoTrie* node);

    NoTrie* root;
};

}  // namespace structures

// construtor
structures::Trie::Trie() {
    root = new NoTrie();
}

// insert
void structures::Trie::insert(std::string chave, unsigned long pos, unsigned long c) {
    root = insert(chave, pos, c, root, 0);
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

// get (busca)
structures::Trie::NoTrie* structures::Trie::get(std::string chave) {
    return get(chave, 0, root);
}

// get (busca) privado
structures::Trie::NoTrie* structures::Trie::get(std::string chave, int num, NoTrie* node) {
    if (node == nullptr)
        return nullptr;

    if (num == chave.size())
        return node;

    return get(chave, num+1, node->filhos()[chave[num]-97]);
}

// keys with prefix
std::vector<std::string> structures::Trie::keysWithPrefix(std::string prefix) {
    std::vector<std::string> vetor;
    NoTrie* node = get(prefix, 0, root);
    if (node != nullptr)
        collect(prefix, node, vetor);
    return vetor;
}

// collect
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