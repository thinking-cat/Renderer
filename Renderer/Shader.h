#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


class Shader {
private:
	unsigned int ID;
	std::vector<unsigned int> shaderHandle;
public:
	//Shader() ����һ���յ� *Shader����*
	Shader() : ID(0) {}

	//Shader(const char* path, GLenum type) 
	// ͨ������*shader�ļ�*·��path���Լ���ָ����shader����type�����һ��shader���� *Shader����*
	Shader(const char* path, GLenum type) {

		std::string shaderContext;
		std::ifstream shaderFile(path);

		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		if (!shaderFile.is_open())
			std::cout << "ERROR::SHADER::FILE::FILE_OPEN failed to open the file!\n" << std::endl;
		try {
			std::stringstream ss;
			ss << shaderFile.rdbuf();
			shaderFile.close();
			shaderContext = ss.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE::READ_ERROR file not successfully read!\n" << std::endl;
		}

		const char* context = shaderContext.c_str();
		unsigned int handle = glCreateShader(type);
		glShaderSource(handle, 1, &context, NULL);
		shaderHandle.push_back(handle);

		this->ID = 0;
	}

	//addShader(const char* path, GLenum type) 
	// ͨ������*shader�ļ�*·��path���Լ���ָ����shader����type�����һ��shader���� *Shader����*
	void addShader(const char* path, GLenum type) {
		std::string shaderContext;
		std::ifstream shaderFile(path);

		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		if (!shaderFile.is_open())
			std::cout << "ERROR::SHADER::FILE::FILE_OPEN failed to open the file!\n" << std::endl;
		try {
			std::stringstream ss;
			ss << shaderFile.rdbuf();
			shaderFile.close();
			shaderContext = ss.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE::READ_ERROR file not successfully read!\n" << std::endl;
		}

		const char* context = shaderContext.c_str();
		unsigned int handle = glCreateShader(type);
		glShaderSource(handle, 1, &context, NULL);
		shaderHandle.push_back(handle);
	}

	//����*Shader����*
	//�������*����*��*����*�����֣�������ɹ����򷵻س���ı��*ID*
	unsigned int Compile() {
		int success = 1;
		for (int i = 0; i < shaderHandle.size(); i++) {
			glCompileShader(shaderHandle[i]);
			char infoLog[512];
			glGetShaderiv(shaderHandle[i], GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shaderHandle[i], 512, NULL, infoLog);
				std::cout << "ERROE::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
				break;
			}
		}

		//����ʧ���򷵻�
		if (!success)
			return success;

		//����
		ID = glCreateProgram();
		for (int i = 0; i < shaderHandle.size(); i++)
			glAttachShader(ID, shaderHandle[i]);
		glLinkProgram(ID);

		char infoLog[512];
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// As shaders are linked to the program,
		// so we delete shaders, and that will release the buffer
		for (int i = 0; i < shaderHandle.size(); i++)
			glDeleteShader(shaderHandle[i]);

		return this->ID;
	}

	//����*Shader����*�е�Bool��Uniform����
	void setBool(const std::string& name, bool val) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (GLint)val);
	}
	//����*Shader����*�е�Float��Uniform����
	void setFloat(const std::string& name, float val) {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
	}
	//����*Shader����*�е�Int��Uniform����
	void setInt(const std::string& name, bool val) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
	}

	//���*Shader����*ID
	unsigned int getID() { return ID; }
};