#ifndef DRIVER_H
#define DRIVER_H
#include <string>
#include "defs.h"
#include "User.h"
#include "Drawable.h"
#include "Location.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

class Driver : public User, public Drawable
{
public:
    // constructor
    Driver(string name, int rating, Size size, const Location &location);

    // member functions

    bool match(Size pSize, int pRating) const; // parameter size and parameter rating

    double getDistance(const Location &location) const;

    // overloading
    void draw(View &view) override;

    // relative comparsion between two drivers
    static int compRatings(Driver *d1, Driver *d2)
    {
        return d2->getRating() - d1->getRating(); // user's getRating function
    }

    static void resetNextId()
    {
        nextId = 0;
    }

private:
    Size size; // enum size
    static const char code;
    static const int driverLayer;
    static int nextId;
};

#endif
