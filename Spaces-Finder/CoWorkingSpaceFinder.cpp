#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "structs.h"
#include "adminfuncs.h"
#include <cctype>

using namespace std;

User usersArray[100];
Booking bookingsArray[100];
Space spaceArray[100];
int activeUserID;
int totalUsersCount = 0;
int totalBookingsCount = 0;
int totalSpacesCount = 0;


int Log_in();
int Sign_up();
int Logging();
void LoadData();
int AddSpace();
void admin_main_menu();
void view_my_bookings(int userid);
void book_space(int userid);
bool isvaliddate(string date);
void FilterSpaces();
void SearchByArea();
bool isNumber(string s);
string stringtolower(string s);

// this is to turn a string into lower case
string stringtolower(string s) {
	int length = s.length();
	for (int i = 0; i < length; i++) {
		s[i] = tolower(s[i]);
	}
	return s;
}


// this is to check if a string is a number or not
bool isNumber(string s) {
	for (char c : s) {
		if (isdigit(c) == false) return false;
	}
	return true;
}


int Log_in() {
	system("cls");
	string username, password;
	bool pass_correct = false, name_correct = false;
	int pass_tries = 3, name_tries = 3;
	cout << "----Log In---" << endl;
	while (!name_correct) {
		cout << "Enter UserName(Case Sensitive): ";
		cin >> username;
		//for admin,username, password=admin
		if (username == "admin") {
			cout << "Password(Case Sensitive): ";
			cin >> password;
			if (password == "admin") {
				system("cls");
				cout << "Logged in as Admin Successfully!" << endl;
				return 0;
			}
			else {
				cout << "Incorrect Admin Password!" << endl;
				continue;
			}
		}
		for (int i = 0; i < totalUsersCount; i++) {
			if (usersArray[i].UserName == username) {
				while (!pass_correct) {
					cout << "Password(Case Sensitive): ";
					cin >> password;
					if (usersArray[i].Password == password) {
						system("cls");
						cout << "Logged in Succsesfully" << endl;
						pass_correct = true;
						return usersArray[i].Id;
					}
					else {
						if (pass_tries > 0) {
							cout << "Incorrect Password" << '\n' << pass_tries << " Tries left" << endl;
							pass_tries--;
							continue;
						}
						else {
							cout << "Incorrect Password" << '\n' << pass_tries << " Tries left" << endl;
							pass_correct = true;
							return -1;

						}
					}
				}
			}
		}
		if (!name_correct) {
			if (name_tries > 0) {
				cout << "Invalid Username" << '\n' << name_tries << " Tries left" << endl;
				name_tries--;
				continue;
			}
			else {
				cout << "Invalid UserName" << '\n' << name_tries << " Tries left" << endl;
				return -1;
			}
		}
	}
}


int Sign_up() {
	system("cls");
	string tempUsername, tempPassword, tempEmail, tempPhone;
	bool pass_correct = false;
	cout << "Enter A UserName: ";
	getline(cin >> ws, tempUsername);
	cout << "Enter Email: ";
	cin >> tempEmail;
	while (!pass_correct) {
		cout << "Create A password:";
		cin >> tempPassword;
		if (tempPassword.length() < 6) {
			cout << "Password Should be more than 6 characters" << endl;
			continue;
		}
		else
			pass_correct = true;
	}
	cout << "Enter Phone Number: ";
	cin >> tempPhone;
	srand(time(0));
	int tempUserID = rand() % (199 - 100 + 1) + 100;
	cout << "Your ID is" << tempUserID << endl;

	ofstream file("Users.csv", ios::app);
	if (file.is_open()) {
		file << tempUsername << "," << tempUserID << "," << tempPassword << "," << tempEmail << "," << tempPhone << "\n";
		file.close();
	}
	else
		return -1;
	usersArray[totalUsersCount].UserName = tempUsername;
	usersArray[totalUsersCount].Password = tempPassword;
	usersArray[totalUsersCount].Id = tempUserID;
	usersArray[totalUsersCount].Email = tempEmail;
	usersArray[totalUsersCount].Phone = tempPhone;
	totalUsersCount++;
	system("cls"); //clearing the Terminal
	return Log_in();
}


int Logging() {
	int choice;
	cout << "-----------" << '\n' << "1- Log in" << '\n' << "2-Don't Have an Account? " << '\n' << "-----------" << endl;
	cin >> choice;;
	if (choice == 1) {
		return Log_in();
	}
	else if (choice == 2) {
		return Sign_up();
	}
	else
		return Logging();
	}


void LoadData() {
	ifstream file("Users.csv");
	if (file.is_open()) {
		string header;
		getline(file, header);

		string tempID, tempUser, tempPassword, tempEmail, tempPhone;


		while (getline(file, tempUser, ',')) {
			getline(file, tempID, ',');
			getline(file, tempPassword, ',');
			getline(file, tempEmail, ',');
			getline(file, tempPhone, '\n');

			usersArray[totalUsersCount].UserName = tempUser;
			usersArray[totalUsersCount].Id = stoi(tempID);
			usersArray[totalUsersCount].Password = tempPassword;
			usersArray[totalUsersCount].Email = tempEmail;
			usersArray[totalUsersCount].Phone = tempPhone;

			totalUsersCount++;
		}
		file.close();


	}
	ifstream file2("bookings.csv");
	if (file2.is_open()) {
		string header;
		getline(file2, header);

		string bookingID, spaceID, userID, Date, Hours, TotalCost, Seats;


		while (getline(file2, bookingID, ',')) {
			getline(file2, spaceID, ',');
			getline(file2, userID, ',');
			getline(file2, Date, ',');
			getline(file2, Hours, ',');
			getline(file2, TotalCost, ',');
			getline(file2, Seats, '\n');

			bookingsArray[totalBookingsCount].BookingId = stoi(bookingID);
			bookingsArray[totalBookingsCount].SpaceId = stoi(spaceID);
			bookingsArray[totalBookingsCount].UserId = stoi(userID);
			bookingsArray[totalBookingsCount].date = Date;
			bookingsArray[totalBookingsCount].Hours = stoi(Hours);
			bookingsArray[totalBookingsCount].TotalCost = stoi(TotalCost);
			bookingsArray[totalBookingsCount].Seats = stoi(Seats);
			totalBookingsCount++;
		}
		file2.close();
	}
     ifstream file3("Spaces.csv");
	if (file3.is_open()) {
		string header;
		getline(file3, header);
		string tempName, tempID, tempArea, tempPricePerHour, tempNoOfSeatAvailable, tempRating, tempHasWifi, tempHasMeetingRoom;
		while (getline(file3, tempName, ',')) {
			getline(file3, tempID, ',');
			getline(file3, tempArea, ',');
			getline(file3, tempPricePerHour, ',');
			getline(file3, tempNoOfSeatAvailable, ',');
			getline(file3, tempRating, ',');
			getline(file3, tempHasWifi, ',');
			getline(file3, tempHasMeetingRoom, '\n');

			spaceArray[totalSpacesCount].Name = tempName;
			spaceArray[totalSpacesCount].SpaceId = stoi(tempID);
			spaceArray[totalSpacesCount].Area = tempArea;
			spaceArray[totalSpacesCount].PricePerHour = stoi(tempPricePerHour);
			spaceArray[totalSpacesCount].NoOfSeatAvailable = stoi(tempNoOfSeatAvailable);
			spaceArray[totalSpacesCount].Rating = stod(tempRating);
			if (tempHasWifi == "Yes")
				spaceArray[totalSpacesCount].HasWifi = true;
			else
				spaceArray[totalSpacesCount].HasWifi = false;
			if (tempHasMeetingRoom == "Yes")
				spaceArray[totalSpacesCount].HasMeetingRoom = true;
			else
				spaceArray[totalSpacesCount].HasMeetingRoom = false;
			totalSpacesCount++;
		}	
		file3.close();
	}
}


void ViewSpaces(int userid) {
	cout << "\n-----------Available Spaces-----------\n" << endl;
	
	for (int i = 0; i < totalSpacesCount; i++) {
		cout << i + 1 << ". ";
		cout << "Space Name: " << spaceArray[i].Name << endl;
		cout << "Space ID: " << spaceArray[i].SpaceId << endl;
		cout << "Area: " << spaceArray[i].Area << endl;
		cout << "Price Per Hour: " << spaceArray[i].PricePerHour << endl;
		cout << "Number of Seats Available: " << spaceArray[i].NoOfSeatAvailable << endl;
		cout << "Rating: " << spaceArray[i].Rating << " / 5" << endl;
		cout << "Has Wifi: " << (spaceArray[i].HasWifi ? "Yes" : "No") << endl;
		cout << "Has Meeting Room: " << (spaceArray[i].HasMeetingRoom ? "Yes" : "No") << endl;
		cout << "-----------------------------" << endl;
	}



while (true) {	
		cout << endl;
		cout << "s --> search area" << endl;
		cout << "f --> filtering" << endl;
		cout << "b --> Book a space" << endl;
		cout << "m --> main menu" << endl;
		cout << "Enter choice (s/f/b/m): ";
		char choice;
		cin >> choice;
		if (choice == 's' || choice == 'S') {
			SearchByArea();
		}
		else if (choice == 'f' || choice == 'F') {
			FilterSpaces();
		}
		else if (choice == 'b' || choice == 'B') {
			book_space(userid);
			
		}
		else if (choice == 'm' || choice == 'M') {
			SaveAll();
			break;
		}
		else {
			cout << "Invalid choice, please enter s, f, b, or m." << endl;
			continue;
		}
	}
}


void SearchByArea() {
	string area;
	cout << "Enter Area: ";
	getline(cin >> ws, area);
	bool found = false;
	cout << "\n-----------Search Results-----------\n" << endl;
	
	for (int i = 0; i < totalSpacesCount; i++) {
		if (stringtolower(spaceArray[i].Area) == stringtolower(area)) {
			found = true;
			cout << "Space Name: " << spaceArray[i].Name << endl;
			cout << "Space ID: " << spaceArray[i].SpaceId << endl;
			cout << "Area: " << spaceArray[i].Area << endl;
			cout << "Price Per Hour: " << spaceArray[i].PricePerHour << endl;
			cout << "Number of Seats Available: " << spaceArray[i].NoOfSeatAvailable << endl;
			cout << "Rating: " << spaceArray[i].Rating << " / 5" << endl;
			cout << "Has Wifi: " << (spaceArray[i].HasWifi ? "Yes" : "No") << endl;
			cout << "Has Meeting Room: " << (spaceArray[i].HasMeetingRoom ? "Yes" : "No") << endl;
			cout << "-----------------------------" << endl;
		}
	}
	if(!found) {
		cout << "No spaces found in this area." << endl;
	}
	system("pause");
	
}


void FilterSpaces() {
	char wifiFilter, meetingRoomFilter;
	double minRating;
	double maxPrice;
	bool found = false;
	cout << "\n------------Filters------------\n" << endl;
	while (true) {
		system("cls");
		cout << "\n------------Filters------------\n" << endl;
		cout << "P --> Max Price" << endl;
		cout << "R --> Min Rating" << endl;
		cout << "W --> WiFi" << endl;
		cout << "M --> Meeting room" << endl;
		cout << "A --> availability" << endl;
		cout << "Enter filter choice (P/R/W/M/A): ";
		char choice;
		cin >> choice;
		if (choice == 'P' || choice == 'p') {
			cout << "Enter maximum price per hour: ";
			cin >> maxPrice;
			cout << "\n--- Results for Price <= " << maxPrice << " ---" << endl;
			for (int i = 0; i < totalSpacesCount; i++) {
				if (spaceArray[i].PricePerHour <= maxPrice) {
					found = true;
					cout << "Space Name: " << spaceArray[i].Name << endl;
					cout << "Space ID: " << spaceArray[i].SpaceId << endl;
					cout << "Price Per Hour: " << spaceArray[i].PricePerHour << endl;
					cout << "-----------------------------" << endl;

				}
			}break;
		}
		else if (choice == 'R' || choice == 'r') {
			cout << "Enter minimum rating: ";
			cin >> minRating;
			for (int i = 0; i < totalSpacesCount; i++) {
				if (spaceArray[i].Rating >= minRating) {
					found = true;
					cout << "Space Name: " << spaceArray[i].Name << endl;
					cout << "Space ID: " << spaceArray[i].SpaceId << endl;
					cout << "Rating: " << spaceArray[i].Rating << " / 5" << endl;
					cout << "-----------------------------" << endl;
				}
			}break;
		}
		else if (choice == 'W' || choice == 'w') {
			cout << "Require WiFi? (Y/N): ";
			cin >> wifiFilter;
			wifiFilter = toupper(wifiFilter);
			for (int i = 0; i < totalSpacesCount; i++) {
				if (spaceArray[i].HasWifi == (wifiFilter == 'Y')) {
					found = true;
					cout << "Space Name: " << spaceArray[i].Name << endl;
					cout << "Space ID: " << spaceArray[i].SpaceId << endl;
					cout << "Has Wifi: " << (spaceArray[i].HasWifi ? "Yes" : "No") << endl;
					cout << "-----------------------------" << endl;
				}
			}break;
		}
		else if (choice == 'M' || choice == 'm') {
			cout << "Require Meeting Room? (Y/N): ";
			cin >> meetingRoomFilter;
			meetingRoomFilter = toupper(meetingRoomFilter);
			for (int i = 0; i < totalSpacesCount; i++) {
				if (spaceArray[i].HasMeetingRoom == (meetingRoomFilter == 'Y')) {
					found = true;
					cout << "Space Name: " << spaceArray[i].Name << endl;
					cout << "Space ID: " << spaceArray[i].SpaceId << endl;
					cout << "Has Meeting Room: " << (spaceArray[i].HasMeetingRoom ? "Yes" : "No") << endl;
					cout << "-----------------------------" << endl;
				}
			}break;
		}
		else if (choice == 'A' || choice == 'a') {
	
	for (int i = 0; i < totalSpacesCount - 1; i++) {
		for (int j = 0; j < totalSpacesCount - i - 1; j++) {
			if (spaceArray[j].NoOfSeatAvailable < spaceArray[j + 1].NoOfSeatAvailable) {
				Space temp = spaceArray[j];
				spaceArray[j] = spaceArray[j + 1];
				spaceArray[j + 1] = temp;
			}
		}
	}
	found = false; 
	for (int i = 0; i < totalSpacesCount; i++) {
		if (spaceArray[i].NoOfSeatAvailable > 0) {
			found = true;
			cout << "Space Name: " << spaceArray[i].Name << endl;
			cout << "Number of Seats: " << spaceArray[i].NoOfSeatAvailable << endl;
			cout << "-----------------------------" << endl;
		}
	}break;
}
		else {
			cout << "Invalid choice, please enter P, R, W, M, or A." << endl;
			continue;
		}
	}
}
	

void view_my_bookings(int userid) {
		for (int i = 0; i < totalBookingsCount; i++) {
			if (bookingsArray[i].UserId == userid) {
				cout << "Booking ID: " << bookingsArray[i].BookingId << endl;
				cout << "Space ID: " << bookingsArray[i].SpaceId << endl;
				cout << "Date: " << bookingsArray[i].date << endl;
				cout << "Hours: " << bookingsArray[i].Hours << endl;
				cout << "Total Cost: " << bookingsArray[i].TotalCost << endl;
				cout << "Seats: " << bookingsArray[i].Seats << endl;
				cout << "-----------------------------" << endl;
			}
		}
	}
	

void book_space(int userid) {
	string chosenspaceid;
	string date, seats, hours;
	bool zebda = false;

	cout << "Enter SpaceID: ";
	cin >> chosenspaceid;
	int j = 0;
	while (zebda == false) {
		while (!isNumber(chosenspaceid)) {
			cout << "enter a valid number for space id: ";
			cin >> chosenspaceid;
		}
		j = 0;
		for (int i = 0; i < totalSpacesCount; i++) {
			if (spaceArray[i].SpaceId == stoi(chosenspaceid)) {
				zebda = true; break;
			}
			j++;
		}
		if (zebda == false) {
			cout << "wrong id, please enter a valid space id: ";
			cin >> chosenspaceid;
		}
	}


	cout << "Enter how many seats you want to book: ";
	cin >> seats;
	bool seatsyes = false;
	if (isNumber(seats) && stoi(seats) <= spaceArray[j].NoOfSeatAvailable && stoi(seats) > 0)
		seatsyes = true;

	while (!seatsyes) {
		cout << "Enter A Valid number, Please Enter how many seats you want to book: ";
		cin >> seats;
		if (isNumber(seats) && stoi(seats) <= spaceArray[j].NoOfSeatAvailable && stoi(seats) > 0) {
			seatsyes = true;
		}
	}


	cout << "Enter how many hours you want to book for: ";
	cin >> hours;
	bool hoursyes = false;
	if (isNumber(hours) && stoi(hours) < 12 && stoi(hours) > 0)
		hoursyes = true;
	while (!hoursyes) {
		cout << "Enter A Valid number, Please Enter how many hours you want to book for (1:12) : ";
		cin >> hours;
		if (isNumber(hours) && stoi(hours) < 12 && stoi(hours) > 0)
			hoursyes = true;
	}


	cout << "Enter the date you want to book for (DD/MM/YYYY): ";
	cin >> date;
	while (!isvaliddate(date)) {
		cout << "Invalid date! Please enter Date Again: ";
		cin >> date;
	}

	srand(time(0));
	bookingsArray[totalBookingsCount].BookingId = rand() % (2000 - 1000 + 1) + 1000;
	bookingsArray[totalBookingsCount].SpaceId = spaceArray[j].SpaceId;
	bookingsArray[totalBookingsCount].UserId = activeUserID;
	bookingsArray[totalBookingsCount].date = date;
	bookingsArray[totalBookingsCount].Hours = stoi(hours);
	bookingsArray[totalBookingsCount].TotalCost = stoi(hours) * spaceArray[j].PricePerHour;
	bookingsArray[totalBookingsCount].Seats = stoi(seats);

	cout << endl << "booking successful!, Here's your booking details: \n";
	cout << "Booking ID: " << bookingsArray[totalBookingsCount].BookingId << endl;
	cout << "Space ID: " << bookingsArray[totalBookingsCount].SpaceId << endl;
	cout << "Date: " << date << endl;
	cout << "Hours: " << hours << endl;
	cout << "Total Cost: " << bookingsArray[totalBookingsCount].TotalCost << endl;
	totalBookingsCount++;
}


bool isvaliddate(string date) {
	if (date.length() != 10) {
		return false;
	}
	if (date[2] != '/' || date[5] != '/') {
		return false;
	}
	for (int i = 0; i < date.length(); i++) {
		if (i == 2 || i == 5) {
			continue;
		}
		else if (!isdigit(date[i])) {
			return false;
		}
	}
	string year = date.substr(6, 4);
	int yearInt = stoi(year);

	if (yearInt > 2029 || yearInt < 2026) {
		return false;
	}
	string month = date.substr(3, 2);
	int monthInt = stoi(month);

	if (monthInt > 12 || monthInt < 1) {
		return false;
	}
	string days = date.substr(0, 2);
	int daysInt = stoi(days);

	if (daysInt > 31 || daysInt < 1) {
		return false;
	}
	return true;

}


int SaveAll() {
	ofstream savespacefile("Spaces.csv");
	if (!savespacefile.is_open()) {
		cout << "couldn't open file";
		return 1;
	}

	savespacefile << "Name,SpaceID,Area,PricePerHour,NoOfSeatAvailable,Rating,HasWifi,HasMeetingRoom\n";
	string wifi, hmr;
	for (int i = 0; i < totalSpacesCount; i++) {
		if (spaceArray[i].HasWifi)
			wifi = "Yes";
		else
			wifi = "No";
		if (spaceArray[i].HasMeetingRoom)
			hmr = "Yes";
		else
			hmr = "No";
		savespacefile << spaceArray[i].Name << "," << spaceArray[i].SpaceId << "," << spaceArray[i].Area << "," << spaceArray[i].PricePerHour <<
			"," << spaceArray[i].NoOfSeatAvailable << "," << spaceArray[i].Rating << "," << wifi << "," << hmr << endl;
	}
	savespacefile.close();


	ofstream savebookingsfile("bookings.csv");
	if (!savebookingsfile.is_open()) {
		cout << "couldn't open file";
		return 1;
	}
	savebookingsfile << "BookingId,SpaceId,UserId,date,Hours,TotalCost,Seats\n";
	for (int i = 0; i < totalBookingsCount; i++) {
		savebookingsfile << bookingsArray[i].BookingId << "," << bookingsArray[i].SpaceId << "," << bookingsArray[i].UserId << "," <<
			bookingsArray[i].date << "," << bookingsArray[i].Hours << "," << bookingsArray[i].TotalCost << "," << bookingsArray[i].Seats << endl;
	}
	savebookingsfile.close();

	ofstream saveuserfile("Users.csv");
	if (!saveuserfile.is_open()) {
		cout << "couldn't open file";
		return 1;
	}
	saveuserfile << "UserName,UserID,Password,Email,Phonen\n";
	for (int i = 0; i < totalUsersCount; i++) {
		saveuserfile << usersArray[i].UserName << "," << usersArray[i].Id << "," << usersArray[i].Password << "," << usersArray[i].Email << "," << usersArray[i].Phone << endl;
	}
	saveuserfile.close();

	return 0;
}


int main(){

	LoadData();
	activeUserID=Logging(); //if -1 there is error  if = 0 activeuser is admin 
	if (activeUserID == 0)
		admin_main_menu();
	ViewSpaces(activeUserID);
}
