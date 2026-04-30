#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "structs.h"
#include "adminfuncs.h"
#include <cctype>

using namespace std;

User* usersArray = nullptr;
Booking* bookingsArray = nullptr;
Space* spaceArray = nullptr;
int activeUserID;
int totalUsersCount = 0, userCapacity = 0;
int totalBookingsCount = 0, bookingCapacity = 0;
int totalSpacesCount = 0, spaceCapacity = 0;


int Log_in();
int Sign_up();
int Logging();
void LoadData();
int AddSpace();
void admin_main_menu();
void view_my_bookings(int userid);
void ViewSpaces(int userid);
void book_space(int userid);
bool isvaliddate(string date);
void FilterSpaces();
void SearchByArea();
int user_main_menu();
void cancel_booking(int userid);

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


// this one is to check if a string is a float (i hate this featureless language)
bool isFloat(string str) {
	try {
		stof(str);
		return true;
	}
	catch (...) {
		return false;
	}
}


// a function to increase array count
void increaseArray(string x) {

	if (x == "space") {
		// a loop to make spacearray bigger by multiplying it's capacity * 2
		if (spaceCapacity == 0)
			spaceCapacity = 5;
		else
			spaceCapacity *= 2;

		Space* biggerarray = new Space[spaceCapacity];

		for (int i = 0; i < totalSpacesCount; i++)
			biggerarray[i] = spaceArray[i];

		if (spaceArray != nullptr)
			delete[] spaceArray;

		spaceArray = biggerarray;
	}

	else if (x == "user") {
		// a loop to make usersarray bigger by multiplying it's capacity * 2
		if (userCapacity == 0)
			userCapacity = 5;
		else
			userCapacity *= 2;

		User* biggerarray = new User[userCapacity];

		for (int i = 0; i < totalUsersCount; i++)
			biggerarray[i] = usersArray[i];

		if (usersArray != nullptr)
			delete[] usersArray;

		usersArray = biggerarray;
	}

	else if (x == "booking") {
		// a loop to make bookingarray bigger by multiplying it's capacity * 2
		if (bookingCapacity == 0)
			bookingCapacity = 5;
		else
			bookingCapacity *= 2;

		Booking* biggerarray = new Booking[bookingCapacity];

		for (int i = 0; i < totalBookingsCount; i++)
			biggerarray[i] = bookingsArray[i];

		if (bookingsArray != nullptr)
			delete[] bookingsArray;

		bookingsArray = biggerarray;
	}
}


int Log_in() {
	system("cls");
	string username, password;
	bool pass_correct = false, name_correct = false;
	int pass_tries = 3, name_tries = 3;
	cout << "----Log In---" << endl;
	while (!name_correct) {
		cout << "Enter UserName(Case Sensitive) (press 'b' to go back): ";
		cin >> username;

		if (username == "b" || username == "B")
			return -1;

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
							cout << "failed to log in" << endl;
							exit(0);
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
				cout << "failed to log in" << endl;
				exit(0);
			}
		}
	}
}


int Sign_up() {
	system("cls");

	if (totalUsersCount == userCapacity) {
		increaseArray("user");
	}

	string tempUsername, tempPassword, tempEmail, tempPhone;
	bool pass_correct = false;
	bool phoneok = false;

	while (true) { // a loop to make sure the username doesn't contain a space 
		bool nameok = true;
		cout << "Enter A UserName (presee 'b' to go back): ";
		getline(cin >> ws, tempUsername);

		if (tempUsername == "b" || tempUsername == "B") // to go back to login or signup page
			return -1;

		for (int i = 0; i < tempUsername.length(); i++) {
			if (tempUsername[i] == ' ') {
				cout << "username can't contain a space.\n";
				nameok = false;
				break;
			}
		}

		if (nameok)
			break;
	}



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

	while (!phoneok) {
		cout << "Enter Phone Number: ";
		cin >> tempPhone;
		if (isNumber(tempPhone)) {
			phoneok = true;
		}
		else {
			cout << "Phone Number must be a number.\n";
			continue;
		}
	}


	int tempUserID = rand() % (199 - 100 + 1) + 100;
	cout << "Your ID is" << tempUserID << endl;

	//ofstream file("Users.csv", ios::app);
	//if (file.is_open()) {
	//	file << tempUsername << "," << tempUserID << "," << tempPassword << "," << tempEmail << "," << tempPhone << "\n";
	//	file.close();
	//}
	//else
	//	return -1;
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
	string choice;
	cout << "-----------" << '\n' << "1- Log in" << '\n' << "2- Don't Have an Account? " << '\n' << "3- exit program\n" << "-----------" << endl;
	cout << "choice: ";
	cin >> choice;;
	if (choice == "1") {
		return Log_in();
	}
	else if (choice == "2") {
		return Sign_up();
	}
	else if (choice == "3") {
		SaveAll();
		exit(0);
	}
	else
		return Logging();
}


void LoadData() {
	// load users from Users.csv into usersarray
	ifstream file("Users.csv");
	if (file.is_open()) {

		string header;
		getline(file, header); // to get rid of the header line
		string tempID, tempUser, tempPassword, tempEmail, tempPhone;


		while (getline(file, tempUser, ',')) {
			if (tempUser.empty() || tempUser == "\n") // a small check for safety
				continue;

			// a loop to make usersarray bigger by multiplying it's capacity * 2
			if (totalUsersCount == userCapacity) {
				increaseArray("user");
			}

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

	// load bookings from bookings.csv into booking array
	ifstream file2("bookings.csv");
	if (file2.is_open()) {

		string header;
		getline(file2, header); // to get rid of the header line
		string bookingID, spaceID, userID, Date, Hours, TotalCost, Seats;


		while (getline(file2, bookingID, ',')) {
			if (bookingID.empty() || bookingID == "\n") // a small check for safety
				continue;

			// a loop to increase the size of booking array if needed
			if (totalBookingsCount == bookingCapacity) {
				increaseArray("booking");
			}

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

	// load spaces from Spaces.csv into spacesarray
	ifstream file3("Spaces.csv");
	if (file3.is_open()) {
		string header;
		getline(file3, header);
		string tempName, tempID, tempArea, tempPricePerHour, tempNoOfSeatAvailable, tempRating, tempHasWifi, tempHasMeetingRoom;
		while (getline(file3, tempName, ',')) {
			if (tempName.empty() || tempName == "\n") // a small check for safety
				continue;

			// a loop to make spacearray bigger by multiplying it's capacity * 2
			if (totalSpacesCount == spaceCapacity) {
				increaseArray("space");
			}

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
		string choice; // changed this to a string, so if the user types something like (hsdnf) no weird behaviour accours
		cin >> choice;
		if (choice == "s" || choice == "S") {
			SearchByArea();
		}
		else if (choice == "f" || choice == "F") {
			FilterSpaces();
		}
		else if (choice == "b" || choice == "B") {
			book_space(userid);
			// this loop is so the user sees the spaces again, probably could've made it in a better way
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
		}
		else if (choice == "m" || choice == "M") {
			system("cls");
			break;
		}
		else {
			cout << "Invalid choice, please enter 's', 'f', 'b', or 'm'." << endl;
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
	if (!found) {
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

	cout <<
		"1. cancel a booking\n"
		"2. main menu\n";

	string choice;
	while (true) {
		cout << "choice: ";
		cin >> choice;
		if (choice == "1") {
			cancel_booking(activeUserID);
			break;
		}
		else if (choice == "2") {
			system("cls");
			break;
		}
	}
}


void book_space(int userid) {
	if (totalBookingsCount == bookingCapacity) { // a small loop to check if we reached max bookings number and increase it
		increaseArray("booking");
	}

	string chosenspaceid = "b";
	string date, hours;
	string seats = "d";
	bool idfound = false;
	bool spaceok = false;
	bool dateok = false;
	int j = 0; // this is the chosen space index in spacesarray
	int availableseats = 0;

	while (true) {

		// --- STEP 1: GET SPACE ID ---
		if (!spaceok) {
			bool idfound = false;
			cout << "Enter SpaceID: ";
			cin >> chosenspaceid;

			while (!idfound) {
				while (!isNumber(chosenspaceid)) {
					cout << "Enter a valid number for space ID: ";
					cin >> chosenspaceid;
				}

				j = 0;
				for (int i = 0; i < totalSpacesCount; i++) {
					if (spaceArray[i].SpaceId == stoi(chosenspaceid)) {
						idfound = true;
						j = i;
						break;
					}
				}

				if (!idfound) {
					cout << "Wrong ID, please enter a valid space ID: ";
					cin >> chosenspaceid;
				}
			}
			spaceok = true; // Check it off the list!
			dateok = false;   // Make sure we ask for a date for this new space
		}

		// --- STEP 2: GET DATE ---
		if (!dateok) {
			cout << "Enter the date you want to book for (DD/MM/YYYY) (press b to go back): ";
			cin >> date;

			if (date == "b" || date == "B") {
				spaceok = false; // They want to go back, so we need a space again
				continue;         // Restart the loop from the top
			}

			while (!isvaliddate(date)) {
				cout << "Invalid date! Please enter Date Again: ";
				cin >> date;
			}
			dateok = true; // Check it off the list!
		}

		// --- STEP 3: CHECK AVAILABILITY ---
		availableseats = spaceArray[j].NoOfSeatAvailable;
		for (int i = 0; i < totalBookingsCount; i++) {
			if (bookingsArray[i].SpaceId == stoi(chosenspaceid) && bookingsArray[i].date == date) {
				availableseats -= bookingsArray[i].Seats; // don't break the loop, there might be more than 1 booking
			}
		}

		if (availableseats <= 0) {
			cout << "The space is fully booked on this date, please choose another date!\n";
			dateok = false; // Force them to pick a new date
			continue; // Restart the loop from the top
		}

		// --- STEP 4: GET SEATS ---
		cout << "-----------------------\nEnter how many seats you want to book (" << availableseats << " seats are available for this space on this date)\n"
			<< "(press 'd' to choose another date, or 'b' to choose another space): ";
		cin >> seats;

		if (seats == "d" || seats == "D") {
			dateok = false;
			continue; // Restart the loop to ask for a new date
		}

		if (seats == "b" || seats == "B") {
			spaceok = false;
			continue; // Restart the loop to ask for a new space
		}

		// If we made it here, they didn't press 'b' or 'd'. Let's check if it's a valid number.
		if (isNumber(seats) && stoi(seats) <= availableseats && stoi(seats) > 0) {
			break; // everything looks good, break out of the loop to proceed to hours
		}
		else {
			cout << "\ninvalid number of seats, please enter the number of seats again.\n";
			// Because spaceok and dateok are true, the loop will just jump right back here to ask for seats again.
		}
	}

	// --- STEP 5: HOURS ---
	cout << "Enter how many hours you want to book for: ";
	cin >> hours;

	while (true) {
		if (isNumber(hours) && stoi(hours) <= 12 && stoi(hours) > 0) {
			break; // Valid hours, break the loop
		}
		cout << "Enter a valid number. Please enter how many hours you want to book for (1-12): ";
		cin >> hours;
	}

	// --- FINAL STEP: BOOKING ---
	bookingsArray[totalBookingsCount].BookingId = rand() % (2000 - 1000 + 1) + 1000;
	bookingsArray[totalBookingsCount].SpaceId = spaceArray[j].SpaceId;
	bookingsArray[totalBookingsCount].UserId = activeUserID;
	bookingsArray[totalBookingsCount].date = date;
	bookingsArray[totalBookingsCount].Hours = stoi(hours);
	bookingsArray[totalBookingsCount].TotalCost = stoi(hours) * spaceArray[j].PricePerHour;
	bookingsArray[totalBookingsCount].Seats = stoi(seats);

	system("cls");
	cout << endl << "Booking successful! Here are your booking details: \n";
	cout << "Booking ID: " << bookingsArray[totalBookingsCount].BookingId << endl;
	cout << "Space ID: " << bookingsArray[totalBookingsCount].SpaceId << endl;
	cout << "Date: " << date << endl;
	cout << "Hours: " << hours << endl;
	cout << "Total Cost: " << bookingsArray[totalBookingsCount].TotalCost << endl;
	totalBookingsCount++;

	system("pause");
	system("cls");
}


void cancel_booking(int userid) {
	string bookid;
	cout << "enter the id for the booking you want to cancel: ";


	while (true) {
		cin >> bookid;

		if (!isNumber(bookid)) {
			cout << "please enter a number for a booking id: ";
			continue;
		}

		bool found = false;
		for (int i = 0; i < totalBookingsCount; i++) {
			if (stoi(bookid) == bookingsArray[i].BookingId && userid == bookingsArray[i].UserId) {
				found = true;
				bookingsArray[i] = bookingsArray[totalBookingsCount - 1];
				totalBookingsCount--;
				system("cls");
				cout << "booking canceled!\n\n";
				break;
			}
		}

		if (!found) {
			cout << "didn't find the booking, please re-enter the booking id: ";
			continue;
		}

		break;
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
	saveuserfile << "UserName,UserID,Password,Email,Phone\n";
	for (int i = 0; i < totalUsersCount; i++) {
		saveuserfile << usersArray[i].UserName << "," << usersArray[i].Id << "," << usersArray[i].Password << "," << usersArray[i].Email << "," << usersArray[i].Phone << endl;
	}
	saveuserfile.close();

	return 0;
}


int user_main_menu() {
	string choice;
	while (true) {

		cout <<
			"          ---Main Menu---        \n"
			"--------------------------------------\n"
			"1. spaces\n"
			"2. view my bookings\n"
			"3. logout\n"
			"4. exit program\n"
			"--------------------------------------\n";

		cout << "choice: ";
		cin >> choice;

		if (choice == "1") {
			system("cls");
			ViewSpaces(activeUserID);
		}
		else if (choice == "2") {
			system("cls");
			view_my_bookings(activeUserID);
		}
		else if (choice == "3") {
			system("cls");
			return 0;
		}
		else if (choice == "4") {
			SaveAll();
			exit(0);
		}
		else {
			continue;
		}
	}
}


int main() {
	srand(time(0));
	LoadData();
	while (true) {
		activeUserID = Logging(); //if -1 there is error  if = 0 activeuser is admin 
		if (activeUserID == 0)
			admin_main_menu();
		else if (activeUserID == -1)
			continue;
		else
			user_main_menu();
	}
}