#include <iostream>
#include <iomanip>
#include <locale>
#include "matrix.h"
#include <vector>

Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
	{
		values[i] = 0;
	}
}

Matrix4::Matrix4(double v[16])
{
	for (int i = 0; i < 16; i++)
	{
		values[i] = v[i];
	}
}

Matrix4::Matrix4(double v00, double v01, double v02, double v03,
				double v10, double v11, double v12, double v13,
				double v20, double v21, double v22, double v23,
				double v30, double v31, double v32, double v33) 
{
	values[0] = v00; values[1] = v01; values[2] = v02; values[3] = v03;
	values[4] = v10; values[5] = v11; values[6] = v12; values[7] = v13;
	values[8] = v20; values[9] = v21; values[10] = v22; values[11] = v23;
	values[12] = v30; values[13] = v31; values[14] = v32; values[15] = v33;
}

double Matrix4::trace() const
{
	double res = 0.0;
	for (int i = 0; i < 4; i++) 
	{
		res += getValue(i, i);
	}
	return res;
}

void Matrix4::inverse()
{
	int n = 4;
	vector<double> line(2 * n, 0);
	vector< vector<double> > A(n, line);

	// Read input data
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = getValue(i, j);
		}
	}

	for (int i = 0; i < n; i++) {
		A[i][n + i] = 1;
	}

	for (int i = 0; i < n; i++) {
		// Search for maximum in this column
		double maxEl = abs(A[i][i]);
		int maxRow = i;
		for (int k = i + 1; k < n; k++) {
			if (abs(A[k][i]) > maxEl) {
				maxEl = A[k][i];
				maxRow = k;
			}
		}

		// Swap maximum row with current row (column by column)
		for (int k = i; k < 2 * n; k++) {
			double tmp = A[maxRow][k];
			A[maxRow][k] = A[i][k];
			A[i][k] = tmp;
		}

		// Make all rows below this one 0 in current column
		for (int k = i + 1; k < n; k++) {
			double c = -A[k][i] / A[i][i];
			for (int j = i; j < 2 * n; j++) {
				if (i == j) {
					A[k][j] = 0;
				}
				else {
					A[k][j] += c * A[i][j];
				}
			}
		}
	}

	// Solve equation Ax=b for an upper triangular matrix A
	for (int i = n - 1; i >= 0; i--) {
		for (int k = n; k < 2 * n; k++) {
			A[i][k] /= A[i][i];
			setValue(i, k - n, A[i][k]);
		}
		// this is not necessary, but the output looks nicer:
		A[i][i] = 1;

		for (int rowModify = i - 1; rowModify >= 0; rowModify--) {
			for (int columModify = n; columModify < 2 * n; columModify++) {
				A[rowModify][columModify] -= A[i][columModify]
					* A[rowModify][i];
			}
			// this is not necessary, but the output looks nicer:
			A[rowModify][i] = 0;
		}
	}
}

Matrix4 Matrix4::transpose() 
{
	Matrix4 res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res.setValue(i, j, getValue(j, i));
		}
	}
	return res;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& mat)
{
	for (int i = 0; i < 4; i++) {
		os << "| " << std::setw(4) << mat.getValue(i, 0) << " " 
			<< std::setw(4) << mat.getValue(i, 1) << " " 
			<< std::setw(4) << mat.getValue(i, 2) << " " 
			<< std::setw(4) << mat.getValue(i, 3) << " |" << endl;
	}
	return os;
}

Matrix4 operator*(const Matrix4 &m1, const Matrix4 &m2)
{
	Matrix4 res = Matrix4();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++) {
				res.setValue(i, j, res.getValue(i, j) + m1.getValue(i, k) * m2.getValue(k, j));
			}
		}
	}
	return res;
}
