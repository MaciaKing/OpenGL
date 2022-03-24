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
bool izq=true;

// Funci�n que visualiza la escena OpenGL
void Display (void)
{
	glutSwapBuffers();
	// Borramos la escena
	glClear (GL_COLOR_BUFFER_BIT);

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

		//EJEMPLO 1,2
		//glRotatef (fAngulo, 0.0f, 0.0f, 1.0f);
		//FIN EJEMPLO 1,2

		//EJEMPLO 3
		//           EJES     X     Y      Z
		//glRotatef (0.0f, fAngulo, 0.0f, 1.0f);
		glRotatef (0.0f, fAngulo, 0.0f, 0.0f);
		//FIN EJEMPLO 3

		glBegin (GL_POLYGON);
			glColor3f (0.0f, 0.0f, 0.0f);
			//         X,    Y
			glVertex3f(-0.02f, 0.0f, 0.0f);
			glVertex3f(0.02f, 0.0f, 0.0f);
			glVertex3f(0.02f, 0.3f, 0.0f);
			glVertex3f(-0.02f, 0.3f, 0.0f);
		glEnd();

	glPopMatrix();
	glFlush();
}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle (void)
{
/*
//EJEMPLO 1
	if(fAngulo <90) {
		fAngulo += 1.0f;
	}else{
		//izq=false;
		fAngulo = -90.0f;
	}
// FIN EJEMPLO 1
*/

/*
//EJEMPLO 2
    if(izq){
		if(fAngulo <90) {
			fAngulo += 1.0f;
		}else{
			izq=false;			
		}
	}else{
		if(fAngulo == -90){
			izq=true;
		}else{
			fAngulo -= 1.0f;
		}
	}
// FIN EJEMPLO 2
*/

//EJEMPLO 3 --> descomentar también linea
	if(fAngulo < 90){
		fAngulo +=0.1f;
	}else{

	}
//FIN EJEMPLO 3
	
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
using namespace std;
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