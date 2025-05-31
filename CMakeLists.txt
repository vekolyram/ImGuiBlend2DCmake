cmake_minimum_required(VERSION 3.15)
project(ImGuiCmake)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含目录设置
include_directories(
        include
        libs/blend2d/include
        libs/glfw/include
        libs/imgui/include/imgui
        libs/imgui/include/imgui/backends
)
# 收集应用程序源文件
file(GLOB APP_SOURCES
        "src/*.cpp"
        "src/*.cxx"
)
# 添加应用程序可执行文件
add_executable(${PROJECT_NAME}
        ${APP_SOURCES}
)

# 链接ImGui库到应用程序
set(GLFW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib-mingw-w64/libglfw3.a)
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})
set(IMGUI_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui/lib-mingw-w64/libimgui.a)
target_link_libraries(${PROJECT_NAME} ${IMGUI_LIBRARY})
set(BLEND2D_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/libs/blend2d/lib-mingw-w64/libblend2d.a)
target_link_libraries(${PROJECT_NAME} ${BLEND2D_LIBRARY})
# Windows系统库
target_link_libraries(${PROJECT_NAME}
        opengl32
        gdi32
)
# 复制资源文件（如果需要）
# configure_file(resources/shaders/shader.frag ${CMAKE_CURRENT_BINARY_DIR}/shader.frag COPYONLY)
#
## 安装规则（可选）
#install(TARGETS ${PROJECT_NAME}
#        RUNTIME DESTINATION bin
#)
#
#install(DIRECTORY include/ DESTINATION include)