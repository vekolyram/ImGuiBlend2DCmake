//
// Created by ASUS on 25-5-31.
//

#include "ImGuiMgr.h"
#include <cstdio>
#include <string>
namespace Backend {
    static void glfw_error_callback(int error, const char *description) {
        throw "GLFW Error!" + std::to_string(error) + description;
    }
    ImGuiMgr::ImGuiMgr(ImguiConfig &config) : currentConfig(&config) {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            return;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        window = glfwCreateWindow(currentConfig->width, currentConfig->height, currentConfig->title, nullptr, nullptr);
        if (window == nullptr)
            return;
        glfwMakeContextCurrent(window);
        glfwSwapInterval(currentConfig->vsync); // Enable vsync
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= currentConfig->flags;
        config.dark ? ImGui::StyleColorsDark() : ImGui::StyleColorsLight();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(config.glsl_version);
        measureWH();
        measureFBWH();
    }
    void ImGuiMgr::pollEvents() { glfwPollEvents(); }
    bool ImGuiMgr::shouldClose() const { return glfwWindowShouldClose(window); }
    void ImGuiMgr::newFrame() const {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (currentConfig->isDockingEnable)
            ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    }
    void ImGuiMgr::render() const {
        ImGui::Render();
        glViewport(0, 0, currentConfig->ms_width, currentConfig->ms_height);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (currentConfig->isViewportEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(window);
    }
    ImGuiMgr::~ImGuiMgr() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }
} // namespace Backend
