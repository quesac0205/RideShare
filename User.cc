#include "User.h"

using namespace std;
User::User(char charType, int num, const string &userName, int userRating, Location userLocation)
    : name(userName),
      rating(userRating),
      location(userLocation)
{ // concatenation to form string id from char and int
    id = "";
    id += charType;
    id += to_string(num);
}

// member functions
string User::getId() const
{
    return id;
}

string User::getName() const
{
    return name;
}

int User::getRating() const
{
    return rating;
}

Location User::getLocation() const
{
    return location;
}

void User::setRating(int newUserRating)
{
    if (newUserRating >= 1 && newUserRating <= 5)
    {
        rating = newUserRating;
    }
    else
    {
        cerr << "Invalid User Rating!" << endl;
    }
}

// setter for location
void User::setLocation(Location &userLocation)
{
    // set userlocation as location
    int xAxis = userLocation.getX();
    int yAxis = userLocation.getY();
    location.setLocation(xAxis, yAxis);
    // location = userLocation;
}

void User::setLocation(int x, int y)
{
    // set location x and y coordinates
    location.setLocation(x, y);
}

// print function
void User::print()
{
    cout << "ID: " << id << ", Name: " << name
         << ", Rating: " << rating << ", Location: ";
    location.print();
    cout << endl;
}