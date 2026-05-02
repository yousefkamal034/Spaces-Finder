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
bool isFloat(string s);
bool isNumber(string s);
bool nospaces(string x);
void displaySpaces();
void ViewSpaces();
int Logging();
void increaseArray(string x);
int user_main_menu();



int AddSpace() {
	system("cls");

	if (totalSpacesCount == spaceCapacity) { // increase the spaceArray if needed
		increaseArray("space");
	}

	string temp, tempName, tempArea;
	string haswifi, hasmr; // hasmr = HasMeetingRoom
	while (true) {
		cout << "enter space name: ";
		getline(cin >> ws, tempName);
		if (!nospaces(tempName)) { // if it contains spaces
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
		cout << "this isn't a positive number, please enter it again: ";
		getline(cin >> ws, temp);
	}
	spaceArray[totalSpacesCount].PricePerHour = stoi(temp);

	cout << "enter number of seats available: ";
	getline(cin >> ws, temp);
	while (!isNumber(temp)) {
		cout << "this isn't a positive number, please enter it again: ";
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

	while (true) { // generate a random spaceid, and check to make sure it's unique
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
	string tempid; // to store the id for the space i want to edit
	bool found = false;
	int j; // this is the index for the space i want to change in the space array
	displaySpaces();

	while (true) { // big loop to get a valid, existing space id
		cout << "enter the id for the space you want to edit (press b to go back): ";
		getline(cin >> ws, tempid);

		if (tempid == "b" || tempid == "B") { // if admin wants to go back
			system("cls");
			return 0;
		}

		else if (isNumber(tempid)) {
			for (int i = 0; i < totalSpacesCount; i++) {
				if (spaceArray[i].SpaceId == stoi(tempid)) {
					found = true;
					j = i;
					break;
				}
			}

			if (found == false) {
				cout << "didn't find space\n";
				continue;
			}
			break;
		}
		
		else {
			cout << "invalid input\n";
		}
	}

	string choice;
	string newwifi, newhmr; // hasmr = has meeting room
	cout << "change:\n1.Name\n2.Area\n3.price per hour\n4.number of seats available\n5.Rating\n6.HasWifi\n7.HasMeetingRoom\n(press 'b' to go back)\nchoice: ";
	
	while (true) { // a big loop to get a valid choice from admin
		getline(cin >> ws, choice);
		if (choice == "b" || choice == "B") {
			system("cls");
			return 0;
		}

		else if (isNumber(choice) && stoi(choice) >= 1 && stoi(choice) <= 7) { // using isNumber so inputs like 1.5 won't work
			break;
		}

		else {
			cout << "please enter a number from 1 to 7, or 'b' to go back.\n";
			cout << "choice: ";
		}

	}


	string temp;
	switch (stoi(choice)) {
	case 1:
		while (true) {
			cout << "enter new name: ";
			getline(cin >> ws, temp);
			if (!nospaces(temp)) {
				cout << "name can't contain spaces.\n";
				continue;
			}
			spaceArray[j].Name = temp;
			break;
		} break;
	case 2:
		while (true) {
			cout << "enter new area: ";
			getline(cin >> ws, temp);
			if (!nospaces(temp)) {
				cout << "area can't contain spaces.\n";
				continue;
			}
			spaceArray[j].Area = temp;
			break;
		} break;
	case 3:
		while (true) {
			cout << "enter new price per hour: ";
			getline(cin >> ws, temp);
			if (!isNumber(temp)) {
				cout << "price per hour must be a number.\n";
				continue;
			}
			spaceArray[j].PricePerHour = stoi(temp);
			break;
		} break;
	case 4:
		while (true) {
			cout << "enter new number of seats available: ";
			getline(cin >> ws, temp);
			if (!isNumber(temp)) {
				cout << "number of seats must be a number.\n";
				continue;
			}
			spaceArray[j].NoOfSeatAvailable = stoi(temp);
			break;
		} break;
	case 5:
		while (true) {
			cout << "enter new rating (0:5) : ";
			getline(cin >> ws, temp);
			if (!isFloat(temp) || stof(temp) > 5 || stof(temp) < 0) {
				cout << "rating must be a number between 0 and 5\n";
				continue;
			}
			spaceArray[j].Rating = stof(temp);
			break;
		} break;
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
			else {
				cout << "please enter 'y' or 'n' only.\n";
				continue;
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
			else {
				cout << "please enter 'y' or 'n' only.\n";
				continue;
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

	displaySpaces();
	while (true) {
		bool found = false;
		while (true) {
			cout << "enter the id for the space you want to delete (press b to go back): ";
			getline(cin >> ws, chosenid);

			if (chosenid == "b" || chosenid == "B") { // if admin chose to go back
				system("cls");
				return 0;
			}

			else if (isNumber(chosenid) && nospaces(chosenid))
				break;
			else
				cout << "id must be a positive integer.\n";
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
				for (int b = 0; b < totalBookingsCount; b++) { // we delete any bookings related to that space
					if (bookingsArray[b].SpaceId == stoi(chosenid)) {
						bookingsArray[b] = bookingsArray[totalBookingsCount - 1];
						totalBookingsCount--;
						b--; // so if there is 2 booking next to each other
					}
				}
				break;
			}
		}

		if (found == false) {
			cout << "didn't find space!\n";
			continue;
		}

		return 0;
	}
}

int ViewAllBookings() {
	system("cls");
	// just read everything from the bookings array bruh
	for (int i = 0; i < totalBookingsCount; i++) {
		cout << "Booking ID: " << bookingsArray[i].BookingId << endl;
		cout << "User ID: " << bookingsArray[i].UserId << endl;
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
		cout << "______________________\n 1.add a space\n 2.edit a space\n 3.delete a space\n 4.View all bookings\n 5.logout \n 6.exit program\n ___________________\n";
		cout << "choice: ";
		getline(cin >> ws, choice);
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
