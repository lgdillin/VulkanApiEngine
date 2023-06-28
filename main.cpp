
#include <iostream>

// we can use vulkan through glfw
//#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include <vulkan/vulkan.h>

#include "GlfwWindow.hpp"


int main() {
	
	GlfwWindow glfwWindow;
	glfwWindow.initialize();
	

	// Simple loop
	while (!glfwWindowShouldClose(glfwWindow.getWindow())) {
		glfwPollEvents();
	}

	// Clean up and exit
	glfwDestroyWindow(glfwWindow.getWindow());
	glfwTerminate();
	return 0;
}