#include <GL/glut.h>
#include <cmath>

// Circle parameters
struct Circle {
    float x, y;
    float radius;
};

float PI = 3.1416;
Circle setA = { -0.2f, 0.0f, 0.1f }; // Circle representing Set A
Circle setB = { -0.1f, 0.0f, 0.1f };  // Circle representing Set B

// Function to draw a circle
void drawCircle(Circle circle) {
    int segments = 100;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * PI * float(i) / float(segments);
        float x = circle.radius * cosf(theta);
        float y = circle.radius * sinf(theta);
        glVertex2f(circle.x + x, circle.y + y);
    }
    glEnd();
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Set A in red
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(setA);

    // Draw Set B in blue
    glColor3f(0.0f, 0.0f, 1.0f);
    drawCircle(setB);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Set Operations with OpenGL");

    glutDisplayFunc(display);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white

    glutMainLoop();
    return 0;
}
