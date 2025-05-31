#include <algorithm>
#include <cstdio>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include "ImGuiMgr.h"
int main(int, char **) {
    ImGuiConfigFlags config = 0;
    {
        config |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        config |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls`
        config |= ImGuiConfigFlags_DockingEnable;
        config |= ImGuiConfigFlags_DpiEnableScaleFonts;
        config |= ImGuiConfigFlags_ViewportsEnable; // 启用多视口
    }
    const Backend::ImGuiMgr imgui("ImGui", 1280, 720, 1, config, "#version 130");
    ImGuiIO &io                     = ImGui::GetIO();
    const int w                     = imgui.w;
    const int h                     = imgui.h;
    const int fb_w                  = imgui.fb_w;
    const int fb_h                  = imgui.fb_h;
    const float font_scaling_factor = std::max(static_cast<float>(fb_w) / static_cast<float>(w),
                                               static_cast<float>(fb_h) / static_cast<float>(h));
    ImFontConfig cnConfig;
    cnConfig.MergeMode = true;
    const ImFont *font1 =
            io.Fonts->AddFontFromFileTTF("C:/Users/ASUS/Desktop/JetBrainsMono.ttf", 16 * font_scaling_factor);
    const ImFont *font2 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc", 16 * font_scaling_factor, &cnConfig,
                                                       io.Fonts->GetGlyphRangesChineseFull());
    io.FontGlobalScale /= (font_scaling_factor);
    IM_ASSERT(font1 || font2 != nullptr);
    // 主循环
    while (!imgui.shouldClose()) {
        Backend::ImGuiMgr::pollEvents();
        imgui.newFrame();
        {
            ImGui::Begin("Control Panel");
            static float fValue = 0.5f;
            ImGui::SliderFloat("Slider", &fValue, 0.0f, 1.0f);
            static bool bCheck = true;
            ImGui::Checkbox("Toggle", &bCheck);
            static int iValue = 0;
            ImGui::InputInt("Input Int", &iValue);
            if (ImGui::Button("Click Me!")) {
                printf("Button clicked!\n");
            }
            static ImVec4 color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            ImGui::ColorEdit3("Color Picker", reinterpret_cast<float *>(&color));
            ImGui::End();
        }
        {
            ImGui::Begin("Log Window");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::Separator();
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Message");
            ImGui::Text("This is a log message.");
            ImGui::End();
        }
        {
            ImGui::Begin("Tree Demo");
            if (ImGui::TreeNode("Node 1")) {
                ImGui::Text("Child content of Node 1");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Node 2")) {
                ImGui::Text("Child content of Node 2");
                ImGui::TreePop();
            }
            ImGui::End();
        }
        ImGui::GetStyle().AntiAliasedLines = true;
        ImGui::GetStyle().AntiAliasedFill  = true;
        imgui.render();
    }
    return 0;
}
