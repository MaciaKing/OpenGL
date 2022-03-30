// Etapa1.cpp
// Fichero principal 
//g++ -o Etapa1 Etapa1.cpp -lGLU -lGL -lglut

////////////////////////////////////////////////////
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;
GLfloat rotate_x=0.0f;
GLfloat rotate_y=0.0f;

// ----------------------------------------------------------
// Funciones 
// ----------------------------------------------------------
void Display(void);
void specialKeys();
void ejesEspaciales();
void Reescalar(int w, int h);
void Cubo();
void Rectangulo();
void Esfera();

// Funci�n que visualiza la escena OpenGL
void Display (void){  
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//  Borrar pantalla y Z-buffer
  // Resetear transformaciones
  glLoadIdentity();
  // Rotar cuando el usuario cambie “rotate_x” y “rotate_y”
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );

  //Cubo();
 // Rectangulo();
 // Esfera();
  ejesEspaciales();
  glFlush();
  glutSwapBuffers();
}

void ejesEspaciales(){   
  /*Eje z*/
glPushMatrix();
   // NO rotamos porque ya esta en el eje
   glColor3f(0,0,1);  
   GLUquadric *quad3;
   quad3 = gluNewQuadric();
   gluCylinder(quad3,0.01f,0.01f,0.8f,32,20);
 glPopMatrix();

   /* Eje y*/
glPushMatrix();   
   glRotatef(-90.0f,1.0f,0.0f,0.0f);
   glColor3f(0,1,0);
   GLUquadric *quad1;
   quad1 = gluNewQuadric();
   gluCylinder(quad1,0.01f,0.01f,0.8f,32,20);
 glPopMatrix();

   /*Eje x*/
glPushMatrix(); 
   glRotatef(90.0f,0.0f,1.0f,0.0f); 
   glColor3f(1,0,0);  
   GLUquadric *quad2;
   quad2 = gluNewQuadric();
   gluCylinder(quad2,0.01f,0.01f,0.8f,32,20);   
 glPopMatrix();
}

void Esfera(){
	glColor3f(1,0,0);
	GLUquadric *quad;
	quad = gluNewQuadric();
	gluSphere(quad,0.1f,100,20);
}

void Cubo(){
  //LADO FRONTAL: lado multicolor
  glBegin(GL_POLYGON);
 
  glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 es rojo
  glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 es verde
  glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 es azul
  glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 es morado
 
  glEnd();

  // LADO TRASERO: lado blanco
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  0.5, -0.5, 0.5 );
  glVertex3f(  0.5,  0.5, 0.5 );
  glVertex3f( -0.5,  0.5, 0.5 );
  glVertex3f( -0.5, -0.5, 0.5 );
  glEnd();
 
  // LADO DERECHO: lado morado
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.0,  1.0 );
  glVertex3f( 0.5, -0.5, -0.5 );
  glVertex3f( 0.5,  0.5, -0.5 );
  glVertex3f( 0.5,  0.5,  0.5 );
  glVertex3f( 0.5, -0.5,  0.5 );
  glEnd();
 
  // LADO IZQUIERDO: lado verde
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
 
  // LADO SUPERIOR: lado azul
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  0.5,  0.5,  0.5 );
  glVertex3f(  0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glEnd();
 
  // LADO INFERIOR: lado rojo
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  0.5, -0.5, -0.5 );
  glVertex3f(  0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
}


void Rectangulo(){
//LADO FRONTAL: lado multicolor
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  0.5, -0.5, 0.7 );
  glVertex3f(  0.5,  0.5, 0.7 );
  glVertex3f( -0.5,  0.5, 0.7 );
  glVertex3f( -0.5, -0.5, 0.7 );
  glEnd();

  // LADO TRASERO: lado blanco
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  0.5, -0.5, 0.7 );
  glVertex3f(  0.5,  0.5, 0.7 );
  glVertex3f( -0.5,  0.5, 0.7 );
  glVertex3f( -0.5, -0.5, 0.7 );
  glEnd();
 
  // LADO DERECHO: lado morado
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.0,  1.0 );
  glVertex3f( 0.5, -0.5, -0.7 );
  glVertex3f( 0.5,  0.5, -0.7 );
  glVertex3f( 0.5,  0.5,  0.7 );
  glVertex3f( 0.5, -0.5,  0.7 );
  glEnd();
 
  // LADO IZQUIERDO: lado verde
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -0.5, -0.5,  0.7 );
  glVertex3f( -0.5,  0.5,  0.7 );
  glVertex3f( -0.5,  0.5, -0.7 );
  glVertex3f( -0.5, -0.5, -0.7 );
  glEnd();
 
  // LADO SUPERIOR: lado azul
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  0.5,  0.5,  0.7 );
  glVertex3f(  0.5,  0.5, -0.7 );
  glVertex3f( -0.5,  0.5, -0.7 );
  glVertex3f( -0.5,  0.5,  0.7 );
  glEnd();
 
  // LADO INFERIOR: lado rojo
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  0.5, -0.5, -0.7 );
  glVertex3f(  0.5, -0.5,  0.7 );
  glVertex3f( -0.5, -0.5,  0.7 );
  glVertex3f( -0.5, -0.5, -0.7 );
  glEnd();
}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle (void){

	glutPostRedisplay();// Indicamos que es necesario repintar la pantalla
}

// ----------------------------------------------------------
// Función que reescala todos los elementos de la pantalla.
// Podemos deformar la ventana, que nuestros objetos no se deformaran.
// ----------------------------------------------------------
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

// ----------------------------------------------------------
// Función de retrollamada “specialKeys()” 
// ----------------------------------------------------------
void specialKeys( int key, int x, int y ) { 
  //  Flecha derecha: aumentar rotación 5 grados
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;
 
  //  Flecha izquierda: disminuir rotación 5 grados
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 5;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;
  
  glutPostRedisplay();//  Solicitar actualización de visualización
}

// ----------------------------------------------------------
// Función “main()”
// ----------------------------------------------------------
int main(int argc, char* argv[]){ 
  //  Inicializar los parámetros GLUT y de usuario proceso
  glutInit(&argc,argv);

  //  Solicitar ventana con color real y doble buffer con Z-buffer 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  // Crear ventana
  glutCreateWindow("Cubo");

  //  Habilitar la prueba de profundidad de Z-buffer
  glEnable(GL_DEPTH_TEST);

  // Funciones de retrollamada
  glutDisplayFunc(Display);
  glutSpecialFunc(specialKeys);
  glutReshapeFunc(Reescalar); 

  //  Pasar el control de eventos a GLUT
  glutMainLoop();
 
  //  Regresar al sistema operativo
  return 0;
 
}