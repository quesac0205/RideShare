#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>

#include "Location.h" // load Location.h

using namespace std;

// base class
class User
{
    // protected member variables
protected:
    string id;         // user id like C12
    string name;       // user name
    int rating;        // rating
    Location location; // user's current location

public:
    // constructor
    User(char charType, int num, const string &userName, int userRating, Location userLocation);

    // getters and setters
    string getId() const;
    string getName() const;
    int getRating() const;
    Location getLocation() const; // get Location object
    void setRating(int newUserRating);
    void setLocation(Location &userLocation); // set location based on location object
    void setLocation(int x, int y);           // set x and y coordinates of location
    void print();
};

#endif