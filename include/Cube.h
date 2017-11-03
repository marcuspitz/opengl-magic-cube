#ifndef CUBE_H
#define CUBE_H

#include "Transform.h"
#include "Vertice.h"

/*! Color struct*/
struct RGB {
    double R;
    double G;
    double B;
    double A;
};

class Cube
{
    public:
        Cube();
        virtual ~Cube();

        void initialize(Vertice *position
                      , double sizeCube
                      , RGB color1
                      , RGB color2
                      , RGB color3
                      , RGB color4
                      , RGB color5
                      , RGB color6);
        void draw();
        void scale(Transform *l);
        void rot(Transform *l);
        void translate(Transform *l);
        void resetTransforms();

        void printMe();

        int line, column, depth, id;
        bool tip = false, center = false;
    private:
        Transform *localScale;
        Transform *localRotation;
        Transform *localTranslation;
        Vertice *position;
        double sizeCube;

        int qtdVertices;
        //face colors
        RGB color01;
        RGB color02;
        RGB color03;
        RGB color04;
        RGB color05;
        RGB color06;

        Vertice **vertices;
        bool initialized = false;

        Transform* getGlobalTransform();
        void addVertice(Vertice *v);
};

#endif // CUBE_H
