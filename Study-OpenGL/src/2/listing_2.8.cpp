#include <GL/glut.h>

#include <cmath>

constexpr int kScreenWidth = 640;
constexpr int kScreenHeight = 480;
#define PI 3.14159265358979323846

GLdouble a, b, c, d;

void Init() {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(4.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, kScreenWidth, 0.0, kScreenHeight);
  a = kScreenWidth / 300.0;
  b = 0;
  c = kScreenHeight / 424.0;
  d = -100 * c;
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINE_STRIP);

  GLdouble x = 0.0;
  while (x <= 300) {
    const GLdouble func = 300 - 100 * cos(2 * PI * x / 100) +
                          30 * cos(4 * PI * x / 100) +
                          6 * cos(6 * PI * x / 100);
    glVertex2d(a * x + b, c * func + d);
    x += 3;
  }

  glEnd();
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(kScreenWidth, kScreenHeight);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Drawing Line Graphs");
  glutDisplayFunc(Display);
  Init();
  glutMainLoop();
}
