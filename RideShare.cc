#include "RideShare.h"
using namespace std;

// constructor and destructor
RideShare::RideShare()
    : listDrivers(Driver::compRatings), listCustomers(Customer::compNames), listDrawables(Drawable::compare) {} // using static compare functions associated with each class

// clean list of drivers and customers
RideShare::~RideShare()
{
    // delete each element in list of drivers
    for (int i = 0; i < listDrivers.getSize(); ++i)
    {
        delete listDrivers.get(i);
    }
    // delete each element in list of customers
    for (int i = 0; i < listCustomers.getSize(); ++i)
    {
        delete listCustomers.get(i);
    }
}

// add a new driver to list
void RideShare::addDriver(const string &name, Size size, int rating, const Location &location)
{

    Driver *newDriver = new Driver(name, rating, size, location); // made a new driver object
    listDrivers.add(newDriver);                                   // add the new Driver object to list of drivers
    listDrawables.add(newDriver);                                 // add the new Driver object to list of drawables
}

// add a new customer to list
void RideShare::addCustomer(const string &name, int rating, const Location &location)
{
    // same approach, create a new customer object, add it to list of customers and drawables
    Customer *newCustomer = new Customer(name, rating, location);
    listCustomers.add(newCustomer);
    listDrawables.add(newCustomer);
}

// get customer by id
Customer *RideShare::getCustomer(const string &id) const
{
    for (int i = 0; i < listCustomers.getSize(); ++i)
    {
        if (listCustomers.get(i)->getId() == id) // get each customer ID and match it with parameter id
        {
            return listCustomers.get(i);
        }
    }
    return nullptr; // other wise return nullptr
}

// find the closest driver for ride based on rating, size and distance matrics
Driver *RideShare::findRide(int rating, Size size, const Location &location) const
{
    Driver *driverMatch = nullptr; // store the matched driver
    double minDistance = -1;       // initiate the value at -1

    for (int i = 0; i < listDrivers.getSize(); ++i) // iterate thru each driver
    {
        Driver *driver = listDrivers.get(i); // get each driver
        if (driver->match(size, rating))     // if the driver is match based on size and rating
        {
            double distance = driver->getDistance(location); // calculate the distance based on location
            if (minDistance == -1 || distance < minDistance)
            {
                minDistance = distance; // update the min Distance
                driverMatch = driver;   // matched the driver
            }
        }
    }
    return driverMatch; // return the matched driver
}

// print customers function
void RideShare::printCustomers() const
{
    for (int i = 0; i < listCustomers.getSize(); ++i)
    {
        listCustomers.get(i)->print();
    }
}

// print drivers function
void RideShare::printDrivers() const
{
    for (int i = 0; i < listDrivers.getSize(); ++i)
    {
        listDrivers.get(i)->print();
    }
}

// draw each drawables by callng draw function on each drawable object
void RideShare::draw(View &view) const
{
    for (int i = 0; i < listDrawables.getSize(); ++i)
    {
        listDrawables.get(i)->draw(view);
    }
}
