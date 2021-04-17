#include "systemc.h"

SC_MODULE(CPU_2) {

	sc_in<bool> isDataBeingDelivered;
	sc_in<bool> clock;

	sc_out<sc_uint<16>> dataInput;
	sc_out<bool> isReading;
	const int washerPrograms[6] = { 0, 800, 900, 1000, 1100, 1200 };//docelowo do usuniêcia to musi siê wyœwietlaæ na HEX'ie a nie w CPU1/CPU2


	void switchHandler();

	SC_CTOR(CPU_2) {
		SC_CTHREAD(switchHandler, clock.pos());
		
	}
};
