#include "config.hpp"

struct Attribute {
    Attribute(const unsigned int count, const unsigned int size, const GLenum type, const bool normalized);
    unsigned int count; // number of elements inside
    unsigned int size;  // size in bytes of one element
    GLenum type;        // type of elements inside
    bool normalized;    // to be normalized
};

class Buffer {
public:
    Buffer(std::vector<float> vertices, std::vector<unsigned int> indices = {});
    ~Buffer();

    void addAttribute(const Attribute attribute);
    void create() const;
    void draw(const unsigned int verticesToDraw, const unsigned int first = 0) const;
private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<Attribute> attributes;
    unsigned int VAO, VBO, EBO;
    unsigned int stride;
};