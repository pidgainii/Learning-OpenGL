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
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>



const int width = 700;
const int height = 700;



// We create vertices array to draw a cube
// Apart from the coordinates, we add colors to each vertex
GLfloat vertices[] = {
	// Front face vertices
	-0.3f, -0.3f, 0.3f,		0.1f, 1.0f, 0.1f, 1.0f, // bottom left 
	0.3f, -0.3f, 0.3f,		0.1f, 1.0f, 0.1f, 1.0f, // bottom right
	0.3f, 0.3f, 0.3f,		0.1f, 1.0f, 0.1f, 1.0f, // upper right
	-0.3f, 0.3f, 0.3f,		0.1f, 1.0f, 0.1f, 1.0f, // upper left

	// Back face vertices
	-0.3f, -0.3f, -0.3f,		0.1f, 1.0f, 0.1f, 1.0f, // bottom left
	0.3f, -0.3f, -0.3f,		0.1f, 1.0f, 0.1f, 1.0f, // bottom right
	0.3f, 0.3f, -0.3f,		0.1f, 1.0f, 0.1f, 1.0f, // upper right
	-0.3f, 0.3f, -0.3f,		0.1f, 1.0f, 0.1f, 1.0f, // upper left

};


GLuint indices[] = {
	// front face
	0, 1, 2,
	2, 3, 0,

	// right face
	1, 5, 2,
	2, 6, 5,

	// back face
	4, 5, 6,
	6, 7, 4,

	// left face
	0, 4, 3,
	4, 7, 3,

	// upper face
	3, 2, 6,
	3, 7, 6,

	// bottom face
	0, 1, 5,
	5, 4, 0
};








// Function we will use temporally
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}




/*
1 - Create some vertices for our triangle
2 - After configuring view port:
	- Create vertex shader
	- Create fragment shader
	- Create shader program and attach shaders to it, and link the program
	- We create VAO and VBO in order to send info about vertices to GPU
3 - In the loop where we mantain our window open:
	- Use the program
	- Bind Vertex array
	- Draw arrays
4 - Delete vertex arrays, buffers, program
*/




int main()
{
	// Let's initialize glfw
	glfwInit();


	// We specify the minor and major version -> 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	// We select the core profile (modern version of OpenGL)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	
	// ----------------------------------------------------------- 


	// Now we are going to create the window, make it part of current context and add some fail logic
	// The context is where OpenGL has all it's state.
	// It's like saying to OPENGL: "Hey, here is where you should draw"
	GLFWwindow* window = glfwCreateWindow(width, height, "MyWindow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error while trying to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// ----------------------------------------------------------- 


	// Now we will activate OpenGL functions with GLAD loader
	gladLoadGL();


	// -----------------------------------------------------------


	// Now we are going to configure our window (viewport, color) and will swap buffers
	glViewport(0, 0, width, height);


	// -----------------------------------------------------------


	// Now we will create vertex and fragment shaders and put them in a shader program
	std::string vertexCode = get_file_contents("default.vert");
	const char* vertexSource = vertexCode.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, 0);
	glCompileShader(vertexShader);

	std::string fragmentCode = get_file_contents("default.frag");
	const char* fragmentSource = fragmentCode.c_str();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, 0);
	glCompileShader(fragmentShader);

	// We create the shader program, attach the shaders and link them
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Now we can actually delete the shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// -----------------------------------------------------------


	// We create VAO, VBO and EBO
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// We load data into VBO and EBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// We load attributes to VAO
	// VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// EBO
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbinding for caution
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// -----------------------------------------------------------


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// We have to clear the color buffer bit
	glClear(GL_COLOR_BUFFER_BIT);
	// We have to swap buffers so that OpenGL displays this window on screen
	glfwSwapBuffers(window);


	// -----------------------------------------------------------


	glEnable(GL_DEPTH_TEST);

	float degrees = 0.0f;
	float movementX = 0.0f;
	float movementZ = 0.0f;


	float previous = glfwGetTime();
	float current = glfwGetTime();

	// Now we want to make sure our window remains open
	while (!glfwWindowShouldClose(window))
	{
		current = glfwGetTime();
		if (current - previous >= 1.0f / 60.0f)
		{
			degrees += 0.5f;
			//movementX += 0.001f;
			movementZ += 0.05f;
			previous = current;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);



		// Here we are going to create the matrices in order to be able
		// make transformations and visualize our cube

		// we initialize the matrices
		glm::mat4 modelWorld = glm::mat4(1.0f);
		glm::mat4 worldView = glm::mat4(1.0f);
		glm::mat4 viewProj = glm::mat4(1.0f);


		// We create the transformations
		// For the model matrix, we will rotate our cube, giving it 3 parameters:
		// The model, the radians, and the axis
		modelWorld = glm::rotate(modelWorld, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
		modelWorld = glm::translate(modelWorld, glm::vec3(movementX, 0.0f, movementZ));
		// We move the world in the opposite direction we would move the camera
		// In this case, we will move it a bit further to negative z
		worldView = glm::translate(worldView, glm::vec3(0.0f, 0.0f, -25.0f));
		
		viewProj = glm::perspective(glm::radians(120.0f), (float)(width / height), 0.1f, 30.0f);



		// We need pointers to know where should we send these matrices
		int modelWorldLoc = glGetUniformLocation(shaderProgram, "model");
		int worldViewLoc = glGetUniformLocation(shaderProgram, "view");
		int viewProjLoc = glGetUniformLocation(shaderProgram, "proj");

		glUniformMatrix4fv(modelWorldLoc, 1, GL_FALSE, glm::value_ptr(modelWorld));
		glUniformMatrix4fv(worldViewLoc, 1, GL_FALSE, glm::value_ptr(worldView));
		glUniformMatrix4fv(viewProjLoc, 1, GL_FALSE, glm::value_ptr(viewProj));



		glBindVertexArray(VAO);
		glDrawElements(GL_LINE_LOOP, 36, GL_UNSIGNED_INT, 0);



		glfwSwapBuffers(window);

		// This function processes events in the event queue and then returns immediately
		glfwPollEvents();
	}


	// -----------------------------------------------------------


	// Now we free resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	
	return 0;
}



