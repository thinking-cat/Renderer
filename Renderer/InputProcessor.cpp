#include "InputProcessor.h"

InputProcessor::InputProcessor(GLFWwindow* window) {
    this->window = window;
    width = 800;
    height = 600;
    Mouse_x = 0;
    Mouse_y = 0;
    Click_x = 0;
    Click_y = 0;
    pressedKey = {};
}

//未实现鼠标点击事件
void InputProcessor::process() {
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        pressedKey[GLFW_KEY_Q] = true;
    if (glfwGetKey(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        pressedKey[GLFW_MOUSE_BUTTON_LEFT] = true;
}

bool InputProcessor::getSignal(int KEY_NAME) {
    if (pressedKey.find(KEY_NAME) == pressedKey.end())
        return false;
    return pressedKey[KEY_NAME];
}

void InputProcessor::clearSignal() {
    if (pressedKey.size() == 0)
        return;
    for (std::unordered_map<int, bool>::iterator itr = pressedKey.begin(); itr != pressedKey.end(); itr++)
        (*itr).second = false;
}