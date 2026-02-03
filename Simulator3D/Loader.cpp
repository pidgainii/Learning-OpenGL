




#include "Loader.h"

#include "ObjLoader.h"


Loader::Loader()
{

}

void Loader::LoadScene(std::vector<Renderable>& scene)
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