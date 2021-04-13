#include "systemc.h"
#include "Switches.h"
#include "CPU.h"


SC_MODULE(SYSTEM) {
	CPU* cpu;
	SWITCHES* switches;

	sc_signal<bool> resetSignal;
	sc_clock clockSignal;
	sc_signal<sc_uint<16>> switchesData{ "switchesData" };
	sc_signal<bool> switchesSendingSignalToCpu;
	sc_signal<bool> cpuProcessSwitchesState;


	SC_CTOR(SYSTEM) : clockSignal("clockSignal", 100, SC_NS) { // 100 nano sekund

		cpu = new CPU("cpu");
		switches = new SWITCHES("sw");


		cpu->clock(clockSignal);
		cpu->inputData(switchesData);
		cpu->reset(resetSignal);
		cpu->isSwitchSending(switchesSendingSignalToCpu);
		cpu->isSwitchDataProcessed(cpuProcessSwitchesState);


		switches->clock(clockSignal);
		switches->input(switchesData);
		switches->reset(resetSignal);
		switches->isSending(switchesSendingSignalToCpu);
		switches->isProcessed(cpuProcessSwitchesState);
	}
	~SYSTEM() {
		delete cpu;
		delete switches;

	}
};

int sc_main(int argc, char* argv[]);
