#ifndef VERTICE_H
#define VERTICE_H


/*!
  Represent a vertice, composed by X, Y, Z e W
*/
class Vertice
{
    public:
        Vertice();
        virtual ~Vertice();
        void initialize(double x, double y, double z, double w);
        double Getx() { return x; }
        void Setx(double val) { x = val; }
        double Gety() { return y; }
        void Sety(double val) { y = val; }
        double Getz() { return z; }
        void Setz(double val) { z = val; }
        double Getw() { return 1.0; }
        void Setw(double val) { w = val; }
    protected:
    private:
        double x;
        double y;
        double z;
        double w;
};

#endif // VERTICE_H
