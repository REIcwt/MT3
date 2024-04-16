#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
struct Vector2 {
	float x;
	float y;
};

struct Vector3 {
	float x, y, z;
};

#pragma region Add
///Add
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
};
#pragma endregion
#pragma region Subtract
///Subtract
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
};
#pragma endregion
#pragma region Multiply
///Multiply
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
};
#pragma endregion
#pragma region Dot
///Dot
float Dot(const Vector3& v1, const Vector3& v2) {
	return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
};
#pragma endregion
#pragma region Length
///Length
float Length(const Vector3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
};
#pragma endregion
#pragma region Normalize
///Normalize
Vector3 Normalize(const Vector3& v) {
	float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0) {
		return { 0, 0, 0 };
	}
	return { v.x / len, v.y / len, v.z / len };
};
#pragma endregion

static const int kColumnWidth = 50;
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* lable) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", lable);

}
