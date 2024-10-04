#include <GL/glut.h>

#include <random>

void Init() {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glPointSize(4.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

struct GLintPoint {
  GLint x, y;
};

int Random(const int min, const int max) {
  std::random_device device;
  std::default_random_engine engine{device()};
  std::uniform_int_distribution distr(min, max);
  return distr(engine);
}

void DrawDot(const GLint x, const GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
}

void Sierpinski() {
  constexpr GLintPoint t[3] = {{10, 10}, {300, 30}, {200, 300}};

  int index = Random(0, 2);
  auto [x, y] = t[index];
  DrawDot(x, y);
  for (int i = 0; i < 1000; i++) {
    index = Random(0, 2);
    x = (x + t[index].x) / 2;
    y = (y + t[index].y) / 2;
    DrawDot(x, y);
  }
  glFlush();
}

void Display() {
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
