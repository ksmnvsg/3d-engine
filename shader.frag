#version 410 core
out vec4 fragColor;

// in vec3 ourColor;
uniform vec4 ourColor;
void main() {
    // fragColor = vec4(ourColor, 1);
    fragColor = ourColor;
}
