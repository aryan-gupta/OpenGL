#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

#include "Shader.h"
#include "Window.h"
#include "Texture.h"
#include "Camera.h"

// settings
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 500;

float deltaTime = 0.0f;	// time between current frame and last frame
Camera* cam;

Shader* Shader::current = nullptr;

int main() {	
	srand(time(NULL));
	
	std::ifstream vtxfile("v1.vs");
	std::string vtxsrc{std::istreambuf_iterator<char>(vtxfile), std::istreambuf_iterator<char>()};
	vtxfile.close();
	
	std::ifstream fragfile("f1.fs");
	std::string frag1src{std::istreambuf_iterator<char>(fragfile), std::istreambuf_iterator<char>()};
	fragfile.close();

	std::ifstream frag2file("f2.fs");
	std::string frag2src{std::istreambuf_iterator<char>(frag2file), std::istreambuf_iterator<char>()};
	frag2file.close();
	
	Window::initGlfw();
	
	Window* window = new Window(SCR_WIDTH, SCR_HEIGHT, "OpenGL Tuts");
	if (!window->isValid()) { return -1; }
	
	window->setClearColor({0.2f, 0.3f, 0.3f, 1.0f});
	
	Shader* sprgm = new Shader(vtxsrc.c_str(), frag1src.c_str());
	if (!sprgm->isValid()) { return -1; }

	Shader* sprgm2 = new Shader(vtxsrc.c_str(), frag2src.c_str());
	if (!sprgm2->isValid()) { return -1; }	
	
	float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
	
	glm::vec3 lampPos(1.2f, 1.0f, 2.0f);	
	
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	
	Texture* tex1 = new Texture(0, "container.jpg");
	Texture* tex2 = new Texture(1, "awesomeface.png");
	
	sprgm->use();
	sprgm->setUniform("tex1", 0);
	sprgm->setUniform("tex2", 1);
	
	cam = new Camera(sprgm, "view", "proj", (float)SCR_WIDTH/(float)SCR_HEIGHT);
	
	unsigned modelLoc = sprgm->getUniform("model");
	unsigned modelLoc2 = sprgm2->getUniform("model");
	
	sprgm2->use();
	glUniform3f(sprgm2->getUniform("objectColor"), 1.0f, 0.5f, 0.31f);
	glUniform3f(sprgm2->getUniform("lightColor"),  1.0f, 1.0f, 1.0f);
	
	float lastFrame;
    while (!window->getShouldClose()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		
        window->processInput();
		window->clear();
		
		{ // model
			// sprgm->use();
			// cam->uploadView();
			// cam->uploadProj();
			// glm::mat4 model;
			// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			// glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		{ // light
			sprgm2->use();
			glm::mat4 model;
			//glm::translate(model, lampPos);
			glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		window->swapBuffers();
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}