#include <systemc.h>

SC_MODULE(HEXDISPLAY) {

	sc_in<bool> isDataBeingDelivered;
	sc_in<bool> clock;

	sc_out<sc_int<16>> dataInput;
	sc_out<bool> isReading;

	const int programs[6] = { 0, 800, 900, 1000, 1100, 1200 };
	int activeId;

	void ShowOnHex();

	SC_CTOR(HEXDISPLAY) {
		SC_CTHREAD(ShowOnHex, clock.pos());
		
	}

};
