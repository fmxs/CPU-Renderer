# Windows 环境准备教程

这是**环境搭建的起步篇**：先把路修好，再运货。此文档**不需要你已有任何源码或 CMake 文件**，只帮你把 Windows 的开发环境装好、路径配好，并准备一个空的工作目录。等环境 OK 了，你再往里面放代码就行。

---

## 两条路线（二选一即可）

* **路线 A：Visual Studio Community**（新手友好，一站式）
* **路线 B：MinGW‑w64 + CMake**（轻量命令行派）

---

## 路线 A：Visual Studio Community（推荐给新手）

### 1) 准备一个**空的**工作目录

在资源管理器里创建（暂时不用放任何文件）：

```
C:\dev\opengl_triangle_demo\
```

> 你也可以放到任意路径，比如 D 盘。重点是：**现在先空着**。

### 2) 安装 Visual Studio

* 前往官网下载安装 **Visual Studio Community 2022**（免费）
* 安装器里勾选 **“使用 C++ 的桌面开发”**（Desktop development with C++）

### 3) 启动 VS 并打开**文件夹**（不是“新建项目”）

* 打开 VS2022 起始面板，选择 **“打开本地文件夹(E)”**
* 选中刚才的 `C:\dev\opengl_triangle_demo\`
* 此时 VS 进入“文件夹视图”。因为目录还空着，**不会**显示 CMake 工程，这是**正常**的。

### 4) 验证工具是否可用（可选）

* 在 VS 顶部菜单 **“视图 → 终端”** 打开集成终端
* 运行：

  ```powershell
  cmake --version
  cl
  ```

  * 若 `cmake` 未找到，可稍后安装 CMake（见路线 B 的第 3 步），或使用 VS 自带的 CMake 支持；
  * `cl` 打印出 MSVC 版本号即可。

> 现在环境就绪、目录也建好了。**之后当你拥有代码与 `CMakeLists.txt` 时**，把它们放进这个目录，VS 会自动识别并配置构建。

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
