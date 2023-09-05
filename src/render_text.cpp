#include <GL/glut.h>
#include <string>

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

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Call the renderText function to display "Hello, World!" at (100, 300)
    renderText("Hello, World! ", 100, 300);
    renderText("This is sayed reza ", 100, 400);

    glFlush();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (GLfloat)w / (GLfloat)h, 1, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Hello World");

    glutDisplayFunc(display);
    //glutReshapeFunc(myReshape);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black

    glutMainLoop();
    return 0;
}
