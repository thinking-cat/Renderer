#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Shader.h"
#include "Beizier.h"
#include "BSpline.h"
#include "InputProcessor.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
inline GLFWwindow* InitGLFW();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
InputProcessor input;


int main()
{
    GLFWwindow* window = InitGLFW();

    if (window == nullptr)
        return -1;

    input.setWindow(window);
    input.setFramebufferSizeCallback(framebuffer_size_callback);
    Beizier b;
    BSpline bs;

    while (!glfwWindowShouldClose(window))
    {
        //input process
        input.process();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (input.getSignal(GLFW_MOUSE_BUTTON_LEFT)) {
            std::pair<float, float> ClickLocation = input.getMouseClickLocation();
            float xpos, ypos;
            xpos = (ClickLocation.first / SCR_WIDTH - 0.5) * 2;
            ypos = (0.5 - ClickLocation.second / SCR_HEIGHT) * 2;
            bs.addControlPoints(xpos, ypos);
        }
        bs.Draw();
        if (input.getSignal(GLFW_KEY_Q)) 
            bs.clear();

        input.clearSignal();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

inline GLFWwindow* InitGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    return window;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}