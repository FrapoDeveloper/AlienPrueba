#include <gl/glut.h>
/*AUTOR: FRAN ESPINO MOSTACERO*/
#include<stdio.h>


//globals

GLuint cabeza;


float elephantrot1;
char ch='1';

float angX = 0;
float angY = 0;
float angZ = 0;

//other functions and main

//.obj loader code begins



void graficarEjes()
{
    glColor3f(0,0,0);
    glBegin(GL_LINES);

        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(50,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,50,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,50);
    glEnd();
}




void loadObj1(char *fname)
{
FILE *fp;
int read;
GLfloat x, y, z;
char ch;
cabeza=glGenLists(1);
fp=fopen(fname,"r");
glPointSize(2);
if (!fp)
    {
        printf("can't open file %s\n", fname);
	  exit(1);
    }

glNewList(cabeza, GL_COMPILE);
{
glPushMatrix();
glBegin(GL_POINTS);


    while(!(feof(fp)))
     {

      read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
      if(read==4&&ch=='v')
      {
       glVertex3f(x,y,z);
      }
     }
    glEnd();
    }

glPopMatrix();
glEndList();
fclose(fp);
}



void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	//glOrtho(-25,25,-2,2,0.1,100);
	glMatrixMode(GL_MODELVIEW);
}

void drawCar1()
{

 	glPushMatrix();

    glColor3f( 0.796 , 0.443 , 0.298 );

 	glScalef(0.3,0.3,0.3);
 	glRotated(-45,1,1,0);
    glRotated(-90,1,0,0);
    glRotated(40,0,1,0);
    glRotated(angX,0,0,-1);


 	glCallList(cabeza);

 	glPopMatrix();

 	//elephantrot=elephantrot+0.6;
 	//if(elephantrot>360)elephantrot=elephantrot-360;
}



void display(void)
{
   	glClearColor (0.0,0.0,0.0,1.0);
   	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   	glLoadIdentity();
   	gluLookAt(60,20,60,0,0,0,0,1,0);

    graficarEjes();
       	drawCar1();



   	glutSwapBuffers(); //swap the buffers

}

void manejarTeclado(unsigned char key,int x, int y)
{
    switch(key)
    {

         case 'a':  angX =angX - 10;
                    break;
       case 'd':  angX =angX + 10;
                    break;


    }
    glutPostRedisplay();
}
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1000,700);
	glutInitWindowPosition(20,20);
	glutCreateWindow("ObjLoader");
	glutReshapeFunc(reshape);
	glutKeyboardFunc(manejarTeclado);//TECLADO
        glutDisplayFunc(display);
	glutIdleFunc(display);
        loadObj1("data/alien.obj");//replace porsche.obj with radar.obj or any other .obj to display it
glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glutMainLoop();

    return 0;
}
