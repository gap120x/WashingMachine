#include "systemc.h"
#include "Switches.h"
#include "CPU.h"

//tzw top modu³, scalaj¹cy modu³y CPU i Switches
SC_MODULE(SYSTEM) {
	//wskaŸniki na modu³y CPU i Switches
	CPU* cpu;
	SWITCHES* switches;

	//sygna³ zegarowy wspólny dla obu modu³ów
	sc_clock clockSignal;

	//sygna³y ³¹cz¹ce modu³y CPU i Switches
	sc_signal<sc_uint<16>> washerProgramData{ "washerProgramData" };
	sc_signal<bool> swOutputSignal;
	sc_signal<bool> cpuProcessingSignal;

	//konstruktor top modu³u
	SC_CTOR(SYSTEM) : clockSignal("clockSignal", 100, SC_NS) { 

		//stworzenie instancji modu³ów
		cpu = new CPU("cpu");
		switches = new SWITCHES("sw");

		//przypisanie portów modu³ów do odpowiednich sygna³ów
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

