#include <iostream>
#include <fstream>
#include "trie.h"

int main() {
    
    using namespace std;

    structures::Trie* arvore = new structures::Trie();

    string filename;
    string word;

    cin >> filename;  // entrada

    ifstream arquivo(filename);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return 1;
    }


    char caractere;
    int estado = 0;
    char chave[];
    int cont_linha;
    cont_pos = 0;

    while (arquivo.get(caractere)) {
        if (caractere == "[") {
            //char* chave = new char[];
            estado = 1;
            cont_linha = 0;
        } else if (caractere == "]") {
            estado = 0;
            arvore->insert(chave, cont_pos, std::strlen(chave));  // mudar comprimento p ser automatico no arquivo da trie
            char = [];
        } else if (estado == 1) {
            chave[std::strlen(chave)] = caractere;
        } else {
            cont_linha++;
        }
        cont_pos++;
    }

    arquivo.close();
    

    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        cout << word << endl;
    }

    return 0;
}

    return 0;
}