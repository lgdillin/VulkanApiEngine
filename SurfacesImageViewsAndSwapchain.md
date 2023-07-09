

- Displaying images to a window is not native to VUlkan
- this also includes swapping out images like in a double/triple buffer
- To do this we need two things
    - swapchain: complex object that handles retrieval and updating
        of images being displayed, or yet to be displayed
    - Surface: an interface between the window and an image in the
        swapchain

= Surface
    - will act as an interface between the window created by GLFW
        and a vulkan defined image in the swapchain
    - surface will need to be created specifically for the window of
        the system we're using
    - could define this manually but would make things complex when 
        going cross platform
    - fortunately, GLFW has a built-in function that returns an adequate
        surface for the current system being used

    glfwCreateWindowSurface(...)

= The "presentation Queue"
    - in order to present a new swapchain image to our surface,
        we need a queue that can handle present operations
    - this is not really a type of queue, but a feature that some have
    - graphics queues usually have the required feature
    - this means our graphics queue and presentation queue wil
        usually be the same queue

= Swapchain
    - Another extension, so we will need to check compatibility
    - the swapchain is a group of images that can be drawn to
        and presented
    - the object is set up so it can be queried to get a new image
        to be drawn to, and then presented
    - This requires a lot of synchornization
    - the swapchain has a few setup requirements

= creating the swapchain
    - A swapchain has 3 major parts
        - Surface capabilities: what the surface is capable of handling
            (eg. image size) memory limitations
        - Surface format: the format of the surface the swapchain will
            present to (eg. RGB, RGBA, etc.)
        - presentation mode: the order and timing of images being
            presented to the surface
    - The swapchain settings are largely based on the surface. we query
        the surface for these parts to ensure compatibility
    - The "presentation mode" can be hard to understand, so lets explore
        it in more detail

= Presentation Mode
    - presentation modes are the order and timing of images being presented
        to the surface
    - there are 4 presentaiton modes and 2 of them are considered undesirable
        due to the risk of introducing "tearing"
    - At any one time, there will be one image present at the surface that is being
        draw to the screen

    - First some information about how monitors work
        - monitors start at top left pixel, and draw to screen row by row
        - when the image completes, the screen is then cleared to start drawing
            again. the period of time AFTER this clear, and BEFORE it starts
            drawing again, is known as a "Vertical blank interval" or
            simply a "Vertical Blank". this is usually the best time to
            replace the surface image

    VK_PRESENT_MODE_IMMEDIATE_KHR

    - In the above mode, the surface image will be replaced immediately
        after the next image to be displayed has finished rendering.
    - This can be an issue. our surface may only be halfway through drawing
        to the screen when we replace it, causing the second half to be a 
        different image. this results in tearing

    VK_PRESENT_MODE_MAILBOX_KHR

    - In "mailbox mode" images ready to present are added to a queue 
        of size 1. the surface uses this image only at a vertical blank
        to avoid tearing
    - if a new image is sent to the queue to be presented, whatever is
        currently in the queue is discarded and becomes a vacant image
        ready to be drawn to again

    VK_PRESENT_MODE_FIFO_KHR

    - Images ready to present are added to a queue of a certain size.
        they are removed one at a time at each vertical blank, so there
        is no tearing.
    - if a new image is sent to the queue to be presented, but queue is
        full, the program will wait
    - if the queue is empty when the next vertical blank occurs, it will
        redraw the image currently held and check again at the next
        vertical blank

    VK_PRESENT_MODE_FIFO_RELAXED_KHR

    - This mode works the same as FIFO mode, except for the situation
        where there are no images on the queue during a vertical blank
    - if the presentation queue is empty during a vertical blank, it
        will start acting like immediate mode
    - The next image placed on to the presentation queue will no longer
        wait for a vertical blank. it will instead be passed straight
        to the surface, like in immediate mode. this will cause tearing.
    - Ater it will return to FIFO mode (wait for the vertical 
        blank to draw again)

= Images and Image views
    - When the swapchain is created, it will automatically create a set of 
        images to be used by the swapchain
    - Since we will be drawing to them, we need access to them. to do this,
        the swapchain can be queried and an arrayu of the images can be
        returned
    - however, these images cant be used directly since they are jsut
        the raw image
    - an "imageView" type can be created to interface with an image
    - an imageView simply describes how to read an image (eg. 2D or 3D
        addresses, format, etc.) and what part of the image to read
        (color channels, mip levels, etc)
    - later on, we will use these imageview when drawing to and presenting
        our images.