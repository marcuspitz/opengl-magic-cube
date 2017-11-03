#ifndef BBOX_H
#define BBOX_H
#include "Vertice.h"

/*! Classe que representa a BBOX de um Poligno */
class BBox
{
    public:
        BBox();

        void initialize(Vertice *min, Vertice *max) {
            this->SetMax(max);
            this->SetMin(min);
        }

        virtual ~BBox();

        /*! Retorna o maior vertice da BBOX */
        Vertice* GetMax() { return max; }
        /*! Define o maior vertice da BBOX */
        void SetMax(Vertice *val) { max = val; }
        /*! Retorna o menor vertice da BBOX */
        Vertice* GetMin() { return min; }
        /*! Define o menor vertice da BBOX */
        void SetMin(Vertice *val) { min = val; }
    private:
        Vertice *min;
        Vertice *max;
};

#endif // BBOX_H
