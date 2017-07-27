#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

GLfloat v[8][3] = {{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}};
GLfloat n[8][3] = {{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}};
GLfloat co[8][3] = {{0,0,0},{1,0,0},{1,1,0},{0,1,0},{0,0,1},{1,0,1},{1,1,1},{0,1,1}};

void polygon(int a,int b,int c,int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(co[a]);
	glNormal3fv(n[a]);
	glVertex3fv(v[a]);
	glColor3fv(co[b]);
	glNormal3fv(n[b]);
	glVertex3fv(v[b]);
	glColor3fv(co[c]);
	glNormal3fv(n[c]);
	glVertex3fv(v[c]);
	glColor3fv(co[d]);
	glNormal3fv(n[d]);
	glVertex3fv(v[d]);
	glEnd();
}

void cube()
{
	polygon(0,3,2,1);
	polygon(3,7,6,2);
	polygon(7,4,5,6);
	polygon(4,0,1,5);
	polygon(1,2,6,5);
	polygon(3,0,4,7);
}

static GLfloat theta[] = {0,0,0};
static GLint axis = 2;
static GLfloat view[] = {0,0,5};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(view[0],view[1],view[2],0,0,0,0,1,0);
	
	glRotatef(theta[0],1,0,0);
	glRotatef(theta[1],1,1,0);
	glRotatef(theta[2],1,0,1);
	
	cube();
	glFlush();
	glutSwapBuffers();
}

void mouse(int btn,int state,int x,int y)
{
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
	if(btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 01;
	if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 02;
	
	theta[axis] += 2;
	if(theta[axis] >= 360)
	theta[axis] -= 360;
	display();
}

void keyboard(unsigned char key,int x,int y)
{
	if(key == 'x') view[0] -= 1;
	if(key == 'X') view[0] += 1;
	if(key == 'y') view[1] -= 1;
	if(key == 'Y') view[1] += 1;
	if(key == 'z') view[2] -= 1;
	if(key == 'Z') view[2] += 1; 
	display();
}

void myReshape(int w, int h)
{
	glViewport(0,0,500,500);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
	{
		glFrustum(-2,2,-2 * (GLfloat) h/(GLfloat) w,2 * (GLfloat) h/(GLfloat) w,2,20);
	}
	else
	glFrustum(-2 * (GLfloat) w/(GLfloat) h,2 * (GLfloat) w/(GLfloat) h,-2,2,2,20);
	
	//gluPerspective(45,w/h,-10,10);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("persp");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

