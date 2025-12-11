#include <iostream>
#include <SDL3/SDL.h>

#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "Framebuffer.h"
#include "Sphere.h"
#include "Random.h"
#include "Object.h"

int main() {
	//constexpr int SCREEN_WIDTH = 1600;
	//constexpr int SCREEN_HEIGHT = 1200;
	constexpr int SCREEN_WIDTH = 640;
	constexpr int SCREEN_HEIGHT = 480;

	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Ray Tracer", SCREEN_WIDTH, SCREEN_HEIGHT);

	Framebuffer framebuffer(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	float aspectRatio = (float)framebuffer.width / (float)framebuffer.height;//framebuffer width divided by framebuffer height (float division)
	Camera camera(60.0f, aspectRatio);
	camera.SetView({ 0, 0, 5 }, { 0, 0, 0 });

	Scene scene; // after camera creation/initialization

	auto red = std::make_shared<Lambertian>(color3_t{ 1.0f, 0.0f, 0.0f });
	auto green = std::make_shared<Lambertian>(color3_t{ 0.0,1.0,0.0 });
	auto blue = std::make_shared<Lambertian>(color3_t{ 0,0,1 });
	auto light = std::make_shared<Emissive>(color3_t{ 1.0f, 1.0f, 1.0f }, 3.0f);
	auto metal = std::make_shared<Metal>(color3_t{ 1.0f, 1.0f, 1.0f }, 0.0f);
	std::shared_ptr<Material> materials[] = {red, green, blue, metal};

	for (int i = 0; i < 15; i++) {
		glm::vec3 position = random::getReal(glm::vec3{ -3.0f }, glm::vec3{ 3.0f });

		std::unique_ptr<Object> sphere = std::make_unique<Sphere>(Transform{ position }, (float)random::getReal(0.2f, 0.5f), materials[random::getInt(0, 3)]);
		scene.AddObject(std::move(sphere));
	}

	scene.SetSky(color3_t{ 0.3f, 0.4f, 0.6f }, color3_t{ 1.0f,1.0f,1.0f });
	//scene.SetSky(color3_t{ 0.0f, 0.0f, 0.0f }, color3_t{ 1.0f,1.0f,1.0f });
	// draw to frame buffer
	framebuffer.Clear({ 0, 0, 0, 255 });
	
	// remove previous "static" code and replace with this
	scene.Render(framebuffer, camera);

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		// check for exit events
		while (SDL_PollEvent(&event)) {
			// window (X) quit
			if (event.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			// escape key quit
			if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
				quit = true;
			}
		}


		// update frame buffer, copy buffer pixels to texture
		framebuffer.Update();

		// copy frame buffer texture to renderer to display
		renderer.CopyFramebuffer(framebuffer);
		renderer.Show();
	}
}