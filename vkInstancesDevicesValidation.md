

== Vulkan instance
	- a vulkan instance is a reference to the vulkan context
	- defines the vulkan version, and its capabilities
	- all vulkan applications start by creating a vulkan instance
	- physical devices accessible to the instance are neumerated and 
		one or more are chosen
	- then the instance creates a logical device to handle the rest of the owkr
	- instances are rarely used beyond this setup

== What is a device?
	- two kinds: physical and logical device
	- physical device: the GPU itself. holds memory and queues to process pipeline,
		but cant be interacted with directly
	- logical device: an interface to the physical device. this will be used a lot,
		through logical device we set up everything on the gpu.

= Physical Device
	- Physical Device is a reference to the GPU itself
	- contains 2 important aspect: 
		- memory: when we want to allocate memory to resources, itm ust be handled
			through the physical device
		- queues: process commands submitted to GPU in FIFO order. different queues
			can be used for different types of command
	- PHysical devices are "retrieved" not created, like most Vulkan concepts
		(remember its a physical device that already exists)
	- Do this by enumerating over all devices and picking a suitable one.

= Queues
	- Physical devices can have multiple types of queues
	- types referred to as "Queue families"
	- a family can have more than one queue in it
	- Example queue family
		- Graphics: a family for processing graphics commands
		- Compute: a family for processing compute shaders (generic commands)
		- Transfer; a family for processing data transfer operations
	- Queue families can be and often are a combination of these
	- When we enumerate our physical devices, we check the device has the 
		queue families we require for the application

= Logical Devices 
	- Acts as an interface to the physical device
	- Will be referenced in a lot of vulkan function
	- most vulkan objects are creatd on the device, and we use the reference
		to the logical device to state which device to create those objects on
	- Creation is relatively simple:
		- Define queue families and number of queues you wish to assign to the 
			logical device from the physical device
		- Define all the device featuers you wish to enable (eg. geometry shader
			anisotrophy, wide lines, etc)
		- define extensions the device will use
		- in the past, you would define validation layers too. as of vulkan 1.1,
			this is deprecated

= Extensions
	- by default, vulkan has no understanding of what a window is
	- makes sense since vulkan is cross-platform and windows on different systems
		are defined differently
	- vulkan uses extensions to add window functionality
	- These extensions are so commonly used that they come pre packaged with vulkan
		anyways
	- can choose requred extensions manually but glfw library has funciton
		to choose them for us

= GLFW
	- originally designed for opengl but updated to work with vulkan
	- cross platform window creation and automatic interfacing
	- contains functions that identifies the required vulkan extensions
		for the host system, and returns a list

	glfwGetRequiredInstanceExtensions() // 

	- can then use this list to set up vulkan with the correct extensions

= Validation Layers
	- by default, vulkan does not validate code. will not report errors, and
		will simply crash if it encounters a fatal error
	- This is to avoid unnecessary overhead of error checking in release code
	- Must enable a validation "layer" to check
		- for example, VK_LAYER_LUNARG_swapchain validates SwapChain 
			functionality. 
		- VK_LAYER_LUNARG_standard_validation is a common all-round layer.
	- Layers are similar to extensions and are not built-in to the core
		Vulkan code. Must be acquired from third parties (however vulkan sdk
		we will acquire will already ahve some)
	- additionally the reporting of validation errors is not a core vulkan
		function and will require another extension to be applied
	- before vulkan 1.1, validation layers could be specified separately for
		an instance and a logical device.  this is no longer the case, now
		the instance validation layers cover both.