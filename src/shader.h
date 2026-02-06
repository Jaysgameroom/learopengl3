#ifndef SHADER_H
#define SHADER_H

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

			const char* vShaderCode = vertexSource.c_str();
			const char* fShaderCode = fragmentSource.c_str();
		}



		void use();

		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;

	


};
#endif
