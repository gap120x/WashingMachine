#include <systemc.h>
#include "Switches.h"

void SWITCHES::clear(void) {
	system("cls");
}

int SWITCHES::readUserInput(void) {
	bool wynik = false;
	int result;	
	while (!wynik) {	
		if (!(cin >> result))
		{
			result = -1;
		}
		if(result < 6 && result !=-1)
		{
			wynik = true;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Nieprawidlowy Wybor! Wprowadz wartosc liczbowa od 0 do 5.";			
			wynik = false;
		}
	}
	return result;
	
	
}

void SWITCHES::sendInput(int userInput) {
	wait();
	isSending.write(1);
	input.write(userInput);
	wait();
}

void SWITCHES::closeSendingOutput(void) {
	wait();
	isSending.write(0);
	wait();
}

void SWITCHES::read(void) {
	int processed = 1;

	while (true) {
		if (processed == 1) {
			int userInput = readUserInput();

			clear();

			sendInput(userInput);
		}

		closeSendingOutput();

		processed = isProcessed.read();
	}
}
