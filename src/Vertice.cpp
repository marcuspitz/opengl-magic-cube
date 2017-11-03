#include "Vertice.h"

Vertice::Vertice()
{
}

void Vertice::initialize(double x, double y, double z, double w)
{
    this -> Setx(x);
    this -> Sety(y);
    this -> Setz(z);
    this -> Setw(w);
}

Vertice::~Vertice()
{
    //dtor
}
