#include <algorithm>
#include <cstdio>
#include <vector>
#include "imgui.h"
#include "imnodes.h"
#define GL_SILENCE_DEPRECATION
#include "ImGuiMgr.h"
int main(int, char **) {
    ImGuiConfigFlags flags = 0;
    {
        flags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        flags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls`
        flags |= ImGuiConfigFlags_DockingEnable;
        flags |= ImGuiConfigFlags_DpiEnableScaleFonts;
        flags |= ImGuiConfigFlags_ViewportsEnable; // 启用多视口
    }
    Backend::ImGuiMgr::ImguiConfig config("ImGui", 1280, 720, flags, 1, "#version 130");
    const Backend::ImGuiMgr imgui(config);
    ImGuiIO &io                     = ImGui::GetIO();
    const int w                     = config.get_width;
    const int h                     = config.get_height;
    const int fb_w                  = config.fb_width;
    const int fb_h                  = config.fb_height;
    const float font_scaling_factor = std::max(static_cast<float>(fb_w) / static_cast<float>(w),
                                               static_cast<float>(fb_h) / static_cast<float>(h));
    auto *cnConfig                  = IM_NEW(ImFontConfig)();
    cnConfig->MergeMode             = true;
    const ImFont *font1 =
            io.Fonts->AddFontFromFileTTF("C:/Users/ASUS/Desktop/JetBrainsMono.ttf", 16 * font_scaling_factor);
    const ImFont *font2 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc", 16 * font_scaling_factor, cnConfig,
                                                       io.Fonts->GetGlyphRangesChineseFull());
    io.FontGlobalScale /= (font_scaling_factor);
    IM_ASSERT(font1 || font2 != nullptr);
    io.ConfigDockingWithShift                         = false;
    ImGui::GetStyle().AntiAliasedLines                = true;
    ImGui::GetStyle().AntiAliasedFill                 = true;
    ImGui::GetStyle().Colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.0f, 1.0f, 0.6f, 0.0f);
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
            {
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1, 0.1, 0.1, 1));
                ImGui::BeginChild("Log Window", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
                ImGui::Text("Fuck World");
                ImGui::Separator();
                ImGui::EndChild();
                ImGui::PopStyleColor();
            }
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
        int start_attr, end_attr;
        bool have = false;
        {
            ImGui::Begin("Graph Demo");
            ImNodes::BeginNodeEditor();
            ImNodes::BeginNode(1);
            ImNodes::BeginOutputAttribute(1);
            ImGui::Text("output pin");
            ImNodes::EndOutputAttribute();
            ImNodes::EndNode();
            ImNodes::BeginNode(2);
            ImNodes::BeginInputAttribute(2);
            ImGui::Text("input pin");
            ImNodes::EndInputAttribute();
            ImNodes::EndNode();
            ImNodes::Link(1, 1, 2);
            ImNodes::MiniMap();
            ImNodes::EndNodeEditor();
            if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
                have = true;
            }
            ImGui::End();
        }
        imgui.render();
    }
    return 0;
}
