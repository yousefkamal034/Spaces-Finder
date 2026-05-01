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
void admin_main_menu();
int SaveAll();
bool isNumber(string s);
bool isFloat(string s);
bool nospaces(string x);
void displaySpaces();
void ViewSpaces(int userid);
int Logging();
void increaseArray(string x);
int user_main_menu();



int AddSpace() {
	system("cls");

	if (totalSpacesCount == spaceCapacity) {
		increaseArray("space");
	}

	string temp ,tempName, tempArea;
	string haswifi, hasmr; // hmr = HasMeetingRoom
	while (true) {
		cout << "enter space name: ";
		getline(cin >> ws, tempName);
		if (!nospaces(tempName)) {
			cout << "name can't contain spaces.\n";
			continue;
		}
		spaceArray[totalSpacesCount].Name = tempName;
		break;
	}


	while (true) {
		cout << "enter space area: ";
		getline(cin >> ws, tempArea);
		if (!nospaces(tempArea)) {
			cout << "area can't contain spaces.\n";
			continue;
		}
		spaceArray[totalSpacesCount].Area = tempArea;
		break;
	}

	cout << "enter price per hour: ";
	getline(cin >> ws, temp);
	while (!isNumber(temp)) {
		cout << "this isn't a number, please enter it again: ";
		getline(cin >> ws, temp);
	}
	spaceArray[totalSpacesCount].PricePerHour = stoi(temp);

	cout << "enter number of seats available: ";
	getline(cin >> ws, temp);
	while (!isNumber(temp)) {
		cout << "this isn't a number, please enter it again: ";
		getline(cin >> ws, temp);
	}
	spaceArray[totalSpacesCount].NoOfSeatAvailable = stoi(temp);

	cout << "what's the place's rating?: ";
	getline(cin >> ws, temp);
	while (!isFloat(temp) || stof(temp) > 5 || stof(temp) < 0) {
		cout << "please enter a number between 0 and 5.0: ";
		getline(cin >> ws, temp);
	}
	spaceArray[totalSpacesCount].Rating = stof(temp);

	while (true) { // to check if the admin entered y or n only
		cout << "does it have wifi? (y,n): ";
		getline(cin >> ws, haswifi);
		if (haswifi == "y" || haswifi == "Y") {
			spaceArray[totalSpacesCount].HasWifi = true; break;
		}
		else if (haswifi == "n" || haswifi == "N") {
			spaceArray[totalSpacesCount].HasWifi = false; break;
		}
		else
			cout << "wrong choice, enter y or n only\n";
	}

	while (true) { // to check if the admin entered y or n only
		cout << "does it have a meeting room? (y,n): ";
		getline(cin >> ws, hasmr);
		if (hasmr == "y" || hasmr == "Y") {
			spaceArray[totalSpacesCount].HasMeetingRoom = true; break;
		}
		else if (hasmr == "n" || hasmr == "N") {
			spaceArray[totalSpacesCount].HasMeetingRoom = false; break;
		}
		else
			cout << "wrong choice, enter y or n only\n";
	}

	while (true) {
		spaceArray[totalSpacesCount].SpaceId = rand() % (1000 - 100 + 1) + 100; // i think between 100 and 1000
		bool unique = true;
		for (int i = 0; i < totalSpacesCount; i++) {
			if (spaceArray[totalSpacesCount].SpaceId == spaceArray[i].SpaceId) {
				unique = false;
				break;
			}
		}
		if (unique)
			break;
	}

	totalSpacesCount++;
	system("cls");
	cout << "added space successfully\n";
	return 0;
}

int EditSpace() {
	system("cls");
	string tempid = "holder"; // to store the id for the space i want to edit
	bool found = false;
	displaySpaces();


	while (!isNumber(tempid) || !nospaces(tempid)) { // this effictively guards from wierd inputs like "dsigdaog nabg"
		cout << "enter the id for the space you want to edit (press b to go back): ";
		getline(cin >> ws, tempid);

		if (tempid == "b" || tempid == "B") { // if admin wants to go back
			return 0;
		}
	}

	int j; // this is the index of the space we want to edit
	for (int i = 0; i < totalSpacesCount; i++) {
		if (spaceArray[i].SpaceId == stoi(tempid)) {
			found = true;
			j = i;
			break;
		}
	}

	if (found == false) {
		system("cls");
		cout << "didn't find space!\n";
		return 0;
	}


	string choice;
	string newwifi, newhmr; // hmr = has meeting room
	cout << "change:\n1.Name\n2.Area\n3.price per hour\n4.number of seats available\n5.Rating\n6.HasWifi\n7.HasMeetingRoom\n(press 'b' to go back)\nchoice: ";
	getline(cin >> ws, choice);

	while (!isNumber(choice) || stoi(choice) < 1 || stoi(choice) > 7) {
		if (choice == "b" || choice == "B") {
			system("cls");
			return 0;
		}
		cout << "this isn't a number, please enter it again (1:7) : ";
		getline(cin >> ws, choice);
	}

	string temp = "holder 2";
	switch (stoi(choice)) {
	case 1:
		while (!nospaces(temp)) {
			cout << "enter new name: ";
			getline(cin >> ws, temp);
		}
		spaceArray[j].Name = temp;
		break;
	case 2:
		while (!nospaces(temp)) {
			cout << "enter new area: ";
			getline(cin >> ws, temp);
		}
		spaceArray[j].Area = temp;
		break;
	case 3:;
		while (!isNumber(temp)) {
			cout << "enter new price: ";;
			getline(cin >> ws, temp);
		}
		spaceArray[j].PricePerHour = stoi(temp);
		break;
	case 4:
		while (!isNumber(temp)) {
			cout << "enter new number of seats available: ";;
			getline(cin >> ws, temp);
		}
		spaceArray[j].NoOfSeatAvailable = stoi(temp);
		break;
	case 5:
		cout << "enter new rating: ";
		getline(cin >> ws, temp);
		while (!isFloat(temp) || stof(temp) > 5 || stof(temp) < 0) {
			cout << "enter new rating (0:5) : ";
			getline(cin >> ws, temp);
		}
		spaceArray[j].Rating = stof(temp);
		break;
	case 6: // loop to make sure admin hits y or n only
		while (true) {
			cout << "does the place have wifi?: (y,n)";
			getline(cin >> ws, temp);
			if (temp == "y" || temp == "Y") {
				spaceArray[j].HasWifi = true; break;
			}
			else if (temp == "n" || temp == "N") {
				spaceArray[j].HasWifi = false; break;
			}
		}break;
	case 7:
		while (true) { // same as above
			cout << "does the place have a meeting room?: (y,n)";
			getline(cin >> ws, temp);
			if (temp == "y" || temp == "Y") {
				spaceArray[j].HasMeetingRoom = true; break;
			}
			else if (temp == "n" || temp == "N") {
				spaceArray[j].HasMeetingRoom = false; break;
			}
		}break;
	}

	system("cls");
	cout << "updated space successfully\n";
	return 0;
}

int DeleteSpace() {
	system("cls");
	string chosenid;
	bool found = false;

	displaySpaces();

	while (true) {
		cout << "enter the id for the space you want to delete (press b to go back): ";
		getline(cin >> ws, chosenid);
		if (nospaces(chosenid))
			break;
		else
			cout << "id can't contain spaces.\n";
	}


	if (chosenid == "b" || chosenid == "B") { // if admin chose to go back
		system("cls");
		return 0;
	}

	while (!isNumber(chosenid)) {
		cout << "this isn't a number, please enter it again: ";
		getline(cin >> ws, chosenid);
	}


	for (int i = 0; i < totalSpacesCount; i++) {
		if (spaceArray[i].SpaceId == stoi(chosenid)) {

			found = true;

			// overwrite this space with the very last space in the array
			spaceArray[i] = spaceArray[totalSpacesCount - 1];

			// -1 from totalspacecount (a space is deleted)
			totalSpacesCount--;

			system("cls");
			cout << "Space deleted from memory!\n";
			break;
		}
	}

	if (found == false) {
		system("cls");
		cout << "didn't find space!\n";
	}

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
	return 0;

}

void admin_main_menu() {
	string choice;
	while (true) { // no need to check if it's a number or not, this loop handles this
		cout << "------------------ ADMIN MAIN MENU---------------------\n";
		cout << "______________________\n 1.add a space\n 2.edit a space\n 3.delete a space\n 4.View all bookings\n 5.logout \n 6.exit program\n __________________\n";
		cout << "choice: ";
		cin >> choice;
		if (choice == "1") {
			AddSpace();
		}
		else if (choice == "2") {
			EditSpace();
		}

		else if (choice == "3") {
			DeleteSpace();
		}

		else if (choice == "4") {
			ViewAllBookings();
		}

		else if (choice == "5") {
			system("cls");
			return;
		}

		else if (choice == "6") {
			SaveAll();
			exit(0);
		}
	}
}


