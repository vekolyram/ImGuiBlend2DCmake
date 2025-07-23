//
// Created by ASUS on 25-5-31.
//

#include "ImGuiMgr.h"
#include <cstdio>
#include <string>
#include "imnodes.h"
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
        window = glfwCreateWindow(currentConfig->set_width, currentConfig->set_height, currentConfig->title, nullptr,
                                  nullptr);
        if (window == nullptr)
            return;
        glfwMakeContextCurrent(window);
        glfwSwapInterval(currentConfig->vsync); // Enable vsync
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImNodes::CreateContext();
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
        glViewport(0, 0, currentConfig->fb_width, currentConfig->fb_height);
        glClearColor(1.0f, 1.0f, 1.0f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (currentConfig->isViewportEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
        measureWH();
        measureFBWH();
    }
    ImGuiMgr::~ImGuiMgr() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImNodes::DestroyContext();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
    }
} // namespace Backend
