#include <systemc.h>

SC_MODULE(SWITCHES) {

	//porty modu�u
	sc_in<bool> isProcessed;
	//wej�cie zegarowe
	sc_in<bool> clk;
	//wyj�cie danych wpisanych przez u�ytkownika (wybrany prze��cznik)
	sc_out<sc_uint<16>> input;
	//wyj�cie sygnalizuj�ce modu� CPU o wysy�aniu danych
	sc_out<bool> isSending;
	

	//funkcje modu�u
	void clearConsole();
	int readUserInput();
	void sendUserInput(int userInput);
	void closeSendingOutput();
	void initRead();


	//konstruktor modu�u
	SC_CTOR(SWITCHES) {
		//w�tek wra�liwy na wzrastaj�ce zbocze zegarowe
		SC_CTHREAD(initRead, clk.pos());
	}

};

