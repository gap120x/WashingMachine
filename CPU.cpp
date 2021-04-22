#include <sstream>
#include <string>
#include "systemc.h"
#include "list"
#include "CPU.h"

using namespace std;

//funkcja, wy�wietlaj�ca stany poszczeg�lnych prze��cznik�w; emituje wygl�d przedniego panelu pralki
void CPU::showSWStates(string switchesLine) {
	cout << "________________________________________" << endl;
	cout << switchesLine << endl;
	cout << "[SW] [05 ] [04 ] [03 ] [02 ] [01 ] [00 ] " << endl;
	cout << "[--------------------------------------]" << endl;

}


//funkcja przechodz�ca przez tablic� prze��cznik�w, sprawdzaj�ca ich stan 
//i aktualizuj�ca informacj� o ich stanie na konsoli
void CPU::washerPanel()
{
	//ci�g znak�w, informuj�cy o stanie ka�ego prze��cznika
	std::stringstream swStrm;
	swStrm << "[SW]";

	//p�tla przechodz�ca po tablicy prze��cznik�w i sprawdzaj�ca ich stany
	for (int i = 5; i >= 0; i--) {
		if (activeSwitches[i] <= 0) {
			//w zale�no�ci od warto�ci w tablicy nast�puje konkatenacja 
			//s�ownego opisu stanu prze��cznika do ci�gu znak�w
			swStrm << " [OFF]";
		}
		else {
			swStrm << " [ON ]";
		}
	}
	//wywo�anie funkcji wy�wietlaj�cej stany prze��cznik�w; w argumencie przesy�amy informacj� o stanach prze��cznik�w
	showSWStates(swStrm.str());
}



//funkcja, kt�ra rozpoczyna proces uruchamiania nowego programu
void CPU::processData(int switchNr) {

	//rozpocz�cie uruchamiania programu
	isProcessed = true;
	//zapisanie id uruchamianego programu do zmiennej
	inProgress = switchNr;
	if (switchNr == 5) {

		cout << "CPU1 Wysyla dane do CPU2" << endl;
		isSendingToCpu2.write(1);

		outputDataCpu2.write(switchNr);

		do {
			wait();
		} while (!isCpu2Reading.read());

		isSendingToCpu2.write(0);
		wait();
	}


}


//funkcja uruchamiaj�ca program o przes�anym w argumencie ID programu
void CPU::launchProgram(int id)
{
	while (true) {
		wait(4);
		if (id < 5 && CPU::inProgress == id && CPU::isProcessed) {
			//koncepcja jest taka, �e id programu jest warto�ci� liczbow� o jeden mniejsz� od numeru programu
			cout << "Uruchomiono Program Nr: " << (id + 1) << "\n";
		}
	}
}

//funkcja zwracaj�ca ilo�� w��czonych prze��cznik�w
int CPU::countActiveSwitches(void)
{
	int active = 0;

	for (int i = 0; i < 6; i++) {
		if (activeSwitches[i] == 1) {
			active++;
		}
	}
	return active;
}

//funkcja zwracaj�ca w��czony/aktywny prze��cznik
int CPU::getActiveSwitch(void)
{
	for (int i = 0; i < 6; i++) {
		if (activeSwitches[i] == 1) {
			return i;
		}
	}
	return -1;
}

//funkcja zmieniaj�ca stan wybranego prze��cznika
void CPU::toggle(int programChoice)
{
	if (activeSwitches[programChoice] == 1) {
		activeSwitches[programChoice] = 0;
	}
	else {
		activeSwitches[programChoice] = 1;
	}
}
void CPU::sendToHex(int value) {

	isSendingToHex.write(1);

	outputHexDisplayData.write(value);

	do {
		wait();
	} while (!areHexesReading.read());

	isSendingToHex.write(0);
}

void CPU::sendToLed(bool value) {
	isSendingToLed.write(1);

	outputLedDisplayData.write(value);

	do {
		wait();
	} while (!isLedReading.read());

	isSendingToLed.write(0);

}

//Zarz�dzanie programami - uruchomienie danego programu, gdy tylko jeden prze��cznik jest aktywny/w��czony;
//gdy wi�cej ni� jeden prze��cznik aktywny, wy�wietla informacj� o b��dzie
void CPU::manageState(void)
{
	//zliczenie aktywnych/w��czonych prze��cznik�w
	int active = countActiveSwitches();

	//je�eli aktywnych prze��cznik�w jest wi�cej ni� jeden wy�wietla b��d
	if (active > 1) {
		isError = true;
		showError();
	}
	//w innym wypadku odpowiedni program jest uruchamiany
	else {
		int switchNr = getActiveSwitch();
		if (switchNr >= 0) {
			//activeProgramId = switchNr;

			processData(switchNr);
			sendToLed(0);
			sendToHex(switchNr);
			

		}
		else
		{
			sendToLed(0);
			sendToHex(-1);
		
			//activeProgramId = -1;
		}

	}
}
//funkcja wy�wietlaj�ca b��d, je�eli jest wi�cej ni� jeden aktywny/w��czony prze��cznik 
void CPU::showError(void)
{
	cout << "Wybrano wiecej niz jeden SW!. " << endl;
	sendToLed(1);
	sendToHex(-2);


}

//funkcja obs�uguj�ca prze��czanie program�w
void CPU::switchHandler(void) {
	washerPanel();

	int data;
	int previousProgramID;
	bool wasErrorPreviously;

	while (true) {
		wasErrorPreviously = isError;
		previousProgramID = activeProgramId;
		switchProgramEnded.write(0);
		isProcessed = false;
		isError = false;
		activeProgramId = -1;

		if (switchReceiving.read() == 1) {

			data = (int)programChoice.read();

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
			switchProgramEnded.write(1);
			washerPanel();
		}
		wait();

	}
}

//funkcj� uruchamiaj�ce poszczeg�lne programy/modu�y pralki
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