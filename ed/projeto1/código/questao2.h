// Copyright [2023] <Rita Louro Barbosa e Bianca Mazzuco Verzola>

class Questao2 {
 public:
    //! construtor com parametro cml
    explicit Questao2(std::string filename); // construtor

 private:
    void lerArquivo(std::ifstream &myfile); // realiza o processamento do arquivo, encontrando os dados a serem salvos nos atributos
    void salvarDado(std::string categoria, std::string dado); // salva os dados encontrados nos atributos, de acordo com sua categoria. 
    void salvarMatriz(std::vector<std::vector<int>> matriz); // salva matriz encontrada o xml correspondente ao caso atual
    void determinarArea(); // realiza o calculo da área de varredura do robô

    int altura; // altura da matriz
    int largura; // largura da matriz


    int x; // coordenada x inicial
    int y; // coordenada y inicial
  
    std::string nome; // nome do cenário atual
    std::vector<std::vector<int>> matriz_E; // Matriz inicial


    enum Select { // controla os estados do programa, organizando o fluxo de processamento. 
    NENHUM,
    ABRIU_CHAVE,
    ABERTURA,
    ABRIU_CATEGORIA,
    FECHAMENTO,
    FECHOU_CATEGORIA,
    INFORMACAO_DADO
    };
};


Questao2::Questao2(std::string filename) {

    std::ifstream myfile (filename);

    if (myfile.is_open()) {   
    lerArquivo(myfile);
    } else std::cout << "Erro ao abrir o arquivo" << std::endl;

    myfile.close();
}

void Questao2::lerArquivo(std::ifstream & myfile) {
   
    structures::ArrayStack<std::string>* pilha = new structures::ArrayStack<std::string>();
    Select select;
    std::string dado;
    std::string identificador;
    std::string categoria;
    std::vector<std::vector<int>> matriz;
    int cont = 0;
    std::string line;
              
    while (getline(myfile, line)) {

    	// salvando a matriz dada depois do identificador <matriz>
        if (select == INFORMACAO_DADO && pilha->top() == "matriz") {

            std::vector<int> linha_matriz;
            for (char c : line) {
                    if (c == '0') 
                	linha_matriz.push_back(0);
                    else if (c == '1') 
                	linha_matriz.push_back(1);
            }
            
            matriz.push_back(linha_matriz);
            cont++;
            if (cont == altura) {
                select = NENHUM;
                salvarMatriz(matriz);
                cont = 0;
                matriz.clear();
            }

	// lendo o resto do arquivo (sem ser a matriz)
        } else {
            for (int i = 0; i < line.size(); i++) {

                if (line[i] == '<') {
                    select = ABRIU_CHAVE;
                    identificador = "";
                } else if (line[i] == '>') {
                    if (select == FECHAMENTO)
                        select = FECHOU_CATEGORIA;
                    else if (select == ABERTURA)
                        select = ABRIU_CATEGORIA;

                } else if (select == ABRIU_CHAVE) {
                    if (line[i] == '/') {
                        select = FECHAMENTO;
                    } else {
                        identificador += line[i];
                        select = ABERTURA;
                    }
                } else if (select == FECHAMENTO || select == ABERTURA) {
                    identificador += line[i];
                } 

                if (select == ABRIU_CATEGORIA) {
                    pilha->push(identificador);
                    select = INFORMACAO_DADO;
                } else if (select == FECHOU_CATEGORIA) {
                    categoria = pilha->pop();
                    salvarDado(categoria, dado);
                    dado = "";
                    select = NENHUM;
                    if (categoria == "cenario") {
                        determinarArea();
                    }
                } else if (select  == INFORMACAO_DADO){
                    dado += line[i];
                }
            }
        }
    }
    delete pilha;
}

void Questao2::salvarDado(std::string categoria, std::string dado) {
    if (categoria == "x")
        x = std::stoi(dado);

    if (categoria == "y")
        y = std::stoi(dado);

    if (categoria == "largura")
        largura = std::stoi(dado);

    if (categoria == "altura")
        altura = std::stoi(dado);
    
    if (categoria == "nome")
    	nome = dado;
}

void Questao2::salvarMatriz(std::vector<std::vector<int>> matriz) {
	matriz_E = matriz;
}

void Questao2::determinarArea() {
	// criando uma matriz R de zeros
	std::vector<std::vector<int>> matriz_R;
	for (int i = 0; i < altura; i++) {
		std::vector<int> linha_matriz_R;
		for (int j = 0; j < largura; j++) {
			linha_matriz_R.push_back(0);
		}
		matriz_R.push_back(linha_matriz_R);
	}

	// fila de tuplas de inteiros
	structures::ArrayQueue<std::tuple<int, int>>* fila = new structures::ArrayQueue<std::tuple<int, int>>(80u);
	std::tuple<int, int> xy(x, y);
	if (matriz_E[x][y] == 1) {
		fila->enqueue(xy);	// insere (x, y) na fila
		matriz_R[x][y] = 1;
	}
	
	while (!fila->empty()) {
		xy = fila->dequeue();	// remover da fila
		
		/*inserindo na fila as coordenadas dos quatro vizinhos que estejam dentro do domínio da matriz 
		(não pode ter coordenada negativa ou superar o número de linhas ou de colunas), 
		com intensidade 1 (em E) e ainda não tenha sido visitado (igual a 0 em R) 
		*/
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

	// contando a quantidade de 1 (uns) na matriz R
	int cont = 0;
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < largura; j++) {
			if (matriz_R[i][j] == 1)
				cont++;
		}
	}
	std::cout << nome << " " << cont << std::endl;
	
}