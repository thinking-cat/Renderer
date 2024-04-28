#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputProcessor {
private:
	std::unordered_map<int, bool> pressedKey;
	GLFWwindow* window;
	unsigned int width, height;
	float Mouse_x, Mouse_y;
	float Click_x, Click_y;

public:
	InputProcessor(GLFWwindow* w);
	InputProcessor() :window(nullptr), width(800), height(600), Mouse_x(0), Mouse_y(0), Click_x(0), Click_y(0), pressedKey({}) {};
	void setWindow(GLFWwindow* w) { window = w; }
	void process();
	void clearSignal();
	bool getSignal(int KEY_NAME);
	void pressed(int KEY_NAME) { pressedKey[KEY_NAME] = true; }
	std::pair<float, float> getMouseLocation() { return std::pair<float, float>(Mouse_x, Mouse_y); }
	std::pair<float, float> getMouseClickLocation() { return std::pair<float, float>(Click_x, Click_y); }
	void setFramebufferSizeCallback(void(*func)(GLFWwindow* window, int width, int height)) { glfwSetFramebufferSizeCallback(window, func); }
	void setMouseClickCallback(void(*func)(GLFWwindow* window, int button, int action, int mods)) { glfwSetMouseButtonCallback(window, func); }
};