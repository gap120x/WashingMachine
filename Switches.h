#include <systemc.h>

SC_MODULE(SWITCHES) {
	sc_in<bool> isProcessed;
	sc_in<bool> clock;

	sc_out<sc_uint<16>> input;
	sc_out<bool> isSending;
	sc_out<bool> reset;


	void clear();
	int readUserInput();
	void sendInput(int userInput);
	void closeSendingOutput();
	void read();

	SC_CTOR(SWITCHES) {
		SC_CTHREAD(read, clock.pos());
	}

};

