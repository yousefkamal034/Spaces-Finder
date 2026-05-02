#include <iostream>
#include <fstream> //input-output
#include <cstdlib> //String Conversions 
#include <ctime> // for srand(time(0));
#include <ctype.h> //for tolower()
#include <string> //string functions
#include "structs.h" //structs file
#include "adminfuncs.h" //admin functions file

using namespace std;

//null pointers for the arrays
User* usersArray = nullptr;
Booking* bookingsArray = nullptr;
Space* spaceArray = nullptr;

int activeUserID;
int totalUsersCount = 0, userCapacity = 0;
int totalBookingsCount = 0, bookingCapacity = 0;
int totalSpacesCount = 0, spaceCapacity = 0;

//all the Functions
int Log_in();
int Sign_up();
int Logging();
void LoadData();
int AddSpace();
void admin_main_menu();
void view_my_bookings(int userid);
void ViewSpaces();
void book_space(int userid);
bool isvaliddate(string date);
void FilterSpaces();
void SearchByArea();
int user_main_menu();
void cancel_booking(int userid);

//to turn all the string into lower case
string stringtolower(string s) {
	int length = s.length();
	for (int i = 0; i < length; i++) {
		s[i] = tolower(s[i]);
	}
	return s;
}

// this one is to check if a string is a float
bool isFloat(string str) {
	try {
		stof(str);
		return true;
	}
	catch (...) {
		return false;
	}
}

// a helper function to check if a string has spaces or not
bool nospaces(string x) {
	for (int i = 0; i < x.length(); i++) {
		if (x[i] == ' ') {
			return false;
		}
	}
	return true;
}

// a small function to remove redundency
void displaySpaces() {
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

//log in
int Log_in() {
	system("cls");
	string username, password;
	bool pass_correct = false, name_correct = false;
	int pass_tries = 3, name_tries = 3;
	cout << "----Log In---" << endl;
	while (!name_correct) 
	{
		while (true)
		{
			cout << "Enter UserName(Case Sensitive) (press 'b' to go back): ";
			getline(cin >> ws, username);
			if (nospaces(username))
				break;
			else
				cout << "username can't contain spaces.\n";
		}
		
		if (username == "b" || username == "B")
			return -1;

		//for admin,username and password=admin
		if (username == "admin")
		{
			while (true) 
			{
				cout << "Password(Case Sensitive): ";
				getline(cin >> ws, password);
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
		}
		for (int i = 0; i < totalUsersCount; i++) {
			if (usersArray[i].UserName == username) {
				while (!pass_correct) {

					while (true) {
						cout << "Password(Case Sensitive): ";
						getline(cin >> ws, password);
						if (nospaces(password))
							break;
						else
							cout << "password can't contain space.\n";
					}

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

//signup
int Sign_up() {
	system("cls");

	if (totalUsersCount == userCapacity) {
		increaseArray("user");
	}

	string tempUsername, tempPassword, tempEmail, tempPhone;

	while (true) { // a loop to make sure the username doesn't contain a space 
		cout << "Enter A UserName (press 'b' to go back): ";
		getline(cin >> ws, tempUsername);

		if (tempUsername == "b" || tempUsername == "B") // to go back to login or signup page
			return -1;

		if (nospaces(tempUsername))
			break;
		else
			cout << "username can't contain a space.\n";
	}
	while (true)
	{
		cout << "Create A password:";
		getline(cin >> ws, tempPassword);
		if (tempPassword.length() >= 6)
		{
			if (nospaces(tempPassword))
				break;
			else
			{
				cout << "Password can't contain spaces" << endl;
				continue;
			}
		}
		else
		{
			cout << "Password Should be more than 6 characters" << endl;
			continue;
		}

	}
	while (true) { // a loop to get an Email
		cout << "Enter Email: ";
		getline(cin >> ws, tempEmail);

		if (nospaces(tempEmail))
			break;
		else {
			cout << "Email can't contain a space.\n";
		}
	}
	while (true)
	{
		cout << "Enter Phone Number: ";
		getline(cin >> ws, tempPhone);
		if (isFloat(tempPhone))
		{
			if (nospaces(tempPhone))
				break;
			else
			{
				cout << "Phone Number can't contain spaces" << endl;
				continue;
			}
		}
		else
		{
			cout << "Phone Number must be a number\n";
			continue;
		}
	}

	int tempUserID = rand() % (199 - 100 + 1) + 100; //generating ID from 100 to 199
	cout << "Your ID is: " << tempUserID << endl;

	//Saving Data To the Arrays
	usersArray[totalUsersCount].UserName = tempUsername;
	usersArray[totalUsersCount].Password = tempPassword;
	usersArray[totalUsersCount].Id = tempUserID;
	usersArray[totalUsersCount].Email = tempEmail;
	usersArray[totalUsersCount].Phone = tempPhone;
	totalUsersCount++;
	system("pause");
	system("cls"); //Clearing the Terminal
	return Log_in();
}

//log in or signup
int Logging() {
	string choice;
	cout << "-----------" << '\n' << "1- Log in" << '\n' << "2- Don't Have an Account? " << '\n' << "3- exit program\n" << "-----------" << endl;
	cout << "choice: ";
	getline(cin >> ws, choice);
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

//load all the files into the arrays 
void LoadData()
{
	string header;
	// load users from Users.csv into usersarray
	ifstream file("Users.csv");
	if (!file.is_open()) 
	{
		cout << "couldn't open users.csv";
		return;
	}
	getline(file, header); // to get rid of the header line
	string tempUserID, tempUser, tempPassword, tempEmail, tempPhone;


	while (getline(file, tempUser, ','))
	{
		if (tempUser.empty() || tempUser == "\n") // a small check for safety
			continue;
		// a loop to make usersarray bigger by multiplying it's capacity * 2
		if (totalUsersCount == userCapacity) 
		{
			increaseArray("user");
		}
		getline(file, tempUserID, ',');
		getline(file, tempPassword, ',');
		getline(file, tempEmail, ',');
		getline(file, tempPhone, '\n');

		usersArray[totalUsersCount].UserName = tempUser;
		usersArray[totalUsersCount].Id = stoi(tempUserID);
		usersArray[totalUsersCount].Password = tempPassword;
		usersArray[totalUsersCount].Email = tempEmail;
		usersArray[totalUsersCount].Phone = tempPhone;

		totalUsersCount++;
	}
	file.close();

	// load bookings from bookings.csv into booking array
	ifstream file2("bookings.csv");
	if (!file2.is_open()) 
	{
		cout << "couldn't open bookings.csv";
		return;
	}
	getline(file2, header); // to get rid of the header line
	string bookingID, spaceID, userID, Date, Hours, TotalCost, Seats;


	while (getline(file2, bookingID, ','))
	{
		if (bookingID.empty() || bookingID == "\n") // a small check for safety
			continue;

		// a loop to increase the size of booking array if needed
		if (totalBookingsCount == bookingCapacity) 
		{
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


	// load spaces from Spaces.csv into spacesarray
	ifstream file3("Spaces.csv");
	if (!file3.is_open())
	{
		cout << "couldn't open Spaces.csv";
		return;
	}
	getline(file3, header);
	string tempName, tempSpaceID, tempArea, tempPricePerHour, tempNoOfSeatAvailable, tempRating, tempHasWifi, tempHasMeetingRoom;

	while (getline(file3, tempName, ','))
	{
		if (tempName.empty() || tempName == "\n") // a small check for safety
			continue;

		// a loop to make spacearray bigger by multiplying it's capacity * 2
		if (totalSpacesCount == spaceCapacity)
		{
			increaseArray("space");
		}

		getline(file3, tempSpaceID, ',');
		getline(file3, tempArea, ',');
		getline(file3, tempPricePerHour, ',');
		getline(file3, tempNoOfSeatAvailable, ',');
		getline(file3, tempRating, ',');
		getline(file3, tempHasWifi, ',');
		getline(file3, tempHasMeetingRoom, '\n');

		spaceArray[totalSpacesCount].Name = tempName;
		spaceArray[totalSpacesCount].SpaceId = stoi(tempSpaceID);
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


void ViewSpaces() {
	displaySpaces();
	while (true) {
		cout << endl;
		cout << "s --> search area" << endl;
		cout << "f --> filtering" << endl;
		cout << "b --> Book a space" << endl;
		cout << "m --> main menu" << endl;
		cout << "Enter choice (s/f/b/m): ";
		string choice; //string, so if the user types something like (hsdnf) no weird behaviour accours
		getline(cin >> ws, choice);
		if (choice == "s" || choice == "S") {
			SearchByArea();
		}
		else if (choice == "f" || choice == "F") {
			FilterSpaces();
		}
		else if (choice == "b" || choice == "B") {
			book_space(activeUserID);
			displaySpaces();
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

//To search The Spaces by Area
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

//Filter by maxprice,minrating,WiFI,MR
void FilterSpaces() {
	string wifiFilter, meetingRoomFilter;
	string minRating;
	string maxPrice;
	bool found = false;

	while (true) {
		system("cls");
		cout << "\n------------Filters------------\n" << endl;
		cout << "P --> Max Price" << endl;
		cout << "R --> Min Rating" << endl;
		cout << "W --> WiFi" << endl;
		cout << "M --> Meeting room" << endl;
		cout << "A --> availability" << endl;
		cout << "Enter filter choice (P/R/W/M/A): ";
		string choice;
		getline(cin >> ws, choice);
		if (choice == "p" || choice == "P") {

			while (true) {
				cout << "Enter maximum price per hour: ";
				getline(cin >> ws, maxPrice);
				if (isFloat(maxPrice))
					break;
			}

			cout << "\n--- Results for Price <= " << maxPrice << " ---" << endl;
			for (int i = 0; i < totalSpacesCount; i++) {
				if (spaceArray[i].PricePerHour <= stof(maxPrice)) {
					found = true;
					cout << "Space Name: " << spaceArray[i].Name << endl;
					cout << "Space ID: " << spaceArray[i].SpaceId << endl;
					cout << "Price Per Hour: " << spaceArray[i].PricePerHour << endl;
					cout << "-----------------------------" << endl;

				}
			}break;
		}
		else if (choice == "R" || choice == "r") {

			while (true) {
				cout << "Enter minimum rating: ";
				getline(cin >> ws, minRating);
				if (isFloat(minRating))
					break;
			}

			for (int i = 0; i < totalSpacesCount; i++) {
				if (spaceArray[i].Rating >= stof(minRating)) {
					found = true;
					cout << "Space Name: " << spaceArray[i].Name << endl;
					cout << "Space ID: " << spaceArray[i].SpaceId << endl;
					cout << "Rating: " << spaceArray[i].Rating << " / 5" << endl;
					cout << "-----------------------------" << endl;
				}
			}break;
		}
		else if (choice == "w" || choice == "W") {
			cout << "Require WiFi? (Y/N): ";
			getline(cin >> ws, wifiFilter);
			wifiFilter = stringtolower(wifiFilter);
			for (int i = 0; i < totalSpacesCount; i++) {
				if (spaceArray[i].HasWifi == (wifiFilter == "y")) {
					found = true;
					cout << "Space Name: " << spaceArray[i].Name << endl;
					cout << "Space ID: " << spaceArray[i].SpaceId << endl;
					cout << "Has Wifi: " << (spaceArray[i].HasWifi ? "Yes" : "No") << endl;
					cout << "-----------------------------" << endl;
				}
			}break;
		}
		else if (choice == "m" || choice == "M") {
			cout << "Require Meeting Room? (Y/N): ";
			getline(cin >> ws, meetingRoomFilter);
			meetingRoomFilter = stringtolower(meetingRoomFilter);
			for (int i = 0; i < totalSpacesCount; i++) {
				if (spaceArray[i].HasMeetingRoom == (meetingRoomFilter == "y")) {
					found = true;
					cout << "Space Name: " << spaceArray[i].Name << endl;
					cout << "Space ID: " << spaceArray[i].SpaceId << endl;
					cout << "Has Meeting Room: " << (spaceArray[i].HasMeetingRoom ? "Yes" : "No") << endl;
					cout << "-----------------------------" << endl;
				}
			}break;
		}
		else if (choice == "a" || choice == "A") {

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

//View all user Bookings
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

//for Booking a space
void book_space(int userid) {
	if (totalBookingsCount == bookingCapacity) { // a small loop to check if we reached max bookings number and increase it
		increaseArray("booking");
	}

	string chosenspaceid;
	string date, hours;
	string seats;
	bool idfound = false;
	bool space_correct = false;
	bool date_correct = false;
	int j; // this is the chosen space index in spacesarray
	int availableseats = 0;

	while (true) {
		// get space id
		if (!space_correct) {
			bool idfound = false;
			cout << "Enter SpaceID: ";
			getline(cin >> ws, chosenspaceid);

			while (!idfound) {
				while (!isFloat(chosenspaceid)) {
					cout << "Enter a valid number for space ID: ";
					getline(cin >> ws, chosenspaceid);
				}

				for (int i = 0; i < totalSpacesCount; i++) {
					if (spaceArray[i].SpaceId == stoi(chosenspaceid)) {
						idfound = true;
						j = i;
						break;
					}
				}

				if (!idfound) {
					cout << "Wrong ID, please enter a valid space ID: ";
					getline(cin >> ws, chosenspaceid);
				}
			}
			space_correct = true;
			date_correct = false;
		}

		// get the date if the dateok = flase
		if (!date_correct) {
			cout << "Enter the date you want to book for (DD/MM/YYYY) (press b to go back): ";
			getline(cin >> ws, date);

			if (date == "b" || date == "B") {
				space_correct = false; // They want to go back, so we need a space again
				continue;         // Restart the loop from the top
			}

			while (!isvaliddate(date)) {
				cout << "Invalid date! Please enter Date Again: ";
				getline(cin >> ws, date);
			}
			date_correct = true; // Check it off the list!
		}

		availableseats = spaceArray[j].NoOfSeatAvailable;
		for (int i = 0; i < totalBookingsCount; i++) {
			if (bookingsArray[i].SpaceId == stoi(chosenspaceid) && bookingsArray[i].date == date) {
				availableseats -= bookingsArray[i].Seats; // don't break the loop, there might be more than 1 booking
			}
		}

		if (availableseats <= 0) {
			cout << "The space is fully booked on this date, please choose another date!\n";
			date_correct = false;
			continue; // restart the loop from the top
		}

		cout << "-----------------------\nEnter how many seats you want to book (" << availableseats << " seats are available for this space on this date)\n"
			<< "(press 'd' to choose another date, or 'b' to choose another space): ";
		getline(cin >> ws, seats);

		if (seats == "d" || seats == "D") {
			date_correct = false;
			continue; // restart the loop to ask for a new date
		}

		if (seats == "b" || seats == "B") {
			space_correct = false;
			continue; // restart the loop to ask for a new space
		}

		if (isFloat(seats) && stoi(seats) <= availableseats && stoi(seats) > 0) {
			break;
		}
		else {
			cout << "\ninvalid number of seats, please enter the number of seats again.\n";
		}
	}

	cout << "Enter how many hours you want to book for: ";
	getline(cin >> ws, hours);

	while (true) {
		if (isFloat(hours) && stoi(hours) <= 12 && stoi(hours) > 0) {
			break; // Valid hours, break the loop
		}
		cout << "Enter a valid number. Please enter how many hours you want to book for (1-12): ";
		getline(cin >> ws, hours);
	}

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

//if the user Want to Cancel a Booking
void cancel_booking(int userid) {
	string bookid;
	cout << "enter the id for the booking you want to cancel: ";

	while (true) {
		getline(cin >> ws, bookid);

		if (!isFloat(bookid)) {
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

//to check if the date is in valid DD/MM/YYYY Format
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

//save all the arrays into the files
int SaveAll()
{
	ofstream file_2("Users.csv");
	if (!file_2.is_open())
	{
		cout << "couldn't open file";
		return 1;
	}
	file_2 << "UserName,UserID,Password,Email,Phone\n"; //Header
	for (int i = 0; i < totalUsersCount; i++)
	{
		file_2 << usersArray[i].UserName << "," << usersArray[i].Id << "," << usersArray[i].Password << "," << usersArray[i].Email << "," << usersArray[i].Phone << endl;
	}
	file_2.close();

	ofstream file22("Spaces.csv");
	if (!file22.is_open())
	{
		cout << "couldn't open file";
		return 1;
	}

	file22 << "Name,SpaceID,Area,PricePerHour,NoOfSeatAvailable,Rating,HasWifi,HasMeetingRoom\n"; //Header
	string wifi, hmr;
	for (int i = 0; i < totalSpacesCount; i++) 
	{
		if (spaceArray[i].HasWifi)
			wifi = "Yes";
		else
			wifi = "No";
		if (spaceArray[i].HasMeetingRoom)
			hmr = "Yes";
		else
			hmr = "No";
		file22 << spaceArray[i].Name << "," << spaceArray[i].SpaceId << "," << spaceArray[i].Area << "," << spaceArray[i].PricePerHour <<
			"," << spaceArray[i].NoOfSeatAvailable << "," << spaceArray[i].Rating << "," << wifi << "," << hmr << endl;
	}
	file22.close();


	ofstream file32("bookings.csv");
	if (!file32.is_open()) 
	{
		cout << "couldn't open file";
		return 1;
	}
	file32 << "BookingId,SpaceId,UserId,date,Hours,TotalCost,Seats\n"; //Header
	for (int i = 0; i < totalBookingsCount; i++) 
	{
		file32 << bookingsArray[i].BookingId << "," << bookingsArray[i].SpaceId << "," << bookingsArray[i].UserId << "," <<
			bookingsArray[i].date << "," << bookingsArray[i].Hours << "," << bookingsArray[i].TotalCost << "," << bookingsArray[i].Seats << endl;
	}
	file32.close();
	
	return 0;
}

//main Menu
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
		getline(cin >> ws, choice);

		if (choice == "1") {
			system("cls");
			ViewSpaces();
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
		activeUserID = Logging(); //if -1 there is an error  if = 0 activeuser is admin 
		if (activeUserID == 0)
			admin_main_menu();
		else if (activeUserID == -1)
			continue;
		else
			user_main_menu();
	}
}