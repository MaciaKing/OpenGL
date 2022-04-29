/*
Fer pull i me dona igual cambis en local
git fetch
git reset
git merge origin
*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;

GLfloat rotarEjeX=1.0f;
GLfloat rotarEjeY=1.0f;
GLfloat rotarEjeZ=-1.0f;

GLfloat aux=0.0f;

bool isRotar=false;
char movimiento='m'; //m= movimiento de la lampara
bool anguloX=true;
bool anguloY=false;

struct movimientoL{
  bool movAnguloX=true; // si es true mueve eje x, si es false eje y
  //char signo='+';  // puede ser + o -
  GLfloat rotarX=0.0f;
  GLfloat rotarY=0.0f;
};

struct movimientoL m;
GLfloat anguloBrazoAereo=0.0f;

// ----------------------------------------------------------
// Funciones 
// ----------------------------------------------------------
void Display(void);
void movementCamara(int key);
void Reescalar(int w, int h);
void Cubo();
void ejesEspaciales();
void Rectangulo();
void Esfera();
void plano();
void cambiarMovimiento(int key);
void lampara();
void rotar();
void moverBrazoAereo();
void moverLampara();
void detectaTecla(unsigned char caracter, int x, int y);
void movimientoLampara(int key,int x,int y);


// Funci�n que visualiza la escena OpenGL
void Display (void){
  //  Borrar pantalla y Z-buffer
  glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Resetear transformaciones
  glLoadIdentity();
  //glTranslatef(aux,0.0f,0.0f);
  
  
  //glRotatef(aux,0.0f,1.0f,0.0f);
  //rotar();
 // gluLookAt(0.0f,0.0f,-0.5f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f); //mirada al centro de la lampara
 // gluLookAt(0.6f,0.0f,-0.5f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f); //mirada desde un lado
   gluLookAt(0.5f,0.0f,0.0f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f);

 /* gluPerspective(90.0f,1.0f,0.0f,10.0f);
  //gluLookAt(1.0f,-1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f); //define una transformacion visual
  //gluLookAt(rotateEjeX,rotateEjeY,rotateEjeZ,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f);
  //gluLookAt(rotateEjeX,rotateEjeY,rotateEjeZ,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
  gluLookAt(0.0f,1.0f,rotarEjeZ,paneoEjeX,paneoEjeY,0.0f,0.0f,1.0f,0.0f);
*/
  //ejesEspaciales();
 // plano();
  lampara();
  glFlush();
  glutSwapBuffers();
}

void rotar(){
  aux+=0.5f;
  glRotatef(aux,0.0f,1.0f,0.0f);
  //glRotatef(aux,1.0f,0.0f,0.0f);
  glutPostRedisplay();//  Solicitar actualización de visualización

}

void plano(){
  // glRectf(-0.2f, 0.0f, 0.2f, 0.5f);
 glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  0.0,  0.0, 0.0 );
  glVertex3f(  1.5,  0.0, 0.0 );
  glVertex3f(  1.5,  0.0, 1.0 );
  glVertex3f(  0.0,  0.0, 1.0 );
 glEnd();
}

void lampara(){
  //Base Lampara
  glPushMatrix();
  glRotatef(-90.0f,1.0f,0.0f,0.0f); 
  glColor3f(1,0,0);
  glutSolidCone(0.1f,0.1f,32,20);
   glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glTranslatef(0.0f,0.0f,-0.05f);
    GLUquadric *quad;
    quad = gluNewQuadric();
    gluCylinder(quad,0.1,0.1,0.05,25,25);
   glPopMatrix();
  glPopMatrix();
  //Fin Base Lampara

//DOS BRAZOS
for(int i=0; i<=2;i=i+1){
  glPushMatrix();
  if(i==2){ //Movemos la segunda Pierna     
      glTranslatef(-0.05f,0.0f,0.0f); 
      glColor3f(   0.0f,  0.0f, 1.0f );
  }else glColor3f(   0.0f,  1.0f, 0.0f );
  glBegin(GL_POLYGON);
    //glColor3f(   0.0,  1.0, 1.0 );
    //Cara Un costat
    glVertex3f(  0.0f, 0.0f, 0.0f );
    glVertex3f(  0.03f, 0.0f, 0.0f );         
    glVertex3f(  0.03f, 0.3f, 0.0f );     
    glVertex3f(  0.0f, 0.3f, 0.0f ); 

    //Cara Un costat
    //glColor3f(1,0,0);
    glVertex3f(  0.03f, 0.0f, 0.0f );
    glVertex3f(  0.03f, 0.0f, 0.03f );         
    glVertex3f(  0.03f, 0.3f, 0.03f );     
    glVertex3f(  0.03f, 0.3f, 0.0f ); 

    //Cara Un costat
   //glColor3f(0,1,0);
    glVertex3f(  0.03f, 0.0f, 0.03f );
    glVertex3f(  0.03f, 0.3f, 0.03f );         
    glVertex3f(  0.0f, 0.3f, 0.03f );     
    glVertex3f(  0.0f, 0.0f, 0.03f ); 

    //Cara Un costat
    //glColor3f(0,0,1);
    glVertex3f(  0.0f, 0.3f, 0.03f );
    glVertex3f(  0.0f, 0.0f, 0.03f );         
    glVertex3f(  0.0f, 0.0f, 0.0f );     
    glVertex3f(  0.0f, 0.3f, 0.0f ); 
  glEnd();
  glPopMatrix();
  //FIN DOS BRAZOS
  }
 
 //BASE AEREA
 glPushMatrix();
 glTranslatef(0.0f,0.0f,-0.05f);//Lo movemos en el cetro de las dos columnas
 glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0, 1.0 );
    //BASE
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(  -0.1f, 0.3f, 0.0f );
    glVertex3f(  0.1f, 0.3f, 0.0f );         
    glVertex3f(  0.1f, 0.3f, 0.1f );     
    glVertex3f(  -0.1f, 0.3f, 0.1f ); 
glEnd();
glBegin(GL_POLYGON);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(  -0.1f, 0.3f, 0.1f ); 
    glVertex3f(  -0.1f, 0.35f, 0.1f );
    glVertex3f(   0.1f, 0.35f, 0.1f ); 
    glVertex3f(   0.1f, 0.3f, 0.1f ); 
glEnd();

glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(  0.1f, 0.35f, 0.1f ); 
    glVertex3f(  0.1f, 0.3f, 0.1f );
    glVertex3f(  0.1f, 0.3f, 0.0f ); 
    glVertex3f(  0.1f, 0.3f, 0.0f  ); 
glEnd();

glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(  0.1f, 0.35f, 0.1f ); 
    glVertex3f(  0.1f, 0.3f, 0.1f );
    glVertex3f(  0.1f, 0.3f, 0.0f ); 
    glVertex3f(  0.1f, 0.35f, 0.0f  ); 
glEnd();

glBegin(GL_POLYGON);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(  0.1f, 0.3f, 0.0f ); 
    glVertex3f(  0.1f, 0.35f, 0.0f );
    glVertex3f(  -0.1f, 0.35f, 0.0f ); 
    glVertex3f(  -0.1f, 0.3f, 0.0f  ); 
glEnd();

glBegin(GL_POLYGON);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(  0.1f, 0.3f, 0.0f ); 
    glVertex3f(  0.1f, 0.35f, 0.0f );
    glVertex3f(  -0.1f, 0.35f, 0.0f ); 
    glVertex3f(  -0.1f, 0.3f, 0.0f  ); 
glEnd();

glBegin(GL_POLYGON);
    glColor3f(0.0f,1.0f,1.0f);
    glVertex3f(  -0.1f, 0.35f, 0.0f ); 
    glVertex3f(  -0.1f, 0.3f, 0.0f );
    glVertex3f(  -0.1f, 0.3f, 0.1f ); 
    glVertex3f(  -0.1f, 0.35f, 0.1f  ); 
glEnd();
    
glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 0.0 );
    //BASE
    glVertex3f(  -0.1f, 0.35f, 0.0f );
    glVertex3f(  0.1f, 0.35f, 0.0f );         
    glVertex3f(  0.1f, 0.35f, 0.1f );     
    glVertex3f(  -0.1f, 0.35f, 0.1f ); 
glEnd();
glPopMatrix();
 //FIN BASE AEREA

glRotatef (anguloBrazoAereo, 1.0f, 0.0f, 0.0f);	///////////////////
//BRAZO AEREO
 glPushMatrix();
 //glTranslatef(-0.01f,0.45f,0.02f);
  glTranslatef(-0.01f,0.35f,0.02f);

glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0, 1.0 );
    //Cara Un costat
    glVertex3f(  0.0f, 0.0f, 0.0f );
    glVertex3f(  0.03f, 0.0f, 0.0f );         
    glVertex3f(  0.03f, 0.3f, 0.0f );     
    glVertex3f(  0.0f, 0.3f, 0.0f ); 
glEnd();
glBegin(GL_POLYGON);
    //glColor3f(1,0,0);
    glVertex3f(  0.03f, 0.0f, 0.0f );
    glVertex3f(  0.03f, 0.0f, 0.03f );         
    glVertex3f(  0.03f, 0.3f, 0.03f );     
    glVertex3f(  0.03f, 0.3f, 0.0f ); 
glEnd();
glBegin(GL_POLYGON);
   //glColor3f(0,1,0);
    glVertex3f(  0.03f, 0.0f, 0.03f );
    glVertex3f(  0.03f, 0.3f, 0.03f );         
    glVertex3f(  0.0f, 0.3f, 0.03f );     
    glVertex3f(  0.0f, 0.0f, 0.03f ); 
glEnd();    
glBegin(GL_POLYGON);
    glVertex3f(  0.0f, 0.3f, 0.03f );
    glVertex3f(  0.0f, 0.0f, 0.03f );         
    glVertex3f(  0.0f, 0.0f, 0.0f );     
    glVertex3f(  0.0f, 0.3f, 0.0f ); 
glEnd();
glBegin(GL_POLYGON);
    glVertex3f(  0.0f, 0.3f, 0.0f );
    glVertex3f(  0.03f, 0.3f, 0.0f );         
    glVertex3f(  0.03f, 0.3f, 0.03f );     
    glVertex3f(  0.0f, 0.3f, 0.03f ); 
glEnd();
glPopMatrix();
//FIN BRAZO AEREO

//MINI BRAZO AEREO
glPushMatrix();
 glColor3f(0.0f,1.0f,0.0f);
 glRotatef(90,1.0f,0.0f,0.0f);     // ROTACION LAMPARA
 glTranslatef(0.0f,0.040f,-0.74f);

 GLUquadric *quad1;
 quad1 = gluNewQuadric();
 gluCylinder(quad1,0.005,0.005,0.1,25,25);
glPopMatrix();

glTranslatef(0.0f,0.74f,-0.03f);
glPushMatrix();
 glColor3f(0.0f,1.0f,1.0f);
 GLUquadric *quad2;
 quad2 = gluNewQuadric();
 gluCylinder(quad2,0.005,0.005,0.1,25,25);
glPopMatrix();
//FIN MINI BRAZO AEREO


//LAMPARA 
glPushMatrix(); 
 glColor3f(1.0f,1.0f,1.0f);
 glTranslatef(0.0f,0.0f,-0.05f);
 if(m.movAnguloX){
   glRotatef(m.rotarY,0.0f,1.0f,0.0f); 
   glRotatef(m.rotarX,1.0f,0.0f,0.0f);
   //printf("EJE X, angulo=%f\n",m.rotarX);
 }else{
   glRotatef(m.rotarX,1.0f,0.0f,0.0f); 
   glRotatef(m.rotarY,0.0f,1.0f,0.0f);  
  // printf("EJE Y, angulo=%f\n",m.rotarY);
 }
    
 glutSolidCone(0.1f,0.1f,32,20);
 //Esfera de luz
  glTranslatef(0.0f,0.0f,0.01f);  
 	glColor3f(1,0,0);
	GLUquadric *quad3;
	quad3 = gluNewQuadric();
	gluSphere(quad3,0.05f,100,20);
glPopMatrix();
//FIN LAMPARA

//moverBrazoAereo();
}

void moverBrazoAereo(){
  anguloBrazoAereo-=0.05f;
  printf("angulo: %f\n",anguloBrazoAereo);
  glutPostRedisplay(); //  Solicitar actualización de visualización

}

/*void moverLampara(){

}*/

void Esfera(){
	glColor3f(1,0,0);
	GLUquadric *quad;
	quad = gluNewQuadric();
	gluSphere(quad,0.1f,100,20);
}

/*
ejesEspaciales: Dibujamos los ejes espaciales.
 El eje y es de color verde
 El eje x es de color rojo
 El eje z es de colo azul
*/
void ejesEspaciales(){   
  //glPushMatrix();
  //glTranslatef(0.0f,0.0f,0.0f);
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

//glPopMatrix();

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

/*
movementCamara -> 
*/
/*
void movementCamara(int key, int x, int y){
  cambiarMovimiento(key);
  if (!isRotar){
    //Movimiento de la camara fijo
    if (key == GLUT_KEY_RIGHT)
      paneoEjeX -= 0.1f;
   
    else if (key == GLUT_KEY_LEFT)
      paneoEjeX += 0.1f;
  
    else if (key == GLUT_KEY_DOWN)
      paneoEjeY -=0.1f;
  
    else if (key == GLUT_KEY_UP)
     paneoEjeY +=0.1f;
  }else{
    //Movimiento de la camara libre
    if (key == GLUT_KEY_RIGHT)
      rotarEjeX -= 0.1f;
   
    else if (key == GLUT_KEY_LEFT)
      rotarEjeX += 0.1f;
  
    else if (key == GLUT_KEY_DOWN)
      rotarEjeZ -=0.1f;
  
    else if (key == GLUT_KEY_UP)
     rotarEjeZ +=0.1f;
  }
  glutPostRedisplay();//  Solicitar actualización de visualización
}
*/
/*
cambiarMovimiento -> Si puslamos la tecla ZZ, cambiamos
de modo de control de la camara.
 1.- Movimiento de la camara punto fijo.
 2.- Movimiento de la camara libre.
*/
/*
void cambiarMovimiento(int key){
 if (key == GLUT_KEY_F1){
    if (isRotar) isRotar=false;
    else  isRotar=true;
 }
 
}*/

void movimientoLampara(int key,int x,int y){
  //MOVIMIENTOS LAMPARA LUZ
  if(movimiento=='m'){ 
     if (key == GLUT_KEY_RIGHT){
       m.movAnguloX=true;
       m.rotarX+=0.5f;
     }
   
    else if (key == GLUT_KEY_LEFT){
       m.movAnguloX=true;
       m.rotarX-=0.5f;
    }

    else if (key == GLUT_KEY_DOWN){
      m.movAnguloX=false;//movimiento en y
      m.rotarY-=0.5f;
    }
  
    else if (key == GLUT_KEY_UP){
      m.movAnguloX=false; //movimiento en y
      m.rotarY+=0.5f;
    }

  //MOVIMIENTOS BRAZO   
  }else if(movimiento=='b'){ 
    if(key == GLUT_KEY_UP){
      if(anguloBrazoAereo<0.5){
        anguloBrazoAereo+=0.5f;
      }
      printf("anguloBrazoAereo --> %f\n",anguloBrazoAereo);
    }else if(key == GLUT_KEY_DOWN){
      if(anguloBrazoAereo>-11.5){
        anguloBrazoAereo-=0.5f;
      }      
      printf("anguloBrazoAereo --> %f\n",anguloBrazoAereo);
    }

  }
  //printf("anguloX= %f\n",anguloX);
  //printf("anguloY= %f\n",anguloY);
  //printf("\n\n");
  glutPostRedisplay();//  Solicitar actualización de visualización  
}

void detectaTecla(unsigned char caracter, int x, int y){
  if(caracter == 'p'){
   // tipoVision='p';
  //}else if(caracter =='t'){
  }else if(caracter == 't'){
   // printf("caracter= %c",caracter);
   // tipoVision='t';
  }else if(caracter=='l'){
    //tipoVision='l';
  }else if(caracter=='m'){ //Movimiento luz 
    movimiento='m';
  }else if(caracter=='b'){ //Movimiento brazo
    movimiento='b';
  }
  printf("caracter= %c\n",caracter);
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
  glutSpecialFunc(movimientoLampara);
  glutKeyboardFunc(detectaTecla);
 // glutKeyboardFunc();
  glutReshapeFunc(Reescalar); 

  //  Pasar el control de eventos a GLUT
  glutMainLoop();
 
  //  Regresar al sistema operativo
  return 0;
 
}
