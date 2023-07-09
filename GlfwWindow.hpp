#pragma once

// we can use vulkan through glfw
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class GlfwWindow {
public:
	GlfwWindow() {
		m_glfwWindow = nullptr;
		m_extensionCount = 0;
		m_windowTitle = "Test Window";
	}

	GLFWwindow *getWindow() { return m_glfwWindow; }

	void initialize() {
		glfwInit();

		// GLFW_NO_API designates Vulkan as the API
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		m_glfwWindow = glfwCreateWindow(
			800,
			600,
			m_windowTitle.c_str(),
			nullptr,
			nullptr
		);

		m_extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(
			nullptr,
			&m_extensionCount,
			nullptr
		);

		std::cout << "Extension count: " << m_extensionCount << std::endl;
	}

private:
	GLFWwindow *m_glfwWindow;
	std::string m_windowTitle;

	uint32_t m_extensionCount;
};