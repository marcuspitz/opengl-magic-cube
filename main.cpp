#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "constantes.h"
#include "Vertice.h"
#include "Cube.h"
#include <unistd.h>
#include "Consts.h"
#include "Globals.h"

/*
    A simple magic cube with OpenGL + GL Utils + Simple Maths
    author: Marcus Pitz
    since: 2017-01
    License: http://www.apache.org/licenses/LICENSE-2.0
*/

/*
void onMouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            printf("\nMOUSE LEFT CLICKED x:%d y:%d", x, y);
            moved = true;
        } else if (button == GLUT_RIGHT_BUTTON) {
            printf("\nMOUSE RIGHT CLICKED x:%d y:%d", x, y);
        }
    } else { //RELEASE
        if (button == GLUT_LEFT_BUTTON) {
            moved = false;
            printf("\nMOUSE LEFT RELEASED x:%d y:%d", x, y);

        } else if (button == GLUT_RIGHT_BUTTON) {
            printf("\nMOUSE RIGHT RELEASED x:%d y:%d", x, y);
        }
    }
}
void onMouseMove(int x, int y)
{
    printf("Mouse move");
    if (moved) {
        int rotX = x - lastX;
        int rotY = y - lastY;

        if (rotX != 0) {
            printf("ROT X=%d", rotX);
            Transform *tX = (Transform*) malloc(sizeof(Transform));
            tX->initialize();
            tX->makeRotationX(rotX);
            Vertice *toFree = posCamera;
            tX->makeRotationX(rotX);
            posCamera = tX->transformVertice(posCamera);
            free(toFree);
        }

        if (rotY != 0) {
            printf("ROT Y=%d", rotY);
            Transform *tY = (Transform*) malloc(sizeof(Transform));
            tY->initialize();
            tY->makeRotationY(rotY);
            Vertice *toFree = posCamera;
            tY->makeRotationY(rotY);
            posCamera = tY->transformVertice(posCamera);
            free(toFree);
        }
    }
    lastX = x;
    lastY = y;
    glutPostRedisplay();
}*/

/**
 The magic is formed like:
    white
    white green
    white blue
    white orange
    white red
    white orange blue
    white red blue
    white red green
    white green orange

    yellow
    yellow blue
    yellow green
    yellow red
    yellow orange
    yellow orange blue
    yellow red blue
    yellow red green
    yellow green orange

    green
    green orange
    green red

    blue
    blue orange
    blue red

    orange

    red
**/
void createMagicCube()
{
    c = (Cube**) malloc(sizeof(Cube)*26);

    //yellow
	Vertice *v1 = (Vertice*) malloc(sizeof(Vertice));
	Cube *c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-5.0, -5.0, 5.5, 1.0);
	c1->initialize(v1, 10.0, yellow, black, black, black, black, black);
	c1->line   = 1;
	c1->column = 1;
	c1->depth  = 0;
	c1->id     = 1;
	c1->center = true;
	c[0] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-5.0, 5.5, 5.5, 1.0);
	c1->initialize(v1, 10.0, yellow, black, black, black, orange, black);
	c1->line   = 0;
	c1->column = 1;
	c1->depth  = 0;
	c1->id     = 2;
	c[1] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(5.5, -5.0, 5.5, 1.0);
	c1->initialize(v1, 10.0, yellow, black, black, green, black, black);
	c1->line   = 1;
	c1->column = 2;
	c1->depth  = 0;
	c1->id     = 3;
	c[2] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-5.0, -15.5, 5.5, 1.0);
	c1->initialize(v1, 10.0, yellow, black, black, black, black, red);
	c1->line   = 2;
	c1->column = 1;
	c1->depth  = 0;
	c1->id     = 4;
	c[3] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-15.5, -5.0, 5.5, 1.0);
	c1->initialize(v1, 10.0, yellow, black, blue, black, black, black);
	c1->line   = 1;
	c1->column = 0;
	c1->depth  = 0;
	c1->id     = 5;
	c[4] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-15.5, 5.5, 5.5, 1.0);
	c1->initialize(v1, 10.0, yellow, black, blue, black, orange, black);
	c1->tip = true;
	c1->line   = 0;
	c1->column = 0;
	c1->depth  = 0;
	c1->id     = 6;
	c[5] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(5.5, 5.5, 5.5, 1.0);
	c1->initialize(v1, 10.0, yellow, black, black, green, orange, black);
	c1->tip = true;
	c1->line   = 0;
	c1->column = 2;
	c1->depth  = 0;
	c1->id     = 7;
	c[6] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(5.5, -15.5, 5.5, 1.0);
	c1->initialize(v1, 10.0, yellow, black, black, green, black, red);
	c1->tip = true;
	c1->line   = 2;
	c1->column = 2;
	c1->depth  = 0;
	c1->id     = 8;
	c[7] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-15.5, -15.5, 5.5, 1.0);
	c1->initialize(v1, 10.0, yellow, black, blue, black, black, red);
	c1->tip = true;
	c1->line   = 2;
	c1->column = 0;
	c1->depth  = 0;
	c1->id     = 9;
	c[8] = c1;
	qtdCube++;

	//red
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-5.0, -15.5, -5.0, 1.0);
	c1->initialize(v1, 10.0, black, black, black, black, black, red);
	c1->center = true;
	c1->line   = 2;
	c1->column = 1;
	c1->depth  = 1;
	c1->id     = 10;
	c[9] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-15.5, -15.5, -5.0, 1.0);
	c1->initialize(v1, 10.0, black, black, blue, black, black, red);
	c1->line   = 2;
	c1->column = 0;
	c1->depth  = 1;
	c1->id     = 11;
	c[10] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(5.5, -15.5, -5.0, 1.0);
	c1->initialize(v1, 10.0, black, black, black, green, black, red);
	c1->line   = 2;
	c1->column = 2;
	c1->depth  = 1;
	c1->id     = 12;
	c[11] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(5.5, -15.5, -15.5, 1.0);
	c1->initialize(v1, 10.0, black, white, black, green, black, red);
	c1->tip = true;
	c1->line   = 2;
	c1->column = 2;
	c1->depth  = 2;
	c1->id     = 13;
	c[12] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-5.0, -15.5, -15.5, 1.0);
	c1->initialize(v1, 10.0, black, white, black, black, black, red);
	c1->line   = 2;
	c1->column = 1;
	c1->depth  = 2;
	c1->id     = 14;
	c[13] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-15.5, -15.5, -15.5, 1.0);
	c1->initialize(v1, 10.0, black, white, blue, black, black, red);
	c1->tip = true;
	c1->line   = 2;
	c1->column = 0;
	c1->depth  = 2;
	c1->id     = 15;
	c[14] = c1;
	qtdCube++;

	//blue
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-15.5, -5.0, -5.0, 1.0);
	c1->initialize(v1, 10.0, black, black, blue, black, black, black);
	c1->center = true;
	c1->line   = 1;
	c1->column = 0;
	c1->depth  = 1;
	c1->id     = 16;
	c[15] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-15.5, 5.5, -5.0, 1.0);
	c1->initialize(v1, 10.0, black, black, blue, black, orange, black);
	c1->line   = 0;
	c1->column = 0;
	c1->depth  = 1;
	c1->id     = 17;
	c[16] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-15.5, -5.0, -15.5, 1.0);
	c1->initialize(v1, 10.0, black, white, blue, black, black, black);
	c1->line   = 1;
	c1->column = 0;
	c1->depth  = 2;
	c1->id     = 18;
	c[17] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-15.5, 5.5, -15.5, 1.0);
	c1->initialize(v1, 10.0, black, white, blue, black, orange, black);
	c1->tip = true;
	c1->line   = 0;
	c1->column = 0;
	c1->depth  = 2;
	c1->id     = 19;
	c[18] = c1;
	qtdCube++;

	//orange
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-5.0, 5.5, -5.0, 1.0);
	c1->initialize(v1, 10.0, black, black, black, black, orange, black);
	c1->center = true;
	c1->line   = 0;
	c1->column = 1;
	c1->depth  = 1;
	c1->id     = 20;
	c[19] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-5.0, 5.5, -15.5, 1.0);
	c1->initialize(v1, 10.0, black, white, black, black, orange, black);
	c1->line   = 0;
	c1->column = 1;
	c1->depth  = 2;
	c1->id     = 21;
	c[20] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(5.5, 5.5, -15.5, 1.0);
	c1->initialize(v1, 10.0, black, white, black, green, orange, black);
	c1->tip = true;
	c1->line   = 0;
	c1->column = 2;
	c1->depth  = 2;
	c1->id     = 22;
	c[21] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(5.5, 5.5, -5.0, 1.0);
	c1->initialize(v1, 10.0, black, black, black, green, orange, black);
	c1->line   = 0;
	c1->column = 2;
	c1->depth  = 1;
	c1->id     = 23;
	c[22] = c1;
	qtdCube++;

	//green
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(5.5, -5.0, -15.5, 1.0);
	c1->initialize(v1, 10.0, black, white, black, green, black, black);
	c1->line   = 1;
	c1->column = 2;
	c1->depth  = 2;
	c1->id     = 24;
	c[23] = c1;
	qtdCube++;
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(5.5, -5.0, -5.0, 1.0);
	c1->initialize(v1, 10.0, black, black, black, green, black, black);
	c1->center = true;
	c1->line   = 1;
	c1->column = 2;
	c1->depth  = 1;
	c1->id     = 25;
	c[24] = c1;
	qtdCube++;

	//white
	v1 = (Vertice*) malloc(sizeof(Vertice));
	c1 = (Cube*) malloc(sizeof(Cube));
	v1->initialize(-5.0, -5.0, -15.5, 1.0);
	c1->initialize(v1, 10.0, black, white, black, black, black, black);
	c1->center = true;
	c1->line   = 1;
	c1->column = 1;
	c1->depth  = 2;
	c1->id     = 26;
	c[25] = c1;
	qtdCube++;


}

void loadColors()
{
    white.R = 1.0;
    white.G = 1.0;
    white.B = 1.0;
    yellow.R = 1.0;
    yellow.G = 1.0;
    yellow.B = 0.0;
    red.R = 1;0;
    red.G = 0;0;
    red.B = 0;0;
    green.R = 0.0;
    green.G = 1.0;
    green.B = 0.0;
    blue.R = 0.0;
    blue.G = 0.0;
    blue.B = 1.0;
    orange.R = 1.0;
    orange.G = 0.64;
    orange.B = 0.0;
    black.R = 0.0;
    black.G = 0.0;
    black.B = 0.0;
}

void reDraw (int w, int h) {
    printf("Redraw w=%d h%d\n", w, h);

    //Camera
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, w/h, 0.1, 1000.0f);
	glViewport(0, 0, (double)width, (double)height);

	//Models
	glMatrixMode (GL_MODELVIEW);
}

void updateCamera () {
    Vertice *newLook   = posCamera;
    Transform *rotUp   = NULL;
    Transform *rotLeft = NULL;

    if (ROT_UP != 0) {
        rotUp = (Transform*) malloc(sizeof(Transform));
        rotUp->initialize();
        rotUp->makeRotationX( ROT_UP );
        newLook = rotUp->transformVertice(newLook);
    }

    if (ROT_LEFT != 0) {
        rotLeft = (Transform*) malloc(sizeof(Transform));
        rotLeft->initialize();
        rotLeft->makeRotationY( ROT_LEFT );
        newLook = rotLeft->transformVertice(newLook);
    }

    ROT_UP   = 0.0;
    ROT_LEFT = 0.0;

    gluLookAt(newLook->Getx(), newLook->Gety(), newLook->Getz()
            , 0,0,0
            , 0,1,0);

    free(posCamera);
    posCamera = newLook;
}

void drawable(void) {
    glMatrixMode (GL_MODELVIEW);
	glClearColor(0.740f, 0.740f, 0.740f, 1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();

    updateCamera();

    glShadeModel(GL_FLAT);

    Cube *cb;
    for (int i = 0; i < qtdCube; i++) {
        cb = c[i];
        cb->draw();
    }

    glFlush();
	glutSwapBuffers();
}

void interpolateRotateX(Cube **c, int qtd ) {
    Transform *rot = (Transform*) malloc(sizeof(Transform));
    rot->initialize();
    rot->makeRotationX(-9);

    for (int i = 0; i < 10; i++) {

        for (int k = 0; k < qtd; k++) {
            c[k]->rot(rot);
        }
        drawable();
        usleep(15000);
    }
}

void interpolateRotateY(Cube **c, int qtd ) {
    Transform *rot = (Transform*) malloc(sizeof(Transform));
    rot->initialize();
    rot->makeRotationY(-9);

    for (int i = 0; i < 10; i++) {

        for (int k = 0; k < qtd; k++) {
            c[k]->rot(rot);
        }
        drawable();
        usleep(15000);
    }
}

void interpolateRotateZ(Cube **c, int qtd ) {
    Transform *rot = (Transform*) malloc(sizeof(Transform));
    rot->initialize();
    rot->makeRotationZ(-9);

    for (int i = 0; i < 10; i++) {

        for (int k = 0; k < qtd; k++) {
            c[k]->rot(rot);
        }
        drawable();
        usleep(15000);
    }
}

void movementX(int column) {
    Cube *cAux;
    int index = 0;
    Cube **toIntp = (Cube**) malloc(sizeof(Cube)*9);
    for (int i = 0; i < qtdCube; i++) {
        cAux = c[i];
        if (cAux->column == column) {
            toIntp[index] = cAux;
            index++;

            //center e coluna 1 tem tratamento igual a !tip
            if ( (!cAux->center) || (column == 1) ) {
                if (cAux->tip) {
                        if ( (cAux->depth == 0) && (cAux->line == 0) )
                            cAux->depth = 2;
                        else if ( (cAux->depth == 2) && (cAux->line == 0) )
                            cAux->line = 2;
                        else if ( (cAux->depth == 2) && (cAux->line == 2) )
                            cAux->depth = 0;
                        else if ( (cAux->depth == 0) && (cAux->line == 2) )
                            cAux->line = 0;
                } else {
                    if ( (cAux->line == 1) && (cAux->depth == 0) ) {
                        cAux->line = 0;
                        cAux->depth = 1;
                    }
                    else if ( (cAux->line == 0) && (cAux->depth == 1) ){
                        cAux->line = 1;
                        cAux->depth = 2;
                    }
                    else if ( (cAux->line == 1) && (cAux->depth == 2) ) {
                        cAux->line = 2;
                        cAux->depth = 1;
                    }
                    else if ( (cAux->line == 2) && (cAux->depth == 1) ) {
                        cAux->line = 1;
                        cAux->depth = 0;
                    }
                    else if ( (cAux->line == 2) && (cAux->depth == 0) ) {
                        cAux->line = 0;
                        cAux->depth = 0;
                    }
                    else if ( (cAux->line == 0) && (cAux->depth == 0) ) {
                        cAux->depth = 2;
                    }
                    else if ( (cAux->line == 0) && (cAux->depth == 2) ) {
                        cAux->line = 2;
                    }
                    else if ( (cAux->line == 2) && (cAux->depth == 2) ) {
                        cAux->depth = 0;
                    }
                }
            }

        }
    }
    interpolateRotateX(toIntp, index);
    free(toIntp);
}

void movementY(int line) {
    Cube *cAux;
    int index = 0;
    Cube **toIntp = (Cube**) malloc(sizeof(Cube)*9);
    for (int i = 0; i < qtdCube; i++) {
        cAux = c[i];
        if (cAux->line == line) {
            toIntp[index] = cAux;
            index++;

            if ( (!cAux->center) || (line == 1) ) {
                if (cAux->tip) {
                    if ( (cAux->depth == 0) && (cAux->column == 0) )
                        cAux->depth = 2;
                    else if ( (cAux->depth == 2) && (cAux->column == 0) )
                        cAux->column = 2;
                    else if ( (cAux->depth == 2) && (cAux->column == 2) )
                        cAux->depth = 0;
                    else if ( (cAux->depth == 0) && (cAux->column == 2) )
                        cAux->column = 0;

                } else {

                   if ( (cAux->column == 1) && (cAux->depth == 0) ) {
                        cAux->column = 0;
                        cAux->depth = 1;
                    }
                    else if ( (cAux->column == 0) && (cAux->depth == 1) ){
                        cAux->column = 1;
                        cAux->depth = 2;
                    }
                    else if ( (cAux->column == 1) && (cAux->depth == 2) ) {
                        cAux->column = 2;
                        cAux->depth = 1;
                    }
                    else if ( (cAux->column == 2) && (cAux->depth == 1) ) {
                        cAux->column = 1;
                        cAux->depth = 0;
                    }
                    else if ( (cAux->depth == 0) && (cAux->column == 0) )
                        cAux->depth = 2;
                    else if ( (cAux->depth == 2) && (cAux->column == 0) )
                        cAux->column = 2;
                    else if ( (cAux->depth == 2) && (cAux->column == 2) )
                        cAux->depth = 0;
                    else if ( (cAux->depth == 0) && (cAux->column == 2) )
                        cAux->column = 0;

                }
            }
        }
    }
    interpolateRotateY(toIntp, index);
    free(toIntp);
}

void movementZ(int depth) {
    Cube *cAux;
    int index = 0;
    Cube **toIntp = (Cube**) malloc(sizeof(Cube)*9);
    for (int i = 0; i < qtdCube; i++) {
        cAux = c[i];
        if (cAux->depth == depth) {
            toIntp[index] = cAux;
            index++;

            if ( (!cAux->center) || (depth == 1) ) {
                if (cAux->tip) {
                    if ( (cAux->line == 0) && (cAux->column == 0) )
                        cAux->column = 2;
                    else if ( (cAux->line == 2) && (cAux->column == 0) )
                        cAux->line = 0;
                    else if ( (cAux->line == 2) && (cAux->column == 2) )
                        cAux->column = 0;
                    else if ( (cAux->line == 0) && (cAux->column == 2) )
                        cAux->line = 2;

                } else {

                   if ( (cAux->column == 1) && (cAux->line == 0) ) {
                        cAux->column = 2;
                        cAux->line = 1;
                    }
                    else if ( (cAux->column == 0) && (cAux->line == 1) ){
                        cAux->column = 1;
                        cAux->line = 0;
                    }
                    else if ( (cAux->column == 1) && (cAux->line == 2) ) {
                        cAux->column = 0;
                        cAux->line = 1;
                    }
                    else if ( (cAux->column == 2) && (cAux->line == 1) ) {
                        cAux->column = 1;
                        cAux->line = 2;
                    }
                    else if ( (cAux->line == 0) && (cAux->column == 0) )
                        cAux->column = 2;
                    else if ( (cAux->line == 2) && (cAux->column == 0) )
                        cAux->line = 0;
                    else if ( (cAux->line == 2) && (cAux->column == 2) )
                        cAux->column = 0;
                    else if ( (cAux->line == 0) && (cAux->column == 2) )
                        cAux->line = 2;

                }
            }
        }
    }
    interpolateRotateZ(toIntp, index);
    free(toIntp);
}

void printCubes() {
    printf("\n\n ************BEGIN CUBE PRINT***********");
    for (int i = 0; i < qtdCube; i++) {
        Cube *cc = c[i];
        cc->printMe();
    }
    printf("\n\n ************END CUBE PRINT***********");
}

void shuffle()
{
    for (int i = 0; i < 50; i++) {
        int eixo = rand() % 3;
        //x
        if (eixo == 0){
            int mov = rand() % 3;
            movementX(mov);
        }
        //y
        else if (eixo == 1){
            int mov = rand() % 3;
            movementY(mov);
        }
        //z
        else if (eixo == 2){
            int mov = rand() % 3;
            movementZ(mov);
        }
    }
}

void onKeyBoardPress(unsigned char key, int x, int y) {
    printf("\n\nKEY:%d\n\n", key);

    if ( (key == KEY_q) || (key == KEY_Q) ) {
        movementX(0);
    } else if ( (key == KEY_w) || (key == KEY_W) ) {
        movementX(1);
    } else if ( (key == KEY_e) || (key == KEY_E) ) {
        movementX(2);
    } else if ( (key == KEY_a) || (key == KEY_A) ) {
        movementY(0);
    } else if ( (key == KEY_s) || (key == KEY_S) ) {
        movementY(1);
    } else if ( (key == KEY_d) || (key == KEY_D) ) {
        movementY(2);
    } else if ( (key == KEY_z) || (key == KEY_Z) ) {
        movementZ(0);
    } else if ( (key == KEY_x) || (key == KEY_X) ) {
        movementZ(1);
    } else if ( (key == KEY_c) || (key == KEY_C) ) {
        movementZ(2);
    } else if ( (key == 75) || (key == 107) )  { //K - RANDOM
        shuffle();
    } else if ( (key == 82) || (key == 114) )  { //R - RESET
        posCamera->Setx(INITIAL_CAMERA_X);
        posCamera->Sety(INITIAL_CAMERA_Y);
        posCamera->Setz(INITIAL_CAMERA_Z);
    } else if ( (key == KEY_P) || (key == KEY_p) ) {
        printCubes();
    }

    glutPostRedisplay(); //re-paint
}
//effects key
void otherKeys (int key, int x, int y) {
    const double ROT_T  = 5;
    const int KEY_RIGHT = 102;
    const int KEY_LEFT  = 100;
    const int KEY_UP    = 101;
    const int KEY_DOWN  = 103;

    if (key == KEY_UP) {
        ROT_UP = ROT_UP + ROT_T;
    }
    else if (key == KEY_DOWN) {
        ROT_UP = ROT_UP - ROT_T;
    }

    else if (key == KEY_LEFT) {
        ROT_LEFT = ROT_LEFT + ROT_T;
    }
    else if (key == KEY_RIGHT) {
        ROT_LEFT = ROT_LEFT - ROT_T;
    }
    glutPostRedisplay();
}

void init (void) {
    //Pos Camera
	posCamera = (Vertice*) malloc(sizeof(Vertice));
	posCamera->initialize(INITIAL_CAMERA_X, INITIAL_CAMERA_Y, INITIAL_CAMERA_Z, 1.0);

	glutKeyboardFunc      ( onKeyBoardPress );
	glutSpecialFunc       ( otherKeys );
	//glutMouseFunc         ( onMouseClick );
	//glutPassiveMotionFunc ( onMouseMove );

	loadColors();

	createMagicCube();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}

int main (int argc, const char * argv[]) {
    glutInit(&argc, (char **)argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition (460, 90);
	glutInitWindowSize (width, height);
	gMainWindow = glutCreateWindow("Magic Cube");

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

    init();

    glutDisplayFunc (drawable);
    glutReshapeFunc (reDraw);
    glutMainLoop();

    return 0;
}
