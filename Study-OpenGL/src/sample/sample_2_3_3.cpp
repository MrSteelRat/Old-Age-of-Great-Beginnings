#include <GL/glut.h>

void Init() {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void HardwiredHouse() {
  glBegin(GL_LINE_LOOP);
  glVertex2i(40, 40);  // draw the shell of house
  glVertex2i(40, 90);
  glVertex2i(70, 120);
  glVertex2i(100, 90);
  glVertex2i(100, 40);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glVertex2i(50, 100);  // draw the chimney
  glVertex2i(50, 120);
  glVertex2i(60, 120);
  glVertex2i(60, 110);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glVertex2i(50, 40);  // draw the door
  glVertex2i(50, 75);
  glVertex2i(65, 75);
  glVertex2i(65, 40);
  glEnd();
  glBegin(GL_LINE_LOOP);
  glVertex2i(75, 70);  // draw the window
  glVertex2i(75, 80);
  glVertex2i(85, 80);
  glVertex2i(85, 70);
  glEnd();
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT);
  HardwiredHouse();
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(480, 320);
  glutInitWindowPosition(200, 300);
  glutCreateWindow("Drawing a house with \"hard-wired\" dimensions");
  glutDisplayFunc(Display);
  Init();
  glutMainLoop();
}