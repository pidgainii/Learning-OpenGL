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





class Simulation {
	public:
		void Run(int width, int height);
	
		void SetUp(int width, int height);
		void Update();
		void Terminate();

		float time;
		GLFWwindow* window;
		// renderer;
};


/*


// for now, we will have our cube here. Later, we will have a list of objects and a camera

float vertices[] = {
    -0.5f,  0.5f, 0.4f, 0.7f, 0.0f, 0.9f, 1.0f,  // 0: front top left
    -0.5f, -0.7f, 0.4f, 0.3f, 0.0f, 0.9f, 1.0f,  // 1: front bottom left
    0.6f, -0.5f, 0.4f, 0.8f, 0.0f, 0.8f, 1.0f,   // 2: front bottom right
    0.5f,  0.4f, 0.4f, 0.5f, 0.0f, 0.9f, 1.0f,   // 3: front top right

    -0.4f,  0.6f, -0.4f, 0.4f, 0.0f, 0.9f, 1.0f, // 4: back top left
    -0.5f, -0.5f, -0.4f, 1.0f, 0.0f, 1.0f, 1.0f, // 5: back bottom left
    0.4f, -0.45f, -0.4f, 0.9f, 0.0f, 0.9f, 1.0f, // 6: back bottom right
    0.55f,  0.6f, -0.4f, 1.0f, 0.0f, 1.0f, 1.0f  // 7: back top right
};
unsigned int indices[] = {
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


*/