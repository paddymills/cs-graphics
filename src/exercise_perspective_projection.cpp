#include <GL/glut.h>
#include <string>

double vw = 800, vh = 600;

double v = 0;
double h = 0;
double d = 0;

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        v += 0.1;
        
        break;
    case 's':
        v -= 0.1;
        
        break;
    case 'a':
        h -= 0.1;
        
        break;
    case 'd':
        h += 0.1;
        
        break;
    case 'i': 
        d -= 0.1;
        
        break;
    case 'o':
        d += 0.1;
        
        break;
    }
    glutPostRedisplay(); // Redraw the scene
}

// Function to render text on the screen
void renderText(const std::string& text, float x, float y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600); // Adjust the values as needed for your window size

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f); // Set text color to white
    glRasterPos2f(x, y);

    // Loop through the characters in the text and render them one by one
    for (const char& character : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Function to handle resizing of the viewport
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //change your perspective view here
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluLookAt(0+h, 0+v, 0-d, 0, 0, -2.0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);

    renderText("h: " + std::to_string(h), 10, 3 * 25);
    renderText("v: " + std::to_string(v), 10, 2 * 25);
    renderText("d: " + std::to_string(d), 10, 1 * 25);

    
    // Draw your scene here
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, -2.0);
        glVertex3f(0.5, -0.5, -2.0);
        glVertex3f(0.0, 0.5, -2.0);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("GLU LookAt with Keyboard");
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
