#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
struct Vector2 {
	float x;
	float y;
};

struct Matrix4x4 {
	float m[4][4];
};

#pragma region Add
///Add
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
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
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
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
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
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
float Inverse(const Matrix4x4& m) {
	Matrix4x4 result{};
	float determinant = matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
		matrix.m[2][1] * matrix.m[3][2] * matrix.m[1][3] +
		matrix.m[3][1] * matrix.m[1][2] * matrix.m[2][3] -
		matrix.m[3][1] * matrix.m[2][2] * matrix.m[1][3] -
		matrix.m[2][1] * matrix.m[1][2] * matrix.m[3][3] -
		matrix.m[1][1] * matrix.m[3][2] * matrix.m[2][3]) -
		matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][2] * matrix.m[1][3] +
			matrix.m[3][0] * matrix.m[1][2] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][2] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][2] * matrix.m[3][3] -
			matrix.m[1][0] * matrix.m[3][2] * matrix.m[2][3]) +
		matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][3] +
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][3] -
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][3]) -
		matrix.m[0][3] * (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][2] +
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][2] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][2] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][2] -
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][2]);



	if (determinant != 0) {
		result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][1] * matrix.m[3][2] * matrix.m[1][3] +
			matrix.m[3][1] * matrix.m[1][2] * matrix.m[2][3] -
			matrix.m[3][1] * matrix.m[2][2] * matrix.m[1][3] -
			matrix.m[2][1] * matrix.m[1][2] * matrix.m[3][3] -
			matrix.m[1][1] * matrix.m[3][2] * matrix.m[2][3]) /
			determinant;

		result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][1] * matrix.m[3][2] * matrix.m[0][3] +
			matrix.m[3][1] * matrix.m[0][2] * matrix.m[2][3] -
			matrix.m[3][1] * matrix.m[2][2] * matrix.m[0][3] -
			matrix.m[2][1] * matrix.m[0][2] * matrix.m[3][3] -
			matrix.m[0][1] * matrix.m[3][2] * matrix.m[2][3]) /
			determinant;

		result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] * matrix.m[3][3] +
			matrix.m[1][1] * matrix.m[3][2] * matrix.m[0][3] +
			matrix.m[3][1] * matrix.m[0][2] * matrix.m[1][3] -
			matrix.m[3][1] * matrix.m[1][2] * matrix.m[0][3] -
			matrix.m[1][1] * matrix.m[0][2] * matrix.m[3][3] -
			matrix.m[0][1] * matrix.m[3][2] * matrix.m[1][3]) /
			determinant;

		result.m[0][3] = -(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] +
			matrix.m[1][1] * matrix.m[2][2] * matrix.m[0][3] +
			matrix.m[2][1] * matrix.m[0][2] * matrix.m[1][3] -
			matrix.m[2][1] * matrix.m[1][2] * matrix.m[0][3] -
			matrix.m[1][1] * matrix.m[0][2] * matrix.m[2][3] -
			matrix.m[0][1] * matrix.m[2][2] * matrix.m[1][3]) /
			determinant;


		result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][2] * matrix.m[1][3] +
			matrix.m[3][0] * matrix.m[1][2] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][2] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][2] * matrix.m[3][3] -
			matrix.m[1][0] * matrix.m[3][2] * matrix.m[2][3]) /
			determinant;

		result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][2] * matrix.m[0][3] +
			matrix.m[3][0] * matrix.m[0][2] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][2] * matrix.m[0][3] -
			matrix.m[2][0] * matrix.m[0][2] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[3][2] * matrix.m[2][3]) /
			determinant;

		result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] * matrix.m[3][3] +
			matrix.m[1][0] * matrix.m[3][2] * matrix.m[0][3] +
			matrix.m[3][0] * matrix.m[0][2] * matrix.m[1][3] -
			matrix.m[3][0] * matrix.m[1][2] * matrix.m[0][3] -
			matrix.m[1][0] * matrix.m[0][2] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[3][2] * matrix.m[1][3]) /
			determinant;

		result.m[1][3] = (matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] +
			matrix.m[1][0] * matrix.m[2][2] * matrix.m[0][3] +
			matrix.m[2][0] * matrix.m[0][2] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][2] * matrix.m[0][3] -
			matrix.m[1][0] * matrix.m[0][2] * matrix.m[2][3] -
			matrix.m[0][0] * matrix.m[2][2] * matrix.m[1][3]) /
			determinant;


		result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][3] +
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][3] -
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][3]) /
			determinant;

		result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][3] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[0][3] +
			matrix.m[3][0] * matrix.m[0][1] * matrix.m[2][3] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[0][3] -
			matrix.m[2][0] * matrix.m[0][1] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[3][1] * matrix.m[2][3]) /
			determinant;

		result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][3] +
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[0][3] +
			matrix.m[3][0] * matrix.m[0][1] * matrix.m[1][3] -
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[0][3] -
			matrix.m[1][0] * matrix.m[0][1] * matrix.m[3][3] -
			matrix.m[0][0] * matrix.m[3][1] * matrix.m[1][3]) /
			determinant;

		result.m[2][3] = -(matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] +
			matrix.m[1][0] * matrix.m[2][1] * matrix.m[0][3] +
			matrix.m[2][0] * matrix.m[0][1] * matrix.m[1][3] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[0][3] -
			matrix.m[1][0] * matrix.m[0][1] * matrix.m[2][3] -
			matrix.m[0][0] * matrix.m[2][1] * matrix.m[1][3]) /
			determinant;

		result.m[3][0] = -(matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[1][2] +
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[2][2] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[1][2] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[3][2] -
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[2][2]) /
			determinant;

		result.m[3][1] = (matrix.m[0][0] * matrix.m[2][1] * matrix.m[3][2] +
			matrix.m[2][0] * matrix.m[3][1] * matrix.m[0][2] +
			matrix.m[3][0] * matrix.m[0][1] * matrix.m[2][2] -
			matrix.m[3][0] * matrix.m[2][1] * matrix.m[0][2] -
			matrix.m[2][0] * matrix.m[0][1] * matrix.m[3][2] -
			matrix.m[0][0] * matrix.m[3][1] * matrix.m[2][2]) /
			determinant;

		result.m[3][2] = -(matrix.m[0][0] * matrix.m[1][1] * matrix.m[3][2] +
			matrix.m[1][0] * matrix.m[3][1] * matrix.m[0][2] +
			matrix.m[3][0] * matrix.m[0][1] * matrix.m[1][2] -
			matrix.m[3][0] * matrix.m[1][1] * matrix.m[0][2] -
			matrix.m[1][0] * matrix.m[0][1] * matrix.m[3][2] -
			matrix.m[0][0] * matrix.m[3][1] * matrix.m[1][2]) /
			determinant;

		result.m[3][3] = (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
			matrix.m[1][0] * matrix.m[2][1] * matrix.m[0][2] +
			matrix.m[2][0] * matrix.m[0][1] * matrix.m[1][2] -
			matrix.m[2][0] * matrix.m[1][1] * matrix.m[0][2] -
			matrix.m[1][0] * matrix.m[0][1] * matrix.m[2][2] -
			matrix.m[0][0] * matrix.m[2][1] * matrix.m[1][2]) /
			determinant;
	}

	return result;
};
#pragma endregion
#pragma region Transpose
///Transpose
float Transpose(const Matrix4x4& m) {
	
};
#pragma endregion
#pragma region MakeIdentity4x4
///Normalize
Matrix4x4 MakeIdentity4x4();
#pragma endregion

static const int kColumnHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kColumnHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}
