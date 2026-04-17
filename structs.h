#pragma once
#include <iostream>
using namespace std;

struct User {
	int Id;
	string UserName, Password, Email, Phone;
	bool IsAdmin;
};

struct Space {
	int SpaceId, PricePerHour, NoOfSeatAvailable;
	float Rating;
	string Name, Area;
	bool HasWifi, HasMeetingRoom;
};

struct Booking {
	string date;
	int BookingId, UserId, SpaceId, Hours, TotalCost, Seats;
};