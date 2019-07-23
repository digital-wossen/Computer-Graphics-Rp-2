/**
 * A simple OpenGL application that demonstrates the use
 * of GLUT bitmap fonts
 *
 * Compile under Linux (gcc or g++):
 *   gcc -Wall -lglut -lGLU -lGL -o bitmapfontGLUT bitmapfontGLUT.c
 * Compile under MinGW with:
 *   g++ -o bitmapfontGLUT -Wall bitmapfontGLUT.c -mwindows glut32.lib -lopengl32 -lglu32
 * (have to add  #include <windows.h>)
 *
 * @author  Dr. Szymon Krupinski, adapted from original program of Prof. David Bernstein
 * @version 1.1
 */
#include "GL/glut.h"

int window;

void* currentFont;




/**
 * Create a window
 *
 * @param title   The title
 * @param width   The width (in pixels)
 * @param height  The height (in pixels)
 * @param x       The x position
 * @param y       The y position
 * @return        The window id
 */
int createWindow(char* title, int width, int height, int x, int y)
{
   int id;
   

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(width, height);
   glutInitWindowPosition(x, y);
   id = glutCreateWindow(title);

   return id;   
}

/**
 * Set the current font 
 *
 * @param font   The font
 */
void setFont(void* font)
{
   currentFont = font;
}

//[drawString
/**
 * Draw a character string
 *
 * @param x        The x position
 * @param y        The y position
 * @param z        The z position
 * @param string   The character string
 */
void drawString(float x, float y, float z, char *string)
{
   glRasterPos3f(x, y, z);
   
   for (char* c=string; *c != '\0'; c++)
   {
      glutBitmapCharacter(currentFont, *c); // Updates the position
   }
}
//]drawString



/**
 * Perform OpenGL initializations
 */
void init() 
{
   glClearColor(1.0, 1.0, 1.0, 1.0);

   // Setup the projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0); // Orthographic

   // Set the current font
   setFont(GLUT_BITMAP_HELVETICA_18);   
}


/**
 * Display/render the OpenGL window
 */
void display() 
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0, 0.0, 0.0);

   // Render the text
   drawString(0.0, 0.0, 0.0, "This is my text floating in space");

   glFlush();
}


/**
 * The reshape callback
 *
 * @param w   The width
 * @param h   The height
 */
void reshape(int w, int h)
{
   GLfloat  aspect;
   

   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   
   glMatrixMode(GL_PROJECTION);

   glLoadIdentity();

   if (w <= h)
   {      
      aspect = (GLfloat)h / (GLfloat)w;      
      glOrtho(-1.5, 1.5, -1.5*aspect, 1.5*aspect, -10.0, 10.0);
   }
   else
   {
      aspect = (GLfloat)w / (GLfloat)h;      
      glOrtho(-1.5*aspect, 1.5*aspect, -1.5, 1.5, -10.0, 10.0);
   }
}



/**
 * The entry point of the application.
 *
 * This function contains calls to GLUT.
 *
 * @param argc  The number of command line arguments
 * @param argv  The array of command line arguments
 * @return      A status code
 */
int main(int argc, char** argv) 
{
   glutInit(&argc, argv);

   window = createWindow("Bitmap Fonts", 640, 480, 0, 0);

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);   

   init();

   glutMainLoop();
}
