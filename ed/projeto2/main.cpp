//! Copyright [2023] Bianca Mazzuco Verzola e Rita Louro Barbosa

#include <iostream>
#include <fstream>
#include "trie.h"

int main() {
    
    using namespace std;

    structures::Trie* arvore = new structures::Trie();

    string filename;
    string word;

    cin >> filename;  // entrada

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return 1;
    }


    int estado = 0;
    string chave;
    int cont_comprimento;
    int cont_pos = 0;
    int pos;

    string line;

    while (getline(file, line)) {			   // lendo arquivo linha por linha
        for (int i = 0; i < line.size(); i++) {
            if (estado == 0 && line[i] == '[') {
                cont_comprimento = 0;
                chave = "";
                pos = cont_pos;
                estado = 1;
            } else if (estado == 1 && line[i] == ']') {
                estado = 2;
            } else if (estado == 1) {
                chave += line[i];
            }
            cont_comprimento++;
            cont_pos++;
        }
        arvore->insert(chave, pos, cont_comprimento);
        cont_pos++;
        estado = 0;
    }

    file.close();

    while (1) {  // leitura das palavras ate' encontrar "0"
        string word;
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        std::vector<std::string> words = arvore->keysWithPrefix(word);
        if (words.size()) {
            cout << word << " is prefix of " << words.size() << " words" << endl;

            structures::Trie::NoTrie* node = arvore->get(word);
            if (node != nullptr && node->comprimento())
                cout << word << " is at (" << node->pos() << "," << node->comprimento() << ")" << endl;

        } else {
            cout << word << " is not prefix" << endl;
        }
    }
    
    delete arvore;

    return 0;
}
