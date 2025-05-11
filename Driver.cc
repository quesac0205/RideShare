#include "Driver.h"
#include "View.h"

// variable initialization
const char Driver::code = 'D';
const int Driver::driverLayer = 1;
int Driver::nextId = 0;

// constructor
Driver::Driver(string n, int r, Size size, const Location &l)
    : Drawable(driverLayer), User(code, ++nextId, n, r, l), size(size) {}

bool Driver::match(Size pSize, int pRating) const
{
    int diff = getRating() - pRating;
    return (size >= pSize) && (diff <= 2); // check if sufficient size and difference is rating is at most 2
}

double Driver::getDistance(const Location &loc) const
{
    int finalX = pow(location.x - loc.x, 2);
    int finalY = pow(location.y - loc.y, 2);
    return sqrt(finalX + finalY); // euclid distance formula
}

void Driver::draw(View &view)
{
    view.drawDriver(location.x, location.y, name[0]);
}
