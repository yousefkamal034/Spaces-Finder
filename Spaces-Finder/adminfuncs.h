#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include "structs.h"
using namespace std;

void admin_main_menu();

int AddSpace() {
	system("cls");
	Space s;
	char haswifi, hmr; // hmr = HasMeetingRoom
	string wifi, meetingroom;
	cout << "enter space name: ";
	getline(cin >> ws, s.Name);
	cout << "enter area: ";
	cin >> s.Area;
	cout << "enter price per hour: ";
	cin >> s.PricePerHour;
	cout << "enter number of seats available: ";
	cin >> s.NoOfSeatAvailable;
	cout << "what's the place's rating?: ";
	cin >> s.Rating;

	while (true) { // to check if the admin entered y or n only
		cout << "does it have wifi? (y,n): ";
		cin >> haswifi;
		if (haswifi == 'y' || haswifi == 'Y') {
			wifi = "Yes"; break;
		}
		else if (haswifi == 'n' || haswifi == 'N') {
			wifi = "No"; break;
		}
		else
			cout << "wrong choice, enter y or n only\n";
	}

	while (true) { // to check if the admin entered y or n only
		cout << "does it have a meeting room? (y,n): ";
		cin >> hmr;
		if (hmr == 'y' || hmr == 'Y') {
			meetingroom = "Yes"; break;
		}
		else if (hmr == 'n' || hmr == 'N') {
			meetingroom = "No"; break;
		}
		else
			cout << "wrong choice, enter y or n only\n";
	}

	srand(time(0)); // c++ why do u have to be like this???, i need this line so rand() works
	s.SpaceId = rand() % (1000 - 100 + 1) + 100; // i think between 100 and 1000
	ofstream file("Spaces.csv", ios::app); //ios::app for appending in the file
	if (file.is_open()) {
		file << s.Name << "," << s.SpaceId << "," << s.Area << "," << s.PricePerHour
			<< "," << s.NoOfSeatAvailable << "," << s.Rating << "," << wifi << "," << meetingroom << endl;
		file.close();
	}
	system("cls");
	admin_main_menu();
	return 0;
}

int EditSpace() { // alot os shinanigans i'll try to comment as good as i can
	system("cls");
	int tempid; // to store the id for the space i want to edit
	cout << "enter the id for the space you want to edit: ";
	cin >> tempid;
	Space s;
	ifstream file("Spaces.csv");
	if (file.is_open()) { // always check if it opened correctly
		string temp; // to store things temporary
		bool matching = false;
		getline(file, temp); // to get rid of the header file
		while (getline(file, s.Name, ',')) {
			getline(file, temp, ','); // to store the id in
			s.SpaceId = stoi(temp);
			if (s.SpaceId == tempid)
				matching = true;

			getline(file, s.Area, ',');

			getline(file, temp, ',');
			s.PricePerHour = stoi(temp);

			getline(file, temp, ',');
			s.NoOfSeatAvailable = stoi(temp);

			getline(file, temp, ',');
			s.Rating = stof(temp);

			getline(file, temp, ',');
			if (temp == "Yes")
				s.HasWifi = true;
			else s.HasWifi = false;

			getline(file, temp);
			if (temp == "Yes")
				s.HasMeetingRoom = true;
			else s.HasMeetingRoom = false;
			if (matching == true) // if we found the space
				break;
			else
				continue;
		}
		if (!matching) { // if we didn't find the space ever
			cout << "didn't find " << tempid << " in the data base, please check the id again";
		}
	}
	file.close();

	int choice;
	string newwifi, newhmr; // hmr = has meeting room
	cout << "change:\n1.Name  2.Area  3.price per hour  4.number of seats available\n 5.Rating  6.HasWifi  7.HasMeetingRoom\n choice: ";
	cin >> choice;
	switch (choice) {
	case 1:
		cout << "enter new name: ";
		cin >> s.Name;
		break;
	case 2:
		cout << "enter new area: ";
		cin >> s.Area;
		break;
	case 3:
		cout << "enter new price: ";
		cin >> s.PricePerHour;
		break;
	case 4:
		cout << "enter new number of seats available: ";
		cin >> s.NoOfSeatAvailable;
		break;
	case 5:
		cout << "enter new rating: ";
		cin >> s.Rating;
		break;
	case 6: // loop to make sure admin hits y or n only
		while (true) {
			cout << "does the place have wifi?: (y,n)";
			char choice2;
			cin >> choice2;
			if (choice2 == 'y' || choice2 == 'Y') {
				s.HasWifi = true; break;
			}
			else if (choice2 == 'n' || choice2 == 'N') {
				s.HasWifi = false; break;
			}
		}break;
	case 7:
		while (true) { // same as above
			cout << "does the place have a meeting room?: (y,n)";
			char choice3;
			cin >> choice3;
			if (choice3 == 'y' || choice3 == 'Y') {
				s.HasMeetingRoom = true; break;
			}
			else if (choice3 == 'n' || choice3 == 'N') {
				s.HasMeetingRoom = false; break;
			}
		}break;
	}

	if (s.HasWifi == true)
		newwifi = "Yes";
	else newwifi = "No";

	if (s.HasMeetingRoom == true)
		newhmr = "Yes";
	else newhmr = "No";

	ifstream origfile("Spaces.csv"); // read from original file
	if (!origfile.is_open()) {
		cout << "couldn't open file";
		return 1;
	}
	ofstream copy("temp.csv"); // write into another file, but change the space with the id in s with the data we entered
	if (!copy.is_open()) {
		cout << "a problem happened, couldn't create temp.csv";
		return 2;
	}
	string line, tempname, tempid2;
	int first2 = 1; // to make sure we don't try to stoi() the header
	while (getline(origfile, line)) {
		stringstream ss(line);
		if (first2 != 1) {
			getline(ss, tempname, ',');
			getline(ss, tempid2, ',');
			if (stoi(tempid2) == s.SpaceId) {
				copy << s.Name << "," << s.SpaceId << "," << s.Area << "," << s.PricePerHour
					<< "," << s.NoOfSeatAvailable << "," << s.Rating << "," << newwifi << "," << newhmr << endl;
				continue;
			}
		}
		first2++;
		copy << line << endl;
	}
	origfile.close();
	copy.close();

	// delete original file, and rename the file we changed
	if (remove("Spaces.csv") != 0) {
		cout << "Error: Could not delete the old database file!\n";
	}
	else {
		if (rename("temp.csv", "Spaces.csv") != 0) {
			cout << "Error: Could not rename the temp file!\n";
		}
		else {
			cout << "space successfully updated!\n";
		}
	}
	admin_main_menu();
}

int DeleteSpace() {
	system("cls");
	int chosenid;
	string header, temp;
	bool found = false;
	Space s;

	cout << "enter the id for the space you want to delete: ";
	cin >> chosenid;

	ifstream origfile("Spaces.csv");
	if (!origfile.is_open()) {
		cout << "error opening file\n";
		return 2;
	}

	getline(origfile, header);

	ofstream copy("temp.csv");
	if (!copy.is_open()) {
		cout << "couldn't create file\n";
		return 2;
	}

	copy << header << endl;

	string line;
	while (getline(origfile, line)) {
		stringstream ss(line);
		getline(ss, s.Name, ',');
		getline(ss, temp, ',');
		if (chosenid == stoi(temp)) {
			found = true;
			continue;
		}

		copy << line << endl;
	}

	origfile.close();
	copy.close();
	system("cls");

	// delete original file, and rename the file we changed
	if (remove("Spaces.csv") != 0) {
		cout << "Error: Could not delete the old database file!\n";
	}
	else {
		if (rename("temp.csv", "Spaces.csv") != 0) {
			cout << "Error: Could not rename the temp file!\n";
		}
		else {
			if (found == true)
				cout << "space successfully deleted!\n";
			else
				cout << "space not found\n";
		}
	}
	admin_main_menu();


}

void admin_main_menu() {
	int choice;
	cout << "______________________\n 1.add a space\n 2.edit a space\n 3.delete a space\n 4.exit program\n __________________\n";
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

		else
			exit(0);
	}
}
