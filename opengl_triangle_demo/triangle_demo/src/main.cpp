#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

// ===== 工具函数 =====
static std::string readTextFile(const char* path) {
    std::ifstream ifs(path);
    if (!ifs) throw std::runtime_error(std::string("Cannot open: ") + path);
    std::stringstream ss; ss << ifs.rdbuf();
    return ss.str();
}

static void checkShader(GLuint sh, const char* tag) {
    GLint ok = 0;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0; glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetShaderInfoLog(sh, len, nullptr, log.data());
        std::cerr << "Shader compile failed [" << tag << "]:\n" << log.data() << "\n";
        throw std::runtime_error("shader compile failed");
    }
}

static void checkProgram(GLuint prog) {
    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0; glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetProgramInfoLog(prog, len, nullptr, log.data());
        std::cerr << "Program link failed:\n" << log.data() << "\n";
        throw std::runtime_error("program link failed");
    }
}

// ===== 初始化函数 =====
GLFWwindow* initWindow(int width, int height) {
    if (!glfwInit()) return nullptr;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(width, height, "Triangle", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) {
        glViewport(0, 0, w, h);
    });
    return window;
}

bool initGLAD() {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    return true;
}

// ===== Shader 函数 =====
GLuint createShaderProgram(const char* vertPath, const char* fragPath) {
    std::string vsrc = readTextFile(vertPath);
    std::string fsrc = readTextFile(fragPath);

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
    glBindAttribLocation(prog, 0, "aPos");
    glBindAttribLocation(prog, 1, "aColor");
    glLinkProgram(prog);
    checkProgram(prog);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

// ===== 顶点数据设置 =====
GLuint setupTriangleVAO() {
    float vertices[] = {
        -0.6f, -0.4f, 1.0f, 0.2f, 0.2f,
         0.6f, -0.4f, 0.2f, 1.0f, 0.2f,
         0.0f,  0.6f, 0.2f, 0.2f, 1.0f,
    };
    GLuint vao = 0, vbo = 0;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // aPos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1); // aColor
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

    return vao;
}

// ===== 渲染主循环 =====
void renderLoop(GLFWwindow* window, GLuint prog, GLuint vao, GLint u_time) {
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
}

// ===== 清理资源 =====
void cleanup(GLuint prog, GLuint vao) {
    glDeleteProgram(prog);
    glDeleteVertexArrays(1, &vao);
    // 如果你保留了 vbo 变量，也 glDeleteBuffers(1, &vbo);
}

// ===== 主函数 =====
int main() {
    GLFWwindow* window = initWindow(800, 600);
    if (!window) return -1;
    if (!initGLAD()) return -1;

    GLuint prog = createShaderProgram("../shaders/triangle.vert", "../shaders/triangle.frag");
    GLint u_time = glGetUniformLocation(prog, "u_time");

    GLuint vao = setupTriangleVAO();

    renderLoop(window, prog, vao, u_time);

    cleanup(prog, vao);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
