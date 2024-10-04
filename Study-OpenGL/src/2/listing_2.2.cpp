#include <GL/glut.h>

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void Reshape(int width, int height) {}

void Mouse(int button, int state, int x, int y) {}

void Keyboard(unsigned char key, int x, int y) {}

void main(int argc, char** argv) 
{
  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("My first attempt");
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutMouseFunc(Mouse);
  glutKeyboardFunc(Keyboard);
  //Init();
  glutMainLoop();
}