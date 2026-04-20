#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "structs.h"
#include "adminfuncs.h"
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
			spaceArray[totalSpacesCount].SpaceId = tempID;
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



void ViewSpaces() {
	cout << "\n-----------Available Spaces-----------\n" << endl;
	
	for (int i = 0; i < totalSpacesCount; i++) {
		cout << i + 1 << ". "
			<< spaceArray[i].Name << " | "
			<< spaceArray[i].Area << " | "
			<< spaceArray[i].PricePerHour << " EGP | "
			<< "☆" << spaceArray[i].Rating << " / 5 " << " | "
			<< "Wifi: " << (spaceArray[i].HasWifi ? "✔" : "✘") << " | "
			<< "Meeting Room: " << (spaceArray[i].HasMeetingRoom ? "✔" : "✘")
			<< endl;
	}
	
}

while(true) {
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
		break;
	}
	else {
		cout << "Invalid choice, please enter s, f, or b." << endl;
		continue;
	}
}


void SearchByArea() {
	string area;
	cout << "Enter Area: ";
	getline(cin >> ws, area);
	bool found = false;
	cout << "\n-----------Search Results-----------\n" << endl;
	
	for (int i = 0; i < totalSpacesCount; i++) {
		if (toLower(spaceArray[i].Area) == toLower(area)) {
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
	cout << "Max Price Per Hour: ";
	cin >> maxPrice;
	cout << "Minimum Rating: ";
	cin >> minRating;
	while (true) {
		cout << "Require Wifi? (y/n): ";
		cin >> wifiFilter;
		if (wifiFilter == 'y' || wifiFilter == 'Y' || wifiFilter == 'n' || wifiFilter == 'N') {
			break;
		}
		else {
			cout << "Invalid choice, please enter y or n." << endl;
		}
	}
	while (true) {
		cout << "Require Meeting Room? (y/n): ";
		cin >> meetingRoomFilter;
		if (meetingRoomFilter == 'y' || meetingRoomFilter == 'Y' || meetingRoomFilter == 'n' || meetingRoomFilter == 'N') {
			break;
		}
		else {
			cout << "Invalid choice, please enter y or n." << endl;
		}
	}
	cout << "\n-----------Filter Results-----------" << endl;
	for (int i = 0; i < totalSpacesCount; i++) {
		if (spaceArray[i].PricePerHour <= maxPrice && spaceArray[i].Rating >= minRating &&
			spaceArray[i].NoOfSeatAvailable > 0) {
			if ((wifiFilter == 'y' || wifiFilter == 'Y') && !spaceArray[i].HasWifi) {
				continue;
			}
			if ((meetingRoomFilter == 'y' || meetingRoomFilter == 'Y') && !spaceArray[i].HasMeetingRoom) {
				continue;
			}
			cout << "Space Name: " << spaceArray[i].Name << endl;
			cout << "Space ID: " << spaceArray[i].SpaceId << endl;
			cout << "Area: " << spaceArray[i].Area << endl;
			cout << "Price Per Hour: " << spaceArray[i].PricePerHour << endl;
			cout << "Number of Seats Available: " << spaceArray[i].NoOfSeatAvailable << endl;
			cout << "Rating: " << spaceArray[i].Rating << " / 5" << endl;
			cout << "Has Wifi: " << (spaceArray[i].HasWifi ? "Yes" : "No") << endl;
			cout << "Has Meeting Room: " << (spaceArray[i].HasMeetingRoom ? "Yes" : "No") << endl;
			cout << "-----------------------------" << endl;
			found = true;
		}
	}
	if (!found) {
		cout << "No spaces found matching the filters." << endl;
	}
	system("pause");
	
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
