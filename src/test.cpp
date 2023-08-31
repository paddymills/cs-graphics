
#include "GL/glut.h"

static GLfloat trans_v = 0.0;   // vertical translate
static GLfloat trans_h = 0.0;   // horizontal translate

float from_rgb_val(int val) {
    return val / 255.0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glTranslatef(trans_h, trans_v, 0.0);
    glRectf(-3, -3, 2, 2);

    glPopMatrix();

    glutSwapBuffers();
}

void kbd(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:    trans_v += 1.0; break;
        case GLUT_KEY_DOWN:  trans_v -= 1.0; break;
        case GLUT_KEY_LEFT:  trans_h -= 1.0; break;
        case GLUT_KEY_RIGHT: trans_h += 1.0; break;
    
        default: break;
    }

    glutPostRedisplay();
}

void init()
{
    glClearColor(
        from_rgb_val(76),
        from_rgb_val(86),
        from_rgb_val(106),
        0.0
    );
    glColor3f(
        from_rgb_val(229),
        from_rgb_val(233),
        from_rgb_val(240)
    );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
}

int main(int argc, char** argv)
{
    int size_w = 640;
    int size_h = 480;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(size_w, size_h);
    int screen_w = glutGet(GLUT_SCREEN_WIDTH);
    int screen_h = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition(screen_w/2 - size_w/2, screen_h/2 - size_h/2);
    
    glutCreateWindow("Assignment 1");
    init();

    glutDisplayFunc(display);
    glutSpecialFunc(kbd);
    glutMainLoop();
}