// Copyright [2023] <Rita Louro Barbosa e Bianca Mazzuco Verzola >

class Questao1 {
 public:
    //! construtor com parametro cml
    explicit Questao1(std::string filename);
    bool correto_aninhamento = true;

 private:
    void verificar_aninhamento(std::ifstream & myfile);

    enum Select {
        FORA_TAG,
        DENTRO_TAG,
        DENTRO_COM_BARRA,
        DENTRO_SEM_BARRA,
        POP,
        PUSH 
    };
    
};


Questao1::Questao1(std::string filename) {

    std::ifstream myfile (filename);

    if (myfile.is_open()) {
        verificar_aninhamento(myfile);
    } else std::cout << "Erro ao abrir o arquivo" << std::endl;

    myfile.close();
}

void Questao1::verificar_aninhamento(std::ifstream & myfile){

    structures::ArrayStack<std::string>* pilha = new structures::ArrayStack<std::string>();   // pilha para a verificação de aninhamento
    Select select = FORA_TAG;
    std::string identificador;
    std::string line;

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
                    correto_aninhamento = false;
                    return;
                } else {
                    pilha->pop();
                    select = FORA_TAG;
                }
            }
        }
    }
    
    // erro se ao final da análise a pilha não estiver vazia
    if (!pilha->empty()) {
        std::cout << "erro" << std::endl;
        correto_aninhamento = false;
        return;
    }

}