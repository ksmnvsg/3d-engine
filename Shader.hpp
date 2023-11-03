#pragma once
#include "config.hpp"
class Shader {
public:
    explicit Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader() noexcept;
    Shader& operator=(const Shader&) = delete;
    Shader(const Shader&) = delete;

    void use() const;
    void setBool(const std::string& name, const bool value) const;
    void setInt(const std::string& name, const int value) const;
    void setFloat(const std::string& name, const float value) const;
    void setVec4(const std::string& name, const float v1, const float v2, const float v3, const float v4) const;
private:
    uint32_t programID;
    void checkShader(const uint32_t shader) const;
    void checkProgram(const uint32_t programID) const;
};