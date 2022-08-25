#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <iostream>
#include <vector>
#include "Vector3.h"
using namespace std;
template <typename myT>
class Mat
{
public:
	int row;
	int col;
	myT** num;

	Mat(const int, const int);
	Mat(const Mat<myT>&);
	~Mat();
	Mat operator+(const Mat<myT>&);
	Mat operator-(const Mat<myT>&);
	Mat operator*(const Mat<myT>&);
	Mat& operator=(const Mat<myT>&);
	myT* operator[](const int);
	// 转置矩阵
	Mat Transpose(); 
	template <typename myT>
	friend ostream& operator<<(ostream&, const Mat<myT>&); 
	template <typename myT>
	friend istream& operator>>(istream&, const Mat<myT>&);
	// 矩阵乘矩阵
	Mat Premultiply(const Mat<myT>& matrix1, const Mat<myT>& matrix2);
	// 矩阵左乘列向量
	Mat Premultiply_vec(const Mat<myT>& matrix, const vector3& vector3);
	// 矩阵右乘行向量
	Mat Postmultiply(const Mat<myT>& matrix1, const Mat<myT>& matrix2);
	// 单位矩阵
	Mat Identity();
};

template <typename myT>
Mat<myT>::Mat(const int r, const int c)
{
	row = r;
	col = c;
	if (row > 0 && col > 0)
	{
		num = new myT * [row]; // myT* [pointer]
		for (int i = 0; i < row; i++)
		{
			num[i] = new myT[col];
		}
	}
	else
	{
		row = 0;
		col = 0;
		num = NULL;
	}
	return;
}

template <typename myT>
Mat<myT>::Mat(const Mat<myT>& mat)
{
	row = mat.row;
	col = mat.col;
	if (row > 0 && col > 0)
	{
		num = new myT * [row];
		for (int i = 0; i < row; i++)
		{
			num[i] = new myT[col];
		}
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				num[i][j] = mat.num[i][j];
			}
		}
	}
	else
	{
		row = 0;
		col = 0;
		num = NULL;
	}
	return;
}

template <typename myT>
Mat<myT>::~Mat()
{
	if (num)
	{
		for (int i = 0; i < row; ++i)
		{
			delete[] num[i];
		}
		delete[] num;
	}
	return;
}

template <typename myT>
Mat<myT> Mat<myT>::operator+(const Mat<myT>& B)
{
	if (this->row == B.row && this->col == B.col)
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				this->num[i][j] += B.num[i][j];
			}
		}
		return *this;
	}
	else
	{
		Mat<myT> dummy(0, 0);
		string errorStr = "No matching matrix";
		throw errorStr;
		return dummy;
	}
}

template <typename myT>
Mat<myT> Mat<myT>::operator-(const Mat<myT>& B)
{
	if (this->row == B.row && this->col == B.col)
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				this->num[i][j] -= B.num[i][j];
			}
		}
		return *this;
	}
	else
	{
		Mat<myT> dummy(0, 0);
		string errorStr = "No matching matrix";
		throw errorStr;
		return dummy;
	}
}

template <typename myT>
Mat<myT>& Mat<myT>::operator=(const Mat<myT>& B)
{
	if (num)
	{
		for (int i = 0; i < row; ++i)
		{
			delete[] num[i];
		}
		delete num;
	}
	row = B.row;
	col = B.col;
	if (row > 0 && col > 0)
	{
		num = new myT * [row];
		for (int i = 0; i < row; ++i)
		{
			num[i] = new myT[col];
		}
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				num[i][j] = B.num[i][j];
			}
		}
	}
	else
	{
		row = 0;
		col = 0;
		num = NULL;
	}
	return *this;
}

template <typename myT>
myT* Mat<myT>::operator[](const int addr)
{
	return addr >= this->row ? NULL : this->num[addr];
}

template <typename T>
std::ostream& operator<<(std::ostream& strm, const Mat<T>& aim)
{
	for (int i = 0; i < aim.row; ++i)
	{
		for (int j = 0; j < aim.col; ++j)
		{
			strm << aim.num[i][j] << ((char)(j == aim.col - 1) ? '\n' : ' ');
		}
		return strm;
	}
}

template <typename T>
std::istream& operator>>(std::istream& strm, const Mat<T>& aim)
{
	for (int i = 0; i < aim.row; ++i)
	{
		for (int j = 0; j < aim.col; ++j)
		{
			strm >> aim.num[i][j];
		}
	}
	return strm;
}

template <typename myT>
Mat<myT> Mat<myT>::operator*(const Mat<myT>& B)
{
	Mat<myT> dummy(0, 0);
	if (this->row == 0 || this->col == 0 || B.row == 0 || B.col == 0 || this->col != B.row)
	{
		string str = "no matching matrix";
		throw str;
		exit(-1);
	}
	else
	{
		Mat<myT> res(this->row, B.col);
		myT trans;
		for (int i = 0; i < res.row; ++i)
		{
			for (int j = 0; j < res.col; ++j)
			{
				trans = 0;
				for (int k = 0; k < this->col; ++k)
				{
					trans += this->num[i][k] * B.num[k][j];
				}
				res.num[i][j] = trans;
			}
		}
		return res;
	}
	return dummy;
}
template <typename myT>
Mat<myT> Mat<myT>::Transpose()
{
	Mat<myT> res(this->col, this->row);
	for (int i = 0; i < this->row; ++i)
	{
		for (int j = 0; j < this->col; ++j)
		{
			res.num[j][i] = this->num[i][j];
		}
	}
	return res;
}

/// <summary>
/// 矩阵左乘向量：矩阵 * 列向量 = 列向量
/// 矩阵在左边，向量在右边，所以叫左乘
/// </summary>
/// <typeparam name="myT"></typeparam>
/// <param name="matrix"></param>
/// <param name="vector"></param>
/// <returns></returns>
template <typename myT>
Mat<myT> Mat<myT>::Premultiply_vec(const Mat<myT>& matrix, const vector3& vec)
{
	// vector3 转成 列向量
	vector<vector<int>> colVector(4, vector<int>(4, 0));
	colVector[0][0] = vec.x;
	colVector[0][1] = vec.y;
	colVector[0][2] = vec.z;

	// A矩阵的列 必须等于 B矩阵的行
	if (matrix.col != colVector.size())
	{
		string str = "no matching matrix";
		throw str;
		Mat<myT> dummy(0, 0);
		return dummy;
	}
	Mat<myT> res(matrix.row, colVector[0].size());
	myT sum;
	for (int i = 0; i < res.row; ++i)
	{
		for (int j = 0; j < res.col; ++j)
		{
			sum = 0;
			for (int k = 0; k < matrix.col; ++k)
			{
				sum += matrix.num[i][k] * colVector[k][j];
			}
			res.num[i][j] = sum;
		}
	}
	return res;
}

/// <summary>
/// 两个矩阵相乘
/// </summary>
/// <param name="matrix">矩阵A</param>
/// <param name="vector">矩阵B</param>
/// <returns></returns>
template <typename myT>
Mat<myT> Mat<myT>::Premultiply(const Mat<myT>& matrix, const Mat<myT>& vector)
{
	if (matrix.col != vector.row)
	{
		string str = "no matching matrix";
		throw str;
		Mat<myT> dummy(0, 0);
		return dummy;
	}
	Mat<myT> res(matrix.row, vector.col);
	myT sum;
	for (int i = 0; i < res.row; ++i)
	{
		for (int j = 0; j < res.col; ++j)
		{
			sum = 0;
			for (int k = 0; k < matrix.col; ++k)
			{
				sum += matrix.num[i][k] * vector.num[k][j];
			}
			res.num[i][j] = sum;
		}
	}
	return res;
}

// 矩阵右乘向量：行向量 * 矩阵 = 行向量
// 矩阵在右边，向量在左边，所以叫右乘
template <typename myT>
Mat<myT> Mat<myT>::Postmultiply(const Mat<myT>& vector, const Mat<myT>& matrix)
{
	if (vector.col != matrix.row)
	{
		string str = "no matching matrix";
		throw str;
		Mat<myT> dummy(0, 0);
		return dummy;
	}
	Mat<myT> res(vector.row, matrix.col);
	myT sum;
	for (int i = 0; i < res.row; ++i)
	{
		for (int j = 0; j < res.col; ++j)
		{
			sum = 0;
			for (int k = 0; k < matrix.row; ++k)
			{
				sum += vector.num[i][k] * matrix.num[k][j];
			}
			res.num[i][j] = sum;
		}
	}
	return res;
}

/// <summary>
/// 创建单位矩阵
/// </summary>
/// <returns>单位矩阵</returns>
template<typename myT>
Mat<myT> Mat<myT>::Identity()
{
	int n = this->row;
	for (int i = 0; i < n; i++) {
		this->num[i][i] = 1;
	}
	return *this;
}
#endif
