#include <systemc.h>
#include "Switches.h"


//funkcja czyszcz�ca konsol�
void SWITCHES::clearConsole(void)
{
	system("cls");
}

//funkcja sprawdzaj�ca ci�g znak�w wpisany przez u�ytkownika
int SWITCHES::readUserInput(void)
{
	bool temp_result = false;
	int result;	
	while (!temp_result) {
		if (!(cin >> result))
		{
			result = -1;
		}
		//je�eli u�ytkownik wybierz� poprawny prze��cznik nast�puj� wyj�cie
		//z p�tli while poprzez zmian� warto�ci zmiennej temp_result
		if(result < 6 && result > -1)
		{
			temp_result = true;
		}
		// w przypadku podania przez u�ytkonika niepoprawnych danych wy�wietlany jest stosowny komunikat
		else
		{
			cout << "Nieprawidlowy Wybor! Wprowadz wartosc liczbowa od 0 do 5.";
			cin.clear();
			cin.ignore();
					
			temp_result = false;
			
		}
	}

	//zwr�cenie wprowadzonych przez u�ytkownika danych
	return result;
	
	
}

//funkcja wysy�aj�ca wybrany przez numer prze��cznika do modu�u CPU
void SWITCHES::sendUserInput(int userInput) 
{
	//wstrzymanie funkcji przez jeden cykl zegarowy
	wait();
	//zakomunikowanie modu�owi CPU o nadchodz�cych danych, tzw handshake
	isSending.write(1);
	//zapisanie wybranego numeru prze��cznika do wyj�cia modu�u
	input.write(userInput);
	wait();
}


//zako�czenie wysy�ania wybranego prze��cznika do CPU
void SWITCHES::closeSendingOutput(void)  
{
	wait();
	//zakomunikowanie CPU o zako�czeniu wysy�ania danych poprzez zmian� warto�ci
	//portu isSending na logiczne false
	isSending.write(0);
	wait();
}


//funkcja inicjalizuj�ca odczyt danych wprowadzonych przez u�ytkownika
//jest uruchamiana przy starcie symulacji w konstruktorze modu�u
void SWITCHES::initRead(void)
{
	int processed = 1;
	//niesko�czona p�tla, kt�ra sprawdza input u�ytkownika
	while (true) {

		//pobranie danych od u�ytkownika
		 if (processed == 1) {
			int userInput = readUserInput();

			//wyczyszczenie konsoli
			clearConsole();

			//wys�anie danych do CPU
			sendUserInput(userInput);
		}
			//zako�czenie wysy�ania danych do CPU
			closeSendingOutput();
			processed = isProcessed.read();

	}
}
