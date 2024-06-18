
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void checkCompileErrors(GLuint shader, std::string type);
    void use() const;

    void setMat4(const std::string& name, const glm::mat4& mat) const;

    ~Shader();

};

#endif