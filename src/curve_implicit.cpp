#include <GL/glut.h>
#include <cmath>

// Define the polynomial coefficients (a, b, c)
float a = 1.0f;
float b = 0.0f;
float c = -0.5f;

// Number of points to generate
int numPoints = 100;

void drawPolynomialCurve() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);  // Set color to white

    glBegin(GL_POINTS);//GL_LINE_STRIP

    for (int i = 0; i < numPoints; ++i) {
        // Calculate x-coordinate within a specified range
        float x = -1.0f + i * (2.0f / (numPoints - 1));

        // Calculate y-coordinate based on the polynomial equation
        float y = a * x * x + b * x + c;

        // Draw the point
        glVertex2f(x, y);
    }

    glEnd();
    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Polynomial Curve using OpenGL and GLUT");
    glutDisplayFunc(drawPolynomialCurve);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
