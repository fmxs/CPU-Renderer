```
[Keyboard 'V']
      │
      ▼
 g_viewIdx (0/1/2)  ────────────────────────────────────────────────────────────────┐
      │                                                                            │
      │                                 [Query display]
      │                          glfwGetFramebufferSize(win)
      │                                    │
      │                                    ▼
      │                           fbW, fbH  (像素尺寸; Retina 可能=2x)
      │                                    │
      │                                    ▼
      │                        ┌───────────────────────────┐
      └──► Compute (x,y,w,h) ─►│ 视口矩形选择器 (三种预设) │
                               └───────────────────────────┘
                                        │
                        ┌───────────────┴───────────────┐
                        │                               │
                        ▼                               ▼
               glViewport(x,y,w,h)              glScissor(x,y,w,h)
                （几何映射：NDC→像素）          （像素写入掩码：允许写入的区域）
                        │                               │
                        │                               │
                        │                         glEnable(GL_SCISSOR_TEST)
                        │                               │
                        │                               │
                        ▼                               ▼
               ┌────────────────┐                 glClearColor(r,g,b,1)
               │ 几何/顶点路径  │                       │
               │ (可选的 draw) │                       ▼
               └──────┬────────┘               glClear(GL_COLOR_BUFFER_BIT)
                      │                                   │
                      │                                   │  只受 Scissor 约束，不看 Viewport
                      │                                   ▼
                      │                          ┌───────────────────────┐
                      └─────────────────────────►│  Framebuffer(后台)    │
                                                 └───────────┬───────────┘
                                                             │
                                                      glfwSwapBuffers
                                                             │
                                                             ▼
                                                   屏幕显示（前台缓冲）


[每帧前置基线]
glDisable(GL_SCISSOR_TEST)
glViewport(0,0,fbW,fbH)
glClearColor(0,0,0,1)  —— 全屏清黑，确定后台缓冲初始状态（基线）
glClear(GL_COLOR_BUFFER_BIT)

[颜色选择]
g_viewIdx → (r,g,b) ∈ {蓝, 红, 绿} —— 冗余信号：位置+颜色双确认
```
