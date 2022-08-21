#include "Model_example.h"
using namespace std;
int main() {

	Model<float> pointX(0, 0, 0);
	Mat<float> modelMatrixX(4,4);
	modelMatrixX = pointX.ModelMatrix(5, 5, 0);

	cout << "Model Matrix:" << endl;
	for (int i = 0; i < modelMatrixX.row; i++) {
		for (int j = 0; j < modelMatrixX.col; j++) {
			cout << modelMatrixX.num[i][j] << ",";
		}
		cout << endl;
	}
	return 0;
}