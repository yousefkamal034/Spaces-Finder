#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "structs.h"
using namespace std;

User usersArray[100];
int totalUsersCount = 0;

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
}
int main(){
	LoadData();
	int activeUserID=Logging(); //if -1 there is error  if = 0 activeuser is admin 
}