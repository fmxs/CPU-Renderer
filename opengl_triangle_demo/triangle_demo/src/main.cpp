#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

// 读取文件工具
static std::string readTextFile(const char* path) {
    std::ifstream ifs(path);
    if (!ifs) { throw std::runtime_error(std::string("Cannot open: ")+path); }
    std::stringstream ss; ss << ifs.rdbuf();
    return ss.str();
}

// 编译检查
static void checkShader(GLuint sh, const char* tag) {
    GLint ok = 0; glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0; glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetShaderInfoLog(sh, len, nullptr, log.data());
        std::cerr << "Shader compile failed [" << tag << "]:\n" << log.data() << "\n";
        throw std::runtime_error("shader compile failed");
    }
}

// 链接检查
static void checkProgram(GLuint prog) {
    GLint ok = 0; glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0; glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetProgramInfoLog(prog, len, nullptr, log.data());
        std::cerr << "Program link failed:\n" << log.data() << "\n";
        throw std::runtime_error("program link failed");
    }
}

static void framebuffer_size_callback(GLFWwindow*, int w, int h) {
    glViewport(0, 0, w, h);
}

int main() {
    // ---------- 1) GLFW + 上下文 ----------
    if (!glfwInit()) return -1;

    // macOS Core Profile 要求 forward compat
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); // 3.2+ 对应 GLSL 150
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1); // VSYNC

    // ---------- 2) GLAD ----------
    // 你已经修好：用 gladLoadGL((GLADloadfunc)glfwGetProcAddress) 或正确的 UserPtr 版本
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n"; return -1;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

    // ---------- 3) 顶点数据 ----------
    // 每个顶点: 2 floats pos + 3 floats color = 5 floats
    float vertices[] = {
        //   aPos.x  aPos.y   r    g    b
           -0.6f,   -0.4f,  1.0f,0.2f,0.2f,
            0.6f,   -0.4f,  0.2f,1.0f,0.2f,
            0.0f,    0.6f,  0.2f,0.2f,1.0f,
    };

    GLuint vao=0, vbo=0;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 位置: layout(location=0) → aPos(vec2)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);

    // 颜色: layout(location=1) → aColor(vec3)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));

    // ---------- 4) Shader ----------
    // A) 从文件读取（你已上传 triangle.vert/frag）
    std::string vsrc = readTextFile("../shaders/triangle.vert");
std::string fsrc = readTextFile("../shaders/triangle.frag");


    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* vsp = vsrc.c_str();
    glShaderSource(vs, 1, &vsp, nullptr);
    glCompileShader(vs);
    checkShader(vs, "vertex");

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fsp = fsrc.c_str();
    glShaderSource(fs, 1, &fsp, nullptr);
    glCompileShader(fs);
    checkShader(fs, "fragment");

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);

    // 绑定 attribute 位置要在 link 前，与 glVertexAttribPointer 的 0/1 保持一致
    glBindAttribLocation(prog, 0, "aPos");
    glBindAttribLocation(prog, 1, "aColor");

    glLinkProgram(prog);
    checkProgram(prog);

    glDeleteShader(vs);
    glDeleteShader(fs);

    // uniform 位置
    GLint u_time = glGetUniformLocation(prog, "u_time");

    // ---------- 5) 主循环 ----------
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.12f, 0.18f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(prog);
        if (u_time >= 0) glUniform1f(u_time, (float)glfwGetTime());

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(prog);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
