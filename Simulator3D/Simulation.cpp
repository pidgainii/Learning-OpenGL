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








 // for now, we will have our cube here. Later, we will have a list of objects and a camera

GLfloat vertices[] = {
	-0.5f,  0.5f, 0.4f, 0.7f, 0.0f, 0.9f, 1.0f,  // 0: front top left
	-0.5f, -0.7f, 0.4f, 0.3f, 0.0f, 0.9f, 1.0f,  // 1: front bottom left
	0.6f, -0.5f, 0.4f, 0.8f, 0.0f, 0.8f, 1.0f,   // 2: front bottom right
	0.5f,  0.4f, 0.4f, 0.5f, 0.0f, 0.9f, 1.0f,   // 3: front top right

	-0.4f,  0.6f, -0.4f, 0.4f, 0.0f, 0.9f, 1.0f, // 4: back top left
	-0.5f, -0.5f, -0.4f, 1.0f, 0.0f, 1.0f, 1.0f, // 5: back bottom left
	0.4f, -0.45f, -0.4f, 0.9f, 0.0f, 0.9f, 1.0f, // 6: back bottom right
	0.55f,  0.6f, -0.4f, 1.0f, 0.0f, 1.0f, 1.0f  // 7: back top right
};
GLuint indices[] = {
	// front side
	0, 1, 3,  // first Triangle
	1, 2, 3,   // second Triangle

	// right side
	3, 2, 6,
	6, 7, 3,

	// posterior side
	6, 5, 7,
	7, 5, 4,

	// left side
	5, 1, 0,
	0, 4, 5,

	// bottom side
	1, 5, 2,
	2, 6, 5,

	// upper side
	0, 3, 4,
	4, 7, 3
};














Simulation::Simulation()
{
	renderer = Renderer();
}


void Simulation::Run(Renderer r)
{
	
	SetUp(r);

	// maybe some functions will be moved to a different class, not the renderer
	while (renderer.windowShouldClose())
	{
		Update();
	}

	Terminate();
	
}


void Simulation::SetUp(Renderer r)
{
	renderer = r;
	renderer.Init();


	time = 0.0f;

	// here we need to create meshes and objects to create our scene
	// temporary mesh and scene
	Mesh mesh1 = Mesh(vertices, indices, 36);
	glm::mat4 modelWorld1 = glm::mat4(1.0f);
	glm::mat4 modelWorld2 = glm::translate(modelWorld1, glm::vec3(0.0f, 1.0f, 0.0f));
	Renderable cube1 = Renderable(mesh1, modelWorld1);
	Renderable cube2 = Renderable(mesh1, modelWorld2);
	std::vector<Renderable> scene;
	scene.push_back(cube1);
	scene.push_back(cube2);
	
	// We also need to initialize shaders here somehow
	// We need to initialize camera here somehow: MVP matrices
	worldView = glm::mat4(1.0f);
	viewProj = glm::mat4(1.0f);
	renderer.setCameraMatrix(worldView, viewProj);

	// tell renderer to enable Depth test
	renderer.EnableDepthTest();

}


void Simulation::Update()
{
	




	// Here we need to tell RENDERER:
	// clear color
	// clear buffer bits
	renderer.Clear();



	// activate the shader program
	// calculate object's positions according to time: MVP matrices actually
	// set MVP matrices (send them to gpu i guess)
	renderer.ActivateShaders();
	
	
	// Tell renderer to draw every object (now only our cube)
	// I guess we need to have renderable objects that can be sent
	// to the renderer. They should contain info about their vertices
	// and about their position each time frame (movement).
	renderer.DrawElements(scene);





	// finally: swap buffers
	//			glfwPollEvents
	// maybe these functions will be done by another guy, not the renderer
	// for now renderer does everything
	renderer.SwapBuffers();
	renderer.ProcessEvents();
}


void Simulation::Terminate()
{
	// we should clean every mesh here
	// TODO: CLEAN MESH OR RENDERABLE OBJECTS

	// tell renderer to clear resources
	renderer.Clean();
}