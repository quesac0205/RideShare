
#include "Controller.h"
#include <sstream>
#include <vector>
#include <iostream>
// #include "rideShare.h"
// #include "View.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::launch()
{
    initRideShare();

    // draw the current map
    displayMap();

    // write the menu and get user input
    int choice = 5;

    // This is the code being run in View
    // cout << "Which test would you like to run?"<< endl;
    // cout << "  (1) Display Map" << endl;
    // cout << "  (2) Print all drivers" << endl;
    // cout << "  (3) Print all customers" << endl;
    // cout << "  (4) Find a ride" << endl;
    // cout << "  (0) Exit" << endl<<endl;

    vector<string> menu = {
        "Display Map",
        "Print all drivers",
        "Print all customers",
        "Find a ride\n\nTests:\n",
        "Test display map",
        "Test find a ride"};
    while (choice != 0)
    {
        view.menu(menu, choice);
        switch (choice)
        {
        case 1:
            displayMap();
            break;
        case 2:
            rideShare.printDrivers();
            break;
        case 3:
            rideShare.printCustomers();
            break;
        case 4:
            findRide();
            break;
        case 5:
            testDisplayMap();
            break;
        case 6:
            testFindRide();
            break;
        }
    }

    cout << "Bye!" << endl;
}

void Controller::displayMap()
{
    view.refreshMap();
    rideShare.draw(view);
    view.displayMap();
}

void Controller::findRide()
{
    rideShare.printCustomers();

    // get customer object
    string customerID;
    cout << "Please Enter Customer ID (for instance C3): ";
    cin >> customerID;

    Customer *findCustomer = rideShare.getCustomer(customerID);
    if (findCustomer == nullptr)
    {
        cout << " Error - No such customer exists!!!" << endl;
        return;
    }

    // get ride information
    Size size;
    Location finalLocation;
    view.getRideInfo(size, finalLocation);

    // display the map
    view.refreshMap();    // flush the old map
    rideShare.draw(view); // draw the view
    view.displayMap();    // view the map

    // find driver based on the customer requirements
    Driver *findDriver = rideShare.findRide(findCustomer->getRating(), size, findCustomer->getLocation());
    if (findDriver == nullptr)
    {
        cout << " Error - No such customer exists!!!" << endl;
        return;
    }

    // change the location of driver and customer both

    findCustomer->setLocation(finalLocation);
    findDriver->setLocation(finalLocation);

    // display the map
    view.refreshMap();    // flush the old map
    rideShare.draw(view); // draw the view
    view.displayMap();    // view the map

    // print driver
    cout << "Driver:";
    findDriver->print();

    cout << "A driver has been successfully assgined to the customer!" << endl;
}

int Controller::testDisplayMap()
{
    RideShare rideShare;
    vector<string> driverNames = {"Elsa", "Densel", "Carter", "Bob", "Alice"};
    vector<Size> driverSizes = {medium, small, large, small, medium};
    vector<int> driverRatings = {5, 4, 3, 4, 5};
    vector<Location> driverLocations = {Location(3, 4), Location(1, 1), Location(5, 4), Location(2, 2), Location(7, 7)};
    vector<string> customers = {"Sally", "Jesse", "Isabelle", "Philip"};
    vector<int> customerRatings = {2, 5, 4, 3};
    vector<Location> customerLocations = {Location(5, 5), Location(3, 7), Location(4, 5), Location(1, 7)};
    initRideShare(rideShare, driverNames, driverSizes, driverRatings, driverLocations, customers, customerRatings, customerLocations);
    view.refreshMap();
    rideShare.draw(view);
    view.displayMap();
    // check that the drivers and customers are at the correct locations on the map
    int score = 0;
    // check that the drivers are at the correct locations
    int tempScore = 2;
    for (int i = 0; i < driverNames.size(); ++i)
    {
        char av = driverNames[i][0];
        Location l = driverLocations[i];
        char mapChar = view.getMap(l.x * 4 - 1, l.y * 2 - 1);
        if (mapChar != av)
        {
            cout << "Driver " << driverNames[i] << " is not at the correct location" << endl;
            cout << "Expected " << av << " at " << l.x << ", " << l.y << endl;
            cout << "Got " << mapChar << " at " << l.x << ", " << l.y << endl;
            tempScore--;
        }
    }

    tempScore = (tempScore < 0 ? 0 : tempScore);

    cout << "Driver location tests complete, score " << tempScore << "/2" << endl;

    score += tempScore;
    tempScore = 2;
    // check that the customers are at the correct locations
    for (int i = 0; i < customers.size(); ++i)
    {
        char av = customers[i][0];
        Location l = customerLocations[i];
        char mapChar = view.getMap(l.x * 4 + 1, l.y * 2);
        if (mapChar != av)
        {
            cout << "Customer " << customers[i] << " is not at the correct location" << endl;
            cout << "Expected " << av << " at " << l.x << ", " << l.y << endl;
            cout << "Got " << mapChar << " at " << l.x << ", " << l.y << endl;
            tempScore--;
        }
    }
    tempScore = (tempScore < 0 ? 0 : tempScore);

    cout << "Customer location tests complete, score " << tempScore << "/2" << endl;

    score += tempScore;

    cout << "Total score: " << score << "/4" << endl;

    return score;
}

int Controller::testFindRide()
{
    RideShare rideShare;
    initRideShare(rideShare);
    int outof = 4;
    int score = 0;

    vector<string> custIds = {"C1", "C2", "C3", "C4"};
    vector<string> driverNames = {"Carter", "Elsa", "Carter Elsa", "Elsa"};

    for (int i = 0; i < custIds.size(); ++i)
    {
        string custId = custIds[i];
        Customer *c = rideShare.getCustomer(custId);
        if (c == nullptr)
        {
            cout << "Customer " << custId << " not found" << endl;
            continue;
        }
        view.refreshMap();
        rideShare.draw(view);
        view.displayMap();
        cout << "Finding ride for customer " << endl;
        c->print();

        int rating = c->getRating();
        Size size = small;
        Location loc = c->getLocation();
        Driver *d = rideShare.findRide(rating, size, loc);
        if (d == nullptr)
        {
            cout << "No driver found for customer " << custId << endl;
            continue;
        }
        cout << "Driver " << d->getName() << " found for customer " << custId << endl;
        if (driverNames[i].find(d->getName()) != string::npos)
        {
            cout << "Correct driver found" << endl;
            score++;
        }
        else
        {
            cout << "Incorrect driver found" << endl;
        }
    }

    cout << "Score: " << score << "/" << outof << endl;

    return 0;
}

void Controller::initRideShare()
{

    rideShare.addDriver("Elsa", medium, 5, Location(3, 4));
    rideShare.addDriver("Densel", small, 4, Location(1, 1));
    rideShare.addDriver("Carter", large, 3, Location(5, 4));
    rideShare.addDriver("Bob", small, 4, Location(2, 2));
    rideShare.addDriver("Alice", medium, 5, Location(7, 7));

    rideShare.addCustomer("Sally", 2, Location(5, 5));
    rideShare.addCustomer("Jesse", 5, Location(3, 7));
    rideShare.addCustomer("Isabelle", 4, Location(4, 5));
    rideShare.addCustomer("Philip", 3, Location(1, 7));
}

void Controller::initRideShare(RideShare &rideShare)
{

    Customer::resetNextId();
    Driver::resetNextId();

    rideShare.addDriver("Elsa", medium, 5, Location(3, 4));
    rideShare.addDriver("Densel", small, 4, Location(1, 1));
    rideShare.addDriver("Carter", large, 2, Location(5, 4));
    rideShare.addDriver("Bob", small, 4, Location(2, 2));
    rideShare.addDriver("Alice", medium, 5, Location(7, 7));

    rideShare.addCustomer("Sally", 2, Location(5, 5));
    rideShare.addCustomer("Jesse", 5, Location(3, 7));
    rideShare.addCustomer("Isabelle", 4, Location(4, 5));
    rideShare.addCustomer("Philip", 3, Location(1, 7));
}

void Controller::initRideShare(RideShare &rideShare,
                               vector<string> driverNames,
                               vector<Size> driverSizes,
                               vector<int> driverRatings,
                               vector<Location> driverLocations,
                               vector<string> customers,
                               vector<int> customerRatings,
                               vector<Location> customerLocations)
{

    Customer::resetNextId();
    Driver::resetNextId();

    for (int i = 0; i < driverNames.size(); ++i)
    {
        rideShare.addDriver(driverNames[i], driverSizes[i], driverRatings[i], driverLocations[i]);
    }
    for (int i = 0; i < customers.size(); ++i)
    {
        rideShare.addCustomer(customers[i], customerRatings[i], customerLocations[i]);
    }
}