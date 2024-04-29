#pragma once
#include <vector>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
double SCR_WIDTH_INVERSE = 1.0 / (double) SCR_WIDTH, SCR_HEIGHT_INVERSE = 1.0 / SCR_HEIGHT;
double xMouse = 0.0, yMouse = 0.0;
double xLastMouse = 0.0, yLastMouse = 0.0;
double xClick = 0.0, yClick = 0.0;
std::unordered_map<int, bool> pressedKey;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;

    SCR_WIDTH_INVERSE = 1.0 / (double)SCR_WIDTH;
    SCR_HEIGHT_INVERSE = 1.0 / (double)SCR_HEIGHT;
}

void mouse_position_callback(GLFWwindow* window, double xpos, double ypos) {
    std::cout << SCR_WIDTH_INVERSE << "," << SCR_HEIGHT_INVERSE << std::endl;

    xLastMouse = xMouse;
    yLastMouse = yMouse;
    xMouse = (xpos * SCR_WIDTH_INVERSE  - 0.5) * 2.0;
    yMouse = (0.5 - ypos * SCR_HEIGHT_INVERSE) * 2.0;
}


inline void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        pressedKey[GLFW_KEY_Q] = true;
}