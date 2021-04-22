#include <sstream>
#include <string>
#include "systemc.h"
#include "list"
#include "CPU.h"

using namespace std;

//funkcja, wyœwietlaj¹ca stany poszczególnych prze³¹czników; emituje wygl¹d przedniego panelu pralki
void CPU::showSWStates(string switchesLine) {
	cout << "________________________________________" << endl;
	cout << switchesLine << endl;
	cout << "[SW] [05 ] [04 ] [03 ] [02 ] [01 ] [00 ] " << endl;
	cout << "[--------------------------------------]" << endl;

}


//funkcja przechodz¹ca przez tablicê prze³¹czników, sprawdzaj¹ca ich stan 
//i aktualizuj¹ca informacjê o ich stanie na konsoli
void CPU::washerPanel()
{
	//ci¹g znaków, informuj¹cy o stanie ka¿ego prze³¹cznika
	std::stringstream swStrm;
	swStrm << "[SW]";

	//pêtla przechodz¹ca po tablicy prze³¹czników i sprawdzaj¹ca ich stany
	for (int i = 5; i >= 0; i--) {
		if (activeSwitches[i] <= 0) {
			//w zale¿noœci od wartoœci w tablicy nastêpuje konkatenacja 
			//s³ownego opisu stanu prze³¹cznika do ci¹gu znaków
			swStrm << " [OFF]";
		}
		else {
			swStrm << " [ON ]";
		}
	}
	//wywo³anie funkcji wyœwietlaj¹cej stany prze³¹czników; w argumencie przesy³amy informacjê o stanach prze³¹czników
	showSWStates(swStrm.str());
}



//funkcja, która rozpoczyna proces uruchamiania nowego programu
void CPU::processData(int switchNr) {

	//rozpoczêcie uruchamiania programu
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


//funkcja uruchamiaj¹ca program o przes³anym w argumencie ID programu
void CPU::launchProgram(int id)
{
	while (true) {
		wait(4);
		if (id < 5 && CPU::inProgress == id && CPU::isProcessed) {
			//koncepcja jest taka, ¿e id programu jest wartoœci¹ liczbow¹ o jeden mniejsz¹ od numeru programu
			cout << "Uruchomiono Program Nr: " << (id + 1) << "\n";
		}
	}
}

//funkcja zwracaj¹ca iloœæ w³¹czonych prze³¹czników
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

//funkcja zwracaj¹ca w³¹czony/aktywny prze³¹cznik
int CPU::getActiveSwitch(void)
{
	for (int i = 0; i < 6; i++) {
		if (activeSwitches[i] == 1) {
			return i;
		}
	}
	return -1;
}

//funkcja zmieniaj¹ca stan wybranego prze³¹cznika
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

//Zarz¹dzanie programami - uruchomienie danego programu, gdy tylko jeden prze³¹cznik jest aktywny/w³¹czony;
//gdy wiêcej ni¿ jeden prze³¹cznik aktywny, wyœwietla informacjê o b³êdzie
void CPU::manageState(void)
{
	//zliczenie aktywnych/w³¹czonych prze³¹czników
	int active = countActiveSwitches();

	//je¿eli aktywnych prze³¹czników jest wiêcej ni¿ jeden wyœwietla b³¹d
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
//funkcja wyœwietlaj¹ca b³¹d, je¿eli jest wiêcej ni¿ jeden aktywny/w³¹czony prze³¹cznik 
void CPU::showError(void)
{
	cout << "Wybrano wiecej niz jeden SW!. " << endl;
	sendToLed(1);
	sendToHex(-2);


}

//funkcja obs³uguj¹ca prze³¹czanie programów
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

//funkcjê uruchamiaj¹ce poszczególne programy/modu³y pralki
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