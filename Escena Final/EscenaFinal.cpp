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
#include <cmath> //Para calcular valores absolutos de variables
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
GLfloat rotarTodo=0.0f;

struct movimientoL{
  bool movAnguloX=true; // si es true mueve eje x, si es false eje y
  //char signo='+';  // puede ser + o -
  GLfloat rotarX=0.0f;
  GLfloat rotarY=0.0f;
};

struct movimientoL m;
GLfloat anguloBrazoAereo=0.0f;

char tipoVision='p';
float center[3]={2.0f,0.0f,0.0f};
float eye[3]={-1.0f,1.0f,1.0f};
bool movCamara=true;

float posx = 0.0f, posy=0.0f;

GLfloat angle = 0.0f;

// ----------------------------------------------------------
// Funciones 
// ----------------------------------------------------------
void Display(void);
void Reescalar(int w, int h);
void Cubo();
void ejesEspaciales();
void Rectangulo();
void Esfera();
void plano();
void cambiarMovimiento(int key);
void lampara();
//void rotar();
void moverBrazoAereo();
void moverLampara();
void detectaTecla(unsigned char caracter, int x, int y);
void movimientoLampara(int key/*,int x,int y*/);
void movementCamara(int key);
void paneo(int key);  
void movimientoCamaraLibre(int key);  
void movimietoEnUnPunto(int key);


// Funci�n que visualiza la escena OpenGL
void Display (void){
  //  Borrar pantalla y Z-buffer
  glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Resetear transformaciones
  glLoadIdentity();
  //glTranslatef(aux,0.0f,0.0f);
  
  //CAMARA
  if (tipoVision=='p'){//paneo
    gluLookAt(posx,eye[1],posy  ,center[0],center[1],center[2],  0.0f,1.0f,0.0f);
  }else if(tipoVision=='t'){ //camara gira entorno en un punto
    gluLookAt(eye[0],eye[1],eye[2]  ,center[0],center[1],center[2],  0.0f,1.0f,0.0f);
  }else if (tipoVision=='o'){//camara libre
    center[0]=posx+cos(angle);
    center[2]=posy + sin(angle);
   // gluLookAt(posx ,eye[1] ,  posy, posx + cos(angle), 0, posy + sin(angle),0,1,0);
     gluLookAt(posx ,eye[1] ,  posy, center[0], center[1], center[2],0,1,0);
  }

  /*//glRotatef(aux,0.0f,1.0f,0.0f);
  //rotar();
  gluPerspective(100.0f,W_WIDTH/W_HEIGHT,0.1f,20.0f);
  //gluLookAt(0.0f,1.0f,-1.0f, 0.0f,0.0f,0.0f, 0.0f,2.0f,0.0f); //mirada al centro de la lampara
  //gluLookAt(0.0f,0.0f,-1.0f, 0.0f,0.0f,0.0f, 0.0f,2.0f,0.0f); //mirada al centro de la lampara
 // gluLookAt(0.6f,0.0f,-0.5f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f); //mirada desde un lado
  gluLookAt(2.5f,0.2f,1.0f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f); //Escena final
  //gluLookAt(2.5f,0.5f,1.0f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f);
  // gluLookAt(0.0f,0.0f,0.5f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f); //mirada desde atras perfecta
  */
  //gluLookAt(0.01f,-1.5f,0.0f, 0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f); //Vista de arriba perfecta

 /* gluPerspective(90.0f,1.0f,0.0f,10.0f);
  //gluLookAt(1.0f,-1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f); //define una transformacion visual
  //gluLookAt(rotateEjeX,rotateEjeY,rotateEjeZ,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f);
  //gluLookAt(rotateEjeX,rotateEjeY,rotateEjeZ,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);
  gluLookAt(0.0f,1.0f,rotarEjeZ,paneoEjeX,paneoEjeY,0.0f,0.0f,1.0f,0.0f);
*/
  
  ejesEspaciales();
  plano();
  lampara();
  glFlush();
  glutSwapBuffers();
}


void plano(){
 //  glRectf(-0.2f, 0.0f, 0.2f, 0.5f);
 //glTranslatef(0.0f,0.0f,0.0f);
 glPushMatrix();
 glColor3f(   1.0,  1.0, 0.0 );
 glRotatef(90.0f,1.0f,0.0f,0.0f);
 glRectf(0.0f, 0.0f, 2.5f, 1.5f);

 glRotatef(90.0f,1.0f,0.0f,0.0f);
 glColor3f(1.0f,0.0f,1.0f);
 glRectf(0.0f, 0.0f, 2.5f, -0.05f);

 glRotatef(90.0f,0.0f,1.0f,0.0f);
 glColor3f(1.0f,0.0f,1.0f);
 glRectf(0.0f, 0.0f, 1.5f, -0.05f);

 glTranslatef(0.0f,0.0f,2.5f);
 glColor3f(1.0f,0.0f,1.0f);
 glRectf(0.0f, 0.0f, 1.5f, -0.05f);

 glTranslatef(1.5f,0.0f,0.0f);
 glRotatef(90.0f,0.0f,1.0f,0.0f);
 glColor3f(1.0f,0.0f,1.0f);
 glRectf(0.0f, 0.0f, 2.5f, -0.05f);

 glColor3f(   1.0,  1.0, 0.0 );
 glTranslatef(0.0f,-0.05f,-1.5f);
 glRotatef(90.0f,1.0f,0.0f,0.0f); 
 glRectf(0.0f, 0.0f, 2.5f, 1.5f);

 glPopMatrix();
 /*glBegin(GL_POLYGON);
  glVertex3f(  0.0,  0.0, 0.0 );
  glVertex3f(  3.0,  0.0, 0.0 );
  glVertex3f(  3.0,  0.0, 3.0 );
  glVertex3f(  0.0,  0.0, 3.0 );
 glEnd();*/
}

void lampara(){
 // glPushMatrix();
  glTranslatef(1.8f,0.05f,1.0f);
  glRotatef(rotarTodo,0.0f,1.0f,0.0f);
  glColor3f(1,1,1);
  //Base Lampara
  glPushMatrix();
  glRotatef(-90.0f,1.0f,0.0f,0.0f); 
  //glColor3f(1,0,0);
  glutSolidCone(0.1f,0.1f,32,20);
   glPushMatrix();
    //glColor3f(1.0f,1.0f,1.0f);
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
      //glColor3f(   0.0f,  0.0f, 1.0f );
  }//selse glColor3f(   0.0f,  1.0f, 0.0f );
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
    //glColor3f(   0.0,  0.0, 1.0 );
    //BASE
   // glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(  -0.1f, 0.3f, 0.0f );
    glVertex3f(  0.1f, 0.3f, 0.0f );         
    glVertex3f(  0.1f, 0.3f, 0.1f );     
    glVertex3f(  -0.1f, 0.3f, 0.1f ); 
glEnd();
glBegin(GL_POLYGON);
   // glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(  -0.1f, 0.3f, 0.1f ); 
    glVertex3f(  -0.1f, 0.35f, 0.1f );
    glVertex3f(   0.1f, 0.35f, 0.1f ); 
    glVertex3f(   0.1f, 0.3f, 0.1f ); 
glEnd();

glBegin(GL_POLYGON);
   // glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(  0.1f, 0.35f, 0.1f ); 
    glVertex3f(  0.1f, 0.3f, 0.1f );
    glVertex3f(  0.1f, 0.3f, 0.0f ); 
    glVertex3f(  0.1f, 0.3f, 0.0f  ); 
glEnd();

glBegin(GL_POLYGON);
   // glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(  0.1f, 0.35f, 0.1f ); 
    glVertex3f(  0.1f, 0.3f, 0.1f );
    glVertex3f(  0.1f, 0.3f, 0.0f ); 
    glVertex3f(  0.1f, 0.35f, 0.0f  ); 
glEnd();

glBegin(GL_POLYGON);
   // glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(  0.1f, 0.3f, 0.0f ); 
    glVertex3f(  0.1f, 0.35f, 0.0f );
    glVertex3f(  -0.1f, 0.35f, 0.0f ); 
    glVertex3f(  -0.1f, 0.3f, 0.0f  ); 
glEnd();

glBegin(GL_POLYGON);
    //glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(  0.1f, 0.3f, 0.0f ); 
    glVertex3f(  0.1f, 0.35f, 0.0f );
    glVertex3f(  -0.1f, 0.35f, 0.0f ); 
    glVertex3f(  -0.1f, 0.3f, 0.0f  ); 
glEnd();

glBegin(GL_POLYGON);
    //glColor3f(0.0f,1.0f,1.0f);
    glVertex3f(  -0.1f, 0.35f, 0.0f ); 
    glVertex3f(  -0.1f, 0.3f, 0.0f );
    glVertex3f(  -0.1f, 0.3f, 0.1f ); 
    glVertex3f(  -0.1f, 0.35f, 0.1f  ); 
glEnd();
    
glBegin(GL_POLYGON);
    //glColor3f(   1.0,  1.0, 0.0 );
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
   // glColor3f(   0.0,  1.0, 1.0 );
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
 //glColor3f(0.0f,1.0f,0.0f);
 glRotatef(90,1.0f,0.0f,0.0f);     // ROTACION LAMPARA
 glTranslatef(0.0f,0.040f,-0.74f);

 GLUquadric *quad1;
 quad1 = gluNewQuadric();
 gluCylinder(quad1,0.005,0.005,0.1,25,25);
glPopMatrix();

//Posible movimiento del objeto
 if(m.movAnguloX){
   glRotatef(m.rotarX,0.0f,0.0f,1.0f);
   //printf("FALSE\n");
 }else{
   glRotatef(m.rotarY,0.0f,1.0f,0.0f);  
   //printf("TRUEEEE\n");
 }

glTranslatef(0.0f,0.74f,-0.03f);
glPushMatrix();
 //glColor3f(0.0f,1.0f,1.0f);
 GLUquadric *quad2;
 quad2 = gluNewQuadric();
 gluCylinder(quad2,0.005,0.005,0.1,25,25);
glPopMatrix();
//FIN MINI BRAZO AEREO


//LAMPARA 
glPushMatrix(); 
 //glColor3f(1.0f,1.0f,1.0f);
 glTranslatef(0.0f,0.0f,-0.05f);    
 glutSolidCone(0.1f,0.1f,32,20);
 //Esfera de luz
  glTranslatef(0.0f,0.0f,0.01f);  
 	//glColor3f(1,0,0);
	GLUquadric *quad3;
	quad3 = gluNewQuadric();
	gluSphere(quad3,0.05f,100,20);
glPopMatrix();
//FIN LAMPARA

//moverBrazoAereo();
//glPopMatrix();
}

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
    if (w <= h)gluPerspective(60,h/(float)w,1,100);        
    else gluPerspective(60,w/(float)h,1,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                             // Activar las modificaciones en el modelo
    glutPostRedisplay();
}


void movimientoLampara(int key){
  //MOVIMIENTOS LAMPARA LUZ
  if(movimiento=='m'){ 
     if (key == GLUT_KEY_RIGHT){
      if(abs(m.rotarY)<6.5 || m.rotarY==6.5){
       m.movAnguloX=false;//movimiento en y
       m.rotarY-=0.5f;
      }
     }
   
    else if (key == GLUT_KEY_LEFT){
      if((abs(m.rotarY)<6.5) || m.rotarY==-6.5){
       m.movAnguloX=false; //movimiento en y
       m.rotarY+=0.5f;
    }
    }

    else if (key == GLUT_KEY_DOWN){
      m.movAnguloX=true;
      m.rotarX+=0.5f;
      //printf("DOOOOWN\n");
    }
    
    else if (key == GLUT_KEY_UP){
      m.movAnguloX=true;
      m.rotarX-=0.5f;   
     // printf("UUUUUP\n");   
    }
    
    printf("rotarX = %f, rotarY= %f\n",m.rotarX,m.rotarY);
  //MOVIMIENTOS BRAZO   
  }else if(movimiento=='b'){ 
    if(key == GLUT_KEY_UP){
      if(anguloBrazoAereo<0.5){
        anguloBrazoAereo+=0.5f;
      }
     // printf("anguloBrazoAereo --> %f\n",anguloBrazoAereo);
    }else if(key == GLUT_KEY_DOWN){
      if(anguloBrazoAereo>-11.5){
        anguloBrazoAereo-=0.5f;
      }      
      //printf("anguloBrazoAereo --> %f\n",anguloBrazoAereo);
    }
  //MOVIMIENTO TOTAL DEL OBJETO
  }else if(movimiento=='t'){
    if (key == GLUT_KEY_LEFT){
          rotarTodo+=1.0f;      
    }else if(key == GLUT_KEY_RIGHT){
          rotarTodo-=1.0f;
    }
  }
  glutPostRedisplay();//  Solicitar actualización de visualización  
}

void detectaTecla(unsigned char caracter, int x, int y){
  if(caracter == 'p'){
   tipoVision='p';
   movCamara=true;
  }else if(caracter=='l'){
    tipoVision='l';
    movCamara=true;
  }else if(caracter=='o'){
    tipoVision='o';
    movCamara=true;
  }else if(caracter=='m'){ //Movimiento luz 
    movimiento='m';
    movCamara=false;
  }else if(caracter=='b'){ //Movimiento brazo
    movimiento='b';
    movCamara=false;
  }else if(caracter=='t'){
    movimiento='t';
    movCamara=false;
  }
  printf("caracter= %c\n",caracter);
}

//MOVIMIENTO CAMARA ----------------------------------------------------------------
void movimientoCamaraOLampara(int key,int x,int y){
  if(movCamara){ // La tecla es para la camara
    movementCamara(key);
  }else  movimientoLampara(key);//el movimiento es para lampara
  
}

//CAMARA
void movementCamara(int key){
  switch (tipoVision){
  case 'p':
    paneo(key);
    break;

  case 't':
   movimietoEnUnPunto(key);
    break;

   case 'o':
   movimientoCamaraLibre(key);
   break;

  default:
    //no hagas nada
    break;
  } 
}

void movimientoCamaraLibre(int key){   
  	if(key==GLUT_KEY_DOWN){
		posx=posx - cos (angle);
		posy=posy - sin(angle);
	}
	else{
		if(key==GLUT_KEY_UP){
	 		posx=posx + cos (angle);
		   posy=posy + sin(angle);
	}
		else {
			if(key==GLUT_KEY_RIGHT){
			angle= angle + 0.1 ;
			 }
			else{
				if(key==GLUT_KEY_LEFT){
					angle=angle - 0.1;
					
				}}
		}}
   
  glutPostRedisplay();//  Solicitar actualización de visualización  
}


void paneo(int key){      
    if (key == GLUT_KEY_UP)
      center[1] +=0.1f;

    else if (key == GLUT_KEY_DOWN)
     center[1]-=0.1f;

    else if (key == GLUT_KEY_LEFT)
     center[2]+= 0.1f;  

    else if (key == GLUT_KEY_RIGHT)
     center[2]-= 0.1f;

  glutPostRedisplay();//  Solicitar actualización de visualización  
}

/*
Movimiento de la camara en entorno al 
punto
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

/* Atiende las opciones del menú desplegable -------------------------------*/
void atiendeMenu (int opcion) {
  switch (opcion) {
  case  1: 
           eye[0]=-1.0f; eye[1]=1.0f; eye[2]=1.0f;
           center[0]=2.0f;center[1]=0.0f; center[2]=0.0f;
           break;
           
  case  2: 
           eye[0]=3.0f; eye[1]=0.5f; eye[2]=1.0f;
           center[0]=2.0f;center[1]=0.0f; center[2]=0.0f;
           break;         
  }
  glutPostRedisplay ();
}

/* Establece las opciones del menú desplegable -----------------------------*/
void menu (void) {

  int idMenuPrincipal, idMenuParalela, idMenuColor;

  idMenuPrincipal= glutCreateMenu (atiendeMenu);
  glutAttachMenu (GLUT_RIGHT_BUTTON);

  //glutAddMenuEntry ("Vista", 1);

  idMenuParalela= glutCreateMenu (atiendeMenu);
  glutAddMenuEntry ("Camara 1", 1);
  glutAddMenuEntry ("Camara 2", 2);
  glutAddMenuEntry ("Camara 3", 3);
  glutSetMenu (idMenuPrincipal);
  glutAddSubMenu ("Posicion Camara", idMenuParalela);

  idMenuColor= glutCreateMenu (atiendeMenu);
  glutAddMenuEntry ("Rojo",  5);
  glutAddMenuEntry ("Verde", 6);
  glutAddMenuEntry ("Azul",  7);
  glutSetMenu (idMenuPrincipal);
  glutAddSubMenu ("Color", idMenuColor);
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
  glutCreateWindow("Escena Final");

  //  Habilitar la prueba de profundidad de Z-buffer
  glEnable(GL_DEPTH_TEST);

  // Funciones de retrollamada
  glutDisplayFunc(Display);
  //glutSpecialFunc(movimientoLampara);
  glutSpecialFunc(movimientoCamaraOLampara);
  glutKeyboardFunc(detectaTecla);
 // glutKeyboardFunc();
  glutReshapeFunc(Reescalar); 

  menu();

  //  Pasar el control de eventos a GLUT
  glutMainLoop();
 
  //  Regresar al sistema operativo
  return 0;
 
}
