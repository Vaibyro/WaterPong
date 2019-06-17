#pragma once

#include <iostream>

using namespace std;

class Matrix4
{
private:
	double values[16];
public:
	Matrix4();
	Matrix4(double v[16]);
	Matrix4(double v00, double v01, double v02, double v03,
		double v10, double v11, double v12, double v13,
		double v20, double v21, double v22, double v23,
		double v30, double v31, double v32, double v33);
	double getValue(int i, int j) const { return values[4 * i + j]; };
	void setValue(int i, int j, double value) { values[4 * i + j] = value; };
	double trace() const;
	void inverse();
	Matrix4 transpose();

	static Matrix4 identity() { return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); };
};

std::ostream& operator<<(std::ostream& os, const Matrix4& mat);
Matrix4 operator*(const Matrix4 &m1, const Matrix4 &m2);