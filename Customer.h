#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include "defs.h"
#include "User.h"
#include "Drawable.h"

using namespace std;

class Customer : public User, public Drawable
{
public:
    // constructor
    Customer(string name, int rating = 5, const Location &l = Location());

    // overloading the functions from base classes
    void print();
    void draw(View &) override;

    static int compRatings(Customer *c1, Customer *c2)
    {
        return c1->getRating() - c2->getRating();
    }

    static int compNames(Customer *c1, Customer *c2)
    {
        // return c1->getName() < c2->getName();
        return c1->getName().compare(c2->getName()); // alphabatically compare customer names
    }

    static void resetNextId()
    {
        nextId = 0;
    }

    //  member variables
private:
    // all three defined as static or class variables
    static const int custLayer;
    static int nextId;
    static const char code;
};

#endif