#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MS_PER_UPDATE 60

struct {
    GLfloat x;
    GLfloat y;
} typedef Point;

void error_callback(int error, const char* description);
void render();
void run(GLFWwindow*);
void update();
void processInput();
double getCurrentTime();