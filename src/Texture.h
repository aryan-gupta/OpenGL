
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// enum IMPORT_TYPE {
	// IMPORT_FILE,
	// IMPORT_RAW
// }

class Shader;

class Texture {
public:
	Texture();
	Texture(unsigned num, const char* file);
	
	void use();
	void setUniform(const Shader* sh, const char* name);
	GLuint getRaw();
	
private:
	int mWidth;
	int mHeight;
	int mNumChan;
	
	unsigned mTexNum;
	
	GLuint mTexture;
	
};
