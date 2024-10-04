#include <jni.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

using namespace std;

// Global variables
int g_iWindowWidth = 1000, g_iWindowHeight = 800;
float g_fRotationRate = 50.0;
float g_fRotate1 = 0.0f;
double g_PreviousTicks, g_CurrentTicks;
GLFWwindow* g_Window;

// Function prototypes
void InitGLFW();
void DisplayGL();
void IdleGL();
void ReshapeGL(int w, int h);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

JNIEXPORT void JNICALL Java_OpenGLRenderer_init(JNIEnv *env, jobject obj) {
    InitGLFW();
}

JNIEXPORT void JNICALL Java_OpenGLRenderer_display(JNIEnv *env, jobject obj) {
    DisplayGL();
}

JNIEXPORT void JNICALL Java_OpenGLRenderer_idle(JNIEnv *env, jobject obj) {
    IdleGL();
}

JNIEXPORT void JNICALL Java_OpenGLRenderer_reshape(JNIEnv *env, jobject obj, jint w, jint h) {
    ReshapeGL(w, h);
}

JNIEXPORT void JNICALL Java_OpenGLRenderer_keyCallback(JNIEnv *env, jobject obj, jint key, jint action) {
    KeyCallback(g_Window, key, 0, action, 0);
}

void InitGLFW() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    g_Window = glfwCreateWindow(g_iWindowWidth, g_iWindowHeight, "OpenGL Template", nullptr, nullptr);
    if (!g_Window) {
        cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(g_Window);
    glfwSetKeyCallback(g_Window, KeyCallback);

    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialize GLEW" << endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
}

void DisplayGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -6.0f);
    glRotatef(g_fRotate1, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
    // Rendering the cube faces
    glEnd();

    glfwSwapBuffers(g_Window);
}

void IdleGL() {
    g_CurrentTicks = glfwGetTime();
    double deltaTicks = g_CurrentTicks - g_PreviousTicks;
    g_PreviousTicks = g_CurrentTicks;

    double deltaTime = deltaTicks;

    g_fRotate1 += (10 * g_fRotationRate * deltaTime);
    g_fRotate1 = fmod(g_fRotate1, 360.0f);
}

void ReshapeGL(int w, int h) {
    if (h == 0)
        h = 1;

    g_iWindowWidth = w;
    g_iWindowHeight = h;

    glViewport(0, 0, g_iWindowWidth, g_iWindowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, g_iWindowWidth / (GLdouble)g_iWindowHeight, 0.1, 100.0);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            case GLFW_KEY_1:
                break;
            case GLFW_KEY_2:
                break;
        }
    }
}
