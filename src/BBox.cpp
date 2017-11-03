#include "BBox.h"
#include "Vertice.h"

//Constructor
BBox::BBox()
{
}
BBox::BBox(Vertice min, Vertice max)
{
    this->SetMax(max);
    this->SetMin(min);
}

//Destructor
BBox::~BBox()
{

}
