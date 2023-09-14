#include <GL/glut.h>
#include <stdlib.h>


double v[4]={0.0, 0.0, 0.0, 0.0};
double h[4]={0.0, 0.0, 0.0, 0.0};

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    /* clip planes */
    glClipPlane(GL_CLIP_PLANE0, v);
    glClipPlane(GL_CLIP_PLANE1, h);
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glutWireSphere(1.0, 20, 16);
    glPopMatrix();

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'e':
        v[0] = 1.0;
        h[1] = 1.0;

        break;
    case 'q':
        v[0] = -1.0;
        h[1] = 1.0;

        break;
    
    case 'd':
        v[0] = 1.0;
        h[1] = -1.0;

        break;
    
    case 'a':
        v[0] = -1.0;
        h[1] = -1.0;

        break;
    }
    glutPostRedisplay(); // Redraw the scene
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
