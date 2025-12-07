#include "Engine.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

#include "scene/Scene.h"
#include "scene/Component.h"
#include "scene/components/CameraComponent.h"

namespace eng {
    void keyCallback(GLFWwindow*, int key, int, int action, int) {
        auto& inputManager = Engine::GetInstance().GetInputManager();
        if (action == GLFW_PRESS) {
            inputManager.SetKeyPressed(key, true);
        } else if (action == GLFW_RELEASE) {
            inputManager.SetKeyPressed(key, false);
        }
    }

    void mouseButtonCallback(GLFWwindow*, int button, int action, int) {
        auto& inputManager = Engine::GetInstance().GetInputManager();
        if (action == GLFW_PRESS) {
            inputManager.SetMouseButtonPressed(button, true);
        } else if (action == GLFW_RELEASE) {
            inputManager.SetMouseButtonPressed(button, false);
        }
    }

    void mouseCursorPositionCallback(GLFWwindow*, double xpos, double ypos) {
        auto& inputManager = Engine::GetInstance().GetInputManager();
        inputManager.SetMousePosition(static_cast<float>(xpos), static_cast<float>(ypos));
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

        // Input manager callbacks
        glfwSetKeyCallback(m_Window, keyCallback);
        glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
        glfwSetCursorPosCallback(m_Window, mouseCursorPositionCallback);

        glfwMakeContextCurrent(m_Window);

        if (glewInit() != GLEW_OK) {
            glfwTerminate();
            return false;
        }

        m_GraphicsApi.Init();

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

            // Prepare camera data
            CameraData cameraData{};
            int width, height;
            glfwGetWindowSize(m_Window, &width, &height);
            float aspect = static_cast<float>(width) / static_cast<float>(height);
            if (m_CurrentScene) {
                if (const auto cameraObject = m_CurrentScene->GetMainCamera()) {
                    // Logic for getting matrices
                    if (const auto cameraComponent = cameraObject->GetComponent<CameraComponent>()) {
                        cameraData.viewMatrix = cameraComponent->GetViewMatrix();
                        cameraData.projectionMatrix = cameraComponent->GetProjectionMatrix(aspect);
                    }
                }
            }

            m_RenderQueue.Draw(m_GraphicsApi, cameraData);

            glm::vec2 lastMousePos = m_InputManager.GetMousePosition();
            m_InputManager.SetMousePositionLastFrame(lastMousePos.x, lastMousePos.y);
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

    FileSystem & Engine::GetFileSystem() {
        return m_FileSystem;
    }

    void Engine::SetCurrentScene(Scene *scene) {
        m_CurrentScene = std::unique_ptr<Scene>(scene);
    }

    Scene * Engine::GetCurrentScene() const {
        return m_CurrentScene.get();
    }
}
