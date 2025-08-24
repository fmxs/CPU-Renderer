# Windows 环境准备教程

对于 Windows 用户来说，要编译和运行本项目，有 **两条常见路线**。你可以根据自己的习惯和磁盘空间来选择。

---

## 路线 A：Visual Studio Community（推荐给新手）

Visual Studio 是微软官方的 IDE，功能完整，集成度高，安装后几乎什么都不用再配置。

### 1. 下载 Visual Studio

* 访问 [Visual Studio 官网](https://visualstudio.microsoft.com/zh-hans/)
* 下载 **Visual Studio Community**（免费版）

### 2. 安装时选择工作负载

* 在安装界面，勾选 **“使用 C++ 的桌面开发”**（Desktop development with C++）
* 这会安装 MSVC 编译器、Windows SDK 和调试器

### 3. 打开并运行项目

* 打开 Visual Studio
* 第一次启动时会出现一个选择面板，不要点“创建新项目”！
* 请选择 **“打开 CMake...”**，然后定位到项目根目录的 `CMakeLists.txt`
* VS 会自动识别为 CMake 工程，点击运行按钮即可构建并执行

> 优点：
>
> * 一站式环境，新手友好
> * 自带调试工具
>
> 缺点：
>
> * 安装包比较大（几 GB）

---

## 路线 B：MinGW-w64 + CMake（轻量级）

如果你不想安装 Visual Studio，可以用 **MinGW-w64** 提供的 GCC/Clang 工具链。

### 1. 下载 MinGW-w64

* 推荐从 [WinLibs](https://winlibs.com/) 获取预编译包
* 选择最新的 **GCC + MinGW-w64 + UCRT** 版本
* 解压到 `C:/mingw64`

### 2. 配置环境变量

* 将 `C:/mingw64/bin` 加入系统环境变量 `PATH`
* 在命令行输入 `gcc --version` 验证是否安装成功

### 3. 使用 CMake 构建

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

* 成功后会生成 `demo.exe`

### 4. 运行

```bash
./demo.exe
```

> 优点：
>
> * 轻量，不依赖 Visual Studio
> * 纯命令行，适合熟悉 Linux/Unix 的用户
>
> 缺点：
>
> * 没有自带的 IDE 和调试器，需要额外安装 VSCode/CLion 等

---

## 总结

* **如果你是初学者** → 推荐 **路线 A (Visual Studio)**，简单省心
* **如果你习惯命令行** → 选择 **路线 B (MinGW + CMake)**，灵活轻量

无论选择哪条路线，编译运行的最终效果是一样的：一个带呼吸渐变的三角形窗口。
