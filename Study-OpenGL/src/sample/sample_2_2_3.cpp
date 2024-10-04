#include <GL/glut.h>

#include <cmath>

#define PI 3.14159265358979323846

GLdouble a, b, c, d;

void Init() 
{
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glPointSize(2.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640, 0.0, 480);
  a = 640 / 4.0;
  b = 0.0;
  c = d = 480 / 2.0;
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_POINTS);

  GLdouble x = 0.0;
  while (x < 4.0) {
    const GLdouble func = exp(-x) * cos(2 * PI * x);
    glVertex2d(a * x + b, c * func + d);
    x += 0.005;
  }

  glEnd();
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Dot Plots");
  glutDisplayFunc(Display);
  Init();
  glutMainLoop();
}
