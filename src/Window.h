
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>

class Window {
public:
	static bool isGlfwInit;
	static bool isGladInit;

	Window();
	Window(const unsigned width, const signed height);
	Window(const unsigned width, const signed height, const char* name);
	
	static void initGlfw();
	static void initGlad();
	
	bool getShouldClose();
	void swapBuffers();
	
	bool isValid();
	GLFWwindow* getRaw();
	
	void clear();
	void setClearColor(std::array<float, 4> color);
	
	void processInput();
	
	void setContextCurrent();
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void mouseCallback(GLFWwindow* window, double x, double y);
	static void scrollCallback(GLFWwindow* window, double x, double y);
	
private:
	GLFWwindow* mWindow;
	unsigned mWidth;
	unsigned mHeight;
	bool mSuccess;
	struct { double x; double y; } mMousePos;
	std::array<float, 4> clearColor;
	
};