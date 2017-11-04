#include "Cube.h"

#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

Cube::Cube()
{
    //ctor
}

Cube::~Cube()
{
    //dtor
}

void Cube::initialize(Vertice *position
                      , double sizeCube
                      , RGB color1
                      , RGB color2
                      , RGB color3
                      , RGB color4
                      , RGB color5
                      , RGB color6)
{
    center = false;
    tip = false;
    initialized    = true;
    qtdVertices    = 0;
    this->color01  = color1;
    this->color02  = color2;
    this->color03  = color3;
    this->color04  = color4;
    this->color05  = color5;
    this->color06  = color6;
    this->position = position;
    this->sizeCube = sizeCube;
    this->localScale       = (Transform*) malloc(sizeof(Transform));
    this->localRotation    = (Transform*) malloc(sizeof(Transform));
    this->localTranslation = (Transform*) malloc(sizeof(Transform));
    this->localScale->initialize();
    this->localRotation->initialize();
    this->localTranslation->initialize();
    double xMin, yMin, zMin;
    double xMax, yMax, zMax;
    xMin = this->position->Getx();
    yMin = this->position->Gety();
    zMin = this->position->Getz();
    xMax = xMin + this->sizeCube;
    yMax = yMin + this->sizeCube;
    zMax = zMin + this->sizeCube;

    Vertice *v;
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMax, zMax, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMax, zMax, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMin, zMax, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMin, zMax, 1.0);
    this->addVertice(v);

    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMax, zMin, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMin, zMin, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMin, zMin, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMax, zMin, 1.0);
    this->addVertice(v);

    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMax, zMax, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMax, zMin, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMin, zMin, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMin, zMax, 1.0);
    this->addVertice(v);

    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMax, zMax, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMin, zMax, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMin, zMin, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMax, zMin, 1.0);
    this->addVertice(v);

    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMax, zMin, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMax, zMax, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMax, zMax, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMax, zMin, 1.0);
    this->addVertice(v);

    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMin, zMin, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMin, zMin, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMax, yMin, zMax, 1.0);
    this->addVertice(v);
    v = (Vertice*) malloc(sizeof(Vertice));
    v->initialize(xMin, yMin, zMax, 1.0);
    this->addVertice(v);
}

Transform* Cube::getGlobalTransform()
{
    Transform *result = (Transform*) malloc(sizeof(Transform));
    result->initialize();
    (*result) * this->localRotation;
    (*result) * this->localScale;
    (*result) * this->localTranslation;
    return result;
}

void Cube::draw()
{
    if (!initialized)
        return;

    int i = 0;
    Vertice *v;

    glPushMatrix();

        Transform *transf = this->getGlobalTransform();
        glMultMatrixd(transf->getTransform());
        free(transf);

        //FACE 01 - Front
        glBegin(GL_QUADS);
            glColor3d(color01.R, color01.G, color01.B);
            glNormal3f(0, 0, 1);
            for (i = 0; i < 4; i++) {
                v = *( this->vertices + i );
                glVertex3d( v->Getx(), v->Gety(), v->Getz() );
            }
        glEnd();

        //FACE 02 - Back
        glBegin(GL_QUADS);
            glColor3d(color02.R, color02.G, color02.B);
            glNormal3f(0, 0, -1);
            for (i = 4; i < 8; i++) {
                v = *( this->vertices + i );
                glVertex3d( v->Getx(), v->Gety(), v->Getz() );
            }
        glEnd();
        //FACE 03 - Left
        glBegin(GL_QUADS);
            glColor3d(color03.R, color03.G, color03.B);
            glNormal3f(-1, 0, 0);
            for (i = 8; i < 12; i++) {
                v = *( this->vertices + i );
                glVertex3d( v->Getx(), v->Gety(), v->Getz() );
            }
        glEnd();
        //FACE 04 - Right
        glBegin(GL_QUADS);
            glColor3d(color04.R, color04.G, color04.B);
            glNormal3f(1, 0, 0);
            for (i = 12; i < 16; i++) {
                v = *( this->vertices + i );
                glVertex3d( v->Getx(), v->Gety(), v->Getz() );
            }
        glEnd();
        //FACE 05 - Up
        glBegin(GL_QUADS);
            glColor3d(color05.R, color05.G, color05.B);
            glNormal3f(0, 1, 0);
            for (i = 16; i < 20; i++) {
                v = *( this->vertices + i );
                glVertex3d( v->Getx(), v->Gety(), v->Getz() );
            }
        glEnd();
        //FACE 06 - Down
        glBegin(GL_QUADS);
            glColor3d(color06.R, color06.G, color06.B);
            glNormal3f(0, -1, 0);
            for (i = 20; i < 24; i++) {
                v = *( this->vertices + i );
                glVertex3d( v->Getx(), v->Gety(), v->Getz() );
            }
        glEnd();

    glPopMatrix();
}

void Cube::scale(Transform *l)
{
    (*this->localScale) * l;
}

void Cube::rot(Transform *l)
{
    (*this->localRotation) * l;
}

void Cube::translate(Transform *l)
{
    (*this->localTranslation) * l;
}

void Cube::resetTransforms()
{
    this->localRotation->makeIdenty();
    this->localScale->makeIdenty();
    this->localTranslation->makeIdenty();
}

void Cube::addVertice(Vertice *v)
{
    if (qtdVertices == 0){
        vertices = (Vertice**) malloc( sizeof(Vertice*) );
        vertices[qtdVertices] = v;
        qtdVertices++;
    } else {
        qtdVertices++;
        vertices = (Vertice**) realloc(vertices, sizeof(Vertice*) * qtdVertices );
        vertices[qtdVertices-1] = v;
    }
}

void Cube::printMe()
{
    printf("\n****");
    printf("line=%d, column=%d, depth=%d, id=%d", line, column, depth, id);
    printf("\n****");
}
