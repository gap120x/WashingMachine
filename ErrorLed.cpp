#include <systemc.h>
#include "ErrorLed.h"

void LED::displayOnLed(void) {

//Gdy procesor przeka¿ê wartoœæ 1 - dioda zaœwieca siê nastepuje to gdy mamy error
	//0 - Dioda nie jest zaœwiecona pralka pracuje poprawnie
	isReading.write(0);

	wait();

	while (true) {

		isReading.write(1);

		do {
			wait();
		} while (!isDataBeingDelivered.read());

		bool temp = (bool)dataInput.read();

		isReading.write(0);

		if (temp) {
			cout << "Error LED: ON" << endl;
		}
		else {
			cout << "Error LED: OFF" << endl;
		}
	}
}