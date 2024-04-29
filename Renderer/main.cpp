#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Config.h"
#include "Shader.h"
#include "Beizier.h"
#include "BSpline.h"
#include "InputProcessor.h"


extern unsigned int SCR_WIDTH, SCR_HEIGHT;
extern double xMouse, yMouse;
extern double xLastMouse, yLastMouse;
extern double xClick, yClick;
extern void framebuffer_size_callback(GLFWwindow* window, int width, int height);
extern void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
extern inline void processInput(GLFWwindow* window);


int main()
{
    //启动Opengl
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //视口
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    //设置响应函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_position_callback);

    Beizier b;
    BSpline bs;

    while (!glfwWindowShouldClose(window))
    {
        //input process

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            bs.addControlPoints(xClick, yClick);
        bs.Draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}




