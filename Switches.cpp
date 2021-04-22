#include <systemc.h>
#include "Switches.h"


//funkcja czyszcz¹ca konsolê
void SWITCHES::clearConsole(void)
{
	system("cls");
}

//funkcja sprawdzaj¹ca ci¹g znaków wpisany przez u¿ytkownika
int SWITCHES::readUserInput(void)
{
	bool temp_result = false;
	int result;	
	while (!temp_result) {
		if (!(cin >> result))
		{
			result = -1;
		}
		//je¿eli u¿ytkownik wybierzê poprawny prze³¹cznik nastêpujê wyjœcie
		//z pêtli while poprzez zmianê wartoœci zmiennej temp_result
		if(result < 6 && result > -1)
		{
			temp_result = true;
		}
		// w przypadku podania przez u¿ytkonika niepoprawnych danych wyœwietlany jest stosowny komunikat
		else
		{
			cout << "Nieprawidlowy Wybor! Wprowadz wartosc liczbowa od 0 do 5.";
			cin.clear();
			cin.ignore();
					
			temp_result = false;
			
		}
	}

	//zwrócenie wprowadzonych przez u¿ytkownika danych
	return result;
	
	
}

//funkcja wysy³aj¹ca wybrany przez numer prze³¹cznika do modu³u CPU
void SWITCHES::sendUserInput(int userInput) 
{
	//wstrzymanie funkcji przez jeden cykl zegarowy
	wait();
	//zakomunikowanie modu³owi CPU o nadchodz¹cych danych, tzw handshake
	isSending.write(1);
	//zapisanie wybranego numeru prze³¹cznika do wyjœcia modu³u
	input.write(userInput);
	wait();
}


//zakoñczenie wysy³ania wybranego prze³¹cznika do CPU
void SWITCHES::closeSendingOutput(void)  
{
	wait();
	//zakomunikowanie CPU o zakoñczeniu wysy³ania danych poprzez zmianê wartoœci
	//portu isSending na logiczne false
	isSending.write(0);
	wait();
}


//funkcja inicjalizuj¹ca odczyt danych wprowadzonych przez u¿ytkownika
//jest uruchamiana przy starcie symulacji w konstruktorze modu³u
void SWITCHES::initRead(void)
{
	int processed = 1;
	//nieskoñczona pêtla, która sprawdza input u¿ytkownika
	while (true) {

		//pobranie danych od u¿ytkownika
		 if (processed == 1) {
			int userInput = readUserInput();

			//wyczyszczenie konsoli
			clearConsole();

			//wys³anie danych do CPU
			sendUserInput(userInput);
		}
			//zakoñczenie wysy³ania danych do CPU
			closeSendingOutput();
			processed = isProcessed.read();

	}
}
