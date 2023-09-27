/**
 *  teaambient.c
 *  This program renders three lighted, shaded teapots, with
 *  different ambient values.
 */
#include <stdlib.h>
#include <GL/glut.h>

 /*  Initialize light source and lighting model.
  */

GLfloat light_position[] =  { 0.0, 1.0, 0.0, 0.0 };

void myinit(void) {
    GLfloat light_ambient[] =   { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] =   { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] =  { 1.0, 1.0, 1.0, 1.0 };
    /* light_position is NOT default value */
   
    // GLfloat light_position[] =  { 0.0, 1.0, 0.0, 0.0 };
    GLfloat global_ambient[] =  { 0.75, 0.75, 0.75, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glFrontFace(GL_CW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void display(void) {
    GLfloat material_ambient[] =  { 0.2, 0.2, 0.2, 1.0 };
  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update light position
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    /*  material has moderate ambient reflection */
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glPushMatrix();
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, -1, 0, 1, 0);
    glutSolidTeapot(1.0);
    glPopMatrix();

    glFlush();

}

void kbd(unsigned char key, int x, int y) {
	switch (key) {
		case 'q':   // increase X-value
            light_position[0] += 0.1;

			break;
		case 'a':   // decrease X-value
            light_position[0] -= 0.1;
        
			break;
		case 'w':   // increase Y-value
            light_position[1] += 0.1;
        
			break;
		case 's':   // decrease Y-value
            light_position[1] -= 0.1;
        
			break;
		case 'e':   // increase Z-value
            light_position[2] += 0.1;
        
			break;
		case 'd':   // decrease Z-value
            light_position[2] -= 0.1;
        
			break;
		
		default:
			break;
	}

    for (int i = 0; i < 3; i++) {
        if (light_position[i] > 1.0) light_position[i] = 1.0;
        else if (light_position[i] < -1.0) light_position[i] = -1.0;
    }
    

	// almost all options change the display, so lets re-draw it
	glutPostRedisplay();
}


void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (GLfloat)w / (GLfloat)h, 1, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(kbd);
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
