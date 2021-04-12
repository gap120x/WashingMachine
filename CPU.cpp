#include <sstream>
#include <string>
#include "systemc.h"
#include "list"
#include "CPU.h"

using namespace std;

void CPU::launchProgram(int id) {
	while (true) {
		wait(4);
		if (id < 6 && CPU::processing == id && CPU::isProcessed) {
			cout << "Uruchomiono Program Nr: " << (id + 1) << " (Predkosc Wirowania: " <<programs[id]<< ")\n";
		}
	}
}

void CPU::display(string switchesLine) {
	cout << "|--------------------------|" << endl;
	cout << switchesLine << endl;
	cout << "|SW| 05| 04| 03| 02| 01 |00| " << endl;

}

void CPU::printWasher(int programId, bool isError) {

	std::stringstream swStrm;

	swStrm << "|SW|";


	if (isError) {

		for (int i = 5; i >= 0; i--) {
			if (activeSwitches[i] <= 0) {
				swStrm << "OFF|";
			}
			else {
				swStrm << " ON|";
			}
		}
	}
	else {

		for (int i = 5; i >= 0; i--) {
			if (activeSwitches[i] <= 0) {
				swStrm << "OFF|";
			}
			else {
				swStrm << " ON|";
			}
		}

	}

	display(swStrm.str());
}


void CPU::processData(int switchNr) {
	isProcessed = true;
	processing = switchNr;
	
}


int CPU::countActiveProgramSwitches(void) {
	int active = 0;

	for (int i = 0; i < 6; i++) {
		if (activeSwitches[i] == 1) {
			active++;
		}
	}

	return active;
}

int CPU::getActiveSwitch(void) {
	for (int i = 0; i < 6; i++) {
		if (activeSwitches[i] == 1) {
			return i;
		}
	}
	return -1;
}

void CPU::toggle(int inputData) {
	if (activeSwitches[inputData] == 1) {
		activeSwitches[inputData] = 0;
	}
	else {
		activeSwitches[inputData] = 1;
	}
}

void CPU::manageState(void) {

	int active = countActiveProgramSwitches();

	if (active > 1) {
		isError = true;
		showError();
	}
	int switchNr = getActiveSwitch();
	if (switchNr >= 0) {		
		processData(switchNr);
	
	}
}

void CPU::showError(void) {
	cout << "Wybrano wiecej niz jeden SW!. " << endl;

}

void CPU::handle(void) {
	printWasher(-1, false);

	int data;
	int previousProgramID;
	bool wasErrorPreviously;

	while (true) {
		wasErrorPreviously = isError;
		previousProgramID = activeProgramId;
		isSwitchDataProcessed.write(0);
		isProcessed = false;
		isError = false;
		activeProgramId = -1;

		if (isSwitchSending.read() == 1) {

			data = (int)inputData.read();

			if (data >= 0 && data <= 5) {
				toggle(data);
				manageState();
			}
			else {
				isError = wasErrorPreviously;
				activeProgramId = previousProgramID;
				manageState();
			}
			wait();
			isSwitchDataProcessed.write(1);
			printWasher(activeProgramId, isError);
		}
		wait();
	}
}


void CPU::launchProgram1(void) {
	CPU::launchProgram(0);
}
void CPU::launchProgram2(void) {
	CPU::launchProgram(1);
}
void CPU::launchProgram3(void) {
	CPU::launchProgram(2);
}
void CPU::launchProgram4(void) {
	CPU::launchProgram(3);
}
void CPU::launchProgram5(void) {
	CPU::launchProgram(4);
}
void CPU::launchProgram6(void) {
	CPU::launchProgram(5);
}