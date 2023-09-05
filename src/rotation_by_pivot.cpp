#include <GL/glut.h>
#include <cmath>

float angle = 0.0f; // Initial angle of rotation
float pivotX = 0.2f; // Pivot point X coordinate
float pivotY = 0.2f; // Pivot point Y coordinate
float rectangleWidth = 0.4f;
float rectangleHeight = 0.2f;

// Function to draw a rectangle
void drawRectangle() {
    glBegin(GL_POLYGON);
    glVertex2f(-rectangleWidth / 2, -rectangleHeight / 2);
    glVertex2f(rectangleWidth / 2, -rectangleHeight / 2);
    glVertex2f(rectangleWidth / 2, rectangleHeight / 2);
    glVertex2f(-rectangleWidth / 2, rectangleHeight / 2);
    glEnd();
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix(); // Push the current matrix onto the stack

    // Rotate around the origin (0,0)
    glTranslatef(pivotX, pivotY, 0.0f); // Translate to the pivot point
    glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around the origin
    glTranslatef(-pivotX, -pivotY, 0.0f); // Translate back to the original position

    // Draw the rotated rectangle
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    drawRectangle();

    glPopMatrix(); // Pop the matrix stack to restore the previous matrix

    glutSwapBuffers();
}

// Function to update the animation (rotation angle)
void update(int value) {
    angle += 1.0f; // Increment the rotation angle
    if (angle > 360.0f) {
        angle -= 360.0f; // Keep the angle within [0, 360) degrees
    }

    glutPostRedisplay(); // Trigger a display update
    glutTimerFunc(16, update, 0); // Call the update function again after 16 milliseconds
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating Rectangle");

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0); // Start the animation timer

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white

    glutMainLoop();
    return 0;
}
