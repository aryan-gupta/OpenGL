
#pragma once

#include <glad/glad.h>

enum SHADER_TYPE {
	VERTEX_SHADER,
	FRAGMENT_SHADER	
};

class Shader {
public:
	Shader(); // Default Shader
	Shader(const SHADER_TYPE t, const GLchar* source); // Single Shader
	Shader(const GLchar* vShader, const GLchar* fShader); // Both Shader
	
	void use() const;
	bool isValid() const;
	GLuint getUniform(const char* name) const;
	GLuint getRaw() const;
	
	void setUniform(const char* name, const bool val);
	void setUniform(const char* name, const int val);
	void setUniform(const char* name, const float val);
	/// @todo Make more overloads for larger data
	// void setUniform (const char* name, const std::instantizer_list<bool> val);
	// void setUniform (const char* name, const std::instantizer_list<int> val);
	// void setUniform (const char* name, const std::instantizer_list<float> val);
	
	static Shader* current;
	
private:
	GLuint mShaderProgram;
	bool mSuccess;
	
	void compile (const GLchar* const vPrgm, const GLchar* const fPrgm);
};
