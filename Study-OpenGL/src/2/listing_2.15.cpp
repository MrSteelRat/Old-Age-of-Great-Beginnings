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

void Mouse(const int button, const int state, const int x, const int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    static GLintPoint corner[2];
    static int num_corners = 0;  // initial value is 0
    corner[num_corners].x = x;
    corner[num_corners].y = kScreenHeight - y;  // flip y coordinate
    num_corners++;                              // have another point
    if (num_corners == 2) {
      glRecti(corner[0].x, corner[0].y, corner[1].x, corner[1].y);
      num_corners = 0;  // back to 0 corners
    }
  } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    glClear(GL_COLOR_BUFFER_BIT);  // clear the window
  }
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(kScreenWidth, kScreenHeight);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Specifying a rectangle with the mouse");
  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  Init();
  glutMainLoop();
}
