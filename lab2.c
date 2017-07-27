#include<GL/glut.h>
#include<stdio.h>

double xmin=50,xmax=100,ymin=50,ymax=100;
double xvmin=200,xvmax=300,yvmin=200,yvmax=300;

int cliptest(double p,double q,double *t1,double *t2)
{
	double t=q/p;
	if(p<0)
	{
		if(t > *t1)
			*t1 = t;
		if(t > *t2)
			return 0;
	}
	if(p>0)
	{
		if(t < *t2) *t2 = t;
		if(t < *t1)
			return 0;
	}
	if(p==0)
		if(q<0)
			return 0;
	return 1;
}

void libar(double x0,double y0,double x1,double y1)
{
	double dx = x1 - x0,dy = y1 - y0,te = 0,tl = 1;
	if(cliptest(-dx,x0-xmin,&te,&tl))
		if(cliptest(dx,xmax-x0,&te,&tl))
			if(cliptest(-dy,y0-ymin,&te,&tl))
				if(cliptest(dy,ymax-y0,&te,&tl))
					{
						if(tl < 1)
						{
							x1 = x0 + dx * tl;
							y1 = y0 + dy * tl;
						}
						if(te > 0)
						{
							x0 = x0 + dx * te;
							y0 = y0 + dy * te;
						}
						double sx = (xvmax - xvmin)/(xmax - xmin);
						double sy = (yvmax - yvmin)/(ymax - ymin);
						double vx0 = xvmin + (x0 - xmin) * sx;
						double vy0 = yvmin + (y0 - ymin) * sy;
						double vx1 = xvmin + (x1 - xmin) * sx;
						double vy1 = yvmin + (y1 - ymin) * sy;
						glColor3f(1,0,0);
						glBegin(GL_LINE_LOOP);
						glVertex2f(xvmin,yvmin);
						glVertex2f(xvmin,yvmax);
						glVertex2f(xvmax,yvmax);
						glVertex2f(xvmax,yvmin);
						glEnd();
						glColor3f(0,1,0);
						glBegin(GL_LINES);
						glVertex2f(vx0,vy0);
						glVertex2f(vx1,vy1);
						glEnd();
					}
}

void display()
{
	double x0=60,x1=80,y0=20,y1=120;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmin,ymax);
	glVertex2f(xmax,ymax);
	glVertex2f(xmax,ymin);
	glEnd();
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glEnd();
	libar(x0,y0,x1,y1);
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
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Liang Barsky");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
