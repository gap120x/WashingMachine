#include <systemc.h>

SC_MODULE(SWITCHES) {

	//porty modu³u
	sc_in<bool> isProcessed;
	//wejœcie zegarowe
	sc_in<bool> clk;
	//wyjœcie danych wpisanych przez u¿ytkownika (wybrany prze³¹cznik)
	sc_out<sc_uint<16>> input;
	//wyjœcie sygnalizuj¹ce modu³ CPU o wysy³aniu danych
	sc_out<bool> isSending;
	

	//funkcje modu³u
	void clearConsole();
	int readUserInput();
	void sendUserInput(int userInput);
	void closeSendingOutput();
	void initRead();


	//konstruktor modu³u
	SC_CTOR(SWITCHES) {
		//w¹tek wra¿liwy na wzrastaj¹ce zbocze zegarowe
		SC_CTHREAD(initRead, clk.pos());
	}

};

