#include <systemc.h>
#include "HexDisplay.h"

void HEXDISPLAY::ShowOnHex(void) {

	// Wartoœci Wejœciwoe:
	// -2 -> B³¹d
	// -1 -> RESET
	// <0,5> -> PROGRAMS
	// OTHER VALUES -> IGNORE

	isReading.write(0);

	//wait();

	while (true) {

		isReading.write(1);

		do {
			wait();
		} while (!isDataBeingDelivered.read());

		int temp = (int)dataInput.read();

		isReading.write(0);

		if (temp < -2 && temp > 5) {
			cout << "Wyœwietlacz otrzyma³ wartoœæ z poza zakresu" << endl;
		}
		else {
			if (temp == -2) {
				cout << "HEX Wyswietlacz: ERROR" << endl;
			}
			else if (temp == -1) {
				cout << "HEX Wyswietlacz: NIC" << endl;
			}
			else {
				cout << "HEX Wyswietlacz: " << programs[temp] << endl;
			}
		}
	}
}