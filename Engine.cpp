#include "Engine.hpp"
Engine::Engine(const unsigned int width, const unsigned int height, const char* title):width(width), height(height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr<<"Failed to create GLFW window\n";
        glfwTerminate();
        EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr<<"Failed to initialize GLEW\n";
        glfwTerminate();
        EXIT_FAILURE;
    }
    glfwSwapInterval(1); // set frame rate to v-sync
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

Engine::~Engine() {
    glfwTerminate();

}

void Engine::processInput(GLFWwindow* window) const {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Engine::run() {
    Shader shader("../shader.vert",  "../shader.frag");
    Buffer buffer(vertices);
    Attribute position(3, sizeof(float), GL_FLOAT, false);
    buffer.addAttribute(position);
    buffer.create();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3, 0.3, 0.3, 1);
        processInput(window);

        shader.use();
        buffer.draw(3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}