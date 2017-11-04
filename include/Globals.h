GLint gMainWindow = 0;
GLint width  = 500
    , height = 500;

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {5.0, 5.0, 500.0, 0.0};  /* Infinite light location. */

Cube **c;
Vertice *posCamera;
int qtdCube = 0;
int lastX, lastY;
bool moved = false;

GLdouble ROT_UP   = 0;
GLdouble ROT_LEFT = 0;

RGB white;
RGB yellow;
RGB red;
RGB green;
RGB blue;
RGB orange;
RGB black;

void safeFree(void* a) {
    if (a != NULL) {
        //printf("safe freeeee");
        free(a);
    }
}
