#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>

#define outcode int

double xmin=50,xmax=100,ymin=50,ymax=100;
double xvmin=200,xvmax=300,yvmin=200,yvmax=300;

int TOP = 4, RIGHT = 8,LEFT = 2, BOTTOM = 1;

int compute(double x,double y)
{
	outcode code = 0;
	if(y > ymax)
	code |= TOP;
	if(y < ymin)
	code |= BOTTOM;
	if(x > xmax)
	code |= RIGHT;
	if(x < xmin)
	code |= LEFT;
	return code;
}

void cs(double x0,double y0,double x1,double y1)
{
	outcode oc0,oc1,ocout;
	int accept = 0, done = 0;
	
	oc0 = compute(x0,y0);
	oc1 = compute(x1,y1);
	
	do{
		if(!(oc0 | oc1))
		{
			accept = 1;
			done = 1;
		}
		else if(oc0 & oc1)
		{
			done = 1;
		}
	  	else
	  	{
	  		double x,y;
	  		ocout = oc0 ? oc0 : oc1;
	  		if(ocout & TOP)
	  		{
	  			x = x0 + (x1 - x0) * (ymax - y0)/(y1 - y0);
	  			y = ymax;
	  		}
	  		if(ocout & BOTTOM)
	  		{
	  			x = x0 + (x1 - x0) * (ymin - y0)/(y1 - y0);
	  			y = ymin;
	  		}
	  		if(ocout & RIGHT)
	  		{
	  			y = y0 + (y1 - y0) * (xmax - x0)/(x1 - x0);
	  			x = xmax;
	  		}
	  		if(ocout & LEFT)
	  		{
	  			y = y0 + (y1 - y0) * (xmin - x0)/(x1 - x0);
	  			x = xmin;
	   		}
	  		
	  		if(ocout == oc0)
	  		{
	  			x0 = x;
	  			y0 = y;
	  			oc0 = compute(x0,y0);
	  		}
	  		if(ocout == oc1)
	  		{
	  			x1 = x;
	  			y1 = y;
	  			oc1 = compute(x1,y1);
	  		}
	  		
	  	}
	  }while(!done);
	if(accept)
	{
		double sx = (xvmax - xvmin)/(xmax - xmin);
		double sy = (yvmax - yvmin)/(ymax - ymin);
		double vx0 = xvmin + (x0 - xmin) * sx;
		double vy0 = yvmin + (y0 - ymin) * sy;
		double vx1 = xvmin + (x1 - xmin) * sx;
		double vy1 = yvmin + (y1 - ymin) * sy;
		glBegin(GL_LINE_LOOP);
		glColor3f(1,0,0);
		glVertex2f(xvmin,yvmin);
		glVertex2f(xvmin,yvmax);
		glVertex2f(xvmax,yvmax);
		glVertex2f(xvmax,yvmin);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex2f(vx0,vy0);
		glVertex2f(vx1,vy1);
		glEnd();
	}	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
		glColor3f(1,0,0);
		glVertex2f(xmin,ymin);
		glVertex2f(xmin,ymax);
		glVertex2f(xmax,ymax);
		glVertex2f(xmax,ymin);
		glEnd();
		glBegin(GL_LINES);
		glColor3f(0,1,0);
		glVertex2f(60,20);
		glVertex2f(80,120);
		glEnd();
		cs(60,20,80,120);
		glFlush();
}

void myinit()
{
	glClearColor(1,1,1,1);
	glColor3f(1,0,0);
	glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,499,0,499);
}

void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("cs");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
