#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "array_stack.h"
#include <stdexcept>
#include <tuple>
#include "array_queue.h"
#include "questao2.h"

enum Select {
	FORA_TAG,
	DENTRO_TAG,
	DENTRO_COM_BARRA,
	DENTRO_SEM_BARRA,
	POP,
	PUSH
};

int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    
//     --------------------  PROBLEMA 1  -------------------------

    structures::ArrayStack<std::string>* pilha = new structures::ArrayStack<std::string>();   // pilha para a verificação de aninhamento
    
    Select select = FORA_TAG;
    std::string identificador;
    
    std::string line;
    std::ifstream myfile (xmlfilename);
    
    if (myfile.is_open()) {
    	while (getline(myfile, line)) {			   // lendo arquivo linha por linha
    		for (int i = 0; i < line.size(); i++) {    // lendo linha caracter por caracter
    			// lidando com o que está dentro de < >
    			if (line[i] == '<') {
    				select = DENTRO_TAG;
    				identificador = "";
    			} else if (line[i] == '>') {
    				if (select == DENTRO_COM_BARRA) 
    					select = POP;
    				else if (select == DENTRO_SEM_BARRA)
    					select = PUSH;
    			} else if (select == DENTRO_TAG) {
    				if (line[i] == '/') {
    					select = DENTRO_COM_BARRA;
    				} else {
    					identificador += line[i];
    					select = DENTRO_SEM_BARRA;
    				}
    			} else if (select == DENTRO_COM_BARRA || select == DENTRO_SEM_BARRA) {
    				identificador += line[i];
    			}

			// empilhando ou desempilhando palavras dentro de < >
    			if (select == PUSH) {
    				pilha->push(identificador);
    				select = FORA_TAG;
    			} else if (select == POP) {
    				if (pilha->size() == 0 || pilha->top() != identificador) {
    					// erro se, ao consultar o topo, a pilha estiver vazia ou se o identificador é diferente
    					std::cout << "erro" << std::endl;
    					return 0;
    				} else {
    					pilha->pop();
    					select = FORA_TAG;
    				}
    			}
    		}
    	}
    	
    	myfile.close();
    	
    	// erro se ao final da análise a pilha não estiver vazia
    	if (!pilha->empty()) {
    		std::cout << "erro" << std::endl;
    		return 0;
    	}
    	
    } else std::cout << "Erro ao abrir o arquivo" << std::endl;

	Questao2 Questao2(xmlfilename);

    return 0;
}
