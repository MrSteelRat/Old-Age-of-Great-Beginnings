#include <GL/glut.h>

#include <fstream>

void Init() {
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void DrawPolyLineFile(char const* file_name) {
  std::fstream in_stream;
  in_stream.open(file_name, std::ios::in);  // open the file
  if (in_stream.fail())
    return;
  glClear(GL_COLOR_BUFFER_BIT);  // clear the screen
  GLint num_polys, num_lines, x, y;
  in_stream >> num_polys;                // read the number of polylines
  for (int j = 0; j < num_polys; ++j) {  // read each polyline
    in_stream >> num_lines;
    glBegin(GL_LINE_STRIP);  // draw the next polyline
    for (int i = 0; i < num_lines; ++i) {
      in_stream >> x >> y;  // read the next x, y, pair
      glVertex2i(x, y);
    }
    glEnd();
  }
  glFlush();
  in_stream.close();
}

void Display() { DrawPolyLineFile("dino.dat"); }

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(100, 150);
  glutCreateWindow("Drawing polylines stored in a file");
  glutDisplayFunc(Display);
  Init();
  glutMainLoop();
}
