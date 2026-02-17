#ifndef SHADER_H
#define SHADER_H

#include <cstddef>
#include <cstdio>
#include <glad/glad.h>
#include <ostream>
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
				fShaderFile.open(fragmentPath);

				std::stringstream  vshaderStream, fShaderStream;

				vshaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();

				vShaderFile.close();
				fShaderFile.close();

				vertexSource = vshaderStream.str();
				fragmentSource = fShaderStream.str();

			}

			catch(std::ifstream::failure& e) {
				std::cout << "Shader file not succesfully read" << e.what() << std::endl;
			}

			const char* c_vertexSource = vertexSource.c_str();
			const char* c_fragmentSource = fragmentSource.c_str();

			unsigned int vertex, fragment;
			int success;

			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &c_vertexSource, NULL);	
			glCompileShader(vertex);
			checkCompileErrors(vertex);

			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &c_fragmentSource, NULL);	
			glCompileShader(fragment);
			checkCompileErrors(fragment);

			ID = glCreateProgram();
			glAttachShader(ID, vertex);
			glAttachShader(ID, fragment);
			glLinkProgram(ID);
			checkLinkErrors(ID);

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
			glUniform1f(glGetUniformLocation(ID, name.c_str()),  value);
		}
		void setVec4(const std::string &name, float values[4]){
			glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, values);
		}

	private:
		int checkCompileErrors(unsigned int shader){
			int success;
			char infolog[1024];

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if(!success){
				glGetShaderInfoLog(shader, 1024, NULL, infolog);
				std::cout << "ERROR: shader compilation failed\n" << infolog << std::endl;
			} else {
				std::cout << "Compilation succesful!" << std::endl;
			}
			return success;
		}

		int checkLinkErrors(unsigned int program){
			int success;
			char infolog[1024];
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success){
				glGetProgramInfoLog(program, 1024, NULL, infolog);
				std::cout << "ERROR: Linking failed\n" << infolog << std::endl;
			} else{
				std::cout << "Linking succesful!" << std::endl;
			}
			return success;
		}

};
#endif
