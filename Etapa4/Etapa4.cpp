// Etapa1.cpp
// Fichero principal 
//g++ -o Etapa1 Etapa1.cpp -lGLU -lGL -lglut

////////////////////////////////////////////////////

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <cmath> 

const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;

/*GLfloat rotarEjeX=1.0f;
GLfloat rotarEjeY=1.0f;
GLfloat rotarEjeZ=0.0f;*/

GLfloat travellX=0.0f;
GLfloat travellY=0.0f;
GLfloat travellZ=0.0f;

GLfloat anguloRotacion=0.0f;

bool isRotar=false;
//Vector al que miramos (desde la camara)
float center[3]={2.0f,0.0f,0.0f};
float eye[3]={0.0f,1.0f,1.0f};
float vectorUnitario=0;

char tipoVision='l'; //p= paneo + tilt
                     //t= travelling/Dolly 
                     //l= movimiento libre de camara

// ----------------------------------------------------------
// Funciones 
// ----------------------------------------------------------
void Display(void);
void movementCamara(int key, int x, int y);
void Reescalar(int w, int h);
void Cubo();
void ejesEspaciales();
void Rectangulo();
void Esfera();
void cambiarMovimiento(int key);
void rotarCamara();
//void detectaTecla(int caracter, int x, int y);
void detectaTecla(unsigned char caracter, int x, int y);
void paneo(int key);   
void movimietoEnUnPunto(int key);
void movimientoCamaraLibre(int key);

void plano();
void calculaVectorUnitario();



// Funci�n que visualiza la escena OpenGL
void Display (void){
  //  Borrar pantalla y Z-buffer
  glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Resetear transformaciones
  glLoadIdentity();

  gluPerspective(90.0f,1.0f,0.0f,10.0f);
  if (tipoVision=='p'){//paneo
    gluLookAt(eye[0],eye[1],eye[2]  ,center[0],center[1],center[2],  0.0f,1.0f,0.0f);
  }else if(tipoVision=='t'){ //camara gira entorno 0,0,0
    calculaVectorUnitario();
    eye[0]=eye[0]*vectorUnitario;
    eye[1]=eye[1]*vectorUnitario;
    eye[2]=eye[2]*vectorUnitario;
    gluLookAt(eye[0],eye[1],eye[2]  ,center[0],center[1],center[2],  0.0f,1.0f,0.0f);
  }else if (tipoVision=='l'){//camara libre
    gluLookAt(eye[0],eye[1],eye[2]  ,center[0],center[1],center[2],  0.0f,1.0f,0.0f); 
  }
  
  ejesEspaciales();
  plano();
  glFlush();
  glutSwapBuffers();
}

void plano(){
 //  glRectf(-0.2f, 0.0f, 0.2f, 0.5f);
 glTranslatef(0.0f,0.0f,0.0f);
 glColor3f(   1.0,  0.0, 0.0 );
 glBegin(GL_POLYGON);
  glVertex3f(  0.0,  0.0, 0.0 );
  glVertex3f(  3.0,  0.0, 0.0 );
  glVertex3f(  3.0,  0.0, 3.0 );
  glVertex3f(  0.0,  0.0, 3.0 );
 glEnd();
}

/*
ejesEspaciales: Dibujamos los ejes espaciales.
 El eje y es de color verde
 El eje x es de color rojo
 El eje z es de colo azul
*/
void ejesEspaciales(){   
  /*Eje z*/
  glPushMatrix();
     // NO rotamos porque ya esta en el eje
     glColor3f(0,0,1);  
     GLUquadric *quad3;
     quad3 = gluNewQuadric();
     gluCylinder(quad3,0.01f,0.01f,0.8f,32,20);
     //Dibujamos el cono de arriba
     glPushMatrix();
        glTranslatef(0.0f,0.0f,0.8f);
        glutSolidCone(0.05f,0.1f,32,20);
     glPopMatrix();
  glPopMatrix();

   /* Eje y*/
glPushMatrix();   
   glRotatef(-90.0f,1.0f,0.0f,0.0f);
   glColor3f(0,1,0);
   GLUquadric *quad1;
   quad1 = gluNewQuadric();
   gluCylinder(quad1,0.01f,0.01f,0.8f,32,20);
   //Dibujamos el cono de arriba
   glPushMatrix();
      glTranslatef(0.0f,0.0f,0.8f);
      glutSolidCone(0.05f,0.1f,32,20);
   glPopMatrix();
glPopMatrix();

   /*Eje x*/
glPushMatrix(); 
   glRotatef(90.0f,0.0f,1.0f,0.0f); 
   glColor3f(1,0,0);  
   GLUquadric *quad2;
   quad2 = gluNewQuadric();
   gluCylinder(quad2,0.01f,0.01f,0.8f,32,20);   
   //Dibujamos el cono de arriba
   glPushMatrix();
      glTranslatef(0.0f,0.0f,0.8f);
      glutSolidCone(0.05f,0.1f,32,20);
   glPopMatrix();
glPopMatrix();
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

/*
movementCamara -> 
*/
void movementCamara(int key, int x, int y){
  switch (tipoVision){
  case 'p':
    paneo(key);
    break;

  case 't':
   movimietoEnUnPunto(key);
    break;

   case 'l':
   movimientoCamaraLibre(key);
   break;

  default:
    //no hagas nada
    break;
  }
 
}

void calculaVectorUnitario(){
  // float unitario= sqrt(paneoEjeX+paneoEjeY+paneoEjeZ);
   //vectorUnitario=sqrt(paneoEjeX+paneoEjeY+paneoEjeZ);;
  vectorUnitario=sqrt(center[0]+center[1]+center[2]);;

}

/*
Movimiento de la camara en entorno al 
punto 0,0,0
*/
void movimietoEnUnPunto(int key){
    if (key == GLUT_KEY_UP){
      eye[1] +=0.1f;
      }

    else if (key == GLUT_KEY_DOWN){
      eye[1] -=0.1f;
      }

    else if (key == GLUT_KEY_LEFT){
      eye[2] += 0.1f;  
      }

    else if (key == GLUT_KEY_RIGHT){
      eye[2] -= 0.1f;
      }
  glutPostRedisplay();//  Solicitar actualización de visualización 
}

/*
paneo + tilt --> movimiento del ojo
  gluLookAt(vector[0],vector[1],vector[2]  ,paneoEjeX,paneoEjeY,paneoEjeZ,  0.0f,1.0f,0.0f);
*/
void paneo(int key){      
    if (key == GLUT_KEY_UP)
      //paneoEjeY +=0.1f;
      center[1] +=0.1f;

    else if (key == GLUT_KEY_DOWN)
     // paneoEjeY -=0.1f;
     center[1]-=0.1f;

    else if (key == GLUT_KEY_LEFT)
     // paneoEjeZ += 0.1f;  
     center[2]+= 0.1f;  

    else if (key == GLUT_KEY_RIGHT)
     // paneoEjeZ -= 0.1f;
     center[2]-= 0.1f;

  glutPostRedisplay();//  Solicitar actualización de visualización  
}

void movimientoCamaraLibre(int key){   
  if (key == GLUT_KEY_UP){
    eye[0]+=0.1f;
    center[0]+=0.1f;
  }    
  else if(key == GLUT_KEY_DOWN){
    eye[0]-=0.1f;
    center[0]-=0.1f;
  }    
  else if(key == GLUT_KEY_LEFT){
     eye[2]-=0.1f;
    center[2]-=0.1f;
  }   
  else if(key ==GLUT_KEY_RIGHT){
     eye[2]+=0.1f;
    center[2]+=0.1f;
  }
   
  glutPostRedisplay();//  Solicitar actualización de visualización  
}

void detectaTecla(unsigned char caracter, int x, int y){

  if(caracter == 'p'){
    tipoVision='p';
  }else if(caracter == 't'){
    tipoVision='t';
  }else if(caracter=='l'){
    tipoVision='l';
  }
  printf("tipoVISION : %c\n",tipoVision);
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
  glutCreateWindow("Movimiento camara");

  //  Habilitar la prueba de profundidad de Z-buffer
  glEnable(GL_DEPTH_TEST);

  // Funciones de retrollamada
  glutDisplayFunc(Display);
  //glutSpecialFunc(specialKeys);
  glutKeyboardFunc(detectaTecla);
  glutSpecialFunc(movementCamara);  
  glutReshapeFunc(Reescalar); 

  //  Pasar el control de eventos a GLUT
  glutMainLoop();
 
  //  Regresar al sistema operativo
  return 0;
 
}