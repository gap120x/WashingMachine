#include "systemc.h"

SC_MODULE(CPU_2) {

	sc_in<bool> isDataBeingDelivered;
	sc_in<bool> clock;

	sc_out<sc_uint<16>> dataInput;
	sc_out<bool> isReading;
	


	void switchHandler();

	SC_CTOR(CPU_2) {
		SC_CTHREAD(switchHandler, clock.pos());
		
	}
};
