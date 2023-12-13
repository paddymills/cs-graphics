#include <GL/glut.h>
#include <cmath>

float angle = 45.0f; // Launch angle in degrees
float initialSpeed = 10.0f; // Initial speed
float g = 9.8f; // Acceleration due to gravity

float time = 0.0f;
float xdir = 1.0;
float ydir = 1.0;

void update(int value) {
    // Calculate the new position using projectile motion equations
    float y = initialSpeed * time * sin(angle) - (0.5 * g * time * time);
    float x = initialSpeed * time * cos(angle);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);

    glutPostRedisplay();
    glutTimerFunc(100, update, 0); // 60 fps
    time += 0.1; // Adjust time step for animation speed
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); // Red rectangle

    // Draw a rectangle
    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Projectile Motion - C++ OpenGL");
    glutInitWindowSize(800, 600);
    glutDisplayFunc(display);

    glutTimerFunc(100, update, 0); // Initial launch

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-10, 10, -10, 10);

    glutMainLoop();
    return 0;
}
