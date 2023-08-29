
/*
    Name:        Patrick Miller
    Class:       CMPSC 457
    Assignment:  Assignment 1
    Date:        8/29/2023
*/

#include "GL/glut.h"


float from_rgb_val(int val) {
    return val / 255.0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
        glVertex2f(-0.7,  0.75);
        glVertex2f( 0.7,  0.75);
        glVertex2f( 0.55, 0.25);
        glVertex2f(-0.55, 0.25);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-0.5,  -0.2);
        glVertex2f( 0.5,  -0.2);
        glVertex2f( 0.0,  -0.5);
    glEnd();

    glFlush();
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
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    int size_w = 640;
    int size_h = 480;


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(size_w, size_h);
    int screen_w = glutGet(GLUT_SCREEN_WIDTH);
    int screen_h = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition(screen_w/2 - size_w/2, screen_h/2 - size_h/2);
    
    glutCreateWindow("Assignment 1");
    glutDisplayFunc(display);
    init();

    glutMainLoop();
}