// Copyright [2023] <Rita Louro Barbosa e Bianca Mazzuco Verzola >

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "array_stack.h"
#include <stdexcept>
#include <tuple>
#include "array_queue.h"
#include "questao2.h"
#include "questao1.h"


int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    
	Questao1 Questao1(xmlfilename);

	if (Questao1.correto_aninhamento){
		Questao2 Questao2(xmlfilename);
	}

    return 0;
}
