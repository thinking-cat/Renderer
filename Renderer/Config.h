#pragma once
#include <vector>
#include <unordered_set>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

unsigned int SCR_WIDTH = 1920, SCR_HEIGHT = 1080;
double SCR_WIDTH_INVERSE = 1.0 / (double) SCR_WIDTH, SCR_HEIGHT_INVERSE = 1.0 / SCR_HEIGHT;
double xMouse = 0.0, yMouse = 0.0;
double xLastMouse = 0.0, yLastMouse = 0.0;
double xClick = 0.0, yClick = 0.0;
bool clicked = false;
bool firstClick = true;
bool isDrawing = false;
std::unordered_set<int> pressedKey;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;

    SCR_WIDTH_INVERSE = 1.0 / (double)SCR_WIDTH;
    SCR_HEIGHT_INVERSE = 1.0 / (double)SCR_HEIGHT;
}

void mouse_position_callback(GLFWwindow* window, double xpos, double ypos) {
    xLastMouse = xMouse;
    yLastMouse = yMouse;
    xMouse = (xpos * SCR_WIDTH_INVERSE  - 0.5) * 2.0;
    yMouse = (0.5 - ypos * SCR_HEIGHT_INVERSE) * 2.0;
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {   
        glfwGetCursorPos(window, &xClick, &yClick);
        xClick = (xClick * SCR_WIDTH_INVERSE - 0.5) * 2.0;
        yClick = (0.5 - yClick * SCR_HEIGHT_INVERSE) * 2.0;
        firstClick = false;
        clicked = true;
        std::cout << xClick << "," << yClick << std::endl;
    }
}
inline void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        pressedKey.insert(GLFW_KEY_Q);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        ImVec2 mousePos = ImVec2((float)xpos, (float)ypos);

        isDrawing = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        isDrawing = false;
    }
}

inline void clearKey() {
    pressedKey = {};
}

class MyUI {
private:
    void createUI();
public:
    void render();
};


void MyUI::createUI() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
                // Handle open file action
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                // Handle save file action
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            // Add edit menu items here
            ImGui::EndMenu();
        }
        // Add more menus if needed

        ImGui::EndMainMenuBar();
    }
}

void MyUI::render() {
    createUI();
}