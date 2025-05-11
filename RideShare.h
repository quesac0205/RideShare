#ifndef RIDESHARE_H
#define RIDESHARE_H

#include "List.h"
#include "Driver.h"
#include "Customer.h"
#include "Drawable.h"
#include "View.h"
#include <string>
#include <cmath>

using namespace std;

class RideShare
{
public:
    RideShare();
    ~RideShare();

    // add a driver and customer
    void addDriver(const string &name, Size size, int rating, const Location &location);
    void addCustomer(const string &name, int rating, const Location &location);
    Customer *getCustomer(const string &id) const;
    // find ride
    Driver *findRide(int rating, Size size, const Location &location) const;

    void printCustomers() const;
    void printDrivers() const;
    void draw(View &view) const;

private:
    List<Driver *> listDrivers;     // list of drivers
    List<Customer *> listCustomers; // list of customers
    List<Drawable *> listDrawables; // list of drawables
};

#endif
