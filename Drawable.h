#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "View.h" // load View.h

class Drawable // abstract class
{
    // protected access for derived classes
protected:
    int layer;

public:
    // constructor
    Drawable(int layer) : layer(layer) {}

    // virtual destructor for proper deletion of derived and base objects when called
    virtual ~Drawable();

    // pure virtual function - derived classes must implement their own body
    virtual void draw(View &view) = 0;

    // class level static member function
    static int compare(Drawable *d1, Drawable *d2);
};

#endif
