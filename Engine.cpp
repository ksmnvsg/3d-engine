#include "Engine.hpp"
Engine::Engine(const uint32_t width, const uint32_t height, const char* title):width(width), height(height) {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS only
    
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::runtime_error("Failed to create GLFW window\n");
    }
    glfwMakeContextCurrent(window); // create OpenGL context
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        std::runtime_error("Failed to initialize GLEW\n");
    }
    glfwSwapInterval(1); // set frame rate to v-sync
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

Engine::~Engine() noexcept {
    glfwTerminate();

}

void Engine::processInput(GLFWwindow* window) const {
    // Read through inputs
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Engine::run() {
    Shader shader("../shader.vert",  "../shader.frag");
    Buffer buffer(vertices);
    buffer.addAttribute(Attribute(3, sizeof(float), GL_FLOAT, false));
    buffer.addAttribute(Attribute(3, sizeof(float), GL_FLOAT, false));
    buffer.init();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3, 0.3, 0.3, 1);
        processInput(window);

        shader.use();
        shader.setVec4("ourColor", cos(glfwGetTime()) * sin(glfwGetTime()), cos(glfwGetTime()), sin(glfwGetTime()), 1);
        buffer.draw(3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}