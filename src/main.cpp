#include <glad/glad.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <memory>
#include <cmath>
#include "Renderer.h"
#include "Scene.h"
#include "Button.h"

// Screen dimensions
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;


// Helper functions
bool initSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL not initialized! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}


SDL_Window* createWindow()
{
    SDL_Window* window = SDL_CreateWindow("3D UI Demo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(!window)
    {
        std::cerr << "Window NOT created! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return window;
}


SDL_GLContext createGLContext(SDL_Window* window)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if(!context)
    {
        std::cerr << "OpenGL context NOT created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    return context;
}


bool initGLAD()
{
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cerr << "GLAD Error" << std::endl;
        return false;
    }
    return true;
}


void cleanup(SDL_Window* window, SDL_GLContext context)
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


glm::vec3 calculatePosition(const size_t objectCount)
{
    constexpr float radius = 2.0f;
    constexpr float angleIncrement = 0.6f;
    const float angle = objectCount * angleIncrement;
    const glm::vec3 center(0.0f, 0.0f, -4.0f);

    // Calculate new object position on the circle
    return center + glm::vec3(
        radius * std::cos(angle),
        radius * std::sin(angle),
        0.0f
    );
}


void processEvents(bool &quit, Renderer &renderer, Scene &scene, const Button* addButtonPtr)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            quit = true;
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            // Convert screen coordinates to a world-space ray
            glm::vec3 rayOrigin, rayDir;
            renderer.screenPosToWorldRay(mouseX, mouseY, rayOrigin, rayDir);

            // Check for intersection with objects in the scene
            Object* pickedObject = scene.pickObject(rayOrigin, rayDir);
            if(pickedObject)
            {
                // If button was clicked -> add a new object (cube)
                if(pickedObject == addButtonPtr)
                {
                    glm::vec3 newPos = calculatePosition(scene.getObjectCount());
                    scene.addObject(std::make_unique<Object>(newPos));
                }
                else
                {
                    scene.removeObject(pickedObject);
                }
            }
        }
    }
}


void runApp(SDL_Window* window)
{
    // Create our Renderer and Scene
    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    Scene scene;

    // Create a 3D button at a fixed location (green cube)
    auto addButton = std::make_unique<Button>(glm::vec3(0.0f, 0.0f, -4.5f));
    // Store the raw pointer for later use
    const Button* addButtonPtr = addButton.get();
    scene.addObject(std::move(addButton));

    bool quit = false;
    while (!quit)
    {
        // Process events
        processEvents(quit, renderer, scene, addButtonPtr);
        // Render the scene
        renderer.render(scene);
        SDL_GL_SwapWindow(window);
    }
}


int main(int argc, char* argv[])
{
    if(!initSDL())
    {
        return -1;
    }

    SDL_Window* window = createWindow();
    if(!window)
    {
        SDL_Quit();
        return -1;
    }

    SDL_GLContext glContext = createGLContext(window);
    if(!glContext)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    if(!initGLAD())
    {
        cleanup(window, glContext);
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Run the application
    runApp(window);

    cleanup(window, glContext);
    return 0;
}

