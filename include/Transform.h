#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vertice.h"

class Transform
{
    public:
        Transform();
        virtual ~Transform();

        void initialize();
        void makeIdenty();
        void makeTranslation(Vertice *v);
        void makeScale(double sX, double sY, double sZ);
        void makeRotationX(double degress);
        void makeRotationY(double degress);
        void makeRotationZ(double degress);

        Transform* operator * (Transform *a);
        Vertice* operator *(Vertice* v);

        double* getTransform() {return this->matrix;}

        float RAS_DEG_TO_RAD = 0.017453292519943295769236907684886;
    private:
        double *matrix;
        void printMatrix();
};

#endif // TRANSFORM_H
