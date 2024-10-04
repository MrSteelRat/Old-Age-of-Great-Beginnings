#include <GL/glut.h>

constexpr int kScreenWidth = 640;
constexpr int kScreenHeight = 480;

void Init() {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glPointSize(4.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, kScreenWidth, 0.0, kScreenHeight);

  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void Display() {}

struct GLintPoint {
  GLint x, y;
};

#define NUM 20
static GLintPoint list[NUM];
static int last = -1;

void Mouse(const int button, const int state, const int x, const int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && last < NUM - 1) {
    list[++last].x = x;
    list[last].y = kScreenHeight - y;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= last; i++) {
      glVertex2i(list[i].x, list[i].y);
    }
    glEnd();
    glFlush();
  } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    last = -1;
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(kScreenWidth, kScreenHeight);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("A polyline drawer based on mouse clicks");
  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  Init();
  glutMainLoop();
}
