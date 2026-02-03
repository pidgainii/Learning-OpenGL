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

#include "Simulation.h"

#include "ObjLoader.h"






Simulation::Simulation()
{
	renderer = Renderer();

	time = 0.0f;


	// TEMPORARY UNTIL WE CREATE CAMERA
	worldView = glm::mat4(1.0f);
	viewProj = glm::mat4(1.0f);
	worldView = glm::translate(worldView, glm::vec3(0.0f, 0.0f, -3.0f));
	worldView = glm::translate(worldView, glm::vec3(0.0f, -1.0f, 0.0f));
	viewProj = glm::perspective(glm::radians(120.0f), 800.0f/600.0f, 0.1f, 30.0f);
}


void Simulation::Run(Renderer r)
{
	
	SetUp(r);

	// maybe some functions will be moved to a different class, not the renderer
	while (!renderer.windowShouldClose())
	{
		Update();
	}

	Terminate();
	
}


void Simulation::SetUp(Renderer r)
{
	renderer = r;
	renderer.Init();


	LoadScene();


	renderer.EnableDepthTest();

}


void Simulation::Update()
{
	
	// Updating movement for each object in scene
	for (Renderable& r : scene)
	{
		glm::mat4 mW = glm::translate(r.modelWorld, r.translation);
		mW = glm::rotate(mW, glm::radians(0.025f), r.rotation);

		r.modelWorld = mW;

	}






	// Here we need to tell RENDERER:
	// clear color
	// clear buffer bits
	renderer.Clear();



	// activate the shader program
	// calculate object's positions according to time: MVP matrices actually
	// set MVP matrices (send them to gpu i guess)
	renderer.ActivateShaders();

	// --------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------------------------
	// ERROR IVE BEEN SEARCHING FOR:
	// MATRICES SHOULD BE SET AFTER THE SHADER IS ACTIVE 
	renderer.setCameraMatrix(worldView, viewProj);
	// --------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------------------------


	
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

void Simulation::LoadScene()
{
	// Loading mesh for airplane
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	loadOBJ("airplane.txt", vertices, indices);
	Mesh* planeMesh = new Mesh(vertices, indices, indices.size());



	// Creating Renderable objects
	// TODO: Create ready to use scenes in JSON format
	glm::mat4 modelWorld1 = glm::mat4(1.0f);
	glm::mat4 modelWorld2 = glm::translate(modelWorld1, glm::vec3(0.0f, 2.0f, 1.0f));
	glm::mat4 modelWorld3 = glm::rotate(modelWorld1, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::vec3 translation1 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 translation2 = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 1.0f, 1.0f);

	Renderable plane1 = Renderable(planeMesh, modelWorld3, translation1, rotation);
	Renderable plane2 = Renderable(planeMesh, modelWorld2, translation2, rotation);


	// Adding objects to our scene
	scene.push_back(plane1);
	scene.push_back(plane2);
}