#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class Shader;

enum Direction : uint16_t {
	Z_POS = 1 << 0, // forward
	Z_NEG = 1 << 1, // backwards
	X_POS = 1 << 2, // right
	X_NEG = 1 << 3, // left
	Y_POS = 1 << 4, // up
	Y_NEG = 1 << 5  // down
};

class Camera {
public:
	Camera(const Shader* sh, const char* view, const char* proj, const float aspect);
	
	void move(const uint16_t dir, const double lastFrame);
	void look(double dx, double dy, double dz = 0);
	void zoom(double mag);
	
	void lookAt(glm::vec3 source, glm::vec3 dest, glm::vec3 up);
	
	void uploadView();
	void uploadProj();
	
private:
	const char* viewName;
	const char* projName;
	const float mAspect;
	
	float mFOV;
	
	struct { 
		float pitch;
		float yaw;
		float roll;
	} mEuler;
	
	glm::mat4 mView;
	glm::mat4 mProj;
	
	glm::vec3 mPos;
    glm::vec3 mFront; // @todo create struct
    glm::vec3 mUp;
	glm::vec3 mRight;
    const glm::vec3 mWorldUp;
	
	// [[depreciated]] GLuint mViewLoc;
	// [[depreciated]] GLuint mProjLoc;
	
	// [[depreciated]]
	// void updateCameraVectors();
	
};