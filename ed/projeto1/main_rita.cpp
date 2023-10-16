#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "array_stack.h"
#include <stdexcept>
#include <tuple>
#include "array_queue.h"

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

class Questao2 {
 public:
    //! construtor com parametro cml
    explicit Questao2(std::string filename);

 private:
    void ler_arquivo(std::string filename);
    void salvar_dado(std::string categoria, std::string dado);
    void salvar_matriz(std::vector<std::vector<int>> matriz);
    void calcular_questao();

    int altura;
    int largura;

    int x;
    int y;
    
    std::string nome;
    std::vector<std::vector<int>> matriz_E;
};

Questao2::Questao2(std::string filename) {
    ler_arquivo(filename);
    //std::cout << "x = " << x << std::endl;
    //std::cout << "y = " << y << std::endl;
    //std::cout << "largura = " << largura << std::endl;
    //std::cout << "altura = " << altura << std::endl;
    //std::cout << "matriz = " << std::endl;
    //for (int i = 0; i < altura; i++) {
    //	for (int j = 0; j < largura; j++) {
    //		std::cout << matriz_E[i][j];
    //	}
    //	std::cout << std::endl;
    //}
}

void Questao2::ler_arquivo(std::string filename) {
   
    structures::ArrayStack<std::string>* pilha = new structures::ArrayStack<std::string>();
    
    std::string select;
    std::string dado;
    std::string palavra;
    std::string categoria;
    std::vector<std::vector<int>> matriz;
    int cont = 0;
    
    std::string line;
    std::ifstream myfile (filename);
    if (myfile.is_open()) {                 
        while (getline(myfile, line)) {
            if (select == "informacao_dado" && pilha->top() == "matriz") {
		std::vector<int> linhaMatriz;
		for (char c : line) {
	    	   if (c == '0') {
			linhaMatriz.push_back(0);
	    	   } else if (c == '1') {
			linhaMatriz.push_back(1);
	    	   }
		}
		matriz.push_back(linhaMatriz);
		cont++;
		if (cont == altura) {
			select = "nenhum";
			salvar_matriz(matriz);
			cont = 0;
			matriz.clear();
		}
            } else {
            for (int i = 0; i < line.size(); i++) {
                //std::cout << "select: " << select << std::endl;
                if (line[i] == '<') {
                    //select = 1;
                    select = "abriu_chave";
                    palavra = "";
                    //std::cout << "abre <: " << palavra << std::endl;
                } else if (line[i] == '>') {
                    if (select == "fechamento") {// select == 2
                        //select = 4;
                        select = "fechou_categoria";
                        
		        } else if (select == "abertura") {//select == 3
		                //select = 5;
		                select = "abriu_categoria";
		        }
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
                    //categoria = palavra;
                    //std::cout << "palavra empilhada: " << palavra << std::endl;
                    //std::cout << "top: " << pilha->top() << std::endl;
                    //select = 0;
                    select = "informacao_dado";
                } else if (select == "fechou_categoria") {
                    categoria = pilha->pop();
                    //std::cout << "categoria: " << categoria << std::endl;
                    //std::cout << "pop: " << palavra << std::endl;
                    //std::cout << "dado: " << dado << std::endl;
                    salvar_dado(categoria, dado);
                    dado = "";
                    select = "informacao_dado";
                    if (categoria == "cenario") {
                    	calcular_questao();
                    }
                } else if (select  == "informacao_dado"){
                    dado += line[i];
                }
                    
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
    
    if (categoria == "nome") {
    	nome = dado;
    }
}

void Questao2::salvar_matriz(std::vector<std::vector<int>> matriz) {
	matriz_E = matriz;
}

void Questao2::calcular_questao() {
	std::vector<std::vector<int>> matriz_R;
	for (int i = 0; i < altura; i++) {
		std::vector<int> linha_matriz_R;
		for (int j = 0; j < largura; j++) {
			linha_matriz_R.push_back(0);
		}
		matriz_R.push_back(linha_matriz_R);
	}

	structures::ArrayQueue<std::tuple<int, int>>* fila = new structures::ArrayQueue<std::tuple<int, int>>(200u);
	std::tuple<int, int> xy(x, y);
	if (matriz_E[x][y] == 1) {
		fila->enqueue(xy);
		matriz_R[x][y] = 1;
	}
	
	while (!fila->empty()) {
		xy = fila->dequeue();
		if (std::get<0>(xy)-1 >=0) {
			std::tuple<int, int> cima(std::get<0>(xy)-1, std::get<1>(xy));
			if (matriz_E[std::get<0>(cima)][std::get<1>(cima)] == 1 && matriz_R[std::get<0>(cima)][std::get<1>(cima)] == 0) {
				fila->enqueue(cima);
				matriz_R[std::get<0>(cima)][std::get<1>(cima)] = 1;
			}
		}
		if (std::get<0>(xy)+1 < altura) {
			std::tuple<int, int> baixo(std::get<0>(xy)+1, std::get<1>(xy));
			if (matriz_E[std::get<0>(baixo)][std::get<1>(baixo)] == 1 && matriz_R[std::get<0>(baixo)][std::get<1>(baixo)] == 0) {
				fila->enqueue(baixo);
				matriz_R[std::get<0>(baixo)][std::get<1>(baixo)] = 1;
			}
		}
		if (std::get<1>(xy)-1 >=0) {
			std::tuple<int, int> esquerda(std::get<0>(xy), std::get<1>(xy)-1);
			if (matriz_E[std::get<0>(esquerda)][std::get<1>(esquerda)] == 1 && matriz_R[std::get<0>(esquerda)][std::get<1>(esquerda)] == 0) {
				fila->enqueue(esquerda);
				matriz_R[std::get<0>(esquerda)][std::get<1>(esquerda)] = 1;
			}
		}
		if (std::get<1>(xy)+1 < largura) {
			std::tuple<int, int> direita(std::get<0>(xy), std::get<1>(xy)+1);
			if (matriz_E[std::get<0>(direita)][std::get<1>(direita)] == 1 && matriz_R[std::get<0>(direita)][std::get<1>(direita)] == 0) {
				fila->enqueue(direita);
				matriz_R[std::get<0>(direita)][std::get<1>(direita)] = 1;
			}
		}
	}
	delete fila;

	int cont = 0;
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < largura; j++) {
			if (matriz_R[i][j] == 1)
				cont++;
		}
	}
	std::cout << nome << " " << cont << std::endl;
	
}
