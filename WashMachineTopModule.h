#include "systemc.h"
#include "Switches.h"
#include "CPU.h"

//tzw top modu�, scalaj�cy modu�y CPU i Switches
SC_MODULE(SYSTEM) {
	//wska�niki na modu�y CPU i Switches
	CPU* cpu;
	SWITCHES* switches;

	//sygna� zegarowy wsp�lny dla obu modu��w
	sc_clock clockSignal;

	//sygna�y ��cz�ce modu�y CPU i Switches
	sc_signal<sc_uint<16>> washerProgramData{ "washerProgramData" };
	sc_signal<bool> swOutputSignal;
	sc_signal<bool> cpuProcessingSignal;

	//konstruktor top modu�u
	SC_CTOR(SYSTEM) : clockSignal("clockSignal", 100, SC_NS) { 

		//stworzenie instancji modu��w
		cpu = new CPU("cpu");
		switches = new SWITCHES("sw");

		//przypisanie port�w modu��w do odpowiednich sygna��w
		cpu->clk(clockSignal);
		cpu->programChoice(washerProgramData);
		cpu->switchReceiving(swOutputSignal);
		cpu->switchProgramEnded(cpuProcessingSignal);


		switches->clk(clockSignal);
		switches->input(washerProgramData);
		switches->isSending(swOutputSignal);
		
	}

	//destruktor
	~SYSTEM() {
		delete cpu;
		delete switches;

	}
};

