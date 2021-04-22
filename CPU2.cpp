
#include <systemc.h>
#include "CPU2.h"


void CPU_2::switchHandler(void) {

	isReading.write(0);

	wait();

	while (true) {

		isReading.write(1);

		do {
			wait();
		} while (!isDataBeingDelivered.read());

		int id = (int)dataInput.read();

		isReading.write(0);	

		if (id == 5) {
			
			cout << "CPU_2: Otrzymal dane od CPU1" << endl;		
			cout << "Uruchomiono Program Nr: 6 "<< "\n";
			

		}
	}
}