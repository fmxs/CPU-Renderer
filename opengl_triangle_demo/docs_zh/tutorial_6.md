# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形
## 设置顶点数据 → VAO + VBO + glVertexAttribPointer 详解

---

## 6-1 🎯 本节目标

我们要在main.cpp里写一个新函数：

```cpp
GLuint setupTriangleVAO();
```

它的任务是：

* 创建一个 VAO（Vertex Array Object）来记住配置
* 创建一个 VBO（Vertex Buffer Object）上传顶点数据
* 设置两个 attribute：

  * location = 0 → 位置 `aPos`（vec2）
  * location = 1 → 颜色 `aColor`（vec3）

---

## 6-2 💡 为啥要分 VAO / VBO？

| 对象  | 是什么                   | 干啥用                           |
| --- | --------------------- | ----------------------------- |
| VBO | 顶点缓冲对象（Vertex Buffer） | 存储你的顶点数据（比如 float\[]）         |
| VAO | 顶点数组对象（Vertex Array）  | 存储“这块数据该怎么读”的配置（偏移、步长、类型、绑定槽） |

一句话总结：**VBO 存数据，VAO 记规则。**

你可以想象 VBO 是你扔进去的一堆小纸片，VAO 是你手写的说明书，告诉 GPU：“每隔几个字节，看成一个点/颜色/UV/法线”。

---

## 6-3 📐 我们的顶点数据结构长这样：

```cpp
float vertices[] = {
   // x,     y,     r,   g,   b
   -0.6f, -0.4f, 1.0f, 0.2f, 0.2f,  // 顶点1
    0.6f, -0.4f, 0.2f, 1.0f, 0.2f,  // 顶点2
    0.0f,  0.6f, 0.2f, 0.2f, 1.0f   // 顶点3
};
```

你可以看成每个顶点有：

* 前两个是位置（x, y）
* 后三个是颜色（r, g, b）

---

## 6-4 🧠 为啥不用两个数组分开写位置 / 颜色？

因为：

* 性能上 interleaved（交叉存储）更适合现代 GPU 的缓存机制
* 写起来少麻烦一堆绑定、同步
* 就三个顶点，不要整花活，越简单越好

---

## 6-5 📦 设计思路：我们写的函数做了啥？

```cpp
GLuint setupTriangleVAO();
```

1. 生成一个 VAO（记录配置）
2. 生成一个 VBO（装 float 数据）
3. 绑定 VAO → 绑定 VBO → 上传数据
4. 设置 `glVertexAttribPointer()`：

   * pos 属性从每个顶点偏移 0 开始，读取 2 个 float
   * color 属性从每个顶点偏移 2 个 float 开始，读取 3 个 float
   * 整体步长是每个顶点占用的字节数：`5 * sizeof(float)`

---

## 6-6 🧠 为什么 glVertexAttribPointer() 要这么写？

```cpp
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
```

翻译为人话是：

> “从当前绑定的 VBO 中，把每隔 `5*sizeof(float)` 字节的前两个 float，解释成 location=0 的 vec2 传给顶点着色器里的 aPos”。

然后：

```cpp
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
```

> “从每组顶点数据里的第 3 个 float 开始，取 3 个 float，作为 location=1 的 vec3 → aColor”。

---

## 6-7 📄 全部代码贴一下（setupTriangleVAO）

```cpp
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

    // 设置 aPos：vec2，从偏移 0 开始，步长 5
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    // 设置 aColor：vec3，从偏移 2 开始，步长 5
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

    return vao;
}
```
