# Windows 环境准备教程

这是 **环境搭建的起步篇**：先把路修好，再运货。本教程分为两条路线：

* Visual Studio 用户（2022 与 2019 配置略有不同）
* MinGW 用户

你不需要已有源码或 CMake 文件，只需要按照下面的说明把开发环境装好、路径配好，并准备一个空的工作目录。

---

## 路线 A：Visual Studio Community

### 1) 创建一个空的工作目录

```powershell
C:\dev\opengl_triangle_demo\
```

此目录用于放置代码与构建产物。现在可以是空的。

---

### 2) 安装 Visual Studio（按版本选择）

#### ✅ Visual Studio 2022

* 前往官网下载 [Visual Studio Community 2022](https://visualstudio.microsoft.com/zh-hans/vs/community/)
* 安装器中勾选：**“使用 C++ 的桌面开发”**（Desktop development with C++）
* 不需要额外安装 CMake（VS2022 自带）

#### ✅ Visual Studio 2019

* 前往官网下载 [Visual Studio 2019](https://visualstudio.microsoft.com/vs/older-downloads/)
* 安装器中勾选：**“使用 C++ 的桌面开发”**
* ⚠️ **需要手动安装 CMake：**

  * 安装 [CMake 官方版本](https://cmake.org/download/)
  * 安装时勾选 “Add CMake to system PATH”

安装完成后，打开 PowerShell 或 VS 的终端，验证工具：

```powershell
cmake --version  # 查看 CMake 是否可用
cl               # 查看 MSVC 编译器是否正常输出版本号
```

---

### 3) 打开 VS 并加载文件夹

* 启动 Visual Studio
* 选择 **“打开本地文件夹”**（不是“新建项目”）
* 选中：`C:\dev\opengl_triangle_demo\`
* 此时进入“文件夹视图”，当你放入 `CMakeLists.txt` 后，VS 会自动识别为 CMake 工程。

---

### 4) 提示：CMake 配置刷新机制

如果你修改了 `CMakeLists.txt` 或新复制了 `.lib` 文件，**请手动刷新 CMake 项目**：

* 菜单栏：项目 → 重新加载 CMake 项目
* 或关闭 VS 后重新打开该文件夹

否则 VS 不会重新识别你的构建内容！

---

## 路线 B：MinGW‑w64 + CMake（轻量命令行）

### 1) 准备一个**空的**工作目录

创建：

```
C:\dev\opengl_triangle_demo\
```

### 2) 安装 MinGW‑w64（GCC 工具链）

* 建议从 WinLibs 获取带 UCRT 的预编译包（64‑bit）
* 解压到 `C:\mingw64`（示例路径）
* 将 `C:\mingw64\bin` 追加到 **系统环境变量 PATH**

### 3) 安装 CMake（Windows x64 安装包）

* 安装时勾选“**Add CMake to system PATH**”或手动把其 `bin` 目录加入 PATH

### 4) 验证安装

打开 PowerShell：

```powershell
gcc --version
cmake --version
```

能看到版本号说明工具可用。

> 之后当你有源码与 `CMakeLists.txt` 时，在该目录执行：
>
> ```powershell
> mkdir build; cd build
> cmake -G "MinGW Makefiles" ..
> cmake --build .
> ```

---

## 该文档做到哪一步为止？

* ✅ 完成：装好编译工具、配好 PATH、创建好**空目录**。
* ⏭️ 下一步（等你准备好源码时再做）：把代码与 `CMakeLists.txt` 放进这个目录，然后用 VS 或命令行编译运行。

> 小贴士：不要在 VS 起始界面点 **“创建新项目”** 或 **“打开项目或解决方案”**。我们是**以文件夹为单位**的工作流；当目录里出现 `CMakeLists.txt` 时，VS 才会把它识别为 CMake 工程。
