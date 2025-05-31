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
        include/imgui
        include/imgui/backends
        libs/glfw/include
)

# 收集ImGui源文件
file(GLOB IMGUI_SOURCES
        "src/imgui/*.cpp"
        "src/imgui/backends/*.cpp"
)

# 收集应用程序源文件（假设在src/目录）
file(GLOB APP_SOURCES
        "src/*.cpp"
        "src/*.cxx"
)

# 创建ImGui静态库
add_library(imgui STATIC
        ${IMGUI_SOURCES}
)

# 设置ImGui库的头文件位置
target_include_directories(imgui PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 添加应用程序可执行文件
add_executable(${PROJECT_NAME}
        ${APP_SOURCES}
)

# 链接ImGui库到应用程序
target_link_libraries(${PROJECT_NAME} imgui)

# 链接GLFW库
if(WIN32)
    # MinGW编译的GLFW静态库
    set(GLFW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/lib-mingw-w64/libglfw3.a)
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})

    # Windows系统库
    target_link_libraries(${PROJECT_NAME}
            opengl32
            gdi32
    )
else()
    # Linux/macOS系统库
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} OpenGL::GL)
endif()

# 复制资源文件（如果需要）
# configure_file(resources/shaders/shader.frag ${CMAKE_CURRENT_BINARY_DIR}/shader.frag COPYONLY)
#
## 安装规则（可选）
#install(TARGETS ${PROJECT_NAME}
#        RUNTIME DESTINATION bin
#)
#
#install(DIRECTORY include/ DESTINATION include)