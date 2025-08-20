// LookAt矩阵在Matrix类中的定义
Mat LookAt(vector3 camPos, vector3 target, vector3 up);

/// <summary>
/// 创建一个给定目标的观察矩阵
/// </summary>
/// <param name="camPos">摄像机位置</param>
/// <param name="target">目标位置</param>
/// <param name="up">世界空间中表示朝上的上向量</param>
/// <returns></returns>
template<typename myT>
Mat<myT> Mat<myT>::LookAt(vector3 camPos, vector3 tar, vector3 up)
{
	Mat<myT> matrix(4, 4);
	vector3 zAxis = vector3::Normalize(zAxis.Subtract(camPos, tar));
	vector3 xAxis = vector3::Normalize(vector3::Cross(up, zAxis));
	vector3 yAxis = vector3::Normalize(vector3::Cross(zAxis, xAxis));
	matrix.num[0][0] = xAxis.x;
	matrix.num[0][1] = xAxis.y;
	matrix.num[0][2] = xAxis.z;
	matrix.num[1][0] = yAxis.x;
	matrix.num[1][1] = yAxis.y;
	matrix.num[1][2] = yAxis.z;
	matrix.num[2][0] = zAxis.x;
	matrix.num[2][1] = zAxis.y;
	matrix.num[2][2] = zAxis.z;
	matrix.num[3][0] = camPos.x;
	matrix.num[3][1] = camPos.y;
	matrix.num[3][2] = camPos.z;
	matrix.num[3][3] = 1;
	return matrix;
}
