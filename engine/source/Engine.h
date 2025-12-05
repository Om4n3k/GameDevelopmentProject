#pragma once
#include <memory>
#include <chrono>

#include "graphics/GraphicsApi.h"
#include "GLFW/glfw3.h"
#include "input/InputManager.h"
#include "render/RenderQueue.h"

namespace eng {
    class Scene;
    class Application;
}

namespace eng {
    class Engine {
    public:
        static Engine& GetInstance();
    private:
        Engine() = default;
        Engine(const Engine&) = delete;
        Engine(Engine&&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine& operator=(Engine&&) = delete;
    public:
        bool Init(int width, int height);
        void Run();
        void Destroy();

        void SetApplication(Application* app);
        Application* GetApplication() const;
        InputManager& GetInputManager();
        GraphicsApi& GetGraphicsApi();
        RenderQueue& GetRenderQueue();

        void SetCurrentScene(Scene* scene);
        Scene* GetCurrentScene() const;
    private:
        std::unique_ptr<Application> m_Application;
        std::chrono::system_clock::time_point m_LastTimePoint;
        GLFWwindow* m_Window = nullptr;
        InputManager m_InputManager;
        GraphicsApi m_GraphicsApi;
        RenderQueue m_RenderQueue;
        std::unique_ptr<Scene> m_CurrentScene;
    };
}