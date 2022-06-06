/*
Fer pull i me dona igual cambis en local
git fetch
git reset
git merge origin

warning --> git config --global core.autocrlf false

*/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include<unistd.h>
#include <cmath> //Para calcular valores absolutos de variables
#include "tgaload.h" 
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

bool movCamara=true;

float posx = 4.600000f, posy=0.530000f;
char tipoVision='o';
GLfloat angle = -3.199999f;
float eye[3]={4.600000f,1.000000f,0.530000f};
float center[3]={3.612520f,0.800000f,0.687745f};

/*
eye[0]= 4.600000,eye[1]= 1.000000,eye[2]= 0.530000 
 center[0]= 3.612520,center[1]= 0.800000,center[2]= 0.687745 
 posx=4.600000, posy=0.530000
*/


GLfloat light[] = {1.0f, 0.0f, 0.0f};
GLfloat posicionLuzLampara[] = {0.0f, 0.0f, 0.0f};
GLfloat luz[] = {1.0f, 0.0f, 0.0f, 1.0f};

bool boira=false;
bool isPrimer=true;
bool vullAnimacio=true;

//Textures
// Qtd m�xima de texturas a serem usadas no programa
#define MAX_NO_TEXTURES 2

#define TEXTURA_PARED 0
#define TEXTURA_SUELO  1

// vetor com os n�meros das texturas
GLuint texture_id[MAX_NO_TEXTURES];

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
void moverBrazoAereo();
void moverLampara();
void detectaTecla(unsigned char caracter, int x, int y);
void movimientoLampara(int key);
void movementCamara(int key);
void paneo(int key);  
void movimientoCamaraLibre(int key);  
void movimietoEnUnPunto(int key);
void animacion();
void initTexture (void);
void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB, GLfloat diffuseR,GLfloat diffuseG,
GLfloat diffuseB, GLfloat specularR, GLfloat specularG, GLfloat specularB, GLfloat shiniess);


// Funci�n que visualiza la escena OpenGL
void Display (void){
  //  Borrar pantalla y Z-buffer
  glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Render de la luz
  glEnable (GL_LIGHTING);
  glEnable (GL_COLOR_MATERIAL);
  glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable (GL_LIGHT0);

/*GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 }; GLfloat light2_position[] = { 2.0, -2.0, 1.0, 1.0 };
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); glLightfv(GL_LIGHT0, GL_POSITION, light1_position); glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT1, GL_POSITION, light2_position);
glEnable(GL_LIGHT0); glEnable(GL_LIGHT1);*/

  //boira
  if(boira){
   glEnable (GL_FOG);
   float color[]={1.0,0.0,0.0,0.5};
   glFogfv(GL_FOG_COLOR,color); 
   glFogi(GL_FOG_MODE, GL_LINEAR);
   glFogf(GL_FOG_START,1.50);
   glFogf(GL_FOG_END,3.5);
  }else {
    glDisable(GL_FOG);
  }

  // Resetear transformaciones
  glLoadIdentity();
  
  //CAMARA
  if (tipoVision=='p'){//paneo
    gluLookAt(posx,eye[1],posy  ,center[0],center[1],center[2],  0.0f,1.0f,0.0f);
   // gluLookAt(eye[0],eye[1],eye[2]  ,center[0],center[1],center[2],  0.0f,1.0f,0.0f);
  }else if(tipoVision=='t'){ //camara gira entorno en un punto
    gluLookAt(eye[0],eye[1],eye[2]  ,center[0],center[1],center[2],  0.0f,1.0f,0.0f);
  }else if (tipoVision=='o'){//camara libre
    //printf("eye[0]= %f,eye[1]= %f,eye[2]= %f \n center[0]= %f,center[1]= %f,center[2]= %f \n posx=%f, posy=%f, angle=%f\n\n",eye[0] ,eye[1] ,  eye[2], center[0], center[1], center[2],posx,posy,angle);
    center[0]=posx+cos(angle);
    center[2]=posy + sin(angle);
    eye[0]=posx; eye[2]=posy;
    gluLookAt(eye[0] ,eye[1] ,  eye[2], center[0], center[1], center[2],0,1,0);       
  }

  
  ejesEspaciales();
  /*if(vullAnimacio){

  }else lampara();*/
  setMaterial(1.0f,0.0f,0.0f,
              1.0f,1.0f,1.0f,
              1.0f,1.0f,1.0f, 1.0f );
  lampara();
  //animacion();
  setMaterial(0.0f,0.0f,0.0f,
              0.0f,0.0f,0.0f,
              0.0f,0.0f,0.0f, 1.0f );
  plano(); //Suelo y paredes.
  glFlush();
  glutSwapBuffers();
}

float x=0.0f;
float y=0.0f;
float z=0.0f;
bool salta=true;
bool atura=true;
void animacion(){
  glPushMatrix();
  float i=0;
   if(y<0.8 && salta){ //salta
   y=y+0.01f;
   z=z-0.005f;
   anguloBrazoAereo=anguloBrazoAereo-0.15f;
   //printf("y=%f\n",y);
   glTranslatef(0.0f,y,z);
   }else if(y>0.1f && atura){ //baja
     salta=false;
     y=y-0.01f;
     z=z-0.005f;
     anguloBrazoAereo=anguloBrazoAereo+0.15f;
     glTranslatef(0.0f,y,z);
   }else{ //gira foco
     atura=false;
   }
   //lampara();
   glutPostRedisplay();//  Solicitar actualización de visualización  
  glPopMatrix();
}

void plano(){
  setMaterial(0.0f, 0.1f, 0.0f, 
  0.1f,0.1f,0.1f, 
  0.0f, 0.9f, 0.0f, 1.0f);
 for(int i=0; i<4;i++){
 glPushMatrix();
 if(i==3){
  glRotatef(90.0f,-1.0f,0.0f,0.0f);
  glRotatef(90.0f,0.0f,0.0f,1.0f);
  glTranslatef(-1.5f,0.0f,0.0f);

 glColor3f(   1.0,  1.0, 1.0 );    //AQUEST TEXTURA
 glRotatef(90.0f,1.0f,0.0f,0.0f);
 glNormal3f(0.0f,1.0f,0.0f);
 //glRectf(0.0f, 0.0f, 1.5f, 1.5f);
 glBindTexture( GL_TEXTURE_2D, texture_id[TEXTURA_PARED]);
 glBegin(GL_POLYGON);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(  0.0f, 0.0f, 0.0f ); 
  glTexCoord2f(1.0f, 0.0f); glVertex3f(  1.5f, 0.0f, 0.0f );
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(  1.5f, 1.5f, 0.0f ); 
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(  0.0f, 1.5f, 0.0f  ); 
 glEnd();


 glRotatef(90.0f,1.0f,0.0f,0.0f);
 glColor3f(1.0f,0.0f,1.0f);
 glRectf(0.0f, 0.0f, 1.5f, -0.05f);

 glRotatef(90.0f,0.0f,1.0f,0.0f);
 glColor3f(1.0f,0.0f,1.0f);
 glRectf(0.0f, 0.0f, 1.5f, -0.05f);

 glTranslatef(0.0f,0.0f,2.5f);
 glColor3f(1.0f,0.0f,1.0f);
 glRectf(0.0f, 0.0f, 0.0f, -0.05f);


 glTranslatef(1.5f,0.0f,0.0f);
 glRotatef(90.0f,0.0f,1.0f,0.0f);
 glColor3f(1.0f,0.0f,1.0f);
 glRectf(1.0f, 0.0f, 2.5f, -0.05f);

 glColor3f(   1.0,  1.0, 0.0 );
 glTranslatef(0.0f,-0.05f,-1.5f);
 glRotatef(90.0f,1.0f,0.0f,0.0f); 
 glRectf(1.0f, 0.0f, 2.5f, 1.5f);
  
 }else{
  //if(i==0) //res
 if(i==1) glRotatef(90.0f,-1.0f,0.0f,0.0f);
 glColor3f(   1.0,  1.0, 1.0 );   // AQUEST TEXTURA
 glRotatef(90.0f,1.0f,0.0f,0.0f);
 //glRectf(0.0f, 0.0f, 2.5f, 1.5f);
 glBindTexture( GL_TEXTURE_2D, texture_id[TEXTURA_PARED]);
 glBegin(GL_POLYGON);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(  0.0f, 0.0f, 0.0f ); 
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(  2.5f, 0.0f, 0.0f );
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(  2.5f, 1.5f, 0.0f ); 
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(  0.0f, 1.5f, 0.0f  ); 
 glEnd();

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

 //glColor3f(   1.0,  0.0, 0.0 );  //AQUEST TEXTURA ENTERRA
 glTranslatef(0.0f,-0.05f,-1.5f);
 glRotatef(90.0f,1.0f,0.0f,0.0f); 
 //glRectf(0.0f, 0.0f, 2.5f, 1.5f);
 glBindTexture( GL_TEXTURE_2D, texture_id[TEXTURA_SUELO]);
 glBegin(GL_POLYGON);
  glTexCoord2f(0.0f, 0.0f);  glVertex3f(  0.0f, 0.0f, 0.0f ); 
  glTexCoord2f(1.0f, 0.0f);  glVertex3f(  2.5f, 0.0f, 0.0f );
  glTexCoord2f(1.0f, 1.0f);  glVertex3f(  2.5f, 1.5f, 0.0f ); 
  glTexCoord2f(0.0f, 1.0f);  glVertex3f(  0.0f, 1.5f, 0.0f ); 
 glEnd();
 }
glPopMatrix(); 
 }
}

void lampara(){  
glPushMatrix();
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
 glColor3f(1.0f,1.0f,1.0f);
 GLUquadric *quad2;
 quad2 = gluNewQuadric();
 gluCylinder(quad2,0.005,0.005,0.1,25,25);
glPopMatrix();
//FIN MINI BRAZO AEREO


//LAMPARA 
glPushMatrix(); 
 //glColor3f(1.0f,1.0f,1.0f);
 glTranslatef(0.0f,0.0f,-0.05f);    
 //glutSolidCone(0.1f,0.1f,32,20);
 //Esfera de luz
  glTranslatef(0.0f,0.0f,0.01f);  
 	//glColor3f(1,0,0);
	GLUquadric *quad3;
	quad3 = gluNewQuadric();

/* glEnable(GL_LIGHT1); 
 glLighti(GL_LIGHT1, GL_SPOT_CUTOFF,45);
 glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10);
 glLightfv(GL_LIGHT1, GL_DIFFUSE, luz);
 glLightfv(GL_LIGHT1,GL_POSITION,posicionLuzLampara);
 glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,light);*/
 
 /*GLfloat light1Value[] = { 0,0,1 };
 glEnable(GL_LIGHT1);
 glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Value);
 glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, 45);
 glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10);
 GLfloat lightbulbPosition[] = { 0,0,0 }, lightbulbSpotlightDirection[] = { 1,1,1 };
 glLightfv(GL_LIGHT1, GL_POSITION, lightbulbPosition);
 glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightbulbSpotlightDirection);
 */
 gluSphere(quad3,0.05f,100,20);

  
glPopMatrix();
//FIN LAMPARA


glPopMatrix();
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
  glPushMatrix();
  glTranslatef(0.0f,1.5f,0.0f);
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
  printf("vullAnimacio=\n");
  /*printf("vullAnimacio= %B\n",vullAnimacio);
  if(vullAnimacio){
    printf("ANIMACIOOO \n");
    animacion(); 
  }*/
	
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
	}else{
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
					
				}
      }

		}
  }   
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
          posx = 4.600000f, posy=0.530000f;
          angle = -3.199999f;
         eye[0]=4.600000f;eye[1]=1.000000f;eye[2]=0.530000f;
          center[0]=3.612520f;center[1]=0.800000f;center[2]=0.687745f;
           break;
          
           
  case  2:  
           eye[0]= 1.475389;eye[1]= 1.000000;eye[2]= 2.482042;
            center[0]= 1.446190;center[1]= 0.800000;center[2]= 1.482469;
          posx=1.504589; posy=3.481616; angle=-1.600000;
           break;  

  case  3:  
        eye[0]= 0.606821;eye[1]= 0.500000;eye[2]= 0.763493; 
 center[0]= 1.606821;center[1]= 0.600000;center[2]= 0.763493; 
 posx=-0.393179; posy=0.763493; angle=0.000000;

           break;  
             

  case  4: 
           
           boira=true;
           //printf("Activada boira\n");
           break;     
  case  5: 
           boira=false;
           printf("Desactiva boira\n");
           break;      

    case  6: 
          x=0.0f;
          y=0.0f;
          z=0.0f;
          salta=true;
          vullAnimacio=true;
          
         break;  
   
  }

  glutPostRedisplay();
}

/* Establece las opciones del menú desplegable -----------------------------*/
void menu (void) {

  int idMenuPrincipal, idMenuParalela, idMenuBoira, idAnimacion;

  idMenuPrincipal= glutCreateMenu (atiendeMenu);
  glutAttachMenu (GLUT_RIGHT_BUTTON);

  idMenuParalela= glutCreateMenu (atiendeMenu);
  glutAddMenuEntry ("Camara 1", 1);
  glutAddMenuEntry ("Camara 2", 2);
  glutAddMenuEntry ("Camara 3", 3);
  glutSetMenu (idMenuPrincipal);
  glutAddSubMenu ("Posicion Camara", idMenuParalela);


  idMenuBoira= glutCreateMenu (atiendeMenu);
  glutAddMenuEntry ("Activa",  4);
  glutAddMenuEntry ("Desactiva",  5);
  glutSetMenu (idMenuPrincipal);
  glutAddSubMenu ("Boira", idMenuBoira);

  idAnimacion= glutCreateMenu (atiendeMenu);
  glutSetMenu (idMenuPrincipal);
  glutAddMenuEntry ("Animacion",  6);
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
  glutSpecialFunc(movimientoCamaraOLampara);
  glutKeyboardFunc(detectaTecla);
  glutReshapeFunc(Reescalar); 

  menu();
  initTexture();

  //  Pasar el control de eventos a GLUT
  glutMainLoop();
 
  //  Regresar al sistema operativo
  return 0;
}

// **********************************************************************
//  void initTexture(void)
//		Define a textura a ser usada 
//
// **********************************************************************
void initTexture (void)
{

	image_t temp_image; // vari�vel que ir� armazenar a textura a ser usada

	// Habilita o uso de textura 
	glEnable(GL_TEXTURE_2D );

	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1 );

	// Define quantas texturas ser�o usadas no programa 
	glGenTextures(1, texture_id);  // 1 = uma textura;
									// texture_id = vetor que guardas os n�meros das texturas

	// Define os n�meros da textura dos cubos
	texture_id[TEXTURA_PARED] = 1001;
	texture_id[TEXTURA_SUELO] = 1002;

	// ****
	// Define a textura do objeto da ESQUERDA
	// ****

	// Define que tipo de textura ser� usada
	// GL_TEXTURE_2D ==> define que ser� usada uma textura 2D (bitmaps)
	// texture_id[TEXTURA_PARED]  ==> define o n�mero da textura 
	glBindTexture( GL_TEXTURE_2D, texture_id[TEXTURA_PARED]);
	// Carrega a primeira imagem .TGA 
	tgaLoad("Imagenes/pared.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);


	// ****
	// Define a textura do objeto da DIREITA
	// ****

	// Define que tipo de textura ser� usada
	// GL_TEXTURE_2D ==> define que ser� usada uma textura 2D (bitmaps)
	// texture_id[TEXTURA_PARED]  ==> define o n�mero da textura 
	glBindTexture(GL_TEXTURE_2D, texture_id[TEXTURA_SUELO]);

	// carrega a segunda imagem TGA 
	tgaLoad ("Imagenes/parquet.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

}

/*
youtube.com/watch?v=4U12rvYOKN4
*/
void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB, GLfloat diffuseR,GLfloat diffuseG,
GLfloat diffuseB, GLfloat specularR, GLfloat specularG, GLfloat specularB, GLfloat shiniess){
GLfloat ambient[] = {ambientR, ambientG, ambientB};
GLfloat diffuse[] = {diffuseR, diffuseG, diffuseB};
GLfloat specular[] = {specularR, specularG, specularB};

glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiniess);
}