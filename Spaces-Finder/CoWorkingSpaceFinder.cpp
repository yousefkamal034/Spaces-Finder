#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "structs.h"
using namespace std;

User usersArray[100];
Booking bookingsArray[100];
int totalUsersCount = 0;
int totalBookingsCount = 0;


int Log_in();
int Sign_up();
int Logging();
void LoadData();
int AddSpace();
void admin_main_menu();
void view_my_bookings(int userid);
void book_space(int userid);
bool isvaliddate(string date);

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
	cout << "Enter A UserName: ";
	getline(cin >> ws, tempUsername);
	cout << "Enter Email: ";
	cin >> tempEmail;
	cout << "Create A Password: ";
	cin >> tempPassword;
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
}

int AddSpace() {
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

void admin_main_menu() {
	int choice;
	cout << "______________________\n 1.add a space\n 2.delete a space\n 3.logout\n 4.TODO\n __________________\n";
	while (true) {
		cout << "choice: ";
		cin >> choice;
		if (choice == 1) {
			system("cls");
			AddSpace();
			break;
		}
		else if (choice == 2)
			continue; //TODO
		else if (choice == 3)
			continue; //TODO
		else 
			continue; //TODO
	}
}
void view_my_bookings(int userid) {
		for (int i = 0; i < totalBookingsCount; i++) {
			if (bookingsArray[i].UserId == userid) {
				cout << "Booking ID: " << bookingsArray[i].BookingId;
				cout << "Space ID: " << bookingsArray[i].SpaceId;
				cout << "Date: " << bookingsArray[i].date;
				cout << "Hours: " << bookingsArray[i].Hours;
				cout << "Total Cost: " << bookingsArray[i].TotalCost;
				cout << "Seats: " << bookingsArray[i].Seats;
				cout << "-----------------------------";
			}
		}
	}
	
void book_space(int userid) {
	int chosenspaceid;
	int hours, seats;
	string date;
		cout << "Enter Space ID: ";
		cin >> chosenspaceid;
		for (int i = 0; i < totalBookingsCount; i++) {
			if (bookingsArray[i].SpaceId == chosenspaceid) {
				//BREAK TAKEN RIGHT HERE , STILL GONNA CONTINUE
				cout << "Enter how many seats you want to book: ";
				cin >> seats;
				while (seats > bookingsArray[i].Seats) {
					cout << "Not enough seats available!\n";
					cin >> seats;
				}
				cout << "Enter how many hours you want to book for: ";
				cin >> hours;
				while (hours > 13) {
					cout << "You can't book for more than 12 hours!\n";
					cin >> hours;
				}
				cout << "Enter the date you want to book for (DD/MM/YYYY): ";
				cin >> date;
				while (!isvaliddate(date)) {
					cout << "Invalid date format! Please enter in DD/MM/YYYY format: ";
					cin >> date;
				}
				int totalcost = hours * bookingsArray[i].TotalCost;
				cout << "booking successful!, Here's your booking details: \n";
				cout << "Booking ID: " << bookingsArray[i].BookingId << endl;
				cout << "Space ID: " << bookingsArray[i].SpaceId << endl;
				cout << "Date: " << date << endl;
				cout << "Hours: " << hours << endl;
				cout << "Total Cost: " << totalcost << endl;
			
			}
		

		}



	
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
		return true;
	}
}

int main(){

	LoadData();
	int activeUserID=Logging(); //if -1 there is error  if = 0 activeuser is admin 
	if (activeUserID == 0)
		admin_main_menu();
	book_space(activeUserID);


}