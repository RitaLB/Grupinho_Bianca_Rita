// Copyright [2023] <Rita Louro Barbosa e Bianca Mazzuco Verzola>

class Questao1 {
 public:
    //! construtor com parametro xml
    explicit Questao1(std::string filename);
    bool correto_aninhamento = true;

 private:
    void verificar_aninhamento(std::ifstream & myfile);

    enum Select {
        NENHUM,
        ABRIU_CHAVE,
        ABERTURA,
        FECHAMENTO,
        FECHOU_CATEGORIA,
        ABRIU_CATEGORIA
    };
    
};


Questao1::Questao1(std::string filename) {

    std::ifstream myfile (filename);

    if (myfile.is_open()) {
        verificar_aninhamento(myfile);
    } else std::cout << "Erro ao abrir o arquivo" << std::endl;

    myfile.close();
}

void Questao1::verificar_aninhamento(std::ifstream &myfile) {

    structures::ArrayStack<std::string>* pilha = new structures::ArrayStack<std::string>();   // pilha para a verificação de aninhamento
    Select select;
    std::string identificador;
    std::string line;

    while (getline(myfile, line)) {			   // lendo arquivo linha por linha
        for (int i = 0; i < line.size(); i++) {		   // lendo linha caracter por caracter
            // lidando com o que está dentro de < >
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

        // empilhando ou desempilhando palavras dentro de < >
            if (select == ABRIU_CATEGORIA) {
                pilha->push(identificador);
                select = NENHUM;
            } else if (select == FECHOU_CATEGORIA) {
                if (pilha->size() == 0 || pilha->top() != identificador) {
                    // erro se, ao consultar o topo, a pilha estiver vazia ou se o identificador é diferente
                    std::cout << "erro" << std::endl;
                    correto_aninhamento = false;
                    delete pilha;
                    return;
                } else {
                    pilha->pop();
                    select = NENHUM;
                }
            }
        }
    }
    
    // erro se ao final da análise a pilha não estiver vazia
    if (!pilha->empty()) {
        std::cout << "erro" << std::endl;
        correto_aninhamento = false;
        delete pilha;
        return;
    }
    delete pilha;
}
