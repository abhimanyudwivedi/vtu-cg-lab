#include<stdio.h>
#include<GL/glut.h>

void obj(double tx,double ty,double tz,double sx,double sy,double sz)
{
	glRotated(50,0,1,0);
	glRotated(10,-1,0,0);
	glRotated(11.7,0,0,-1);
	
	glTranslated(tx,ty,tz);
	glScaled(sx,sy,sz);
	glutSolidCube(1);
	glLoadIdentity();
}

void display()
{
	glViewport(0,0,500,500);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	obj(0,0,0.5,1,1,0.04);
	obj(0.0,-0.5,0,1,0.04,1);
	obj(-0.5,0,0,0.04,1,1);
	
	obj(0,-0.3,0,0.02,0.2,0.02);
	obj(0,-0.3,-0.4,0.02,0.2,0.02);
	obj(0.4,-0.3,0,0.02,0.2,0.02);
	obj(0.4,-0.3,-0.4,0.02,0.2,0.02);
	
	obj(0.2,-0.18,-0.2,0.6,0.02,0.6);
	
	glRotated(50,0,1,0);
	glRotated(10,-1,0,0);
	glRotated(11.7,0,0,-1);
	
	glTranslated(0.3,-0.1,-0.3);
	glutSolidTeapot(0.09);
	glLoadIdentity();
	glFlush();
}


void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	float ambient[] = {1,1,1,1};
	float lightpos[] = {27,80,2,3};
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("teapot");
	glutDisplayFunc(display);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,lightpos);
	glMaterialfv(GL_FRONT,GL_AMBIENT,ambient);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
