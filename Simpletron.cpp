#include <iostream>
#include <iomanip>
#include <cstdlib>

using std::cout;
using std::cin;
using std::internal;
using std::showpos;
using std::setfill;
using std::setw;
using std::endl;
using std::noshowpos;

int main() {
	// I/O operations
	const int READ = 10;
	const int WRITE = 11;
	// loading and storing operations
	const int LOAD = 20;
	const int STORE = 21;
	// arithmetcs operations
	const int ADD = 30;
	const int SUBTRACT = 31;
	const int DIVIDE = 32;
	const int MULTIPLY = 33;
	// control transfer operations
	const int BRANCH = 40;
	const int BRANCHNEG = 41;
	const int BRANCHZERO = 42;
	const int HALT = 43;
	const int MEM_SIZE = 100; // memory size
	int memory[MEM_SIZE] = {0,0}; // array memory
	int accumulator; 
	int instructionRegister;
	int operationCode;
	int operand;
	int counter = 0;
	int entry;
	
	cout << "*** Bem vindo ao Simpletron! ***\n" 
		 << "* Por favor insira uma instrucao (ou data word) por vez em seu programa.\n"
		 << "* Eu vou digitar o numero de alocacao e o ponto de interrogacao (?).\n"
		 << "* Entao voce digita a palavra para a alocacao.\n" 
		 << "* Digite o numero -99999 para parar de inserir dados no seu programa\n\n";
	
	cout << "Codigo de operacao da linguagem SML (Simpletron Machine language) \tSignificado\n"
		 << "* Operacoes de entrada/saida\n"
		 << "READ = 10; \t\tLe uma palavra do teclado para uma posicao especifica da memoria.\n"
		 << "WRITE = 11; \t\tEscreve na tela uma palavra de uma posicao especifica da memoria.\n"
		 << "* Operacoes de carregamento e armazenamento\n"
		 << "LOAD = 20; \t\tCarrega uma palavra de uma posicao especifica na memoria para o acumulador.\n"
		 << "STORE = 21; \t\tArmazena uma palavra do acumulador para uma posicao especifica na memoria.\n"
		 << "* Operacoes aritmeticas\n"
		 << "ADD = 30; \t\tAdiciona uma palavra de uma posicao especifica na memoria a palavra no acumulador (deixa\n"
		 << "\t\t\to resultado no acumulador)\n"
		 << "SUBTRACT = 31; \t\tSubtrai uma palavra de uma posicao especifica na memoria da palavra no acumulador (deixa o\n"
		 << "\t\t\tresultado no acumulador)\n"
		 << "DIVIDE = 32; \t\tDivide uma palavra de uma posicao especifica na memoria pela palavra no acumulador (deixa\n"
		 << "\t\t\to resultado no acumulador).\n"
		 << "MULTIPLY = 33; \t\tMultiplica uma palavra de uma posicao especifica na memoria pela palavra no acumulador\n"
		 << "\t\t\t(deixa o resultado no acumulador).\n"
		 << "* Operacoes de transferencia de controle\n"
		 << "BRANCH = 40; \t\tDesvia para uma posicao especifica na memoria.\n"
		 << "BRANCHNEG = 41; \tDesvia para uma posicao especifica na memoria se o acumulador for negativo.\n"
		 << "BRANCHZERO = 42; \tDesvia para uma posicao especifica na memoria se o acumulador for zero.\n"
		 << "HALT = 43; \t\tSuspende - o programa completou sua tarefa.\n\n"
		 << "Insira as instrucoes\n";
	
	// filling memory
	cout << setw(2) << counter << " ? ";
	cin >> entry;
	
	while(entry != -9999) {	// while don't put the sentinel
		while (entry < -9999 || entry > 9999) { // entry is invalid
			cout << setw(2) << counter << " ? ";
			cin >> entry;
		} 
			
		memory[counter] = entry;
		counter++;		
		cout << setw(2) << counter << " ? ";
		cin >> entry;		
	} 
	
	cout << "Carregamento do programa completo.\n";
	cout << "Iniciando a execucao do programa.\n";
	
	// instruction execution cicle
	counter = 0;
	instructionRegister = memory[counter];
	
	while (instructionRegister != 4300) {
		operationCode = instructionRegister / 100;
		operand = instructionRegister % 100;
		
		switch (operationCode) {
			case 10: // read
				cout << "? ";
				cin >> memory[operand];
				counter++;
				break;
			case 11: // write
				cout << memory[operand] << endl;
				counter++;
				break;
			case 20: // loading
				accumulator = memory[operand];
				counter++;
				break;
			case 21: // store
				memory[operand] = accumulator;
				counter++;
				break;
			case 30: // add
				accumulator += memory[operand];
				
				if (accumulator > 9999) {
					cout << "O resultado " << accumulator << " estourou o valor maximo +9999\n" 
						 << "A execucao do Simpletron foi interrompida\n";
					system("pause");
					return 0;
				}
				
				counter++;
				break;
			case 31: // subtract
				accumulator -= memory[operand];
				
				if (accumulator < -9999) {
					cout << "O resultado " << accumulator << " estourou o valor minimo -9999\n" 
						 << "A execucao do Simpletron foi interrompida\n";
					system("pause");
					return 0; 
				}
				
				counter++;
				break;
			case 32: // divide
				if (memory[operand] == 0) {
					cout << "Voce tentou dividir por zero\n" 
						 << "A execucao do Simpletron foi interrompida\n";
					system("pause");
					return 0;
				}
				
				accumulator /= memory[operand];
				counter++;
				break;
			case 33: // multiply
				accumulator *= memory[operand];
				
				if (accumulator > 9999) {
					cout << "O resultado " << accumulator << " estourou o valor maximo +9999\n" 
						 << "A execucao do Simpletron foi interrompida\n";
					system("pause");
					return 0;
				}
				
				counter++;
				break;
			case 40: // to branch
				counter = operand;
				break;
			case 41: // to branch if negative
				if (accumulator < 0) counter = operand;
				break;
			case 42: // to branch if zero
				if (accumulator == 0) counter = operand;
				break;
			default:
				cout << "A instrucao " << instructionRegister << " alocada em " << counter 
					 << " tem codigo invalido\n"
					 << "A execucao do Simpletron foi interrompida\n";
					system("pause");
					return 0;
		}		
		
		instructionRegister = memory[counter];
	}	
	
	// print dump of computer
	cout << "REGISTERS:\n" <<
	"accumulator \t" << showpos << setfill('0') << internal << accumulator << endl <<
	"counter \t" << noshowpos << counter << endl <<
	"instructionRegister \t" << showpos << internal << instructionRegister << endl <<
	"operationCode \t" << noshowpos << operationCode << endl <<
	"operand \t" << setw(2) << operand << endl << endl <<
	"MEMORY:\n   " << setfill(' ');
	
	for (int i = 0; i <= 9; i++) { // print columns numbers
		cout << setw(5) << i << " ";
	}
	
	for (int i = 0; i < 100; i++) { // print lines
		if (i % 10 == 0) { // print ten numbers in one line
			cout << endl << setw(2) << noshowpos << i << " ";
		} 
		cout << setw(5) << showpos << setfill('0') << internal << memory[i] << ' ';		
	}
	
	cout << endl;
	system("pause");
}