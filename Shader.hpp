#include "config.hpp"
class Shader {
public:
    Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath);
    ~Shader();

    void use() const;
    void setBool(const std::string name, const bool value) const;
    void setInt(const std::string name, const int value) const;
    void setFloat(const std::string name, const float value) const;
    void setVec4(const std::string name, const float v1, const float v2, const float v3, const float v4) const;
private:
    unsigned int programID;
    void checkShader(const unsigned int shader) const;
    void checkProgram(const unsigned int programID) const;
};