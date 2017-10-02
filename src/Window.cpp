
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include <iostream>
#include <cmath>

#include "Window.h"
#include "Camera.h"

bool Window::isGlfwInit = false;
bool Window::isGladInit = false;

extern float deltaTime;
extern Camera* cam;

Window::Window() 
: Window(800, 600, "A Window") {}


Window::Window(const unsigned width, const signed height)
: Window(width, height, "A Window") {}


Window::Window(const unsigned width, const signed height, const char* name) 
: mWidth(width), mHeight(height) {
	Window::initGlfw();
	
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	
	// Create our Window
	mWindow = glfwCreateWindow(mWidth = mode->width, mHeight = mode->height, name, glfwGetPrimaryMonitor(), NULL);
    if (mWindow == NULL) {
        std::cerr << "ERROR::WINDOW::WINDOW_CREATION_FAILED" << std::endl;
        mSuccess = false;
		return;
    }
	
    setContextCurrent();
	
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
	
	// https://stackoverflow.com/a/28660673
	glfwSetWindowUserPointer(mWindow, this); // set user pointer to this class
    glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCallback); // so we can get the window the call back applies to
	glfwSetCursorPosCallback(mWindow, mouseCallback);
	glfwSetScrollCallback(mWindow, scrollCallback); 
	
	Window::initGlad();
	
	glEnable(GL_DEPTH_TEST); 
	
	glfwGetCursorPos(mWindow, &mMousePos.x, &mMousePos.y);
	
	mSuccess = true;
}


GLFWwindow* Window::getRaw() {
	return mWindow;
}


void Window::processInput() {
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);
	
	uint16_t bit = 0;
    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
        bit |= Z_POS;
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
        bit |= Z_NEG;
    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
        bit |= X_NEG;
    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
        bit |= X_POS;
	
	cam->move(bit, deltaTime);
}


void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Window::setClearColor(std::array<float, 4> color) {
	glClearColor(color[0], color[1], color[2], color[3]);	
	clearColor = color;
}


void Window::initGlfw() {
	if (!Window::isGlfwInit) {
		// Configure GL to create window with correct version info
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwInit();
		Window::isGlfwInit = true;
	}
}


void Window::initGlad() {
	if (!Window::isGladInit) {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "ERROR::WINDOW::INIT_GLAD_FAILED" << std::endl;
			return;
		}
		Window::isGladInit = true;
	}
}


void Window::setContextCurrent() {
	glfwMakeContextCurrent(mWindow);
}


bool Window::isValid() {
	return mSuccess;
}


void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	Window* currWin = static_cast<Window*>(glfwGetWindowUserPointer(window));
	currWin->mWidth = width;
	currWin->mHeight = height;
	glViewport(0, 0, width, height);
}


void Window::mouseCallback(GLFWwindow* window, double x, double y) {
	Window* currWin = static_cast<Window*>(glfwGetWindowUserPointer(window));
	
	float dx = x - currWin->mMousePos.x;
    float dy = currWin->mMousePos.y - y;
	
    currWin->mMousePos.x = x;
    currWin->mMousePos.y = y;

	cam->look(dx, dy);
}


void Window::scrollCallback(GLFWwindow* window, double x, double y) {
	cam->zoom(y);
}


bool Window::getShouldClose() {
	return glfwWindowShouldClose(mWindow);
}


void Window::swapBuffers() {
	glfwSwapBuffers(mWindow);
}