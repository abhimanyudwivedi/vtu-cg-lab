#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

typedef float point[3];

point v[] = {{0,0,1},{0,0.942809,-0.33333},{-0.816496,-0.471404,-0.33333},{0.816496,-0.471404,-0.33333}};

int n;

void triangle(point a,point b,point c)
{
	glBegin(GL_TRIANGLES);
	glNormal3fv(a);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();
}

void div_tri(point a,point b,point c,int m)
{
	point v1,v2,v3;
	int j;
	if(m>0)
	{
		for(j=0;j<3;j++) v1[j] = (a[j]+b[j])/2;
		for(j=0;j<3;j++) v2[j] = (a[j]+c[j])/2;
		for(j=0;j<3;j++) v3[j] = (b[j]+c[j])/2;
		div_tri(a,v1,v2,m-1);
		div_tri(b,v1,v3,m-1);
		div_tri(c,v2,v3,m-1);
	}
	else
	{
		triangle(a,b,c);
	}
	
}

void tetrahedron(int m)
{
	glColor3f(0,0,1);
	div_tri(v[3],v[1],v[2],m);
	
	glColor3f(1,0,0);
	div_tri(v[0],v[1],v[2],m);
		
	glColor3f(0,1,0);
	div_tri(v[0],v[1],v[3],m);
	
	glColor3f(0,0,0);
	div_tri(v[0],v[2],v[3],m);
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	tetrahedron(n);
	glFlush();
	glutSwapBuffers();
}

void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
	{
		glOrtho(-2,2,-2 * (GLfloat) h/(GLfloat) w,2 * (GLfloat) h/(GLfloat) w,-10,10);
	}
	else
		glOrtho(-2 * (GLfloat) w/(GLfloat) h,2 * (GLfloat) w/(GLfloat) h,-2,2,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void main(int argc,char **argv)
{
	printf("enter n");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("sierpinski");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1,1,1,1);
	glutMainLoop();
}1
