#include<iostream>
#include<fstream>
#include "structs.h"
#include <string>
using namespace std;

void Reading() {
	User usersarray[10];
	int UserCount = 0;
	ifstream file("Users.csv");
	string tempUsername, tempPassword, tempEmail, tempUserID, tempPhone;

	if (file.is_open()) {
		string header;
		getline(file, header); //to remove header line in the file

		//getline to get all the line
		//file is the file variable
		//getline will stop if he find ","
		//while loop for getting all the lines in the file
		while (getline(file, tempUsername, ',')) {
			getline(file, tempUserID, ',');
			getline(file, tempPassword, ',');
			getline(file, tempEmail, ',');
			getline(file, tempPhone, '\n'); // "\n" because there is no ", " again

			//Storing The Data into the structs
			usersarray[UserCount].Id = stoi(tempUserID); // "stoi() to convert string to int
			usersarray[UserCount].UserName = tempUsername;
			usersarray[UserCount].Password = tempPassword;
			usersarray[UserCount].Email = tempEmail;
			usersarray[UserCount].Phone = tempPhone;
			usersarray[UserCount].IsAdmin = false;

			UserCount++;
		}
		file.close();
		for (int i = 0; i <  UserCount; i++)
			cout << "User Name: "<<usersarray[i].UserName <<
				"(ID: " << usersarray[i].Id << " )" <<
				"User's Phone: " << usersarray[i].Phone << endl;
	}
	else
		cout << "File Error" << endl;
}

void Writing(){
	string tempUsername, tempPassword, tempEmail, tempUserID="0", tempPhone;
	cout << "Enter User's Name: ";
	cin >> tempUsername;
	cout << "Enter Email: ";
	cin >> tempEmail;
	cout << "Enter Password: ";
	cin >> tempPassword;
	cout << "Enter Phone Number: ";
	cin >> tempPhone;

	ofstream file("Users.csv", ios::app); //ios::app for appending in the file

	file << tempUsername << "," << tempUserID << "," << tempPassword << "," << tempEmail << ", "
		<< tempPassword << "\n";
	file.close();


}

