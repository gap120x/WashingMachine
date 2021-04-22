#include <systemc.h>
#include "ErrorLed.h"

void LED::displayOnLed(void) {

//Gdy procesor przeka�� warto�� 1 - dioda za�wieca si� nastepuje to gdy mamy error
	//0 - Dioda nie jest za�wiecona pralka pracuje poprawnie
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