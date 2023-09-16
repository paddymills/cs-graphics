/*
	Name: Patrick Miller
	Student ID: pjm6196
	Email: pjm6196@psu.edu

	Please write what this program does or also mention what doesn't work .

	Status:
	1. create polygons by selecting points in the window
	2. commit a polygon by right-clicking
	3. set last commited polygon's color to Red or Green by pressing 'r' or 'g' respectively
	4. preview the current polygon being built in grey
	5. press 'c' to clear all polygons
	6. press 'q' to quit
	7. click and hold left button to display a line from the last point to the cursor
*/

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>


using namespace std;

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

bool g_bDragging = true;

struct Point {
	int x, y;
};

struct Color {
	float r, g, b;
};

struct Polygon {
	vector<Point> points;
	Color color;
};

vector<Polygon> polygons;
Polygon working_polygon;
Point mouse_pos;

void finalize() {
	printf("finalizing polygon\n");

	// push working_polygon onto polygons
	Polygon copied = working_polygon;
	polygons.push_back(copied);

	// create new working_polygon
	working_polygon.points.clear();

	// call repaint
	glutPostRedisplay();
}

int normalize_mouse(int mouse_y) {
	return WINDOW_HEIGHT - mouse_y;
}

// MOUSE Function
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//When your mouse dragging this function is working
		printf("Left button pressed down\n");

		// set state to dragging
		g_bDragging = true;

		// repaint display
		glutPostRedisplay();
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		// When you release your mouse left button
		printf("Left button press released at (%d, %d)\n", x, y);

		// release dragging state
		g_bDragging = false;
		
		// add point to current creating polygon
		Point new_point = { x, normalize_mouse(y) };
		working_polygon.points.push_back(new_point);

		// repaint display
		glutPostRedisplay();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		// When you want to finish your polygon creation
		printf("Right button pressed down\n");

		// finalize & paint polygon
		finalize();
	}
}

void OnMouseMove(int mouse_x, int mouse_y) {
	if (g_bDragging && working_polygon.points.size() > 0) {
		// When you drag, create a line from the last point
		printf("dragging\n");

		// set mouse position
		mouse_pos.x = mouse_x;
		mouse_pos.y = normalize_mouse(mouse_y);

		// call repaint
		glutPostRedisplay();
	}
}

void kbd(unsigned char key, int x, int y) {
	switch (key) {
		case 'r':	// fill last polygon with red
			polygons.back().color.r = 1.0;
			polygons.back().color.g = 0.0;
			polygons.back().color.b = 0.0;

			break;
		case 'g':	// fill last polygon with green
			polygons.back().color.r = 0.0;
			polygons.back().color.g = 1.0;
			polygons.back().color.b = 0.0;
			break;
		case 't':	// fill last polygon with no color
			polygons.back().color.r = 0.0;
			polygons.back().color.g = 0.0;
			polygons.back().color.b = 0.0;

			break;
		case 'c':	// clear the screen
			polygons.clear();
			working_polygon.points.clear();

			break;
		case 'd':	// Bonus: drop polygon down from its position
			printf("Moving working polygon down 10 points\n");
			for (int i = 0; i < working_polygon.points.size(); i++) {
				working_polygon.points[i].y -= 10;
			}

			break;
		case 'q':	// exit application
			glutLeaveMainLoop();
			break;
		
		default:
			break;
	}

	// almost all options change the display, so lets re-draw it
	glutPostRedisplay();
}

void display() {
	printf("Display function\n");
	
	// temporary variables
	Polygon polygon;
	Point point;
	
	glClear(GL_COLOR_BUFFER_BIT);

	// draw polygons
	for (int i = 0; i < polygons.size(); i++) {
		printf("Painting polygon %d\n", i);
		polygon = polygons[i];

		// set polygon color
    	glColor3f(polygon.color.r, polygon.color.g, polygon.color.b);

		// draw polygon
		glBegin(GL_POLYGON);
		for (int j = 0; j < polygon.points.size(); j++) {
			point = polygon.points[j];

			printf(" > Painting point %d (%d, %d)\n", j, point.x, point.y);
			glVertex2f(point.x, point.y);
		}
		glEnd();
	}

	// show working polygon in grey
	glColor3f(0.5, 0.5, 0.5);	// grey
	glBegin(GL_POLYGON);
	for (int i = 0; i < working_polygon.points.size(); i++) {
		point = working_polygon.points[i];
		glVertex2f(point.x, point.y);
	}
	glEnd();

	// if dragging, draw line from last point to cursor
	if (g_bDragging && working_polygon.points.size() > 0) {
		Point last_point = working_polygon.points.back();
		glBegin(GL_LINES);
			glVertex2f(last_point.x, last_point.y);
			glVertex2f(mouse_pos.x, mouse_pos.y);
		glEnd();
	}
	
	glFlush();
}

void OnReshape(int w, int h) {
	printf("Reshape\n");

	// update window dimensions
	WINDOW_WIDTH = w;
	WINDOW_HEIGHT = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void Init(void) {
	printf("init\n");
	glClearColor(1.0, 1.0, 1.0, 1.0);	// this is white

	glPointSize(5.0);
	glLogicOp(GL_XOR);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Polygon Creation using mouse");
	Init();

	// callback functions
	glutMouseFunc(mouse);
	glutKeyboardFunc(kbd);
	glutMotionFunc(OnMouseMove);
	glutDisplayFunc(display);
	glutReshapeFunc(OnReshape);

	glutMainLoop();
	return 0;
}
