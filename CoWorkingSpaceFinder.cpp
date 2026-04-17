#include <iostream>
using namespace std;

struct user {
	int Id;
	string UserName, Password, Email, Phone;
	bool IsAdmin;
};

struct space {
	int SpaceId, PricePerHour, NoOfSeatAvailable;
	float Rating;
	string Name, Area;
	bool HasWifi, HasMeetingRoom;
};

struct booking {
	string date;
	int BookingId, UserId, SpaceId, Hours, TotalCost, Seats;
};

int main(){

}