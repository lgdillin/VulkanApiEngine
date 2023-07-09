#pragma once

// we can use vulkan through glfw
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// project libraries
#include "VulkanRendererGlfw.hpp"
#include "GlfwWindow.hpp"

class GlfwGameRunner {
private:
	VulkanRendererGlfw vk;
	GlfwWindow glfwWindow;

public:
	GlfwGameRunner() {
		glfwWindow = GlfwWindow();
		vk = VulkanRendererGlfw();
	}

	~GlfwGameRunner() {
		// Clean up and exit
		glfwDestroyWindow(glfwWindow.getWindow());
		glfwTerminate();
	}

	int initializeGame() {
		glfwWindow.initialize();
		return vk.initialize(&glfwWindow);
	}

	void run() {
		// Simple loop
		while (!glfwWindowShouldClose(glfwWindow.getWindow())) {
			glfwPollEvents();
		}

		vk.cleanUp();
	}

};