#ifndef __MATRIX_2_H__
#define __MATRIX_2_H__
#include <iostream>
template <typename myT>
class Mat
{
public:
	int row;
	int col;
	myT **num;

	Mat(const int, const int);
	Mat(const Mat<myT> &);
	~Mat();
	Mat operator+(const Mat<myT> &);
	Mat operator-(const Mat<myT> &);
	Mat operator*(const Mat<myT> &);
	Mat &operator=(const Mat<myT> &);
	myT *operator[](const int);
	// Mat Hadamard(const Mat<myT> &); // Hadamard Matrix
	Mat Transpose(); // zhuan zhi matrix
	template <typename T>
	friend ostream &operator<<(ostream &, const Mat<T> &);
	template <typename T>
	friend istream &operator>>(istream &, const Mat<T> &);

	Mat Premultiply(const Mat<myT> &vector, const Mat<myT> &matrix);
	Mat Postmultiply(const Mat<myT> &matrix, const Mat<myT> &vector);
};

template <typename myT>
Mat<myT>::Mat(const int r, const int c)
{
	row = r;
	col = c;
	if (row > 0 && col > 0)
	{
		num = new myT *[row]; // myT* [pointer]
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
Mat<myT>::Mat(const Mat<myT> &mat)
{
	row = mat.row;
	col = mat.col;
	if (row > 0 && col > 0)
	{
		num = new myT *[row];
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
Mat<myT> Mat<myT>::operator+(const Mat<myT> &B)
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
Mat<myT> Mat<myT>::operator-(const Mat<myT> &B)
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
Mat<myT> &Mat<myT>::operator=(const Mat<myT> &B)
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
		num = new myT *[row];
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
myT *Mat<myT>::operator[](const int addr)
{
	return addr >= this->row ? NULL : this->num[addr];
}

template <typename T>
std::ostream &operator<<(std::ostream &strm, const Mat<T> &aim)
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
std::istream &operator>>(std::istream &strm, const Mat<T> &aim)
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
Mat<myT> Mat<myT>::operator*(const Mat<myT> &B)
{
	Mat<myT> dummy(0, 0);
	if (!this->row || !this->col || B.row || B.col || this->col != B.row)
	{
		string str = "no matching matrix";
		throw str;
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

template <typename myT>
Mat<myT> Mat<myT>::Premultiply(const Mat<myT> &vector, const Mat<myT> &matrix)
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

template <typename myT>
Mat<myT> Mat<myT>::Postmultiply(const Mat<myT> &matrix, const Mat<myT> &vector)
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
#endif