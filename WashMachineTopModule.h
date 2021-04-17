#include "systemc.h"
#include "Switches.h"
#include "CPU.h"
#include "CPU2.h"
//tzw top modu³, scalaj¹cy modu³y CPU i Switches
SC_MODULE(SYSTEM) {
	//wskaŸniki na modu³y CPU i Switches
	CPU* cpu;
	CPU_2* cpu2;
	SWITCHES* switches;

	//sygna³ zegarowy wspólny dla obu modu³ów
	sc_clock clockSignal;

	//sygna³y ³¹cz¹ce modu³y CPU i Switches
	sc_signal<sc_uint<16>> washerProgramData{ "washerProgramData" };
	sc_signal<sc_uint<16>> cpu2Data{ "cpu2Data" };
	sc_signal<bool> swOutputSignal;
	sc_signal<bool> cpuProcessingSignal;
	sc_signal<bool> cpu1SendingToCpu2;
	sc_signal<bool> cpu2ReadingCpu1Data;
	//konstruktor top modu³u
	SC_CTOR(SYSTEM) : clockSignal("clockSignal", 100, SC_NS) { 

		//stworzenie instancji modu³ów
		cpu2 = new CPU_2("cpu2");
		cpu = new CPU("cpu");
		switches = new SWITCHES("sw");

		//przypisanie portów modu³ów do odpowiednich sygna³ów
		cpu->clk(clockSignal);
		cpu->programChoice(washerProgramData);
		cpu->switchReceiving(swOutputSignal);
		cpu->switchProgramEnded(cpuProcessingSignal);
		cpu->outputDataCpu2(cpu2Data);
		cpu->isSendingToCpu2(cpu1SendingToCpu2);
		cpu->isCpu2Reading(cpu2ReadingCpu1Data);

		switches->clk(clockSignal);
		switches->input(washerProgramData);
		switches->isSending(swOutputSignal);
		
		cpu2->clock(clockSignal);
		cpu2->dataInput(cpu2Data);
		cpu2->isDataBeingDelivered(cpu1SendingToCpu2);
		cpu2->isReading(cpu2ReadingCpu1Data);
	}

	//destruktor
	~SYSTEM() {
		delete cpu;
		delete switches;

	}
};

