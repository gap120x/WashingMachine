#include <sstream>
#include <string>
#include "systemc.h"
#include "list"

using namespace std;

SC_MODULE(CPU)
{
	sc_in<bool> clock;
	sc_in<bool> reset;
	sc_in<sc_uint<16>> inputData;
	sc_in<bool> isSwitchSending;
	sc_out<bool> isSwitchDataProcessed;

	const int programs[6] = { 0, 800, 900, 1000, 1100, 1200 };
	int activeSwitches[6] = { 0, 0, 0, 0, 0,0};
	int activeProgramId = -1;
	bool isError = false;
	int processing = 0;
	bool isProcessed = false;

	void launchProgram(int id);
	void display(string switchesLine);
	void printWasher(int programId, bool isError);
	int countActiveProgramSwitches();
	void handle(void);
	void manageState(void);
	void toggle(int inputData);
	void processData(int switchNr);
	int getActiveSwitch(void);
	void showError(void);

	void launchProgram1();
	void launchProgram2();
	void launchProgram3();
	void launchProgram4();
	void launchProgram5();
	void launchProgram6();

	SC_CTOR(CPU) {
		SC_CTHREAD(handle, clock.pos());

		SC_CTHREAD(launchProgram1, clock.pos());
		SC_CTHREAD(launchProgram2, clock.pos());
		SC_CTHREAD(launchProgram3, clock.pos());
		SC_CTHREAD(launchProgram4, clock.pos());
		SC_CTHREAD(launchProgram5, clock.pos());
		SC_CTHREAD(launchProgram6, clock.pos());

		reset_signal_is(reset, true);
	}

};