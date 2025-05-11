#include "Drawable.h"
#include <iostream>

using namespace std;

// destructor implementation
Drawable::~Drawable()
{
}

int Drawable::compare(Drawable *d1, Drawable *d2)
{
    if (d1 == nullptr || d2 == nullptr)
    {
        cerr << "d1 or d2 are null pointers." << endl;
        return 0;
    }
    return d1->layer - d2->layer; // relative comparison between two drawable objects
};
