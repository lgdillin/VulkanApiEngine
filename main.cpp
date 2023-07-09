
#include <iostream>

// we can use vulkan through glfw
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include <vulkan/vulkan.h>

#include "GlfwWindow.hpp"
#include "VulkanRendererGlfw.hpp"
#include "GlfwGameRunner.hpp"


int main() {
	GlfwGameRunner game;
	if (game.initializeGame() == EXIT_FAILURE) return EXIT_FAILURE;
	game.run();

	return 0;
}