#include "Model_example.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix.h"
#include <vector>
#include <iostream>
using namespace std;
int main() {

	/*Model<float> pointX(0, 0, 0);
	Mat<float> modelMatrixX(4, 4);
	modelMatrixX = pointX.ModelMatrix(0, 0, 0);

	cout << "Model Matrix:" << endl;
	for (int i = 0; i < modelMatrixX.row; i++) {
		for (int j = 0; j < modelMatrixX.col; j++) {
			cout << modelMatrixX.num[i][j] << ",";
		}
		cout << endl;
	}*/

	vector3 a(3, 0, 0);
	vector3 b(0, 4, 0);
	vector3 c; 
	c = c.Cross(a, b);

	cout << c.x << "," << c.y << "," << c.z << endl;

	// ͶӰ�ռ����� = ĳ��������� * Model���� * View���� * Project����
	vector3 locPos(1, 1, 1);	// ��ı���λ����Ϣ
	vector3 worldPos(3, 4, 5);	// ��ı���λ����Ϣ
	vector4 quaternion(0, 0, 0, 1);	// �����ת��Ϣ
	vector3 scale(1, 1, 1);		// ���������Ϣ
	Model<float> model(locPos, worldPos, quaternion, scale);
	Mat<float> modelMat(4, 4);

	modelMat = model.ModelMatrix();

	for (int i = 0; i < modelMat.row; i++) {
		for (int j = 0; j < modelMat.col; j++) {
			cout << modelMat.num[i][j] << ",";
		}
		cout << endl;
	}
	return 0;
}