#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include "structs.h"
using namespace std;

extern User usersArray[100];
extern Booking bookingsArray[100];
extern Space spaceArray[100];
extern int totalUsersCount;
extern int totalBookingsCount;
extern int totalSpacesCount;

void LoadData();
void admin_main_menu();
int SaveAll();


int AddSpace() {
	system("cls");
	int j = totalSpacesCount;

	//Space s;
	char haswifi, hasmr; // hmr = HasMeetingRoom
	//string wifi, meetingroom;
	cout << "enter space name: ";
	getline(cin >> ws, spaceArray[j].Name);
	cout << "enter area: ";
	cin >> spaceArray[j].Area;
	cout << "enter price per hour: ";
	cin >> spaceArray[j].PricePerHour;
	cout << "enter number of seats available: ";
	cin >> spaceArray[j].NoOfSeatAvailable;
	cout << "what's the place's rating?: ";
	cin >> spaceArray[j].Rating;

	while (true) { // to check if the admin entered y or n only
		cout << "does it have wifi? (y,n): ";
		cin >> haswifi;
		if (haswifi == 'y' || haswifi == 'Y') {
			spaceArray[j].HasWifi = true; break;
		}
		else if (haswifi == 'n' || haswifi == 'N') {
			spaceArray[j].HasWifi = false; break;
		}
		else
			cout << "wrong choice, enter y or n only\n";
	}

	while (true) { // to check if the admin entered y or n only
		cout << "does it have a meeting room? (y,n): ";
		cin >> hasmr;
		if (hasmr == 'y' || hasmr == 'Y') {
			spaceArray[j].HasMeetingRoom = true; break;
		}
		else if (hasmr == 'n' || hasmr == 'N') {
			spaceArray[j].HasMeetingRoom = false; break;
		}
		else
			cout << "wrong choice, enter y or n only\n";
	}

	srand(time(0)); // c++ why do u have to be like this???, i need this line so rand() works
	spaceArray[j].SpaceId = rand() % (1000 - 100 + 1) + 100; // i think between 100 and 1000

	//ofstream file("Spaces.csv");
	//if (!file.is_open()) {
	//	cout << "couldn't open file";
	//	return 1;
	//}

	//file << "Name,SpaceID,Area,PricePerHour,NoOfSeatAvailable,Rating,HasWifi,HasMeetingRoom\n";
	//string wifi, hmr;
	//for (int i = 0; i < totalSpacesCount; i++) {
	//	if (spaceArray[i].HasWifi)
	//		wifi = "Yes";
	//	else
	//		wifi = "No";
	//	if (spaceArray[i].HasMeetingRoom)
	//		hmr = "Yes";
	//	else
	//		hmr = "No";
	//	file << spaceArray[i].Name << "," << spaceArray[i].SpaceId << "," << spaceArray[i].Area << "," << spaceArray[i].PricePerHour <<
	//		"," << spaceArray[i].NoOfSeatAvailable << "," << spaceArray[i].Rating << "," << wifi << "," << hmr << endl;
	//}
	//file.close();

	totalSpacesCount++;
	system("cls");
	admin_main_menu();
	return 0;
}

int EditSpace() { // alot os shinanigans i'll try to comment as good as i can
	system("cls");
	int tempid; // to store the id for the space i want to edit
	cout << "enter the id for the space you want to edit: ";
	cin >> tempid;
	int j = 0;
	for (int i = 0; i < totalSpacesCount; i++) {
		if (spaceArray[i].SpaceId == tempid) {
			break;
		}
		j++;
	}


	int choice;
	string newwifi, newhmr; // hmr = has meeting room
	cout << "change:\n1.Name  2.Area  3.price per hour  4.number of seats available\n 5.Rating  6.HasWifi  7.HasMeetingRoom\n choice: ";
	cin >> choice;
	switch (choice) {
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
		cin >> spaceArray[j].PricePerHour;
		break;
	case 4:
		cout << "enter new number of seats available: ";
		cin >> spaceArray[j].NoOfSeatAvailable;
		break;
	case 5:
		cout << "enter new rating: ";
		cin >> spaceArray[j].Rating;
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

	//ofstream file("Spaces.csv"); // read from original file
	//if (!file.is_open()) {
	//	cout << "couldn't open file";
	//	return 1;
	//}

	//file << "Name,SpaceID,Area,PricePerHour,NoOfSeatAvailable,Rating,HasWifi,HasMeetingRoom\n";
	//string wifi, hmr;
	//for (int i = 0; i < totalSpacesCount; i++) {
	//	if (spaceArray[i].HasWifi)
	//		wifi = "Yes";
	//	else
	//		wifi = "No";
	//	if (spaceArray[i].HasMeetingRoom)
	//		hmr = "Yes";
	//	else
	//		hmr = "No";
	//	file << spaceArray[i].Name << "," << spaceArray[i].SpaceId << "," << spaceArray[i].Area << "," << spaceArray[i].PricePerHour <<
	//		"," << spaceArray[i].NoOfSeatAvailable << "," << spaceArray[i].Rating << "," << wifi << "," << hmr << endl;
	//}
	//file.close();

	system("cls");
	cout << "updated space successfully\n";
	admin_main_menu();
	return 0;
}

int DeleteSpace() {
	system("cls");
	int chosenid;
	bool found = false;

	cout << "enter the id for the space you want to delete: ";
	cin >> chosenid;

	for (int i = 0; i < totalSpacesCount; i++) {

		if (spaceArray[i].SpaceId == chosenid) {

			found = true;

			// Overwrite this space with the very last space in the array
			spaceArray[i] = spaceArray[totalSpacesCount - 1];

			// Shrink the active size of the array so that last space is "deleted"
			totalSpacesCount--;

			cout << "Space deleted from memory!\n";
			break;
		}
	}
	//ofstream file("Spaces.csv");
	//if (!file.is_open()) {
	//	cout << "couldn't open file!\n";
	//	return 2;
	//}

	//file << "Name,SpaceID,Area,PricePerHour,NoOfSeatAvailable,Rating,HasWifi,HasMeetingRoom\n";
	//for (int i = 0; i < totalSpacesCount; i++) {
	//	string wifi, hmr;
	//	if (spaceArray[i].HasWifi)
	//		wifi = "Yes";
	//	else
	//		wifi = "No";
	//	if (spaceArray[i].HasMeetingRoom)
	//		hmr = "Yes";
	//	else
	//		hmr = "No";
	//	file << spaceArray[i].Name << "," << spaceArray[i].SpaceId << "," << spaceArray[i].Area << "," << spaceArray[i].PricePerHour <<
	//		"," << spaceArray[i].NoOfSeatAvailable << "," << spaceArray[i].Rating << "," << wifi << "," << hmr << endl;
	//}
	//file.close();
	admin_main_menu();
	return 0;
}

int ViewAllBookings() {
	system("cls");
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

void admin_main_menu() {
	int choice;
	cout << "______________________\n 1.add a space\n 2.edit a space\n 3.delete a space\n 4.View all bookings\n 5.exit program\n __________________\n";
	while (true) {
		cout << "choice: ";
		cin >> choice;
		if (choice == 1) {
			system("cls");
			AddSpace();
			break;
		}
		else if (choice == 2) {
			EditSpace();
			break;
		}

		else if (choice == 3) {
			DeleteSpace();
			break;
		}

		else if (choice == 4) {
			ViewAllBookings();
			break;
		}

		else
			SaveAll();
		exit(0);
	}
}


