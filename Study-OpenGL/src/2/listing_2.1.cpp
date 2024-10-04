#include <GL/glut.h>

void Display() 
{ 
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}
void Reshape(int width, int height) {}
void Mouse(int button, int state, int x, int y) {}
void Keyboard(unsigned char key, int x, int y) {}

void main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutCreateWindow("");
  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutMouseFunc(Mouse);
  glutKeyboardFunc(Keyboard);
  glutMainLoop();
}