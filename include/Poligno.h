#ifndef POLIGNO_H
#define POLIGNO_H

#include "Transform.h"
#include "BBox.h"
#include "Vertice.h"

/*! Estrutura para cor RGBA */
struct RGBA {
    double R;
    double G;
    double B;
    double A;
};

/*!
  Classe que representa o Poligno no mundo
*/
class Poligno
{
    public:
        Poligno();
        virtual ~Poligno();

        void initialize();
        /*! Desenha o poligno e seus filhos. */
        void draw();
        /*! Adiciona um Poligno filho */
        void addFilho(Poligno *f);
        /*! Adiciona um Vertice para o Poligno */
        void addVertice(Vertice *v);
        /*! Seta a cor RGBA */
        void setColor(double R, double G, double B, double A);
        /*! Aplica a transformação de escala */
        void scale(Transform *l);
        /*! Aplica a transformação de rotação */
        void rot(Transform *l);
        /*! Aplica a transformação de translação */
        void translate(Transform *l);

        void setDrawBbox(bool a) {this->drawBbox = a;}
        bool isSelect(Vertice *v);
        /*! Aplica a matriz de identidade para todas as transformações resetando-as */
        void resetTransforms();
        /*! Recalcula a BBOX do Poligno */
        void reDefineBBox();
        /*! Busca o vertice mais proximo do ponto, utilizando distância euclidiana */
        Vertice* getProximitVertice(double x, double y);
        /*! Remove o Vertice do Poligno */
        void removeVertice(Vertice *v);
    private:
        Transform *localScale;
        Transform *localRotation;
        Transform *localTranslation;
        bool drawBbox;
        BBox *bbox;
        RGBA colors;

        Vertice **vertices;
        Poligno **filhos;

        int qtdFilhos;
        int qtdVertices;

        void defineBbox(Vertice *v);
        double retMax(double a1, double a2);
        double retMin(double a1, double a2);
        Transform* getGlobalTransform();
};

#endif // POLIGNO_H
