#pragma once
#include "config.hpp"

struct Attribute {
    explicit Attribute(const uint32_t count, const uint32_t size, const GLenum type, const bool normalized);
    const uint32_t count;     // number of elements inside
    const uint32_t size;      // size in bytes of one element
    const GLenum type;        // type of elements inside
    const bool normalized;    // to be normalized
};

class Buffer {
public:
    explicit Buffer(const std::vector<float>& vertices, const std::vector<uint32_t>& indices = {});
    ~Buffer() noexcept;
    void addAttribute(const Attribute& attribute); // add an attribute to split vertex data
    void init() const; // initialize with attributes set
    void draw(const uint32_t verticesToDraw, const uint32_t first = 0) const;
private:
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    std::vector<Attribute> attributes;
    uint32_t VAO, VBO, EBO;
    uint32_t stride;
};