#include <systemc.h>

SC_MODULE(LED) {

	sc_in<bool> isDataBeingDelivered;
	sc_in<bool> clock;

	sc_out<bool> dataInput;
	sc_out<bool> isReading;


	int activeId;

	void displayOnLed();

	SC_CTOR(LED) {
		SC_CTHREAD(displayOnLed, clock.pos());
	
	}

};