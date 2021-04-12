#include "systemc.h"
#include "WashingMachine.h"

SYSTEM* top_module = NULL;

int sc_main(int argc, char* argv[]) {

	cout << "Pralka Zostala Uruchomiona" << endl;

	top_module = new SYSTEM("top_module");
	sc_start();

	return(0);
}