#include <GL/glut.h>
#include <vector>
#include <cmath>

// Control points
std::vector<std::pair<float, float>> controlPoints;
bool drawing = false;


int factorial(int n) {
    if ( n < 2 ) return 1;

    return n * factorial(n - 1);
}

void drawQuadraticBezierCurve() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);  // Set color to white
    glLineWidth(2.0f);

    if (controlPoints.size() >= 3) {
        glBegin(GL_POINTS); //GL_POINTS or GL_LINE_STRIP

        // Calculate points on the curve
        for (float t = 0; t <= 1; t += 0.01) {
            // float x = (1 - t) * (1 - t) * controlPoints[0].first + 2 * (1 - t) * t * controlPoints[1].first + t * t * controlPoints[2].first;
            // float y = (1 - t) * (1 - t) * controlPoints[0].second + 2 * (1 - t) * t * controlPoints[1].second + t * t * controlPoints[2].second;
            
            float x = 0.0;
            float y = 0.0;
            int n = controlPoints.size();
            int n_fact = factorial(n);
            for (int k = 0; k < n; k++) {
                int c = n_fact / ( factorial(k) * factorial(n-k) );
                x += controlPoints[k].first  * c * pow(t, k) * pow( 1-t, n-k );
                y += controlPoints[k].second * c * pow(t, k) * pow( 1-t, n-k );
            }
            
            glVertex2f(x, y);
        }

        glEnd();

        // Draw control points
        glColor3f(1.0f, 0.0f, 0.0f);  // Set color to red
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        for (auto point : controlPoints) {
            glVertex2f(point.first, point.second);
        }
        glEnd();
    }
    

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        controlPoints.push_back(std::make_pair((float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1, 1 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2));
        glutPostRedisplay();  // Trigger the display function to draw the Bezier curve
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        controlPoints.clear();
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Quadratic Bezier Curve");
    glutDisplayFunc(drawQuadraticBezierCurve);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}
