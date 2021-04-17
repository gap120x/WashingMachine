#include <sstream>
#include <string>
#include "systemc.h"
#include "list"

using namespace std;

SC_MODULE(CPU)
{

	//porty modu�u

	//wej�cie zegarowe
	sc_in<bool> clk;

	//wybrany prze��cznik (kt�ry uruchamia odpowiedni modu�/program�w pralki)
	sc_in<sc_uint<16>> programChoice;

	//wej�cie sygnalizuj�ce o wysy�aniu danych z modu�u Switches
	sc_in<bool> switchReceiving;

	//wyj�cie sygnalizuj�ce o przetworzeniu wybrania ��danego programu
	sc_out<bool> switchProgramEnded;

	//tablica przechowuj�ca pr�dko�ci wirowania poszczeg�lnych program�w pralki
	const int washerPrograms[6] = { 0, 800, 900, 1000, 1100, 1200 };

	//pocz�tkowy stan prze��cznik�w (0 - wy��czony, 1 - w��czony)
	int activeSwitches[6] = { 0, 0, 0, 0, 0,0};

	//zmienna przechowuj�ca numer aktywnego programu, startowa warto�� to -1
	int activeProgramId = -1;

	//zmienna przechowuj�ca informacj� o ostatnim b��dzie
	//b��d rozumiemy jako wybranie 2 program�w na raz (2 prze��czniki w��czone/aktywne w tym samym momencie)
	bool isError = false;
	
	//zmienna przechowuj�ca identyfikator programu, kt�ry aktualnie jest uruchamiany
	int inProgress = 0;

	//zmienna informuj�ca o zmianie programu pralki
	bool isProcessed = false;

	sc_out<sc_uint<16>> outputDataCpu2;
	sc_in<bool> isCpu2Reading;
	sc_out<bool> isSendingToCpu2;



	//funckje modu�u
	void launchProgram(int id);
	void showSWStates(string switchesLine);
	void washerPanel();
	int countActiveSwitches();
	void switchHandler(void);
	void manageState(void);
	void toggle(int programChoice);
	void processData(int switchNr);
	int getActiveSwitch(void);
	void showError(void);

	void launchProgram1();
	void launchProgram2();
	void launchProgram3();
	void launchProgram4();
	void launchProgram5();


	//konstruktor modu�u CPU
	SC_CTOR(CPU) {

		//w�tki wra�liwe na wzrastaj�ce zbocze zegarowe, uruchamiane przy starcie symulacji
		SC_CTHREAD(switchHandler, clk.pos());

		SC_CTHREAD(launchProgram1, clk.pos());
		SC_CTHREAD(launchProgram2, clk.pos());
		SC_CTHREAD(launchProgram3, clk.pos());
		SC_CTHREAD(launchProgram4, clk.pos());
		SC_CTHREAD(launchProgram5, clk.pos());
		

		
	}

};