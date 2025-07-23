//
// Created by ASUS on 25-5-31.
//

#ifndef IMGUIMGR_H
#define IMGUIMGR_H
#include <GLFW/glfw3.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
namespace Backend {
    static void glfw_error_callback(int error, const char *description);
    class ImGuiMgr {
    public:
        struct ImguiConfig {
        public:
            const char *title;
            const ImGuiConfigFlags flags;
            const int vsync;
            const int set_width, set_height;
            int get_width, get_height, fb_width, fb_height;
            int last_width = 0, last_height = 0;
            const char *glsl_version;
            bool dark;
            bool isDockingEnable;
            bool isViewportEnable;
            explicit ImguiConfig(const char *title = "DefaultTitle", const int width = 1280, const int height = 720,
                                 const ImGuiConfigFlags flags = 0, const int vsync = 1,
                                 const char *glsl_version = "#version 130", const bool dark = true) :
                title(title), flags(flags), vsync(vsync), set_width(width), set_height(height),
                glsl_version(glsl_version), dark(dark), isDockingEnable(flags & ImGuiConfigFlags_DockingEnable),
                isViewportEnable(flags & ImGuiConfigFlags_ViewportsEnable), get_width(0), get_height(0), fb_width(0),
                fb_height(0) {};
        };
        ImguiConfig *currentConfig;
        ImGuiMgr(ImguiConfig &config);
        ~ImGuiMgr();
        static void pollEvents();
        void newFrame() const;
        void render() const;
        void measureWH() const {
            currentConfig->last_width  = currentConfig->get_width,
            currentConfig->last_height = currentConfig->get_height;
            glfwGetWindowSize(window, &currentConfig->get_width, &currentConfig->get_height);
            if (currentConfig->last_width == 0 || currentConfig->last_height == 0) {
                currentConfig->last_width  = currentConfig->get_width,
                currentConfig->last_height = currentConfig->get_height;
            }
        }
        void measureFBWH() const {
            glfwGetFramebufferSize(window, &currentConfig->fb_width, &currentConfig->fb_height);
        }
        [[nodiscard]] bool shouldClose() const;
        GLFWwindow *window;
    };
} // namespace Backend
#endif // IMGUIMGR_H
