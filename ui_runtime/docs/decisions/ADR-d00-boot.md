# ADR-d00-boot: 启动 Demo 的架构决策记录

## 背景 (Context)
需要一个最小 demo 来验证 UI 框架的基础设施是否能跑通：
- OpenGL 渲染管线是否初始化正确
- Framebuffer vs Window 尺寸是否区分清楚
- 输入坐标能否和逻辑 UI 空间对齐
- 日志系统与时间模块能否正常工作

## 决策 (Decision)
- 平台先锁定 **macOS + OpenGL 3.3 Core Profile**，不做跨平台。
- 使用 **GLFW** 管理窗口和输入，调用 `Input::SetupCallbacks` 填充鼠标坐标。
- Renderer 采用 `Renderer2D_GL` 的最小实现，支持矩形绘制。
- 引入 **日志节流**（每 2 秒打印一次），用于验证尺寸/坐标。

## 备选方案 (Alternatives)
- 跨平台：引入 **glad** 作为 OpenGL loader → 放弃，初期过重。
- 不写日志，纯靠肉眼观察方块变色 → 放弃，验证不可靠。

## 后果 (Consequences)
- Demo 只能在 macOS 下运行，Windows/Linux 无法直接构建。
- Retina 下，`fbW/fbH` 可能是 `winW/winH` 的 2 倍，需要检查输入坐标一致性。
- 后续 demo 必须抽象出跨平台层，否则每次都要改 `#ifdef`。

## 状态 (Status)
Accepted – 作为最小可运行 demo 的基准。

## 参考 (References)
- ADR 模式说明: https://adr.github.io/
