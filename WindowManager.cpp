#include "WindowManager.h"

WindowManager::WindowManager(int width, int height, const char* name) {
	// Initialize GLFW
	glfwInit();

	// Specify OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window and check if it worked
	window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	// We will use this to call the resize method as a callback
	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, WindowManager::resizeCallback);

	// Initialize glad, if this doesn't work we have no game and glViewport() will force a crash anyways
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Resize callback doesn't get called on creation, so we just force an update here
	updateViewport();
}

WindowManager::~WindowManager() {
	// Clean up GLFW
	glfwDestroyWindow(window);
	glfwTerminate();
}

void WindowManager::fullscreen(bool fullscreen) {
	// Changing window monitor counts as a resize, so it will run our resize callback
	if (fullscreen) {
		// Set fullscreen
		if (glfwGetWindowMonitor(window) != nullptr) {
			// The window is already fullscreen, don't waste time
			return;
		}

		// Store the location and size of the window for when we go back
		glfwGetWindowPos(window, &windowedX, &windowedY);
		glfwGetWindowSize(window, &windowedWidth, &windowedHeight);

		// Set fullscreen, we need the video mode and the monitor to go fullscreen on
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		GLFWmonitor** monitors;
		const GLFWvidmode* mode;
		int nmonitors;
		int monitorX;
		int monitorY;
		int monitorWidth;
		int monitorHeight;
		monitors = glfwGetMonitors(&nmonitors);
		int centerX = windowedX + windowedWidth / 2;
		int centerY = windowedY + windowedHeight / 2;

		// Go on a quest for the best monitor
		for (int i = 0; i < nmonitors; i++) {
			// Get monitor position data
			mode = glfwGetVideoMode(monitors[i]);
			glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);
			monitorWidth = mode->width;
			monitorHeight = mode->height;

			// Does this monitor contain window center?
			if (centerX > monitorX && centerY > monitorY && 
				centerX < monitorX + monitorWidth && centerY < monitorY + monitorHeight) {
				monitor = monitors[i];
				break;
			}
		}

		// Finally set fullscreen
		mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	} else {
		// Set windowed
		if (glfwGetWindowMonitor(window) == nullptr) {
			// The window is already windowed, don't waste time
			return;
		}

		// Just set it back to windowed mode, simple
		glfwSetWindowMonitor(window, nullptr, windowedX, windowedY, windowedWidth, windowedHeight, GLFW_DONT_CARE);
	}
}

bool WindowManager::update() {
	// Update the screen and return the window status
	glfwSwapBuffers(window);
	glfwPollEvents();
	return glfwWindowShouldClose(window);
}

int WindowManager::getWidth() {
	// Getter for width
	return width;
}

int WindowManager::getHeight() {
	// Getter for height
	return height;
}

void WindowManager::resizeCallback(GLFWwindow* window, int width, int height) {
	// Send this event to the class responsible for this window
	static_cast<WindowManager*>(glfwGetWindowUserPointer(window))->updateViewport();
}

void WindowManager::updateViewport() {
	// Get the window size and call glViewport()
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}