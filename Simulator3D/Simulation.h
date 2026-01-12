#include <glad/glad.h>
#include <GLFW/glfw3.h>



// TODO: Create variable time: time of the simulation
//


class Simulation {
	public:
		void Run(int width, int height);
	
		void SetUp(int width, int height);
		void Update();
		void Terminate();

		float time;
		GLFWwindow* window;
		// Renderer renderer;
};