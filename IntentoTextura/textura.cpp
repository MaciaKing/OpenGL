/*#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>*/
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "BMPLoader.h"
GLuint tex2D;
GLfloat angle;
 
// Parámetros de inicialización
void init() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.1, 0.1, 0.4, 0.0);
    glShadeModel(GL_SMOOTH);
    CBMPLoader bmpLoader;
    bmpLoader.LoadBmp("/123-bmp.bmp");
     
 
         // Crear textura
    glGenTextures(1, &tex2D);
    glBindTexture(GL_TEXTURE_2D, tex2D);
 
 
         // Configuración de parámetros de filtro de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 
 
         // Establecer datos de textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpLoader.imageWidth, bmpLoader.imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bmpLoader.image);
    angle = 0;
}
 
 
 /** Dibuja una caja de madera */
void DrawBox(){
    glEnable(GL_TEXTURE_2D);
 
         /** Seleccionar textura */
    glBindTexture(GL_TEXTURE_2D, tex2D);
 
         /** Empiece a dibujar el cuadrilátero */
    glBegin(GL_QUADS);
 
         /// Lado delantero
         glNormal3f (0.0f, 0.0f, 1.0f); / ** Especifique la normal para apuntar al observador * /
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
 
         /// parte trasera
         glNormal3f (0.0f, 0.0f, -1.0f); / ** Especificar la normal de regreso al observador * /
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
 
         /// Superficie superior
         glNormal3f (0.0f, 1.0f, 0.0f); / ** Especificar normal ascendente * /
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f, 1.0f, -1.0f);
 
         /// superficie inferior
         glNormal3f (0.0f, -1.0f, 0.0f); / ** Especifique la normal para que esté boca abajo * /
    glTexCoord2f(0.0f, 0.0f);glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);glVertex3f(-1.0f, -1.0f, -1.0f);
 
         /// lado derecho
         glNormal3f (1.0f, 0.0f, 0.0f); / ** Especifique la normal a la derecha * /
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
    
         /// lado izquierdo
         glNormal3f (-1.0f, 0.0f, 0.0f); / ** Especifique la normal a la izquierda * /
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
 
 
 // Función de devolución de llamada de dibujo
void display() {
         // Borrar los datos del marco anterior
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotated(angle, 1, 1, 0);
    DrawBox();
    glPopMatrix();
 
         // Ejecutar comandos de dibujo
    glFlush();
    angle ++;
    glutPostRedisplay();
}
 
 
 // Función de devolución de llamada de cambio de tamaño de ventana
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 0.1, 100000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
int main(int argc, const char * argv[]) {
         // Inicializar el modo de visualización
    glutInit(&argc, const_cast<char **>(argv));
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB|GLUT_DEPTH);
 
 
         // Inicializar la ventana
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
 
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
 
         // iniciar el dibujo del bucle principal
    glutMainLoop();
    return 0;
