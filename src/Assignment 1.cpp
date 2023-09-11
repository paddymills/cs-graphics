/*
Name: <YOUR NAME>
Student ID: <STUDENT ID>
Email: <YOUR EMAIL>

Please write what this program does or also mention what doesn't work .

Status:
1. This code can create ...
2. 

*/



#include <GL/glut.h>
#include <vector>
#include<iostream>


using namespace std;
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

bool g_bDragging = true;

// MOUSE Function
void mouse(int button, int state, int x, int y)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//When your mouse dragging this function is working
		

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		// When you release your mouse left button
		

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// When you want to finish your polygon creation

	}

}

void display()
{
	// Create your LINES for polygon 
	printf("Display function");
	

}

void OnReshape(int w, int h)
{
	printf("Reshape");
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void Init(void)
{
	printf("init");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(5.0);
	glLogicOp(GL_XOR);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}



void OnMouseMove(int mouse_x, int mouse_y)
{
	if (g_bDragging)
	{
		// When you drag, create a line from the last point
		printf("dragging");
		
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Polygon Creation using mouse");
	Init();
	glutMouseFunc(mouse);
	glutMotionFunc(OnMouseMove);
	glutDisplayFunc(display);
	glutReshapeFunc(OnReshape);

	glutMainLoop();
	return 0;
}
