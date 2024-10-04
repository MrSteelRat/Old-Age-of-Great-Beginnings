#include <GL/glut.h>
#include <stdlib.h>

void Init(void) {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glPointSize(1.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

struct GLintPoint {
  GLint x, y;
};

int Random(int m) { return rand() % m; }

void DrawDot(GLint x, GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void Sierpinski(void) {
  constexpr GLintPoint t[8] = {
    {106, 80},
    {106, 240},
    {106, 400},
    {319, 400},
    {532, 400},
    {532, 240},
    {532, 80},
    {319, 80}};

  int index = Random(8);
  struct GLintPoint point = t[index];
  DrawDot(point.x, point.y);
  for (int i = 0; i < 1000000; i++) {
    index = Random(8);
    point.x = (point.x + 2*t[index].x) / 3;
    point.y = (point.y + 2*t[index].y) / 3;
    DrawDot(point.x, point.y);
  }
  glFlush();
}

void Display(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  Sierpinski();
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Sierpinski triangle");
  glutDisplayFunc(Display);
  Init();
  glutMainLoop();
}
