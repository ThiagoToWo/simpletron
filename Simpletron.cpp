#include <iostream>
#include <iomanip>

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
	const short MEM_SIZE = 100; // memory size
	short memory[MEM_SIZE] = {0,0}; // array memory
	short accumulator; 
	short instructionRegister;
	short operationCode;
	short operand;
	short counter = 0;
	short entry;
	
	cout << "*** Bem vindo ao Simpletron! ***\n" <<
	"* Por favor insira uma instrução (ou data word) por vez em seu programa.\n" <<
	"* Eu vou digitar o número de alocação e o ponto de interrogação (?).\n" <<
	"* Então você digita a palavra para a alocação.\n" <<
	"* Digite o número -99999 para parar de inserir dados no seu programa\n";
	
	// filling memory
	cout << setw(2) << counter << " ? ";
	cin >> entry;
	
	while(entry != -9999) {		
		memory[counter] = entry;
		counter++;
		cout << setw(2) << counter << " ? ";
		cin >> entry;
	} 
	
	memory[counter] = -9999;
	cout << "Carregamento do programa completo.\n";
	cout << "Iniciando a execução do programa.\n";
	
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
				counter++;
				break;
			case 31: // subtract
				accumulator -= memory[operand];
				counter++;
				break;
			case 32: // divide
				accumulator /= memory[operand];
				counter++;
				break;
			case 33: // multiply
				accumulator *= memory[operand];
				counter++;
				break;
			case 40: // branch
				counter = operand;
				break;
			case 41:
				if (accumulator < 0) counter = operand;
				break;
			case 42:
				if (accumulator == 0) counter = operand;
				break;				
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