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


#include "Renderer.h"

#include <iostream>




// TODO: This method will take a list of renderable objects
// and load them to gpu i guess
// For now it will just take our cube

// Update -> Meshes are loaded to GPU when being created,
// no need to do that here
void Renderer::Init()
{
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

	// Now we will activate OpenGL functions with GLAD loader
	gladLoadGL();

	// TODO: make variables for width and height
	glViewport(0, 0, 800, 600);


	// TODO: specify shaders in some other way
	shaderProgram = ShaderProgram("default.vert", "default.frag");
}



void Renderer::Clear()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer::ActivateShaders()
{
	shaderProgram.ActivateProgram();
	// here we should set worldView and viewProj matrixes
}

void Renderer::setModelMatrix(glm::mat4 modelWorld)
{
	// here we should set modelWorld matrix
	shaderProgram.setM(modelWorld);
}

void Renderer::setCameraMatrix(glm::mat4 worldView, glm::mat4 viewProj)
{
	// here we should set WorldView and ViewProj matrices
	shaderProgram.setV(worldView);
	shaderProgram.setP(viewProj);
}





void Renderer::DrawElements(std::vector<Renderable> scene)
{
	// for each element, the renderer should draw the mesh using the
	// mesh vao, vbo and ebo i guess
	// also it should say to the shader programme to set the model matrix
	for (Renderable r : scene)
	{
		shaderProgram.setM(r.modelWorld);
		r.mesh->vao.Bind();

		// the index count is how many indices to draw, mesh should know that
		// also it should know the draw mode
		glDrawElements(GL_LINE_LOOP, r.mesh->indexCount, GL_UNSIGNED_INT, 0);
	}
}

bool Renderer::windowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Renderer::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void Renderer::ProcessEvents()
{
	glfwPollEvents();
}

// delete buffers and shader program
void Renderer::Clean()
{
	// call mesh.clean for every object I guess.
	// or maybe the simulation does this things
	// yep
	shaderProgram.DeleteProgram();

	glfwTerminate();
}