#include "Simulation.h"



void Simulation::Run(int width, int height)
{
	SetUp(width, height);

	while (!glfwWindowShouldClose(window))
	{
		Update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Terminate();
}


void Simulation::SetUp(int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	time = 0.0f;
	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);


	// renderer.initialize vbo vao etc


	// We also need to initialize shaders here somehow

}


void Simulation::Update()
{
	// Calculate camera position, and set camera matrices i guess
	// calculate body positions according to time ------->
	// --------> we need to have objects that can be rendered

	// in order to pass them to the renderer in this function
}


void Simulation::Terminate()
{
	// tell renderer to clear resources

	glfwTerminate();
}