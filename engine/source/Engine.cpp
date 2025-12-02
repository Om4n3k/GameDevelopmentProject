#include "Engine.h"
#include "Application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace eng {
    void keyCallback(GLFWwindow* window, int key, int, int action, int) {
        auto& inputManager = Engine::GetInstance().GetInputManager();
        if (action == GLFW_PRESS) {
            inputManager.SetKeyPressed(key, true);
        } else if (action == GLFW_RELEASE) {
            inputManager.SetKeyPressed(key, false);
        }
    }

    Engine &Engine::GetInstance() {
        static Engine instance;
        return instance;
    }

    bool Engine::Init(int width, int height) {
        if (!m_Application) {
            return false;
        }

        if (!glfwInit()) {
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, "Engine", nullptr, nullptr);
        if (m_Window == nullptr) {
            glfwTerminate();
            return false;
        }

        glfwSetKeyCallback(m_Window, keyCallback);

        glfwMakeContextCurrent(m_Window);

        if (glewInit() != GLEW_OK) {
            glfwTerminate();
            return false;
        }

        return m_Application->Init();
    }

    void Engine::Run() {
        if (!m_Application) {
            return;
        }

        m_LastTimePoint = std::chrono::high_resolution_clock::now();
        while (!glfwWindowShouldClose(m_Window) && !m_Application->NeedsToBeClosed()) {
            glfwPollEvents();

            auto now = std::chrono::high_resolution_clock::now();
            const float deltaTime = std::chrono::duration<float>(now - m_LastTimePoint).count();
            m_LastTimePoint = now;

            m_Application->Update(deltaTime);

            m_GraphicsApi.SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            m_GraphicsApi.ClearBuffers();

            m_RenderQueue.Draw(m_GraphicsApi);

            glfwSwapBuffers(m_Window);
        }
    }

    void Engine::Destroy() {
        if (m_Application) {
            m_Application->Destroy();
            m_Application.reset();
            glfwTerminate();
            m_Window = nullptr;
        }
    }

    void Engine::SetApplication(Application* app) {
        m_Application.reset(app);
    }

    Application* Engine::GetApplication() const {
        return m_Application.get();
    }

    InputManager& Engine::GetInputManager() {
        return m_InputManager;
    }

    GraphicsApi& Engine::GetGraphicsApi() {
        return m_GraphicsApi;
    }

    RenderQueue& Engine::GetRenderQueue() {
        return m_RenderQueue;
    }
}
