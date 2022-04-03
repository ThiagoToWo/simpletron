#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstdlib>
using std::atoi;

#include <cstring>
using std::strtok;
using std::strcmp;
using std::strcpy;

int main() {
	const int MEM_SIZE = 100; // memory size
	char memory[MEM_SIZE][100]; // array memory
	int accumulator; 
	char instructionRegister[100];
	char operationCode[4];
	int operand;
	int counter = 0;
	char *token[3];
	char srcName[50];
	
	/*Codigos de operacao da linguagem SAL (Simple Assembly language)
	* Operacoes de entrada/saida
	LER: Le uma palavra do teclado para uma posicao especifica da memoria.
	IMP (imprimir): Escreve na tela uma palavra de uma posicao especifica da memoria.
	* Operacoes de carregamento e armazenamento
	CRG (carregar): Carrega uma palavra de uma posicao especifica na memoria para o acumulador.
	ARM (armazenar): Armazena uma palavra do acumulador para uma posicao especifica na memoria.
	* Operacoes aritmeticas
	SOM (somar): Adiciona uma palavra de uma posicao especifica na memoria a palavra no acumulador (deixa
		o resultado no acumulador)
	SUB (subtrair): Subtrai uma palavra de uma posicao especifica na memoria da palavra no acumulador (deixa o
		resultado no acumulador)
	DIV (dividir): Divide uma palavra de uma posicao especifica na memoria pela palavra no acumulador (deixa
		o resultado no acumulador).
	MUL (multiplicar): Multiplica uma palavra de uma posicao especifica na memoria pela palavra no acumulador
		(deixa o resultado no acumulador).
	* Operacoes de transferencia de controle
	IRP (ir para): Desvia para uma posicao especifica na memoria.
	IRN (ir para se negativo): Desvia para uma posicao especifica na memoria se o acumulador for negativo.
	IRZ (ir para se zero): Desvia para uma posicao especifica na memoria se o acumulador for zero.
	FIM: Suspende - o programa completou sua tarefa.*/
	
	cout << "src? ";
	cin >> srcName;
	
	ifstream source(srcName);
	
	if (!source) {
		cout << "Falha ao abrir o arquivo.\n";
		system("pause");
		return -1;
	}
	
	while(source.getline(memory[counter], 100)) {			
		cout << memory[counter] << '\n';		
		counter++;	
	}	
	
	cout << "Carregamento do programa " << srcName << " completo.\n";
	cout << "Iniciando a execucao do programa.\n";
	
	// instruction execution cicle
	counter = 0;
	strcpy(instructionRegister, memory[counter]);
	token[0] = strtok(instructionRegister, " ");	
	token[1] = strtok('\0', " ");
	token[2] = strtok('\0', " ");
	
	while (strcmp(token[1], "FIM") != 0) {
		strcpy(operationCode, token[1]);
		operand = atoi(token[2]);
		
		if (!strcmp(operationCode, "LER")) {
			cout << "? ";
			cin >> memory[operand];
			counter++;
		} else if (!strcmp(operationCode, "IMP")) {
			cout << memory[operand] << endl;
			counter++;
		} else if (!strcmp(operationCode, "CRG")) {
			accumulator = atoi(memory[operand]);
			counter++;
		} else if (!strcmp(operationCode, "ARM")) {
			 itoa(accumulator, memory[operand], 10);
			counter++;
		} else if (!strcmp(operationCode, "SOM")) {
			accumulator += atoi(memory[operand]);
			
			if (accumulator > 9999) {
				cout << "O resultado " << accumulator << " estourou o valor maximo +9999\n" 
					 << "A execucao do Simpletron foi interrompida\n";
				system("pause");
				return 0;
			}
			
			counter++;
		} else if (!strcmp(operationCode, "SUB")) {
			accumulator -= atoi(memory[operand]);
			
			if (accumulator < -9999) {
				cout << "O resultado " << accumulator << " estourou o valor minimo -9999\n" 
					 << "A execucao do Simpletron foi interrompida\n";
				system("pause");
				return 0; 
			}
			
			counter++;
		} else if (!strcmp(operationCode, "DIV")) {
			if (atoi(memory[operand]) == 0) {
				cout << "Voce tentou dividir por zero\n" 
					 << "A execucao do Simpletron foi interrompida\n";
				system("pause");
				return 0;
			}
			
			accumulator /= atoi(memory[operand]);
			counter++;
		} else if (!strcmp(operationCode, "MUL")) {
			accumulator *= atoi(memory[operand]);
			
			if (accumulator > 9999) {
				cout << "O resultado " << accumulator << " estourou o valor maximo +9999\n" 
					 << "A execucao do Simpletron foi interrompida\n";
				system("pause");
				return 0;
			}
			
			counter++;
		} else if (!strcmp(operationCode, "IRP")) {
			counter = operand;
		} else if (!strcmp(operationCode, "IRN")) {
			if (accumulator < 0) counter = operand;
			else counter++;
		} else if (!strcmp(operationCode, "IRZ")) {
			if (accumulator == 0) counter = operand;
			else counter++;			
		} else {
			cout << "A instrucao " << token[1] << " alocada em " << counter 
				 << " tem codigo invalido\n"
				 << "A execucao do Simpletron foi interrompida\n";
				system("pause");
				return 0;
		}
		
		strcpy(instructionRegister, memory[counter]);
		token[0] = strtok(instructionRegister, " ");	
		token[1] = strtok('\0', " ");
		token[2] = strtok('\0', " ");
	}	
	
	system("pause");	
}