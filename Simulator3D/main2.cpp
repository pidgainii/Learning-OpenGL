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


#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;





// set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
float vertices2[] = {
    -0.5f,  0.5f, 0.4f, 0.7f, 0.0f, 0.9f, 1.0f,  // 0: front top left
    -0.5f, -0.7f, 0.4f, 0.3f, 0.0f, 0.9f, 1.0f,  // 1: front bottom left
    0.6f, -0.5f, 0.4f, 0.8f, 0.0f, 0.8f, 1.0f,   // 2: front bottom right
    0.5f,  0.4f, 0.4f, 0.5f, 0.0f, 0.9f, 1.0f,   // 3: front top right

    -0.4f,  0.6f, -0.4f, 0.4f, 0.0f, 0.9f, 1.0f, // 4: back top left
    -0.5f, -0.5f, -0.4f, 1.0f, 0.0f, 1.0f, 1.0f, // 5: back bottom left
    0.4f, -0.45f, -0.4f, 0.9f, 0.0f, 0.9f, 1.0f, // 6: back bottom right
    0.55f,  0.6f, -0.4f, 1.0f, 0.0f, 1.0f, 1.0f  // 7: back top right
};
unsigned int indices2[] = {
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






int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Now we will activate OpenGL functions with GLAD loader
    gladLoadGL();

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);



    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    ShaderProgram shaderP = ShaderProgram("default.vert", "default.frag");



    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0); // position
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float))); // color
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);




    // camera matrices
    glm::mat4 modelWorld = glm::mat4(1.0f);
    glm::mat4 worldView = glm::mat4(1.0f);
    glm::mat4 viewProj = glm::mat4(1.0f);
    worldView = glm::translate(worldView, glm::vec3(0.0f, 0.0f, -1.0f));
    viewProj = glm::perspective(glm::radians(120.0f), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 30.0f);
    float degrees = 0.01f;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle
        shaderP.ActivateProgram();



        modelWorld = glm::rotate(modelWorld, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));

        shaderP.setMVP(modelWorld, worldView, viewProj);

        
        //glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized);
        glDrawElements(GL_LINE_LOOP, 36, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shaderP.DeleteProgram();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
