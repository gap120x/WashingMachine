#include "systemc.h"
#include "WashMachineTopModule.h"

//wska�nik na modu� topModule
SYSTEM* topModule = NULL;


//funkcja main, gdzie rozpoczyna si� symulacja
int sc_main(int argc, char* argv[]) {

	cout << "Pralka Zostala Uruchomiona" << endl;

	//stworzenie instancji modu�u g��wnego (top modu�)
	topModule = new SYSTEM("top_module");

	//start symulacji
	sc_start();

	return(0);
}