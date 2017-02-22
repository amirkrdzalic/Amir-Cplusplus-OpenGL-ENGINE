#include "ShaderNova.h"
#include <fstream>
#include <iostream>
#include <vector>

namespace Amir3DEngine
{
	ShaderNova::ShaderNova() :
		m_numAttributes(0),
		m_program(0),
		m_vertexShader(0),
		m_fragShader(0)
	{

	}

	bool ShaderNova::readFileToBuffer(std::string filePath, std::string & buffer)
	{
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail())
		{
			perror(filePath.c_str());
			return false;
		}

		file.seekg(0, std::ios::end);
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);

		fileSize -= file.tellg();

		buffer.resize(fileSize);

		file.read((char *)&(buffer[0]), fileSize);
		file.close();

		return true;
	}

	void ShaderNova::programSetup(std::vector<SHADER_TYPE> types)
	{
		m_program = glCreateProgram();

		for (int i = 0; i < types.size(); i++)
		{
			switch (types[i])
			{
			case SHADER_TYPE::VERTEX:
				m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
				break;
			case SHADER_TYPE::FRAGMENT:
				m_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			case SHADER_TYPE::GEOMETRY:
				m_geoShader = glCreateShader(GL_GEOMETRY_SHADER);
				break;
			default:
				break;
			}
		}
	}


	void ShaderNova::compileShaders(const char * source, GLuint _id, const std::string & shaderName)
	{
		glShaderSource(_id, 1, &source, nullptr);

		glCompileShader(_id);

		GLint success = 0;
		glGetShaderiv(_id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(_id, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(_id); 

			std::printf("%s\n", &errorLog[0]);

		}
	}

	void ShaderNova::compileShadersFromFile(const std::vector<std::string> & shaderFilePaths)
	{
		std::vector<SHADER_TYPE> type;

		int i = 0;

		switch (shaderFilePaths.size())
		{
		case 2:
			ShaderNova::readFileToBuffer(shaderFilePaths[i], vertSource);
			ShaderNova::readFileToBuffer(shaderFilePaths[i + 1], fragSource);

			type.push_back(SHADER_TYPE::VERTEX);
			type.push_back(SHADER_TYPE::FRAGMENT);

			programSetup(type);

			compileShaders(vertSource.c_str(), m_vertexShader, shaderFilePaths[i]);
			compileShaders(fragSource.c_str(), m_fragShader, shaderFilePaths[i + 1]);
			break;
		case 3:
			ShaderNova::readFileToBuffer(shaderFilePaths[i], vertSource);
			ShaderNova::readFileToBuffer(shaderFilePaths[i + 1], fragSource);
			ShaderNova::readFileToBuffer(shaderFilePaths[i + 2], geometrySource);

			type.push_back(SHADER_TYPE::VERTEX);
			type.push_back(SHADER_TYPE::FRAGMENT);
			type.push_back(SHADER_TYPE::GEOMETRY);

			programSetup(type);

			compileShaders(vertSource.c_str(), m_vertexShader, shaderFilePaths[i]);
			compileShaders(fragSource.c_str(), m_fragShader, shaderFilePaths[i + 1]);
			compileShaders(geometrySource.c_str(), m_geoShader, shaderFilePaths[i + 2]);
			break;
		default:
			break;
		}

		vertSource = "";
		fragSource = "";
		geometrySource = "";
	}

	void ShaderNova::linkShaders()
	{
		
		glAttachShader(m_program, m_vertexShader);
		glAttachShader(m_program, m_fragShader);

	
		glLinkProgram(m_program);

		
		GLint isLinked = 0;
		glGetProgramiv(m_program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(m_program, maxLength, &maxLength, &errorLog[0]);

		
			glDeleteProgram(m_program);
		
			glDeleteShader(m_vertexShader);
			glDeleteShader(m_fragShader);

			
			std::printf("%s\n", &errorLog[0]);
		}

		
		glDetachShader(m_program, m_vertexShader);
		glDetachShader(m_program, m_fragShader);

		
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragShader);

		glGetError();

		std::cout << glGetError() << " no errors with GL GET ERROR for if it is 0" << std::endl;
	}

	void ShaderNova::addAttributes(const std::string & attributeName)
	{
		glBindAttribLocation(m_program, m_numAttributes++, attributeName.c_str());

		std::cout << attributeName << " loaded." << std::endl;
	}

	GLint ShaderNova::getUniformLocation(const std::string & uniformName)
	{
		GLint location = glGetUniformLocation(m_program, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
			std::cout << "location = GL_INVALID_INDEX  " + uniformName << std::endl;
	
		return location;
	}

	void ShaderNova::startUse()
	{
		glUseProgram(m_program);
		for (int i = 0; i < m_numAttributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void ShaderNova::stopUse()
	{
		glUseProgram(0);
		for (int i = 0; i < m_numAttributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	void ShaderNova::dispose()
	{
		if (m_program)
		{
			glDeleteProgram(m_program);
		}
	}
}