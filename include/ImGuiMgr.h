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
        ImGuiMgr(const char *title, int width, int height, int vsync, ImGuiConfigFlags config, const char *glsl_version,
                 bool dark = true);
        ~ImGuiMgr();
        static void pollEvents();
        void newFrame() const;
        void render() const;
        [[nodiscard]] bool shouldClose() const;
        GLFWwindow *window;
        int w = 0, h = 0, fb_w = 0, fb_h = 0;
        const bool isDockingEnable, isViewportEnable;
    };
} // namespace Backend
#endif // IMGUIMGR_H
