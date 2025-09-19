```
                 [OS 鼠标事件]
                        │
                        ▼
                 glfwPollEvents()
                        │
                        ▼
cursorPosCB(x,y) ───► g_mouseX, g_mouseY
                       (事件通道: 输入/状态)


                 [OS 窗口事件]
                        │
             ┌──────────┴──────────┐
             ▼                     ▼
   glfwGetWindowSize()       glfwGetFramebufferSize()
             │                     │
             ▼                     ▼
          winW, winH           fbW, fbH
       (逻辑/UI 尺寸)       (物理像素/GPU画布)


                 glfwGetTime() + fmod()
                        │
                        ▼
                        t
                 (渲染用时间因子)


winW, winH + fbW, fbH + t
            │
            ▼
   glViewport + glClearColor + glClear
            │
            ▼
   glfwSwapBuffers(win) ──► [屏幕显示: 背景渐变]


(winW,winH, fbW,fbH, g_mouseX,g_mouseY)
            │
            ▼
   sx=fbW/winW, sy=fbH/winH (派生变量)
            │
            ▼
        printf(...) ──────► [日志输出]


```
