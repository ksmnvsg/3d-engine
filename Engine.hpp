#include "config.hpp"
#include "Shader.hpp"
#include "Buffer.hpp"

class Engine {
public:
    Engine(const unsigned int width, const unsigned int height, const char* title);
    ~Engine();
    void run();
private:
    unsigned int width;
    unsigned int height;
    GLFWwindow* window;
    
    void processInput(GLFWwindow* window) const;
    static void framebufferSizeCallback(GLFWwindow*, int width, int height) { glViewport(0, 0, width, height); }

    std::vector<float> vertices = {
         // positions         // colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };
    std::vector<unsigned int> indices = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};  
};