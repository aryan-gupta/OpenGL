
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

#include "Texture.h"
#include "Shader.h"

Texture::Texture() {}


Texture::Texture(unsigned num, const char* file)
:mTexNum(num) {
	stbi_set_flip_vertically_on_load(true);  
	
	glGenTextures(1, &mTexture);
	glActiveTexture(GL_TEXTURE0 + mTexNum);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	unsigned char *data = stbi_load(file, &mWidth, &mHeight, &mNumChan, 0);
	
	if (!data) {
		std::cerr << "ERROR::TEXTURE::STB::IMAGE_LOAD_FAILED" << std::endl;
		return;
	}
	
	switch (mNumChan) {
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
		
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);
}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

GLuint Texture::getRaw() {
	return mTexture;
}

void Texture::setUniform(const Shader* sh, const char* name) {
	glUniform1i(glGetUniformLocation(sh->getRaw(), name), mTexNum);
	// OR
	//sh->setUniform(name, mTexNum);
}