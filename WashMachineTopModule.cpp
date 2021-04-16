#include "systemc.h"
#include "WashMachineTopModule.h"

//wskaŸnik na modu³ topModule
SYSTEM* topModule = NULL;


//funkcja main, gdzie rozpoczyna siê symulacja
int sc_main(int argc, char* argv[]) {

	cout << "Pralka Zostala Uruchomiona" << endl;

	//stworzenie instancji modu³u g³ównego (top modu³)
	topModule = new SYSTEM("top_module");

	//start symulacji
	sc_start();

	return(0);
}