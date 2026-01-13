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

	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);



	time = 0.0f;

	// RENDERER:
	// gladLoadGL
	// glViewport
	// create VBO, VAO, EBO, generate them
	// Bind VAO, bind VBO, bind EBO

	// ¿Send data, vertices, indices to VBO and EBO? maybe
	// ¿Indicate which part of data is color and position? maybe

	// Unbind


	
	// We also need to initialize shaders here somehow
	// We need to initialize camera here somehow: MVP matrices

	// tell renderer to enable Depth test

}


void Simulation::Update()
{
	// Calculate camera position, and set camera matrices i guess
	// calculate body positions according to time ------->
	// --------> we need to have objects that can be rendered

	// in order to pass them to the renderer in this function


	// I think we should create a simulation scene, which will have an array
	// of objects to render in our simulation.
	// But for now, lets do it with one single cube




	// Here we need to tell RENDERER:
	// clear color
	// clear buffer bits

	// activate the shader program
	// calculate object's positions according to time: MVP matrices actually
	// set MVP matrices (send them to gpu i guess)

	// Tell renderer to draw every object (now only our cube)
	// I guess we need to have renderable objects that can be sent
	// to the renderer. They should contain info about their vertices
	// and about their position each time frame (movement).






	// finally: swap buffers
	//			glfwPollEvents
}


void Simulation::Terminate()
{
	// tell renderer to clear resources

	glfwTerminate();
}