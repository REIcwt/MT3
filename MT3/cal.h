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

//MakePerspectiveFovMatrix
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result{};

	result.m[0][0] = ((1 / aspectRatio) * (1.0f / (tan(fovY / 2))));
	result.m[1][1] = (1.0f / (tan(fovY / 2)));

	result.m[2][2] = (farClip / (farClip - nearClip));
	result.m[3][2] = ((-nearClip * farClip) / (farClip - nearClip));

	result.m[2][3] = 1.0f;

	return result;
};
//MakeOrthographicMatrix
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result = {};
		
	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = -2.0f / (farClip - nearClip);
	result.m[3][3] = 1.0f;

	result.m[3][0] = -((right + left) / (right - left));
	result.m[3][1] = -((top + bottom) / (top - bottom));
	result.m[3][2] = nearClip / (farClip - nearClip));

	return result;
};

//MakeViewportMatrix
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result = {};

	result.m[0][0] = width / 2.0f;
	result.m[3][0] = left + width / 2.0f;

	result.m[1][1] = -height / 2.0f;
	result.m[3][1] = top + height / 2.0f;

	result.m[2][2] = maxDepth - minDepth;
	result.m[3][2] = minDepth;

	result.m[3][3] = 1.0f;

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
