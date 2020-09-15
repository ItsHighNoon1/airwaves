#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class WindowManager {
	// Responsible for the window 
public:
	WindowManager(int width, int height, const char* name);
	~WindowManager();
	void fullscreen(bool fullscreen);
	bool update();
	int getWidth();
	int getHeight();
private:
	static void resizeCallback(GLFWwindow* window, int width, int height);
	void updateViewport();
	GLFWmonitor* bestMonitor();

	GLFWwindow* window;
	int width;
	int height;
	int windowedX;
	int windowedY;
	int windowedWidth;
	int windowedHeight;
};