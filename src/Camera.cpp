#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Camera.h"
#include "Shader.h"

const float SPEED = 5.0f;

Camera::Camera(const Shader* sh, const char* view, const char* proj, const float aspect)
: viewName(view), projName(proj), mAspect(aspect), mFOV(45.0f), mEuler{0.0, 90.0, 0.0}, mPos(0.0f, 0.0f, 0.0f), mFront(0.0, 0.0, 1.0),
mUp(0.0f, 1.0f, 0.0f), mRight(1.0f, 0.0f, 0.0f), mWorldUp(0.0f, 1.0f, 0.0f) {
	
	mView = glm::mat4(1.0f); // instantize as identity matrix
	mProj = glm::mat4(1.0f);
	
	// mViewLoc = mShader->getUniform(view);
	// mProjLoc = mShader->getUniform(proj);
	// @todo make constructor parameters
	mProj = glm::perspective(glm::radians(mFOV), mAspect, 0.1f, 100.0f);
	uploadProj();
	
	mView = glm::lookAt(mPos, mPos + mFront, mUp);
	uploadView();
}


void Camera::move(const uint16_t dir, const double lastFrame) {
	float velocity = 5.0f * lastFrame;
	
	if (dir & Z_POS)
		mPos += mFront * velocity;
	if (dir & Z_NEG)
		mPos -= mFront * velocity;
	if (dir & X_POS)
		mPos += mRight * velocity;
	if (dir & X_NEG)
		mPos -= mRight * velocity;
	if (dir & Y_POS)
		mPos += mUp    * velocity;
	if (dir & Y_NEG)
		mPos -= mUp    * velocity;
	
	lookAt(mPos, mPos + mFront, mUp);
}


void Camera::look(double dx, double dy, double dz) {
	float msen = 0.1f;
	
	dx *= msen;
	dy *= msen;

	mEuler.yaw   += dx;
	mEuler.pitch += dy;

	if (mEuler.pitch > 89.0f)
		mEuler.pitch = 89.0f;
	else if (mEuler.pitch < -89.0f)
		mEuler.pitch = -89.0f;
	
	mEuler.yaw = std::fmod(mEuler.yaw, 360.0f);
	
	mFront.x = cos(glm::radians(mEuler.yaw)) * cos(glm::radians(mEuler.pitch));
	mFront.y = sin(glm::radians(mEuler.pitch));
	mFront.z = sin(glm::radians(mEuler.yaw)) * cos(glm::radians(mEuler.pitch));
	
	mFront = glm::normalize(mFront);
	mRight = glm::normalize(glm::cross(mFront, mWorldUp)); 
	mUp    = glm::normalize(glm::cross(mRight, mFront));
	
	lookAt(mPos, mPos + mFront, mUp);
}


void Camera::zoom(double mag) {
	float msen = 2.0f;
	
	mFOV -= mag * msen;
	
	if (mFOV < 1.0f)
		mFOV = 1.0f;
	else if (mFOV > 45.0f)
		mFOV = 45.0f;
	
	mProj = glm::perspective(glm::radians(mFOV), mAspect, 0.1f, 100.0f);
	uploadProj();
}


void Camera::lookAt(glm::vec3 source, glm::vec3 dest, glm::vec3 up) {
	mView = glm::lookAt(source, dest, up);
	uploadView();
}


void Camera::uploadView() {
	glUniformMatrix4fv(Shader::current->getUniform(viewName), 1, GL_FALSE, glm::value_ptr(mView));
}

void Camera::uploadProj() {
	glUniformMatrix4fv(Shader::current->getUniform(projName), 1, GL_FALSE, glm::value_ptr(mProj));
}