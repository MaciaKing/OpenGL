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

// Funci�n que visualiza la escena OpenGL
void Display (void)
{
	glutSwapBuffers();
	// Borramos la escena
	glClear (GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		// Rotamos las proximas primitivas
		glRotatef (fAngulo, 0.0f, 0.0f, 1.0f);
		// Creamos a continuaci�n dibujamos los tres poligonos
		glBegin (GL_POLYGON);
			glColor3f (1.0f, 1.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glColor3f (0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);
			glColor3f (0.0f, 1.0f, 0.0f);
			glVertex3f(-0.5f, 0.866f, 0.0f);
		glEnd();

		glBegin (GL_POLYGON);
			glColor3f (1.0f, 1.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glColor3f (1.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);
			glColor3f (0.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, -0.866f, 0.0f);
		glEnd();

		glBegin (GL_POLYGON);
			glColor3f (1.0f, 1.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glColor3f (0.0f, 1.0f, 1.0f);
			glVertex3f(-0.5f, 0.866f, 0.0f);
			glColor3f (0.0f, 0.0f, 1.0f);
			glVertex3f(-0.5f, -0.866f, 0.0f);
		glEnd();
	glPopMatrix();
	
		/*Triangulo que no gira*/
		//glPushMatrix();
		glBegin (GL_POLYGON);
			glColor3f (0.0, 0.0, 0.0);
			glVertex3f(0.25,-0.25,-0.25);
			glVertex3f(0.25,0.25,-0.25);
			glVertex3f(-0.25,0.25,-0.25);		
		glEnd();
	//	glPopMatrix();
		/*FIN NO GIRAR*/

	
	glFlush();
	//reshapeScene(W_WIDTH,W_HEIGHT);
}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle (void)
{
	// Incrementamos el �ngulo
	fAngulo += 0.1f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360)
		fAngulo -= 360;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
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