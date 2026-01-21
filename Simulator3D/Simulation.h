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



/*

The simulation needs to have a vector of renderable objects called
scene.

It will call render.draw (scene) every frame and also it should be responsible
for camera (worldview and viewproj matrixes

I think simulation does not care about windows

*/

#pragma once


class Simulation {
	public:
		Simulation();

		void Run(Renderer r);

		void SetUp(Renderer r);
		void Update();
		void Terminate();

		float time;
		Renderer renderer;

		// temporary
		glm::mat4 worldView;
		glm::mat4 viewProj;

		std::vector<Renderable> scene;
};



