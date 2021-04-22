#include "systemc.h"
#include "Switches.h"
#include "CPU.h"
#include "CPU2.h"
#include "HexDisplay.h"
#include "ErrorLed.h"
//tzw top modu�, scalaj�cy modu�y CPU i Switches
SC_MODULE(SYSTEM) {
	//wska�niki na modu�y CPU i Switches
	CPU* cpu;
	CPU_2* cpu2;
	SWITCHES* switches;
	HEXDISPLAY* hex;
	LED* led;

	//sygna� zegarowy wsp�lny dla obu modu��w
	sc_clock clockSignal;

	//sygna�y ��cz�ce modu�y CPU i Switches
	sc_signal<sc_uint<16>> washerProgramData{ "washerProgramData" };
	sc_signal<sc_uint<16>> cpu2Data{ "cpu2Data" };
	sc_signal<sc_int<16>> hexDisplayData{ "hexDisplayData" };
	sc_signal<bool> ledDisplayData{ "ledDisplayData" };


	sc_signal<bool> swOutputSignal;
	sc_signal<bool> cpuProcessingSignal;
	sc_signal<bool> cpu1SendingToCpu2;
	sc_signal<bool> cpu2ReadingCpu1Data;
	sc_signal<bool> cpuSendingToHex;
	sc_signal<bool> hexesReadingCpuData;
	sc_signal<bool> cpuSendingToLed;
	sc_signal<bool> ledReadingCpuData;



	//konstruktor top modu�u
	SC_CTOR(SYSTEM) : clockSignal("clockSignal", 100, SC_NS) { 

		//stworzenie instancji modu��w
		cpu2 = new CPU_2("cpu2");
		cpu = new CPU("cpu");
		switches = new SWITCHES("sw");
		hex = new HEXDISPLAY("hex");
		led = new LED("led");


		//przypisanie port�w modu��w do odpowiednich sygna��w
		cpu->clk(clockSignal);
		cpu->programChoice(washerProgramData);
		cpu->switchReceiving(swOutputSignal);
		cpu->switchProgramEnded(cpuProcessingSignal);
		cpu->outputDataCpu2(cpu2Data);
		cpu->isSendingToCpu2(cpu1SendingToCpu2);
		cpu->isCpu2Reading(cpu2ReadingCpu1Data);
		cpu->isSendingToHex(cpuSendingToHex);
		cpu->areHexesReading(hexesReadingCpuData);
		cpu->outputHexDisplayData(hexDisplayData);
		cpu->isSendingToLed(cpuSendingToLed);
		cpu->isLedReading(ledReadingCpuData);
		cpu->outputLedDisplayData(ledDisplayData);

		switches->clk(clockSignal);
		switches->input(washerProgramData);
		switches->isSending(swOutputSignal);
		
		cpu2->clock(clockSignal);
		cpu2->dataInput(cpu2Data);
		cpu2->isDataBeingDelivered(cpu1SendingToCpu2);
		cpu2->isReading(cpu2ReadingCpu1Data);

		hex->clock(clockSignal);
		hex->dataInput(hexDisplayData);		
		hex->isDataBeingDelivered(cpuSendingToHex);
		hex->isReading(hexesReadingCpuData);

		led->clock(clockSignal);
		led->dataInput(ledDisplayData);
		led->isDataBeingDelivered(cpuSendingToLed);
		led->isReading(ledReadingCpuData);
	}

	//destruktor
	~SYSTEM() {
		delete cpu;
		delete cpu2;
		delete switches;
		delete hex;


	}
};

