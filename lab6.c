#include<stdio.h>
#include<GL/glut.h>

void draw_point(GLint x,GLint y)
{
	glBegin(GL_POINTS);
	glColor3f(1,0,0);
	glVertex2f(x,y);
	glEnd();
}

void plot(GLint h,GLint k,GLint x,GLint y)
{
	draw_point(x+h,y+k);
	draw_point(-x+h,y+k);
	draw_point(x+h,-y+k);
	draw_point(-x+h,-y+k);
	draw_point(y+h,x+k);
	draw_point(-y+h,x+k);
	draw_point(y+h,-x+k);
	draw_point(-y+h,-x+k);
}

void cdraw(GLint h,GLint k,GLint r)
{
	GLint d = 1 - r,y = r,x = 0;
	while(y>x)
	{	plot(h,k,x,y);
		if(d<0)
		{
			d += 2 * x + 3;
		}
		else
		{
			d += 2 * (x-y) + 5;
			--y;
		}
		++x;
	}
	plot(h,k,x,y);
}

void circle()
{
	GLint x = 100,y = 100, r = 50;
	int i,n=50;
	for(i=0;i<n;i+=3)
	cdraw(x,y+i,r);
}

void parallelopiped(GLint xo,GLint yo,GLint x1,GLint y1,GLint x2,GLint y2,GLint x3,GLint y3)
{
	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xo,yo);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glEnd();
}

void plpr()
{
	GLint xo = 200,yo = 100,x1 = 200,y1=175,x2=300,y2=225,x3 = 300,y3 = 150;
	int i;
	for(i=0;i<50;i += 2 )
	{
		parallelopiped(xo+i,yo+i,x1+i,y1+i,x2+i,y2+i,x3+i,y3+i);
	}
}

void myinit()
{
	glClearColor(1,1,1,1);
	glColor3f(1,0,0);
	glPointSize(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,499,0,499);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	circle();
	plpr();
	glFlush();
}

void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("cylinder");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
