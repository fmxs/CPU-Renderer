# Step2工程文件介绍
Step2_myWindows.zip

## 需要环境
- Visual studio
- 安装工作负荷 “桌面应用和移动应用” ==> “使用C++的桌面开发”

## 打开示例工程的方法
1. 打开文件夹EmapleProject，下载里面的压缩包Step2_myWindows.zip
2. 使用解压工具，解压Step2_myWindows.zip，得到Step2_myWindows.zip文件夹
3. 打开Step2_myWindows.zip文件夹
4. 双击文件夹中的Step2_myWindows.sln文件
5. 等待VS启动，在VS中打开main.c
6. 运行工程

# 创建工程的步骤
本节工程并不是控制台应用程序，而是桌面应用程序，具体创建方法如下：
1. ![image](https://user-images.githubusercontent.com/65701532/187611437-dba9a15d-6d68-4c1b-a6c8-83855113b168.png)
2. ![image](https://user-images.githubusercontent.com/65701532/187611472-65e0e92f-c378-4dc7-bafb-b7bbaffa4cf4.png)
3. ![image](https://user-images.githubusercontent.com/65701532/187611560-845e0192-6613-443a-9305-3f620dcd2dde.png)
4. 打开本节的示例代码main.c
![image](https://user-images.githubusercontent.com/65701532/187612043-aaf76f87-ff5c-4791-a28e-ee191b1faa27.png)
5. 右键解决方案管理器中的源文件，新建文件
![image](https://user-images.githubusercontent.com/65701532/187612354-f2e2d4f8-5776-4409-b9f3-28deae137334.png)
6. 重命名文件为main.c，注意后缀，是.c，不是.cpp
![image](https://user-images.githubusercontent.com/65701532/187612507-3bd30445-fce7-48cb-bd7f-a06a07e1eab3.png)
7. 复制github中的代码
![image](https://user-images.githubusercontent.com/65701532/187612127-488cb7a6-fb53-40dc-aacf-c48109cce341.png)
复制成功会出现绿勾勾，如下图
![image](https://user-images.githubusercontent.com/65701532/187612608-bc199af5-cafe-48c6-87e9-1abeada058ca.png)
6. 将代码粘贴到第6步创建的main.c里
7. 保存一下，若弹出提示框，选择以其他编码保存
![image](https://user-images.githubusercontent.com/65701532/187613182-1a31b4f0-9668-4810-af3e-43114039e987.png)
8. 选择UTF-8
![image](https://user-images.githubusercontent.com/65701532/187613261-7660081f-64d8-4029-bbeb-4bf783383224.png)
9. 运行工程
![image](https://user-images.githubusercontent.com/65701532/187612855-b87f639d-553e-4d1e-aa91-99b6d248c76f.png)

# 本节实现了什么
1. 使用win api创建一个1024*768的窗口，以及鼠标监听事件

# 运行效果

## 窗口
![image](https://user-images.githubusercontent.com/65701532/186637550-6a5e109d-9f12-4acd-a472-106a15b7b7b6.png)

## 鼠标单击事件
![image](https://user-images.githubusercontent.com/65701532/186637622-3a02bcda-0c6e-4132-9150-a8729fdc720e.png)
