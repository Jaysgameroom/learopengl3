#ifndef SHADER_H
#define SHADER_H

#include <cstdio>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader 
{
	public:
		unsigned int ID;

		Shader(const char* vertexPath, const char* fragmentPath) {

			std::string vertexSource, fragmentSource;
			std::ifstream vShaderFile, fShaderFile;

			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


			try	{
				vShaderFile.open(vertexPath);
				fShaderFile.open(vertexPath);

				std::stringstream  vshaderStream, fShaderStream;

				vshaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();

				vShaderFile.close();
				fShaderFile.close();

				vertexSource = vshaderStream.str();
				fragmentSource = fShaderStream.str();

			}

			catch(std::ifstream::failure e) {
				std::cout << "Shader file not succesfully read" << std::endl;
			}

			const char* c_vertexSource = vertexSource.c_str();
			const char* c_fragmentSource = fragmentSource.c_str();

			unsigned int vertex, fragment;
			int success;
			char infolog[512];

			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &c_vertexSource, NULL);	
			glCompileShader(vertex);


			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(vertex, 512, NULL, infolog);
				std::cout << "ERROR: vertex shader compilation failed\n" << infolog << std::endl;
			}

			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &c_fragmentSource, NULL);	
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(fragment, 512, NULL, infolog);
				std::cout << "ERROR: fragment shader compilation failed\n" << infolog << std::endl;
			}


			std::cout << "one" << std::endl;
			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);

			std::cout << "one" << std::endl;

			std::cout << "one" << std::endl;

			glDeleteShader(vertex);
			glDeleteShader(fragment);


		}

		void use() {
			glUseProgram(ID);
		};

		void setBool(const std::string &name, bool value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
		};
		void setInt(const std::string &name, int value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()),  value);
		}
		void setFloat(const std::string &name, float value) const
		{
			glUniform1i(glGetUniformLocation(ID, name.c_str()),  value);
		}




};
#endif
