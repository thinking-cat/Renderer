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
	//Shader() 创建一个空的 *Shader程序*
	Shader() : ID(0) {}

	//Shader(const char* path, GLenum type) 
	// 通过所给*shader文件*路径path，以及所指定的shader类型type，添加一个shader进入 *Shader程序*
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
	// 通过所给*shader文件*路径path，以及所指定的shader类型type，添加一个shader进入 *Shader程序*
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

	//编译*Shader程序*
	//编译包括*编译*和*链接*两部分，如果都成功，则返回程序的编号*ID*
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

		//编译失败则返回
		if (!success)
			return success;

		//链接
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

	//设置*Shader程序*中的Bool型Uniform变量
	void setBool(const std::string& name, bool val) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (GLint)val);
	}
	//设置*Shader程序*中的Float型Uniform变量
	void setFloat(const std::string& name, float val) {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
	}
	//设置*Shader程序*中的Int型Uniform变量
	void setInt(const std::string& name, bool val) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
	}

	//获得*Shader程序*ID
	unsigned int getID() { return ID; }
};