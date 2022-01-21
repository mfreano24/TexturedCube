#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Shape.h"

using namespace std;

shared_ptr<Shape> triangle;

string RESDIR = "../../resources/";

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//ccw to face in +z?
vector<float> posBuf{ -0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f };

void Start() {
	triangle = make_shared<Shape>(posBuf);
	for (int i = 0; i < posBuf.size(); i++) {
		cerr << "posBuf[" << i << "] = " << posBuf[i] << endl;
	}
	triangle->initShape();
	triangle->setShaders(RESDIR + "tut_vert.glsl", RESDIR + "tut_frag.glsl");
	
	
}

void Update() {
	//game code
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	triangle->draw();
}

int main(){
	//init, context versions and openGL profile setting
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creation of a GLFW Window, setting up OpenGL context.
	GLFWwindow* window = glfwCreateWindow(800, 600, "Textured Cube", NULL, NULL);
	if (window == NULL) {
		cerr << "Failed to create OpenGL window..." << endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad initialization (according to learnopengl)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cerr << "Failed to initialize GLAD" << endl;
		exit(1);
	}

	//and we're off
	cerr << "OpenGL Version: " << glGetString(GL_VERSION) << endl;

	Start();

	while (!glfwWindowShouldClose(window)) {
		ProcessInput(window);
		Update();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}