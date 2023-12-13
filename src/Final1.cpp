#include <GL/glut.h>

// Define the properties of the moving rectangle
float movingRectX = 50.0f;
float movingRectY = 50.0f;
float movingRectWidth = 20.0f;
float movingRectHeight = 20.0f;
float movingRectSpeedX = 8.0f;
float movingRectSpeedY = 4.0f;

// Define the properties of the stationary rectangle
float stationaryRectX = 150.0f;
float stationaryRectY = 150.0f;
float stationaryRectWidth = 60.0f;
float stationaryRectHeight = 60.0f;

// Define the screen boundaries
float screenWidth = 600.0f;
float screenHeight = 400.0f;

bool checkCollision(int x, int y) {
    if (
        x >= stationaryRectX && x <= stationaryRectX + stationaryRectWidth &&
        y >= stationaryRectY && y <= stationaryRectY + stationaryRectHeight
    )
        return true;
    
    return false;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the moving rectangle
    glColor3f(1.0, 0.0, 0.0); // Red color
    glBegin(GL_POLYGON);
    glVertex2f(movingRectX, movingRectY);
    glVertex2f(movingRectX + movingRectWidth, movingRectY);
    glVertex2f(movingRectX + movingRectWidth, movingRectY + movingRectHeight);
    glVertex2f(movingRectX, movingRectY + movingRectHeight);
    glEnd();

    // Draw the stationary rectangle
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glBegin(GL_POLYGON);
    glVertex2f(stationaryRectX, stationaryRectY);
    glVertex2f(stationaryRectX + stationaryRectWidth, stationaryRectY);
    glVertex2f(stationaryRectX + stationaryRectWidth, stationaryRectY + stationaryRectHeight);
    glVertex2f(stationaryRectX, stationaryRectY + stationaryRectHeight);
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    // Update the position of the moving rectangle
    movingRectX += movingRectSpeedX;
    movingRectY += movingRectSpeedY;

    // Check for collisions with the screen boundaries
    if (movingRectX < 0 || movingRectX + movingRectWidth > screenWidth) {
        movingRectSpeedX *= -1; // Reverse the direction on collision
    }

    if (movingRectY < 0 || movingRectY + movingRectHeight > screenHeight) {
        movingRectSpeedY *= -1; // Reverse the direction on collision
    }

    //code goes here
    if (
        checkCollision(movingRectX, movingRectY) || 
        checkCollision(movingRectX, movingRectY + movingRectHeight) || 
        checkCollision(movingRectX + movingRectWidth, movingRectY) || 
        checkCollision(movingRectX + movingRectWidth, movingRectY + movingRectHeight)
    ) {
        stationaryRectX += movingRectSpeedX;
        stationaryRectY += movingRectSpeedY;

        movingRectSpeedX *= -1; // Reverse the direction on collision
        movingRectSpeedY *= -1; // Reverse the direction on collision
    }

    // Check for stationary rect collisions with the screen boundaries
    if (stationaryRectX < 0) {
        stationaryRectX *= -1;
    }
    if (stationaryRectY < 0) {
        stationaryRectY *= -1;
    }
    if (stationaryRectX + stationaryRectWidth > screenHeight) {
        stationaryRectX = stationaryRectX + stationaryRectWidth - screenWidth; // Reverse the direction on collision
    }
    if (stationaryRectY + stationaryRectHeight > screenHeight) {
        stationaryRectY = stationaryRectY + stationaryRectHeight - screenHeight; // Reverse the direction on collision
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Call update function every 16 milliseconds
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Collision Avoidance");

    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
