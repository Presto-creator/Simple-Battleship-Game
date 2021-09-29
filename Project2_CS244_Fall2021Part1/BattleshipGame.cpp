
#include "battleship.h"
#include <iostream>
/*
* Simple Battleship Simulator by Preston
* Finished on 9/29/2021
* Features BattleshipGame.cpp, testingFile.cpp, battleship.h, battleship.cpp
* If you want to use testingFile.cpp, change BattleshipGame.cpp's main to main0 or whatever, and change testineFile.cpp to main
*/

using std::cout; using std::cin; using std::endl;


int main() {

	string answer;
	Fleet fleet;
	fleet.deployFleet();

	Location userFire;

	do {
		cout << "Would you like the ships' status and position to be printed?\nEnter Y or y for yes, anything else for no: ";
		cin >> answer;
		if (answer.at(0) == 'Y' || answer.at(0) == 'y') {
			fleet.printFleet();
			cout << endl;
		}
		else {
			cout << endl << "Not printing status of ships." << endl;
		}

		userFire.fire();

		switch (fleet.isHitNSink(userFire)) {
		case 0:
			cout << "User missed!" << endl;
			break;
		case 1:
			cout << "Ship sunk at ";
			userFire.print();
			break;
		case 2:
			cout << "The ship at ";
			userFire.print();
			cout << " is already sunk!" << endl;
			break;
		}

		cout << endl;


	} while (fleet.operational());
	
	cout << endl << endl;
	fleet.printFleet();
	cout << "\n\nGame over! You Win!";
	return 0;
}