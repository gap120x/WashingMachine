#include <sstream>
#include <string>
#include "systemc.h"
#include "list"

using namespace std;

SC_MODULE(CPU)
{

	//porty modu³u

	//wejœcie zegarowe
	sc_in<bool> clk;

	//wybrany prze³¹cznik (który uruchamia odpowiedni modu³/programów pralki)
	sc_in<sc_uint<16>> programChoice;

	//wejœcie sygnalizuj¹ce o wysy³aniu danych z modu³u Switches
	sc_in<bool> switchReceiving;

	//wyjœcie sygnalizuj¹ce o przetworzeniu wybrania ¿¹danego programu
	sc_out<bool> switchProgramEnded;

	//tablica przechowuj¹ca prêdkoœci wirowania poszczególnych programów pralki
	const int washerPrograms[6] = { 0, 800, 900, 1000, 1100, 1200 };

	//pocz¹tkowy stan prze³¹czników (0 - wy³¹czony, 1 - w³¹czony)
	int activeSwitches[6] = { 0, 0, 0, 0, 0,0};

	//zmienna przechowuj¹ca numer aktywnego programu, startowa wartoœæ to -1
	int activeProgramId = -1;

	//zmienna przechowuj¹ca informacjê o ostatnim b³êdzie
	//b³¹d rozumiemy jako wybranie 2 programów na raz (2 prze³¹czniki w³¹czone/aktywne w tym samym momencie)
	bool isError = false;
	
	//zmienna przechowuj¹ca identyfikator programu, który aktualnie jest uruchamiany
	int inProgress = 0;

	//zmienna informuj¹ca o zmianie programu pralki
	bool isProcessed = false;

	sc_out<sc_uint<16>> outputDataCpu2;
	sc_in<bool> isCpu2Reading;
	sc_out<bool> isSendingToCpu2;



	//funckje modu³u
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


	//konstruktor modu³u CPU
	SC_CTOR(CPU) {

		//w¹tki wra¿liwe na wzrastaj¹ce zbocze zegarowe, uruchamiane przy starcie symulacji
		SC_CTHREAD(switchHandler, clk.pos());

		SC_CTHREAD(launchProgram1, clk.pos());
		SC_CTHREAD(launchProgram2, clk.pos());
		SC_CTHREAD(launchProgram3, clk.pos());
		SC_CTHREAD(launchProgram4, clk.pos());
		SC_CTHREAD(launchProgram5, clk.pos());
		

		
	}

};