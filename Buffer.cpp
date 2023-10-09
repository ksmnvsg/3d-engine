#include "Buffer.hpp"

Attribute::Attribute(const unsigned int count, const unsigned int size, const GLenum type, const bool normalized):
count(count), size(size), type(type), normalized(normalized) {

}

Buffer::Buffer(std::vector<float> vertices, std::vector<unsigned int> indices):
vertices(vertices), indices(indices), stride(0) {
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

    if (!indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), indices.data(), GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Buffer::addAttribute(const Attribute attribute) {
    attributes.push_back(attribute);
    stride += attribute.count * attribute.size; 
}

void Buffer::create() const {
    size_t count = 0;
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    for (size_t i=0; i<attributes.size(); i++) {
        /*
        void glVertexAttribPointer(	GLuint index,   // index of the attribute
            GLint size,                             // number of elements inside attribute
            GLenum type,                            // type of elements inside attribute
            GLboolean normalized,                   // to normalize data or not
            GLsizei stride,                         // space in bytes between two consecutive vertex attributes
            const void * pointer);                  // data start offset in bytes inside the buffer

        */
        glVertexAttribPointer(i, attributes[i].count, attributes[i].type, attributes[i].normalized, 
            stride, (void*)(count));
        glEnableVertexAttribArray(i);
        count+=attributes[i].count * attributes[i].size;
    }
}

void Buffer::draw(const unsigned int verticesToDraw, const unsigned int first) const {
    glBindVertexArray(VAO);
    if (indices.empty()) {
        glDrawArrays(GL_TRIANGLES, first, verticesToDraw);
    } else {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
}