
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

static const size_t LOG_LEN = 1024; 

static const char* VERTEX_SOURCE = "";
// R"(
// #version 330 core
// layout (location = 0) in vec3 aPos; 
// layout (location = 1) in vec2 tPos; 

// out vec2 texCord;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 proj;

// void main() {
    // gl_Position = proj * view * model * vec4(aPos, 1.0);
	// texCord = tPos;
// }
// )";


static const char* FRAGMENT_SOURCE = "";
// R"(
// #version 330 core

// in vec2 texCord;

// out vec4 FragColor;

// uniform sampler2D tex1;
// uniform sampler2D tex2;

// void main()
// {
    // FragColor = mix(texture(tex1, texCord), texture(tex2, texCord), 0.2);
    // // FragColor = texture(tex1, texCord);
// } 
// )";


Shader::Shader () {
	compile(VERTEX_SOURCE, FRAGMENT_SOURCE);
	Shader::current = const_cast<Shader*>(this);;
}


Shader::Shader (const SHADER_TYPE t, const GLchar* source) {
	switch (t) {
		case VERTEX_SHADER:
			compile(source, FRAGMENT_SOURCE);
		break;
		
		case FRAGMENT_SHADER:
			compile(VERTEX_SOURCE, source);
		break;
		
		default:
			std::cerr << "ERROR::SHADER::COMPILE_OPTION_NOT_VALID" << std::endl;
		break;
	}
	Shader::current = const_cast<Shader*>(this);;
}


Shader::Shader (const GLchar* vShader, const GLchar* fShader) {
	compile(vShader, fShader);
	Shader::current = const_cast<Shader*>(this);;
}


void Shader::use () const {
	glUseProgram(mShaderProgram);
	Shader::current = const_cast<Shader*>(this);
}


bool Shader::isValid () const {
	return mSuccess;
}


GLuint Shader::getRaw () const {
	return mShaderProgram;
}


void Shader::setUniform (const char* name, const bool val) {
	glUniform1i(glGetUniformLocation(mShaderProgram, name), (int)val);
}


void Shader::setUniform (const char* name, const int val) {
	glUniform1i(glGetUniformLocation(mShaderProgram, name), val);
}


void Shader::setUniform (const char* name, const float val) {
	glUniform1f(glGetUniformLocation(mShaderProgram, name), val); 
}


GLuint Shader::getUniform(const char* name) const {
	glGetUniformLocation(mShaderProgram, name);
}

void Shader::compile (const GLchar* vPrgm, const GLchar* fPrgm) {
	int success = 0; // to check complanation status
	char log[LOG_LEN]; // for compile error message
	
	// Create the Vertex Program
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // create shader
	glShaderSource(vertexShader, 1, &vPrgm, NULL); // apply source
	glCompileShader(vertexShader); // compile
	
	// Check for any errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // get status
	if (!success) {
		glGetShaderInfoLog(vertexShader, LOG_LEN, NULL, log); // get log info
		std::cerr << "ERROR::SHADER::VERTEX_SHADER::COMPILE_FAILED\n" << log << std::endl;
		mSuccess = false;
		return;
	}
	
	// Create the Fragment Program
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fPrgm, NULL);
	glCompileShader(fragmentShader);
	
	// Check for any errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // get status
	if (!success) {
		glGetShaderInfoLog(fragmentShader, LOG_LEN, NULL, log); // get log info
		std::cerr << "ERROR::SHADER::FRAGMENT_SHADER::COMPILE_FAILED\n" << log << std::endl;
		mSuccess = false;
		return;
	}
	
	// Create our final program
	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, vertexShader);
	glAttachShader(mShaderProgram, fragmentShader);
	glLinkProgram(mShaderProgram);
	
	// Check for any errors
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(mShaderProgram, LOG_LEN, NULL, log);
		std::cerr << "ERROR::SHADER::SHADER_PROGRAM::LINKING_FAILED" << log << std::endl;
		mSuccess = false;
		return;
	}
	
	// Delete old shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	mSuccess = true;
}

