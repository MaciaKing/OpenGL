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

/*paraEjemplo12
	Movemos el rectangula a partir de una "base"
*/
void paraEjemplo12(){
		//EJEMPLO 1,2
		glRotatef (fAngulo, 0.0f, 0.0f, 1.0f);
		//FIN EJEMPLO 1,2
		glBegin (GL_POLYGON);
			glColor3f (0.0f, 0.0f, 0.0f);
			glVertex3f(-0.02f, 0.0f, 0.0f);
			glVertex3f(0.02f, 0.0f, 0.0f);
			glVertex3f(0.02f, 0.3f, 0.0f);
			glVertex3f(-0.02f, 0.3f, 0.0f);
		glEnd();
		glFlush();
}

/*paraEjemplo3
	Para mover este rectangulo en el eje X
*/
void paraEjemplo3(){
	glPushMatrix();
	glTranslatef(posX, 0.0f, 0.0f),
	glBegin (GL_POLYGON);
		glColor3f (0.0f, 0.0f, 0.0f);
		glVertex3f(-0.02f, 0.0f, 0.0f);
		glVertex3f(0.02f, 0.0f, 0.0f);
		glVertex3f(0.02f, 0.3f, 0.0f);
		glVertex3f(-0.02f, 0.3f, 0.0f);
	glEnd();
	glPopMatrix();
}


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

	paraEjemplo12();
	//paraEjemplo3();
	glPopMatrix();
	glFlush();
}

/*ejemplo1
	Movemos el rectangulo a x angulos
*/
void ejemplo1(){
	if(fAngulo <90) {
		fAngulo += 1.0f;
	}else{
		//izq=false;
		fAngulo = -90.0f;
	}	
}

/*ejemplo2
	Movemos el rectangulo a la izquierda
	y a la derecha como un pendulo
*/
void ejemplo2(){
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
}

/*ejemplo2
	Movemos el rectangulo a la izquierda
	y a la derecha. Desplazando TODO el objeto
*/
void ejemplo3(){
	if(posX<0.2 && segueix){
       posX+=0.01f;
	}else{
		segueix=false;
		posX-=0.01f;
		if(posX<=-0.2){ //Si llega al maximo permitido
			segueix=true;
		}
	}
}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle (void){
	//ejemplo1();
	ejemplo2();
	//ejemplo3();
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