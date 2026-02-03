/*
 * Licensed under the Apache License, Version 2.0.
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Application.h"

#include <iostream>




Application::Application()
{
	// TEMPORARY UNTIL WE CREATE CAMERA
	worldView = glm::mat4(1.0f);
	viewProj = glm::mat4(1.0f);
	worldView = glm::translate(worldView, glm::vec3(0.0f, 0.0f, -3.0f));
	worldView = glm::translate(worldView, glm::vec3(0.0f, -1.0f, 0.0f));
	viewProj = glm::perspective(glm::radians(120.0f), 800.0f / 600.0f, 0.1f, 30.0f);
}


void Application::Run()
{
	Setup();

	// maybe some functions will be moved to a different class, not the renderer
	while (!glfwWindowShouldClose(window))
	{
		// TODO: calculate time
		// TODO: change simulation so that it changes scene depending on time
		sim.Update(time, scene);

		// ----------------------------------------------------------
		// TODO: We need to create a function inside renderer that not only draws but:
		// clears, activates shaders, sets camera matrices and draw elements
		// It can be called: renderer.Render(scene)
		// ----------------------------------------------------------
		//renderer.setCameraMatrix(worldView, viewProj);
		renderer.Render(scene, worldView, viewProj);


		// TODO: maybe create window class to manage all of this glfw stuff
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Terminate();

}


void Application::Setup()
{
	time = 0.0f;

	sim = Simulation();
	renderer = Renderer();
	loader = Loader();

	// create window
	// glfw stuff
	// context
	// poll events, swap buffers

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// TODO: make variables for width and height
	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	renderer.Init();



	loader.LoadScene(scene);
}


void Application::Terminate()
{
	// we should clean every mesh here
	// TODO: CLEAN MESH OR RENDERABLE OBJECTS

	// tell renderer to clear resources
	glfwTerminate();
	renderer.Clean();
}