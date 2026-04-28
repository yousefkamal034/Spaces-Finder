#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include "structs.h"
using namespace std;

extern User* usersArray;
extern Booking* bookingsArray;
extern Space* spaceArray;
extern int totalUsersCount;
extern int totalBookingsCount;
extern int totalSpacesCount, spaceCapacity;
extern int activeUserID;

void LoadData();
int admin_main_menu();
int SaveAll();
bool isNumber(string s);
bool isFloat(string s);
void ViewSpaces(int userid);
int Logging();
void increaseSpaceArray();



int AddSpace() {
	system("cls");

	if (totalSpacesCount == spaceCapacity) {
		increaseSpaceArray();
	}

	string temp;
	char haswifi, hasmr; // hmr = HasMeetingRoom
	cout << "enter space name: ";
	getline(cin >> ws, spaceArray[totalSpacesCount].Name);

	cout << "enter area: ";
	cin >> spaceArray[totalSpacesCount].Area;

	cout << "enter price per hour: ";
	cin >> temp;
	while (!isNumber(temp)) {
		cout << "this isn't a number, please enter it again: ";
		cin >> temp;
	}
	spaceArray[totalSpacesCount].PricePerHour = stoi(temp);

	cout << "enter number of seats available: ";
	cin >> temp;
	while (!isNumber(temp)) {
		cout << "this isn't a number, please enter it again: ";
		cin >> temp;
	}
	spaceArray[totalSpacesCount].NoOfSeatAvailable = stoi(temp);

	cout << "what's the place's rating?: ";
	cin >> temp;
	while (!isFloat(temp) || stof(temp) > 5 || stof(temp) < 0) {
		cout << "please enter a number between 0 and 5.0: ";
		cin >> temp;
	}
	spaceArray[totalSpacesCount].Rating = stof(temp);

	while (true) { // to check if the admin entered y or n only
		cout << "does it have wifi? (y,n): ";
		cin >> haswifi;
		if (haswifi == 'y' || haswifi == 'Y') {
			spaceArray[totalSpacesCount].HasWifi = true; break;
		}
		else if (haswifi == 'n' || haswifi == 'N') {
			spaceArray[totalSpacesCount].HasWifi = false; break;
		}
		else
			cout << "wrong choice, enter y or n only\n";
	}

	while (true) { // to check if the admin entered y or n only
		cout << "does it have a meeting room? (y,n): ";
		cin >> hasmr;
		if (hasmr == 'y' || hasmr == 'Y') {
			spaceArray[totalSpacesCount].HasMeetingRoom = true; break;
		}
		else if (hasmr == 'n' || hasmr == 'N') {
			spaceArray[totalSpacesCount].HasMeetingRoom = false; break;
		}
		else
			cout << "wrong choice, enter y or n only\n";
	}

	srand(time(0)); // c++ why do u have to be like this???, i need this line so rand() works
	spaceArray[totalSpacesCount].SpaceId = rand() % (1000 - 100 + 1) + 100; // i think between 100 and 1000

	totalSpacesCount++;
	system("cls");
	cout << "added space successfully\n";
	admin_main_menu();
	return 0;
}

int EditSpace() {
	system("cls");
	string tempid; // to store the id for the space i want to edit
	bool found = false;
	cout << "enter the id for the space you want to edit (press q to go back): ";
	cin >> tempid;

	if (tempid == "q" || tempid == "Q") { // if admin wants to go back
		admin_main_menu();
		return 0;
	}

	while (!isNumber(tempid)) { // this effictively guards from wierd inputs like "dsigdaognabg"
		cout << "this isn't a number, please enter it again: ";
		cin >> tempid;
	}

	int j = 0; // this loop is to get the index of the space we want to edit and store it in a variable
	for (int i = 0; i < totalSpacesCount; i++) {
		if (spaceArray[i].SpaceId == stoi(tempid)) {
			found = true;
			break;
		}
		j++;
	}

	if (found = false) {
		cout << "didn't find space!\n";
		admin_main_menu();
		return 0;
	}


	string choice;
	string newwifi, newhmr; // hmr = has meeting room
	cout << "change:\n1.Name\n2.Area\n3.price per hour\n4.number of seats available\n5.Rating\n6.HasWifi\n7.HasMeetingRoom\n(press 'q' to go back)\nchoice: ";
	cin >> choice;

	if (choice == "Q" || choice == "q") {
		system("cls");
		admin_main_menu();
		return 0;
	}

	while (!isNumber(choice)) {
		cout << "this isn't a number, please enter it again: ";
		cin >> choice;
	}

	string temp;
	switch (stoi(choice)) {
	case 1:
		cout << "enter new name: ";
		cin >> spaceArray[j].Name;
		break;
	case 2:
		cout << "enter new area: ";
		cin >> spaceArray[j].Area;
		break;
	case 3:
		cout << "enter new price: ";
		cin >> temp;
		while (!isNumber(temp)) {
			cout << "this isn't a number, please enter it again: ";
			cin >> temp;
		}
		spaceArray[j].PricePerHour = stoi(temp);
		break;
	case 4:
		cout << "enter new number of seats available: ";
		cin >> temp;
		while (!isNumber(temp)) {
			cout << "this isn't a number, please enter it again: ";
			cin >> temp;
		}
		spaceArray[j].NoOfSeatAvailable = stoi(temp);
		break;
	case 5:
		cout << "enter new rating: ";
		cin >> temp;
		while (!isFloat(temp) || stof(temp) > 5 || stof(temp) < 0) {
			cout << "please enter a number between 0 and 5.0: ";
			cin >> temp;
		}
		spaceArray[j].Rating = stof(temp);
		break;
	case 6: // loop to make sure admin hits y or n only
		while (true) {
			cout << "does the place have wifi?: (y,n)";
			char choice2;
			cin >> choice2;
			if (choice2 == 'y' || choice2 == 'Y') {
				spaceArray[j].HasWifi = true; break;
			}
			else if (choice2 == 'n' || choice2 == 'N') {
				spaceArray[j].HasWifi = false; break;
			}
		}break;
	case 7:
		while (true) { // same as above
			cout << "does the place have a meeting room?: (y,n)";
			char choice3;
			cin >> choice3;
			if (choice3 == 'y' || choice3 == 'Y') {
				spaceArray[j].HasMeetingRoom = true; break;
			}
			else if (choice3 == 'n' || choice3 == 'N') {
				spaceArray[j].HasMeetingRoom = false; break;
			}
		}break;
	}

	system("cls");
	cout << "updated space successfully\n";
	admin_main_menu();
	return 0;
}

int DeleteSpace() {
	system("cls");
	string chosenid;
	bool found = false;

	cout << "enter the id for the space you want to delete (press b to go back): ";
	cin >> chosenid;

	if (chosenid == "b" || chosenid == "B") { // if admin chose to go back
		admin_main_menu();
		return 0;
	}

	while (!isNumber(chosenid)) {
		cout << "this isn't a number, please enter it again: ";
		cin >> chosenid;
	}


	for (int i = 0; i < totalSpacesCount; i++) {
		if (spaceArray[i].SpaceId == stoi(chosenid)) {

			found = true;

			// Overwrite this space with the very last space in the array
			spaceArray[i] = spaceArray[totalSpacesCount - 1];

			// -1 from totalspacecount (a space is deleted)
			totalSpacesCount--;

			cout << "Space deleted from memory!\n";
			break;
		}
	}

	if (found == false) {
		cout << "didn't find space!\n";
	}

	admin_main_menu();
	return 0;
}

int ViewAllBookings() {
	system("cls");
	// just read everything from the bookings array bruh
	for (int i = 0; i < totalBookingsCount; i++) {
		cout << "Booking ID: " << bookingsArray[i].BookingId << endl;
		cout << "Space ID: " << bookingsArray[i].SpaceId << endl;
		cout << "Date: " << bookingsArray[i].date << endl;
		cout << "Hours: " << bookingsArray[i].Hours << endl;
		cout << "Total Cost: " << bookingsArray[i].TotalCost << endl;
		cout << "Seats: " << bookingsArray[i].Seats << endl;
		cout << "-----------------------------" << endl;
	}
	admin_main_menu();
	return 0;

}

int admin_main_menu() {
	string choice;
	cout << "______________________\n 1.add a space\n 2.edit a space\n 3.delete a space\n 4.View all bookings\n 5.logout \n 6.exit program\n __________________\n";
	while (true) { // no need to check if it's a number or not, this loop handles this
		cout << "choice: ";
		cin >> choice;
		if (choice == "1") {
			return AddSpace();
		}
		else if (choice == "2") {
			return EditSpace();
		}

		else if (choice == "3") {
			return DeleteSpace();
		}

		else if (choice == "4") {
			return ViewAllBookings();
		}

		else if (choice == "5") {
			system("cls");
			activeUserID = Logging();
			if (activeUserID == 0)
				return admin_main_menu();
			ViewSpaces(activeUserID);
			return 0;
		}

		else if (choice == "6") {
			SaveAll();
			exit(0);
		}
	}
}


