// Copyright [2023] <Rita Louro Barbosa e Bianca Mazzuco Verzola >
class Questao2 {
 public:
    //! construtor com parametro cml
    explicit Questao2(std::string filename);

 private:
    void ler_arquivo(std::ifstream & myfile);
    void salvar_dado(std::string categoria, std::string dado);
    void salvar_matriz(std::vector<std::vector<int>> matriz);
    void calcular_questao();

    int altura;
    int largura;

    int x;
    int y;
    
    std::string nome;
    std::vector<std::vector<int>> matriz_E;

    enum Select {
	INFORMACAO_DADO,
	NENHUM,
	ABRIU_CHAVE,
	FECHAMENTO,
	FECHOU_CATEGORIA,
	ABERTURA,
    ABRIU_CATEGORIA
    };
};

Questao2::Questao2(std::string filename) {

    std::ifstream myfile (filename);

    if (myfile.is_open()) {   
    ler_arquivo(myfile);
    } else std::cout << "Erro ao abrir o arquivo" << std::endl;

    myfile.close();
}

void Questao2::ler_arquivo(std::ifstream & myfile) {
   
    structures::ArrayStack<std::string>* pilha = new structures::ArrayStack<std::string>();
    Select select;
    std::string dado;
    std::string palavra;
    std::string categoria;
    std::vector<std::vector<int>> matriz;
    int cont = 0;
    std::string line;
              
    while (getline(myfile, line)) {
        if (select == INFORMACAO_DADO && pilha->top() == "matriz") {

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
                select = NENHUM;
                salvar_matriz(matriz);
                cont = 0;
                matriz.clear();
            }
        } else {
            for (int i = 0; i < line.size(); i++) {

                if (line[i] == '<') {
                    //select = 1;
                    select = ABRIU_CHAVE;
                    palavra = "";
                } else if (line[i] == '>') {
                    if (select == FECHAMENTO) {// select == 2
                        select = FECHOU_CATEGORIA;
                        
                    } else if (select == ABERTURA) {//select == 3
                        select = ABRIU_CATEGORIA;
                    }
                } else if (select == ABRIU_CHAVE) { //select == 1
                    if (line[i] == '/') {
                        select = FECHAMENTO;
                    } else {
                        palavra += line[i];
                        select = ABERTURA;
                    }
                } else if (select == FECHAMENTO || select == ABERTURA) { //select == 2 || select == 3
                    palavra += line[i];
                } 

                if (select == ABRIU_CATEGORIA) {
                    pilha->push(palavra);
                    select = INFORMACAO_DADO;
                } else if (select == FECHOU_CATEGORIA) {
                    categoria = pilha->pop();
                    salvar_dado(categoria, dado);
                    dado = "";
                    select = INFORMACAO_DADO;
                    if (categoria == "cenario") {
                        calcular_questao();
                    }
                } else if (select  == INFORMACAO_DADO){
                    dado += line[i];
                }
                    
            }
        }
        
    }
    
    if (!pilha->empty()) {
        std::cout << "erro" << std::endl;
        return;
    }
        
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