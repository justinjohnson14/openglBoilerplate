#include "main.h"
#include <GLFW/glfw3.h>

GLfloat vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

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

    run(window);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void render()
{
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //Draw step
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //Unbind the VAO and VBO (optional for safety)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void run(GLFWwindow* window)
{
    double previous = getCurrentTime();
    double lag = 0.0;
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        double current = getCurrentTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        processInput();

        while(lag >= MS_PER_UPDATE)
        {
            update();
            lag -= MS_PER_UPDATE;
        }

        render();

        glfwSwapBuffers(window);
    }
}

void update()
{

}

void processInput()
{
    glfwPollEvents();
}

double getCurrentTime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}