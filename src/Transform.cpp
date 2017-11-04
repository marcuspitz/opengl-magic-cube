#include "Transform.h"
#include <windows.h>
#include <math.h>
#include <stdio.h>

Transform::Transform()
{
    //ctor
}

Transform::~Transform()
{
    free(matrix);
}

void Transform::initialize()
{
    this->matrix = (double*) malloc(sizeof(double)*16);
    this->makeIdenty();
}
void Transform::makeIdenty()
{
    /**
    	1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 **/
    *matrix        = 1.0; (*(matrix+1))  = 0.0; (*(matrix+2))  = 0.0; (*(matrix+3))  = 0.0;
    (*(matrix+4))  = 0.0; (*(matrix+5))  = 1.0; (*(matrix+6))  = 0.0; (*(matrix+7))  = 0.0;
    (*(matrix+8))  = 0.0; (*(matrix+9))  = 0.0; (*(matrix+10)) = 1.0; (*(matrix+11)) = 0.0;
    (*(matrix+12)) = 0.0; (*(matrix+13)) = 0.0; (*(matrix+14)) = 0.0; (*(matrix+15)) = 1.0;
    //printMatrix();
}

void Transform::makeTranslation(Vertice *v)
{
    this->makeIdenty();
    (*(matrix+12)) = v->Getx();
    (*(matrix+13)) = v->Gety();
    (*(matrix+14)) = v->Getz();
    //(*(matrix+3)) = v->Getx();
    //(*(matrix+7)) = v->Gety();
    //(*(matrix+11)) = v->Getz();
    //printMatrix();
}

void Transform::makeScale(double sX, double sY, double sZ)
{
    this->makeIdenty();
    (*(matrix+0))  = sX;
    (*(matrix+5))  = sY;
    (*(matrix+10)) = sZ;
    //printMatrix();
}

void Transform::makeRotationX(double degress)
{
    double rad = degress * 0.017453292519943295769236907684886;
    this->makeIdenty();
    (*(matrix+5))  =  cos(rad);
    (*(matrix+9))  = -sin(rad);
    (*(matrix+6))  =  sin(rad);
    (*(matrix+10)) =  cos(rad);
    //printMatrix();
}
void Transform::makeRotationY(double degress)
{
    double rad = degress * 0.017453292519943295769236907684886;
    this->makeIdenty();
    (*(matrix+0))  =  cos(rad);
    (*(matrix+8))  =  sin(rad);
    (*(matrix+2))  = -sin(rad);
    (*(matrix+10)) =  cos(rad);
    //printMatrix();
}
void Transform::makeRotationZ(double degress)
{
    double rad = degress * 0.017453292519943295769236907684886;
    this->makeIdenty();
    (*(matrix+0))  =  cos(rad);
    (*(matrix+4))  = -sin(rad);
    (*(matrix+1))  =  sin(rad);
    (*(matrix+5))  =  cos(rad);
    //printMatrix();
}

Transform* Transform::operator * (Transform *a) {
    double *m2 = this->getTransform();
    double *t  = a->getTransform();
    double *result = (double*) malloc(sizeof(double)*16);

    result[0] = (m2[0] * t[0]) + (m2[1] * t[4]) + (m2[2] * t[8]) + (m2[3] * t[12]);
    result[1] = (m2[0] * t[1]) + (m2[1] * t[5]) + (m2[2] * t[9]) + (m2[3] * t[13]);
    result[2] = (m2[0] * t[2]) + (m2[1] * t[6]) + (m2[2] * t[10]) + (m2[3] * t[14]);
    result[3] = (m2[0] * t[3]) + (m2[1] * t[7]) + (m2[2] * t[11]) + (m2[3] * t[15]);

    result[4] = (m2[4] * t[0]) + (m2[5] * t[4]) + (m2[6] * t[8]) + (m2[7] * t[12]);
    result[5] = (m2[4] * t[1]) + (m2[5] * t[5]) + (m2[6] * t[9]) + (m2[7] * t[13]);
    result[6] = (m2[4] * t[2]) + (m2[5] * t[6]) + (m2[6] * t[10]) + (m2[7] * t[14]);
    result[7] = (m2[4] * t[3]) + (m2[5] * t[7]) + (m2[6] * t[11]) + (m2[7] * t[15]);

    result[8]  = (m2[8] * t[0]) + (m2[9] * t[4]) + (m2[10] * t[8]) + (m2[11] * t[12]);
    result[9]  = (m2[8] * t[1]) + (m2[9] * t[5]) + (m2[10] * t[9]) + (m2[11] * t[13]);
    result[10] = (m2[8] * t[2]) + (m2[9] * t[6]) + (m2[10] * t[10]) + (m2[11] * t[14]);
    result[11] = (m2[8] * t[3]) + (m2[9] * t[7]) + (m2[10] * t[11]) + (m2[11] * t[15]);

    result[12] = (m2[12] * t[0]) + (m2[13] * t[4]) + (m2[14] * t[8]) + (m2[15] * t[12]);
    result[13] = (m2[12] * t[1]) + (m2[13] * t[5]) + (m2[14] * t[9]) + (m2[15] * t[13]);
    result[14] = (m2[12] * t[2]) + (m2[13] * t[6]) + (m2[14] * t[10]) + (m2[15] * t[14]);
    result[15] = (m2[12] * t[3]) + (m2[13] * t[7]) + (m2[14] * t[11]) + (m2[15] * t[15]);

    free(matrix);
    matrix = result;
}

Vertice* Transform::operator *(Vertice* v) {
    double x = this->matrix[0]*v->Getx() + this->matrix[4]*v->Gety() + this->matrix[8]*v->Getz() + this->matrix[12]*v->Getw();
    double y = this->matrix[1]*v->Getx() + this->matrix[5]*v->Gety() + this->matrix[9]*v->Getz() + this->matrix[13]*v->Getw();
    double z = this->matrix[2]*v->Getx() + this->matrix[6]*v->Gety() + this->matrix[10]*v->Getz() + this->matrix[14]*v->Getw();
    double w = this->matrix[3]*v->Getx() + this->matrix[7]*v->Gety() + this->matrix[11]*v->Getz() + this->matrix[15]*v->Getw();

    v->Setx(x);
    v->Sety(y);
    v->Setz(z);
    v->Setw(w);

    return v;
}

void Transform::printMatrix()
{
    printf("\n\n\nMATRIZ\n\n%f-%f-%f-%f\n%f-%f-%f-%f\n%f-%f-%f-%f\n%f-%f-%f-%f\n\n",
           matrix[0],matrix[1],matrix[2],matrix[3],
           matrix[4],matrix[5],matrix[6],matrix[7],
           matrix[8],matrix[9],matrix[10],matrix[11],
           matrix[12],matrix[13],matrix[14],matrix[15]);
}
