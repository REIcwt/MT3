#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include<cmath>

struct Vector3 {
	float x, y, z;
};

struct Matrix4x4 {
	float m[4][4];
};

//move
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{};
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
};

//size
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;
	return result;
};

//X axis
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result{};

	result.m[0][0] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[1][1] = std::cos(radian);
	result.m[2][1] = std::sin(radian) * -1;
	result.m[1][2] = std::sin(radian);
	result.m[2][2] = std::cos(radian);

	return result;
};

//Y axis
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result{};

	result.m[1][1] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[0][0] = std::cos(radian);
	result.m[2][0] = std::sin(radian);
	result.m[0][2] = std::sin(radian) * -1;
	result.m[2][2] = std::cos(radian);

	return result;
};

//Z axis
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{};

	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[0][0] = std::cos(radian);
	result.m[1][0] = std::sin(radian) * -1;
	result.m[0][1] = std::sin(radian);
	result.m[1][1] = std::cos(radian);

	return result;
};

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

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result{};
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);

	Matrix4x4 rotateMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	result = Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));
	return result;
};

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
