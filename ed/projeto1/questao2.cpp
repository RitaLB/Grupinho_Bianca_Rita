
#include <iostream>
#include <string>
#include <fstream>
#include "array_stack.h"
#include <stdexcept>

class Questao2 {
 public:
    //! construtor com parametro cml
    explicit Questao2(std::string filename);

 private:
    void ler_arquivo(std::string filename);
    void salvar_dado(std::string categoria, std::string dado);

    int altura;
    int largura;

    int x;
    int y;
};

Questao2::Questao2(std::string filename) {
    ler_arquivo(filename);
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "largura = " << largura << std::endl;
    std::cout << "altura = " << altura << std::endl;
}

void Questao2::ler_arquivo(std::string filename) {
   
    structures::ArrayStack<std::string>* pilha = new structures::ArrayStack<std::string>();
    
    std::string select;
    std::string dado;
    std::string palavra;
    std::string categoria;

    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()) {                 
        while (getline(myfile, line)) {
            for (int i = 0; i < line.size(); i++) {
                //std::cout << "select: " << select << std::endl;
                if (line[i] == '<') {
                    //select = 1;
                    select = "abriu_chave";
                    palavra = "";
                    //std::cout << "abre <: " << palavra << std::endl;
                } else if (line[i] == '>') {
                    if (select == "fechamento") // select == 2
                        //select = 4;
                        select = "fechou_categoria";
                        dado = "";
                } else if (select == "abertura") {//select == 3
                        //select = 5;
                        select = "abriu_categoria";
                    //std::cout << "fecha >: " << palavra << std::endl;
                } else if (select == "abriu_chave") { //select == 1
                    if (line[i] == '/') {
                        //select = 2;
                        select = "fechamento";
                        //std::cout << "com barra: " << palavra << std::endl;
                    } else {
                        palavra += line[i];
                        //select = 3;
                        select = "abertura";
                        //std::cout << "sem barra: " << palavra << std::endl;
                    }
                } else if (select == "fechamento" || select == "abertura") { //select == 2 || select == 3
                    palavra += line[i];
                    //std::cout << "add: " << palavra << std::endl;
                } 

                if (select == "abriu_categoria") {
                    pilha->push(palavra);
                    categoria = palavra;
                    std::cout << "palavra empilhada: " << palavra << std::endl;
                    //std::cout << "top: " << pilha->top() << std::endl;
                    //select = 0;
                    select = "informacao_dado";
                } else if (select == "fechou_categoria") {
                    pilha->pop();
                    std::cout << "categoria: " << categoria << std::endl;
                    std::cout << "pop: " << palavra << std::endl;
                    std::cout << "dado: " << dado << std::endl;
                    salvar_dado(categoria, dado);
                    
                    select = "informacao_dado";
                }
                if (select  == "informacao_dado"){
                    dado += line[i];
                }
                    
            }
            
        }
        
        myfile.close();
        if (!pilha->empty()) {
            std::cout << "erro" << std::endl;
            //return;
        }
        
    } else std::cout << "Erro ao abrir o arquivo" << std::endl;
}

void Questao2::salvar_dado(std::string categoria, std::string dado){
    if (categoria == "x"){
        x = std::stoi(dado);
    }

    if (categoria == "y"){
        y = std::stoi(dado);
    }

    if (categoria == "largura"){
        largura = std::stoi(dado);
    }

    if (categoria == "altura"){
        altura = std::stoi(dado);
    }
}

