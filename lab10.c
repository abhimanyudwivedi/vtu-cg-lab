#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

#define maxx 25
#define maxy 20

float xo = 50, yo = 50;
	int x[maxx],y[maxy],dx=15,dy=20;

void myinit()
{
	glClearColor(1,1,1,1);
	glColor3f(1,0,0);
	glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,499,0,499);
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int i,j;
	for(i=0;i<maxx;i++)
	x[i] = xo + i * dx;
	for(i=0;i<maxy;i++)
	y[i] = yo + i * dy;
//	glColor3f(1,0,0);
	for(i=0;i<maxx-1;i++)
	for(j=0;j<maxy-1;j++)
	{
	glBegin(GL_LINE_LOOP);
		glColor3f(1,0,0);
		glVertex2f(x[i],y[j]);
		glVertex2f(x[i],y[j+1]);
		glVertex2f(x[i+1],y[j+1]);
		glVertex2f(x[i+1],y[j]);
	glEnd();
	}
	glFlush();
	//glFlush();
}


void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("mesh");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
