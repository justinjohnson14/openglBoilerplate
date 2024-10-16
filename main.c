#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void error_callback(int error, const char* description)
{

}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int main()
{
    if(!glfwInit())
    {
        fprintf(stderr, "Error initializing GLFW!\n");
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(800, 800, "New Window", NULL, NULL);
    if(!window)
    {
        fprintf(stderr, "Error creating window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Error initializing GLEW\n");
        glfwTerminate();
        return -1;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while(!glfwWindowShouldClose(window))
    {
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}