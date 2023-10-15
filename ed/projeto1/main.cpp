#include <iostream>
#include <string>
#include <fstream>
#include "array_stack.h"
#include <stdexcept>

int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    
    structures::ArrayStack<std::string>* pilha;
    
    int select = 0;
    std::string palavra;
    
    std::string line;
    std::ifstream myfile (xmlfilename);
    if (myfile.is_open()) {
    	while (getline(myfile, line)) {
    		for (int i = 0; i < line.size(); i++) {
    			if (line[i] == '<') {
    				select = 1;
    				palavra = "";
    			} else if (line[i] == '>') {
    				if (select == 2) 
    					select = 4;
    				else if (select == 3)
    					select = 5;
    			}
    			if (select = 1) {
    				if (line[i] == '/') 
    					select = 2;
    				else 
    					select = 3;
    			} else if (select == 2 || select == 3) {
    				palavra += line[i];
    			}
    			if (select == 5) {
    				pilha->push(palavra);
    			} else if (select == 4) {
    				if (pilha->top() == palavra) {
    					pilha->pop();
    				} else {
    					throw "erro";
    				}
    			}
    				
    		}
    		
    	}
    	
    	myfile.close();
    	if (!pilha->empty()) {
    		throw "erro";
    	}
    	
    } else std::cout << "Erro ao abrir o arquivo" << std::endl;

    //std::cout << xmlfilename << std::endl;  // esta linha deve ser removida

    return 0;
}

