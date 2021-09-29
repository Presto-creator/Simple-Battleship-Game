#include "battleship.h"
#include <iostream>
#include <ctime>
#include<string>
using namespace std;

//this is a friend function to Location class.
bool compare(const Location& loc1, const Location& loc2) {
    return (loc1 == loc2);
    /*notice that == operator is overloaded for the Location class*/

}

//overloding the << operator to teach the compiler how to print a ship info using cout
ostream& operator<<(ostream& os, const Ship& sh)
{
    string status;
    if (!sh.sunk)
        status = " up ";
    else
        status = " sunk ";
    sh.loc.print();

    os << "->" << status;
    return os;
}

//--------Location implementation-----------------------------------------------------------------------//

Location::Location() {
    /*void constructor, dynamically allocates the coordinates array and assigns -1 to both of the coordinates*/
    coordinates = new int[2];
    coordinates[0] = -1;
    coordinates[1] = -1;
}

Location::Location(int x, int y) {
    coordinates = new int[2];
    coordinates[0] = x;
    coordinates[1] = y;
}

void Location::pick() {
    /*picks a random location. Means assigns 1 to 6 to the elements of the coordinates array*/
    coordinates[0] = rand() % FIELD_SIZE;
    coordinates[1] = rand() % FIELD_SIZE;
}

void Location::fire() {
    
    do {
        
        cout << "enter x and y on seperate lines as 1-6 each: ";
        cin >> this->coordinates[0];
        cout << " ";
        cin >> this->coordinates[1];
        if (this->coordinates[0] < 1 || this->coordinates[0] > FIELD_SIZE || this->coordinates[1] < 1 || this->coordinates[1] > FIELD_SIZE) {
            cout << "Coordinate input failed! Try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            this->coordinates[0] = -1;
            this->coordinates[1] = -1;
        }
            
    } while (cin.fail() || this->coordinates[0] < 0 || this->coordinates[0] > FIELD_SIZE || this->coordinates[1] < 0 || this->coordinates[1] > FIELD_SIZE);

}

void Location::print() const {
    /*prints location in format "[x,y]" e.g., [2,4]*/
    cout << "[" << coordinates[0] << ", " << coordinates[1] << "]";
}


Location::Location(const Location& org) { /* copycostructor*/
    coordinates = new int[2];
    coordinates[0] = org.coordinates[0];
    coordinates[1] = org.coordinates[1];
}
Location& Location::operator=(const Location& rhs) {
    /*assignment overloading*/
    if (this != &rhs) {
        /*no need to delete the older array since it has the same length.*/
        coordinates[0] = rhs.coordinates[0];
        coordinates[1] = rhs.coordinates[1];
    }
    return *this;
}
Location::~Location() {
    /*destructor*/
    delete[] coordinates;
}


//--------Ship implementation------------------------------------------------//

Ship::Ship() {
    
    sunk = false;
}

bool Ship::match(const Location& otherLocation)const { 
    if (compare(this->loc, otherLocation)) {
        return true;
    }
    else {
        return false;
    }
}

void Ship::sink()
{
    sunk = true;
}

void Ship::setLocation(const Location& z)
{
    this->loc = z;
}

void Ship::printShip() const
{
    this->loc.print();
        if (this->isSunk()) {
            cout << " is sunk!" << endl;
    }
        else {
            cout << " is above water! " << endl;
        }
}

//--------Fleet implementation ------------------//

int Fleet::check(const Location& loc) const
{
    for (int i = 0; i < FLEET_SIZE; ++i) {
        if (this->ships[i].match(loc)) {
            return i;
        }
    }
    return -1;
}


void Fleet::deployFleet()
{
    for (int i = 0; i < FLEET_SIZE; ++i) {
        Location loc(rand() % FLEET_SIZE, rand() % FLEET_SIZE);
        ships[i].setLocation(loc);
    }
}

bool Fleet::operational() const
{
    for (int i = 0; i < FLEET_SIZE; ++i) {
        if (!(this->ships[i].isSunk())) {
            return true;
        }
    }
    return false;
}

int Fleet::isHitNSink(const Location& loc)
{
    for (int i = 0; i < FLEET_SIZE; ++i) {
        if (this->ships[i].match(loc)) {
            if (this->ships[i].isSunk()) {
                return 2;
            }
            else {
                return 1;
            }
        }
    }

    return 0;
}

void Fleet::printFleet() const
{
    cout << endl;
    for (int i = 0; i < FLEET_SIZE; ++i) {
        cout << "Ship " << i << ": ";
        ships[i].printShip();
    }
}

Ship* Fleet::getShipList()
{
    return nullptr;
}

int Fleet::getFleetSize()
{
    return 0;
}


