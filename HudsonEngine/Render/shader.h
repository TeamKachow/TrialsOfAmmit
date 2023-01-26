#pragma once
#include "../Util/stdafx.h"

namespace Hudson::Render {
    class Shader
    {
        public:
            unsigned int ID;

            Shader() {}

            Shader& Use() {
                glUseProgram(this->ID);
                return *this;
            }

            void Compile(const char* vertexSource, const char* fragmentSource) {

                unsigned int vertShader, fragShader;

                // vertex Shader
                vertShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertShader, 1, &vertexSource, NULL);
                glCompileShader(vertShader);
                checkCompileErrors(vertShader, "VERTEX");

                // fragment Shader
                fragShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragShader, 1, &fragmentSource, NULL);
                glCompileShader(fragShader);
                checkCompileErrors(fragShader, "FRAGMENT");

                // _shader program
                this->ID = glCreateProgram();
                glAttachShader(this->ID, vertShader);
                glAttachShader(this->ID, fragShader);
                glLinkProgram(this->ID);
                checkCompileErrors(this->ID, "PROGRAM");

                // delete shaders
                glDeleteShader(vertShader);
                glDeleteShader(fragShader);
            }

            // utility functions for uniform functions - Brandon - This will likely need expanding to allow for further _shader support
            void setBool(const char* name, bool value) const
            {
                glUniform1i(glGetUniformLocation(ID, name), (int)value);
            }
            void SetFloat(const char* name, float value, bool useShader = false) {
                glUniform1f(glGetUniformLocation(ID, name), value);
            };
            void SetInteger(const char* name, int value, bool useShader = false) {
                glUniform1i(glGetUniformLocation(ID, name), value);
            };
            void SetFloat2(const char* name, float x, float y) {
                glUniform2f(glGetUniformLocation(this->ID, name), x, y);
            };
            void SetFloat2Array(const char* name, float value[2]) {
                glUniform2f(glGetUniformLocation(this->ID, name), value[0], value[1]);
            };
            void SetVector2(const char* name, const glm::vec2& value) {
                glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
            };
            void SetFloat3(const char* name, float x, float y, float z) {
                glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
            };
            void SetFloat3Array(const char* name, float value[3]) {
                glUniform3f(glGetUniformLocation(this->ID, name), value[0], value[1], value[2]);
            };
            void SetVector3(const char* name, const glm::vec3& value) {
                glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
            };
            void SetFloat4(const char* name, float x, float y, float z, float w) {
                glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
            };
            void SetFloat4Array(const char* name, float value[4]) {
                glUniform4f(glGetUniformLocation(this->ID, name), value[0], value[1], value[2], value[3]);
            };
            void SetVector4(const char* name, const glm::vec4& value) {
                glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
            };
            void SetMatrix4(const char* name, const glm::mat4& matrix) {
                glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
            };

        private:
            // Function for checking _shader compilation/linking errors.
            void checkCompileErrors(unsigned int shader, std::string type)
            {
                int success;
                char infoLog[1024];
                if (type != "PROGRAM")
                {
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                    if (!success)
                    {
                        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                        std::cout << "SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                    }
                }
                else
                {
                    glGetProgramiv(shader, GL_LINK_STATUS, &success);
                    if (!success)
                    {
                        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                        std::cout << "PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                    }
                }
            }
    };

}
