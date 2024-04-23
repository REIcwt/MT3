#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

struct Matrix4x4 {
	float m[4][4];
};

#pragma region Add
///Add
static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
};
#pragma endregion

#pragma region Subtract
///Subtract
static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
};
#pragma endregion

#pragma region Multiply
///Multiply
static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
};
#pragma endregion

#pragma region Inverse
///Inverse
static Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result{};
	float determinant = m.m[0][0] * (m.m[1][1] * m.m[2][2] * m.m[3][3] +
		m.m[2][1] * m.m[3][2] * m.m[1][3] +
		m.m[3][1] * m.m[1][2] * m.m[2][3] -
		m.m[3][1] * m.m[2][2] * m.m[1][3] -
		m.m[2][1] * m.m[1][2] * m.m[3][3] -
		m.m[1][1] * m.m[3][2] * m.m[2][3]) -
		m.m[0][1] * (m.m[1][0] * m.m[2][2] * m.m[3][3] +
			m.m[2][0] * m.m[3][2] * m.m[1][3] +
			m.m[3][0] * m.m[1][2] * m.m[2][3] -
			m.m[3][0] * m.m[2][2] * m.m[1][3] -
			m.m[2][0] * m.m[1][2] * m.m[3][3] -
			m.m[1][0] * m.m[3][2] * m.m[2][3]) +
		m.m[0][2] * (m.m[1][0] * m.m[2][1] * m.m[3][3] +
			m.m[2][0] * m.m[3][1] * m.m[1][3] +
			m.m[3][0] * m.m[1][1] * m.m[2][3] -
			m.m[3][0] * m.m[2][1] * m.m[1][3] -
			m.m[2][0] * m.m[1][1] * m.m[3][3] -
			m.m[1][0] * m.m[3][1] * m.m[2][3]) -
		m.m[0][3] * (m.m[1][0] * m.m[2][1] * m.m[3][2] +
			m.m[2][0] * m.m[3][1] * m.m[1][2] +
			m.m[3][0] * m.m[1][1] * m.m[2][2] -
			m.m[3][0] * m.m[2][1] * m.m[1][2] -
			m.m[2][0] * m.m[1][1] * m.m[3][2] -
			m.m[1][0] * m.m[3][1] * m.m[2][2]);



	if (determinant != 0) {
		result.m[0][0] = (m.m[1][1] * m.m[2][2] * m.m[3][3] +
			m.m[2][1] * m.m[3][2] * m.m[1][3] +
			m.m[3][1] * m.m[1][2] * m.m[2][3] -
			m.m[3][1] * m.m[2][2] * m.m[1][3] -
			m.m[2][1] * m.m[1][2] * m.m[3][3] -
			m.m[1][1] * m.m[3][2] * m.m[2][3]) /
			determinant;

		result.m[0][1] = -(m.m[0][1] * m.m[2][2] * m.m[3][3] +
			m.m[2][1] * m.m[3][2] * m.m[0][3] +
			m.m[3][1] * m.m[0][2] * m.m[2][3] -
			m.m[3][1] * m.m[2][2] * m.m[0][3] -
			m.m[2][1] * m.m[0][2] * m.m[3][3] -
			m.m[0][1] * m.m[3][2] * m.m[2][3]) /
			determinant;

		result.m[0][2] = (m.m[0][1] * m.m[1][2] * m.m[3][3] +
			m.m[1][1] * m.m[3][2] * m.m[0][3] +
			m.m[3][1] * m.m[0][2] * m.m[1][3] -
			m.m[3][1] * m.m[1][2] * m.m[0][3] -
			m.m[1][1] * m.m[0][2] * m.m[3][3] -
			m.m[0][1] * m.m[3][2] * m.m[1][3]) /
			determinant;

		result.m[0][3] = -(m.m[0][1] * m.m[1][2] * m.m[2][3] +
			m.m[1][1] * m.m[2][2] * m.m[0][3] +
			m.m[2][1] * m.m[0][2] * m.m[1][3] -
			m.m[2][1] * m.m[1][2] * m.m[0][3] -
			m.m[1][1] * m.m[0][2] * m.m[2][3] -
			m.m[0][1] * m.m[2][2] * m.m[1][3]) /
			determinant;


		result.m[1][0] = -(m.m[1][0] * m.m[2][2] * m.m[3][3] +
			m.m[2][0] * m.m[3][2] * m.m[1][3] +
			m.m[3][0] * m.m[1][2] * m.m[2][3] -
			m.m[3][0] * m.m[2][2] * m.m[1][3] -
			m.m[2][0] * m.m[1][2] * m.m[3][3] -
			m.m[1][0] * m.m[3][2] * m.m[2][3]) /
			determinant;

		result.m[1][1] = (m.m[0][0] * m.m[2][2] * m.m[3][3] +
			m.m[2][0] * m.m[3][2] * m.m[0][3] +
			m.m[3][0] * m.m[0][2] * m.m[2][3] -
			m.m[3][0] * m.m[2][2] * m.m[0][3] -
			m.m[2][0] * m.m[0][2] * m.m[3][3] -
			m.m[0][0] * m.m[3][2] * m.m[2][3]) /
			determinant;

		result.m[1][2] = -(m.m[0][0] * m.m[1][2] * m.m[3][3] +
			m.m[1][0] * m.m[3][2] * m.m[0][3] +
			m.m[3][0] * m.m[0][2] * m.m[1][3] -
			m.m[3][0] * m.m[1][2] * m.m[0][3] -
			m.m[1][0] * m.m[0][2] * m.m[3][3] -
			m.m[0][0] * m.m[3][2] * m.m[1][3]) /
			determinant;

		result.m[1][3] = (m.m[0][0] * m.m[1][2] * m.m[2][3] +
			m.m[1][0] * m.m[2][2] * m.m[0][3] +
			m.m[2][0] * m.m[0][2] * m.m[1][3] -
			m.m[2][0] * m.m[1][2] * m.m[0][3] -
			m.m[1][0] * m.m[0][2] * m.m[2][3] -
			m.m[0][0] * m.m[2][2] * m.m[1][3]) /
			determinant;


		result.m[2][0] = (m.m[1][0] * m.m[2][1] * m.m[3][3] +
			m.m[2][0] * m.m[3][1] * m.m[1][3] +
			m.m[3][0] * m.m[1][1] * m.m[2][3] -
			m.m[3][0] * m.m[2][1] * m.m[1][3] -
			m.m[2][0] * m.m[1][1] * m.m[3][3] -
			m.m[1][0] * m.m[3][1] * m.m[2][3]) /
			determinant;

		result.m[2][1] = -(m.m[0][0] * m.m[2][1] * m.m[3][3] +
			m.m[2][0] * m.m[3][1] * m.m[0][3] +
			m.m[3][0] * m.m[0][1] * m.m[2][3] -
			m.m[3][0] * m.m[2][1] * m.m[0][3] -
			m.m[2][0] * m.m[0][1] * m.m[3][3] -
			m.m[0][0] * m.m[3][1] * m.m[2][3]) /
			determinant;

		result.m[2][2] = (m.m[0][0] * m.m[1][1] * m.m[3][3] +
			m.m[1][0] * m.m[3][1] * m.m[0][3] +
			m.m[3][0] * m.m[0][1] * m.m[1][3] -
			m.m[3][0] * m.m[1][1] * m.m[0][3] -
			m.m[1][0] * m.m[0][1] * m.m[3][3] -
			m.m[0][0] * m.m[3][1] * m.m[1][3]) /
			determinant;

		result.m[2][3] = -(m.m[0][0] * m.m[1][1] * m.m[2][3] +
			m.m[1][0] * m.m[2][1] * m.m[0][3] +
			m.m[2][0] * m.m[0][1] * m.m[1][3] -
			m.m[2][0] * m.m[1][1] * m.m[0][3] -
			m.m[1][0] * m.m[0][1] * m.m[2][3] -
			m.m[0][0] * m.m[2][1] * m.m[1][3]) /
			determinant;

		result.m[3][0] = -(m.m[1][0] * m.m[2][1] * m.m[3][2] +
			m.m[2][0] * m.m[3][1] * m.m[1][2] +
			m.m[3][0] * m.m[1][1] * m.m[2][2] -
			m.m[3][0] * m.m[2][1] * m.m[1][2] -
			m.m[2][0] * m.m[1][1] * m.m[3][2] -
			m.m[1][0] * m.m[3][1] * m.m[2][2]) /
			determinant;

		result.m[3][1] = (m.m[0][0] * m.m[2][1] * m.m[3][2] +
			m.m[2][0] * m.m[3][1] * m.m[0][2] +
			m.m[3][0] * m.m[0][1] * m.m[2][2] -
			m.m[3][0] * m.m[2][1] * m.m[0][2] -
			m.m[2][0] * m.m[0][1] * m.m[3][2] -
			m.m[0][0] * m.m[3][1] * m.m[2][2]) /
			determinant;

		result.m[3][2] = -(m.m[0][0] * m.m[1][1] * m.m[3][2] +
			m.m[1][0] * m.m[3][1] * m.m[0][2] +
			m.m[3][0] * m.m[0][1] * m.m[1][2] -
			m.m[3][0] * m.m[1][1] * m.m[0][2] -
			m.m[1][0] * m.m[0][1] * m.m[3][2] -
			m.m[0][0] * m.m[3][1] * m.m[1][2]) /
			determinant;

		result.m[3][3] = (m.m[0][0] * m.m[1][1] * m.m[2][2] +
			m.m[1][0] * m.m[2][1] * m.m[0][2] +
			m.m[2][0] * m.m[0][1] * m.m[1][2] -
			m.m[2][0] * m.m[1][1] * m.m[0][2] -
			m.m[1][0] * m.m[0][1] * m.m[2][2] -
			m.m[0][0] * m.m[2][1] * m.m[1][2]) /
			determinant;
	}


	return result;
};
#pragma endregion

#pragma region Transpose
///Transpose
static Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}
	return result;
};
#pragma endregion

#pragma region MakeIdentity4x4
///MakeIdentity4x4
static Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				result.m[i][j] = 1.0f;  // Set diagonal elements to 1
			}
			else {
				result.m[i][j] = 0.0f;  // Set off-diagonal elements to 0
			}
		}
	}
	return result;
};
#pragma endregion

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
static void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* lable) {
	Novice::ScreenPrintf(x, y, "%s", lable);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + 20 + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}
