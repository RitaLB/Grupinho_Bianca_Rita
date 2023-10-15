#include <iostream>
#include <string>
#include <fstream>
#include "array_stack.h"
#include <stdexcept>

int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    
    structures::ArrayStack<std::string>* pilha = new structures::ArrayStack<std::string>();
    
    int select = 0;
    std::string palavra;
    
    std::string line;
    std::ifstream myfile (xmlfilename);
    if (myfile.is_open()) {
    	while (getline(myfile, line)) {
    		for (int i = 0; i < line.size(); i++) {
    			//std::cout << "select: " << select << std::endl;
    			if (line[i] == '<') {
    				select = 1;
    				palavra = "";
    				//std::cout << "abre <: " << palavra << std::endl;
    			} else if (line[i] == '>') {
    				if (select == 2) 
    					select = 4;
    				else if (select == 3)
    					select = 5;
    				//std::cout << "fecha >: " << palavra << std::endl;
    			} else if (select == 1) {
    				if (line[i] == '/') {
    					select = 2;
    					//std::cout << "com barra: " << palavra << std::endl;
    				} else {
    					palavra += line[i];
    					select = 3;
    					//std::cout << "sem barra: " << palavra << std::endl;
    				}
    			} else if (select == 2 || select == 3) {
    				palavra += line[i];
    				//std::cout << "add: " << palavra << std::endl;
    			}
    			if (select == 5) {
    				pilha->push(palavra);
    				//std::cout << "palavra empilhada: " << palavra << std::endl;
    				//std::cout << "top: " << pilha->top() << std::endl;
    				select = 0;
    			} else if (select == 4) {
    				if (pilha->top() == palavra) {
    					pilha->pop();
    					//std::cout << "pop: " << palavra << std::endl;
    				} else {
    					std::cout << "erro" << std::endl;
    					return 0;
    				}
    				select = 0;
    			}
    				
    		}
    		
    	}
    	
    	myfile.close();
    	if (!pilha->empty()) {
    		std::cout << "erro" << std::endl;
    		return 0;
    	}
    	
    } else std::cout << "Erro ao abrir o arquivo" << std::endl;

    //std::cout << xmlfilename << std::endl;  // esta linha deve ser removida

    return 0;
}
