// Etapa1.cpp
// Fichero principal 
//g++ -o Etapa1 Etapa1.cpp -lGLU -lGL -lglut

////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes. 
GLfloat posX; // Indica la posicion en el eje X
// Ejes de rotacion
GLfloat xRot=0;
GLfloat yRot=0;
GLfloat zRot=0;
bool izq=true;
bool segueix=true;

void pendulo1();
void Display (void);
void Idle (void);
void Reescalar(int w, int h);

// Funci�n que visualiza la escena OpenGL
void Display (void){
	glutSwapBuffers();	
	glClear (GL_COLOR_BUFFER_BIT);// Borramos la escena

	glPushMatrix();
	// Rectangulo Base
		glBegin (GL_POLYGON);
			glColor3f (0.0f, 0.0f, 0.0f);
			//         X,    Y
			glVertex3f(-0.2f, 0.0f, 0.0f);
			glVertex3f(0.2f, 0.0f, 0.0f);
			glVertex3f(0.2f, -0.05f, 0.0f);
			glVertex3f(-0.2f, -0.05f, 0.0f);
		glEnd();

	//Primer brazo
		glRotatef (fAngulo, 0.0f, 0.0f, 1.0f);
		glBegin (GL_POLYGON);
			glColor3f (1.0f, 0.1f, 0.1f);
			//         X,    Y
			glVertex3f(-0.02f, -0.02f, 0.0f);
			glVertex3f(0.02f, -0.02f, 0.0f);
			glVertex3f(0.02f, 0.3f, 0.0f);
			glVertex3f(-0.02f, 0.3f, 0.0f);
		glEnd();
		
		glPushMatrix();
	//Segundo brazo
		glTranslatef(0.0f,0.3f,0.0f);
		glRotatef (fAngulo, 0.0f, 0.0f, 1.0f);		
		glBegin (GL_POLYGON);
			glColor3f (0.0f, 0.1f, 1.f);
			//         X,    Y
			glVertex3f(-0.01f, -0.02f, 0.0f);
			glVertex3f(0.01f, -0.02f, 0.0f);
			glVertex3f(0.01f, 0.3f, 0.0f);
			glVertex3f(-0.01f, 0.3f, 0.0f);
		glEnd();	
		glPopMatrix();

	glPopMatrix();
	glFlush();
}

/*
pendulo1
	Movemos el rectangulo a la izquierda
	y a la derecha como un pendulo
*/
void pendulo1(){
    if(izq){
		if(fAngulo <70) {
			fAngulo += 1.0f;
		}else{
			izq=false;			
		}
	}else{
		if(fAngulo == -70){
			izq=true;
		}else{
			fAngulo -= 1.0f;
		}
	}
}




// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle (void){
	pendulo1();
	glutPostRedisplay();// Indicamos que es necesario repintar la pantalla
}


void Reescalar(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.0, 1.0, -1.0 * h / w, 1.0 * h / w, -1.0, 1.0);
    else
        glOrtho(-1.0 * w / h,
            1.0 * w / h, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                             // Activar las modificaciones en el modelo
    glutPostRedisplay();
}


// Funci�n principal
int main(int argc, char **argv) 
{
	fAngulo=0;
	// Inicializamos la librer�a GLUT
	glutInit (&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition (100,100);
	glutInitWindowSize (W_WIDTH, W_HEIGHT);
	//glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE);
	

	// Creamos la nueva ventana
	glutCreateWindow ("Mi primera Ventana");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho (-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
    glutReshapeFunc(Reescalar);  

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0; 
}