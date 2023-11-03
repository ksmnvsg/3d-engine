#pragma once
#include "config.hpp"
#include "Shader.hpp"
#include "Buffer.hpp"

class Engine {
public:
    explicit Engine(const uint32_t width, const uint32_t height, const char* title);
    ~Engine() noexcept;
    Engine(const Engine&) = delete; // to maintain RAII
    Engine& operator=(const Engine&) = delete;

    void run();
private:
    [[maybe_unused]] const uint32_t width;
    [[maybe_unused]] const uint32_t height;
    GLFWwindow* window;
    
    void processInput(GLFWwindow* window) const;
    static inline void framebufferSizeCallback(GLFWwindow*, int width, int height) { glViewport(0, 0, width, height); }

    std::vector<float> vertices = {
         // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };
    std::vector<uint32_t> indices = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    std::vector<float> texCoords = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };  
};