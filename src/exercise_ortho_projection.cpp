
#include <stdio.h>
#include <GL/glut.h>
#include <string>


using namespace std;

double v = 0;
double h = 0;
double depth = 0;

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    printf("Hit key: %c", key);
    switch (key) {
    case 'w': // Pan up
        v += 0.1;
        
        break;
    case 's': // Pan down
        v -= 0.1;
        
        break;
    case 'a': // Pan left 
        h -= 0.1;

        break;
    case 'd': // Pan right
        h += 0.1;
        
        break;
    case 'i': // Pan in 
        depth -= 0.1;

        break;
    case 'o': // Pan out
        depth += 0.1;

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
    printf("Reshape called");
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// Function to display the scene
void display() {
    printf("display called");
    glClear(GL_COLOR_BUFFER_BIT);

    //change your orthographic view here
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1+h, 1+h, -1+v,1+v, -1+depth,1+depth);
    glMatrixMode(GL_MODELVIEW);

    renderText("h: " + to_string(h), 10, 3 * 25);
    renderText("v: " + to_string(v), 10, 2 * 25);
    renderText("d: " + to_string(depth), 10, 1 * 25);
    

    // Draw your scene here
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Orthographics Projection with Keyboard");
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}