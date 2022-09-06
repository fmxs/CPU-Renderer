// Step10.1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "Vector4_example.h"
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

/// <summary>
/// 
/// </summary>
/// <param name="center">相机朝向向量</param>
/// <param name="normal">多边形法向量</param>
/// <returns></returns>
float culling(vector4 center, vector4 normal) {
    vector4 eye_dir;
    center.Subtract(center, eye_dir);
    eye_dir.Normalize(eye_dir);
    normal.Normalize(normal);
    return normal.Dot(normal, eye_dir);
}