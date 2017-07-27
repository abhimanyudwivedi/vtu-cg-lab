#include<stdio.h>
#include<GL/glut.h>

void draw(float x,float y)
{
	glColor3f(0,1,0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void edge(float x1,float y1,float x2,float y2,int *le,int *re)
{
	float mx,x,temp;
	int i;
	if((y2-y1)<0)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if((y2-y1)!=0)
		mx = (x2 - x1)/(y2 - y1);
	else
		mx = x2 - x1;
		
	x = x1;
	for(i=y1;i<=y2;i++)
	{
		if(x < (float)le[i])
			le[i] = (int)x;
		if(x > (float)re[i])
			re[i] = (int)x;
		x += mx;
	}
}

void scan(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
	int le[500],re[500];
	int i,j;
	for(i=0;i<500;i++)
	{
		le[i] = 500;
		re[i] = 0;
	}
	edge(x1,y1,x2,y2,le,re);
	edge(x2,y2,x3,y3,le,re);
	edge(x3,y3,x4,y4,le,re);
	edge(x4,y4,x1,y1,le,re);
	for(j=0;j<500;j++)
	{
		if(le[j] < re[j])
			for(i = le[j];i <= re[j];i++)
				draw(i,j);
	}
}

void display()
{
	float x1=200,y1=200,x2=500,y2=300,x3=200,y3=400,x4=300,y4=300;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);
	glEnd();
	scan(x1,y1,x2,y2,x3,y3,x4,y4);
	glFlush();	
}

void myinit()
{
	glClearColor(1,1,1,1);
	glColor3f(1,0,0);
	glPointSize(2);
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
	glutCreateWindow("scanfill");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
