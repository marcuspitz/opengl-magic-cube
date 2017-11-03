#include "Poligno.h"
#include <windows.h>
#include <float.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include "math.h"

Poligno::Poligno()
{
    //ctor
}

Poligno::~Poligno()
{
    //dtor
    free(localScale);
    free(localRotation);
    free(localTranslation);
    free(bbox);

    int i;
    //Limpa as listas
    for (i = 0; i < qtdFilhos; i++)
        free(*(filhos+i));
    for (i = 0; i < qtdVertices; i++)
        free(*(vertices+i));
    free(filhos);
    free(vertices);
}

void Poligno::initialize()
{
    this->drawBbox   = false;
    localScale       = (Transform*) malloc(sizeof(Transform));
    localRotation    = (Transform*) malloc(sizeof(Transform));
    localTranslation = (Transform*) malloc(sizeof(Transform));
    bbox             = (BBox*) malloc(sizeof(BBox));
    Vertice *vMax    = (Vertice*) malloc(sizeof(Vertice));
    vMax->Setw(1.0);
    double MIN = -99999999;
    vMax->Setx(MIN);
    vMax->Sety(MIN);
    vMax->Setz(MIN);
    Vertice *vMin    = (Vertice*) malloc(sizeof(Vertice));
    vMin->Setw(1.0);
    vMin->Setx(DBL_MAX);
    vMin->Sety(DBL_MAX);
    vMin->Setz(DBL_MAX);
    bbox->initialize(vMin, vMax);
    localScale->initialize();
    localRotation->initialize();
    localTranslation->initialize();
    qtdFilhos   = 0;
    qtdVertices = 0;
    colors.R = 0.0;
    colors.G = 0.0;
    colors.B = 0.0;
    colors.A = 0.0;
}

/**
 * Retorna a matriz de transformação global
 * Ele irá translatar até a origem e fazer a rotação e escala
 * depois fazer a translação inversa e aplicar a translação
 */
Transform* Poligno::getGlobalTransform()
{
    Transform *result = (Transform*) malloc(sizeof(Transform));
    result->initialize();

    Vertice *v = (Vertice*) malloc(sizeof(Vertice));
    v->Setw(1);
    v->Setx( (bbox->GetMax()->Getx() + bbox->GetMin()->Getx()) / 2 );
    v->Sety( (bbox->GetMax()->Gety() + bbox->GetMin()->Gety()) / 2 );
    v->Setz( (bbox->GetMax()->Getz() + bbox->GetMin()->Getz()) / 2 );
    Transform *inverse = (Transform*) malloc(sizeof(Transform));
    inverse->initialize();
    inverse->makeTranslation(v);
    Transform *origin = (Transform*) malloc(sizeof(Transform));
    origin->initialize();
    v->Setx(v->Getx()*-1);
    v->Sety(v->Gety()*-1);
    v->Setz(v->Getz()*-1);
    origin->makeTranslation(v);

    //Ordem das transformações
    //result->multiply(inverse);
    result->multiply(origin);
    result->multiply(this->localRotation);
    result->multiply(this->localScale);
    result->multiply(inverse);
    //result->multiply(origin);
    result->multiply(this->localTranslation);

    free(v);

    return result;
}

void Poligno::draw()
{
    printf("\n DESENHANDO O POLIGNO, Data: %s, Hora: %s",__DATE__,__TIME__);

    int i = 0;
    Vertice *v;
    Poligno *filho;
    glColor3d(colors.R, colors.G, colors.B);

    //copia e empilha
    glPushMatrix();

        Transform *transf = this->getGlobalTransform();
        glMultMatrixd(transf->getTransform());
        free(transf);

        //POLIGNO
        glLineWidth(2.0);
        glBegin(GL_LINE_LOOP);
            //Vertices
            for (i = 0; i < this->qtdVertices; i++) {
                v = *( this->vertices + i );
                printf("\n DESENHANDO O VERTICE X=%f,Y=%f,Z=%f, Data: %s, Hora: %s"
                       ,v->Getx(), v->Gety(),v->Getz(),__DATE__,__TIME__);
                glVertex2d( v->Getx(), v->Gety() );
            }
        glEnd();

        if (this->drawBbox) {
            //BBOX
            glColor3d(1.0, 0.0, 0.0);
            glLineWidth(1.0);
            glBegin(GL_LINE_LOOP);
                printf("\n DESENHANDO BBOX, Data: %s, Hora: %s",__DATE__,__TIME__);
                Vertice *vMax = bbox->GetMax();
                Vertice *vMin = bbox->GetMin();
                glVertex2d( vMin->Getx(), vMin->Gety() );
                glVertex2d( vMin->Getx(), vMax->Gety() );
                glVertex2d( vMax->Getx(), vMax->Gety() );
                glVertex2d( vMax->Getx(), vMin->Gety() );
            glEnd();
        }

        //Chama o desenho dos filhos
        for (i = 0; i < this->qtdFilhos; i++) {
            filho = (Poligno*) ( *( this->filhos + i ) );
            filho->draw();
        }
    //retira o topo e poem o anterior como 'main'
    glPopMatrix();
}

void Poligno::addFilho(Poligno *f)
{
    if (qtdFilhos == 0){
        filhos = (Poligno**) malloc( sizeof(Poligno) );
        filhos[qtdFilhos] = f;
        qtdFilhos++;
    } else {
        qtdFilhos++;
        filhos = (Poligno**) realloc(filhos, sizeof(Poligno) * qtdFilhos );
        filhos[qtdFilhos-1] = f;
    }
}

void Poligno::addVertice(Vertice *v)
{
    printf("\n ADICIONANDO O VERTICE X=%f,Y=%f,Z=%f, Data: %s, Hora: %s"
                       ,v->Getx(), v->Gety(),v->Getz(),__DATE__,__TIME__);
    defineBbox(v);
    if (qtdVertices == 0){
        vertices = (Vertice**) malloc( sizeof(Vertice) );
        vertices[qtdVertices] = v;
        qtdVertices++;
    } else {
        qtdVertices++;
        vertices = (Vertice**) realloc(vertices, sizeof(Vertice) * qtdVertices );
        vertices[qtdVertices-1] = v;
    }
}

void Poligno::defineBbox(Vertice *v)
{
    //Calculo BBox
    Vertice *vMax = bbox->GetMax();
    Vertice *vMin = bbox->GetMin();

    // X
    if (v->Getx() < vMin->Getx()){
        vMin->Setx(v->Getx());
    }
    if (v->Getx() > vMax->Getx()){
        vMax->Setx(v->Getx());
    }

    // Y
    if (v->Gety() < vMin->Gety()){
        vMin->Sety(v->Gety());
    }
    if (v->Gety() > vMax->Gety()){
        vMax->Sety(v->Gety());
    }

    // Z
    if (v->Getz() < vMin->Getz()){
        vMin->Setz(v->Getz());
    }
    if (v->Getz() > vMax->Getz()){
        vMax->Setz(v->Getz());
    }

    printf("\n ***********BBOX MAX X=%f,Y=%f,Z=%f, Data: %s, Hora: %s\n\n" ,bbox->GetMax()->Getx(), bbox->GetMax()->Gety(),bbox->GetMax()->Getz(),__DATE__,__TIME__);
    printf("\n ***********BBOX MIN X=%f,Y=%f,Z=%f, Data: %s, Hora: %s" ,bbox->GetMin()->Getx(), bbox->GetMin()->Gety(),bbox->GetMin()->Getz(),__DATE__,__TIME__);
}

void Poligno::setColor(double R, double G, double B, double A)
{
    this->colors.R = R;
    this->colors.G = G;
    this->colors.B = B;
    this->colors.A = A;
}

void Poligno::scale(Transform *l)
{
    this->localScale->multiply(l);
}

void Poligno::rot(Transform *l)
{
    this->localRotation->multiply(l);
}

void Poligno::translate(Transform *l)
{
    this->localTranslation->multiply(l);
}

double Poligno::retMax(double a1, double a2)
{
    if (a1 > a2)
        return a1;
    else
        return a2;
}

double Poligno::retMin(double a1, double a2)
{
    if (a1 < a2)
        return a1;
    else
        return a2;
}

/**
 * ScanLine
 **/
bool Poligno::isSelect(Vertice *v)
{
    Transform *global = getGlobalTransform();
    double ti, xint, yint;
    Vertice *v1;
    Vertice *v2;
    int qtd = 0;
    for (int i = 0; i < this->qtdVertices; i++) {
        v1 = this->vertices[i];
        if (i == (this->qtdVertices-1)  )
            v2 = this->vertices[0];
        else
            v2 = this->vertices[i+1];

        v1 = global->transformVertice(v1);
        v2 = global->transformVertice(v2);

        if (v1->Gety() != v2->Gety()) {

            ti = ( v->Gety() - v1->Gety() ) / ( v2->Gety() - v1->Gety() );
            if ( (ti >= 0) && (ti <= 1) ){
                xint = v1->Getx() + ( v2->Getx() - v1->Getx() ) * ti;
                yint = v->Gety();
                if (xint == 0.0)
                    break;
                else if ( (xint > v->Getx())
                       && (yint > retMin(v1->Gety(),v2->Gety()) )
                       && (yint <= retMax(v1->Gety(),v2->Gety())) ) {
                    qtd++;
                }
            }
        } else {
            if(v->Gety() == v1->Gety() &&
               v->Getx() >= retMin(v1->Getx(), v2->Getx()) &&
               v->Getx() <= retMax(v1->Getx(), v2->Getx())){
                break;
            }
        }
    }
    return (qtd % 2) != 0;
}

void Poligno::resetTransforms()
{
    this->localRotation->makeIdenty();
    this->localScale->makeIdenty();
    this->localTranslation->makeIdenty();
}

Vertice* Poligno::getProximitVertice(double x, double y)
{
    Vertice *result;
    Vertice *v;
    double minDist = 99999999.9;
    double euclid;
    for (int i = 0; i < qtdVertices; i++) {
        v = vertices[i];
        euclid = pow(v->Getx() - x, 2) + pow(v->Gety() - y, 2);
        if (euclid < minDist) {
            minDist = euclid;
            result = v;
        }
    }
    return result;
}

void Poligno::reDefineBBox()
{
    free(bbox->GetMax());
    free(bbox->GetMin());
    free(bbox);

    Vertice *vMax    = (Vertice*) malloc(sizeof(Vertice));
    vMax->Setw(1.0);
    double MIN = -99999999;
    vMax->Setx(MIN);
    vMax->Sety(MIN);
    vMax->Setz(MIN);
    Vertice *vMin    = (Vertice*) malloc(sizeof(Vertice));
    vMin->Setw(1.0);
    vMin->Setx(DBL_MAX);
    vMin->Sety(DBL_MAX);
    vMin->Setz(DBL_MAX);
    bbox->initialize(vMin, vMax);

    Vertice *v;
    for (int i = 0; i < qtdVertices; i++) {
        v = vertices[i];
        this->defineBbox(v);
    }
}

void Poligno::removeVertice(Vertice *v)
{
    Vertice **vNew;
    int qtdNew = this->qtdVertices - 1;
    if (qtdNew == 0) {
        free(vertices);
        qtdVertices = 0;
    } else {
        vNew = (Vertice**) malloc(sizeof(Vertice) * qtdNew);
        int k = 0;
        for (int i = 0; i < qtdVertices; i++) {
            if (vertices[i] != v) {
                vNew[k] = vertices[i];
                k++;
            }
        }
        qtdVertices = qtdNew;
        vertices = vNew;
    }
    free(v);
}


