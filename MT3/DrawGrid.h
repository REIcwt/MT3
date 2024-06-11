#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include<cmath>
#include <cal.h>


void DrawGrid(const Matrix4x4& worldViewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10; ///how many 

	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex){
		float x = -kGridHalfWidth + xIndex * kGridEvery;
		Vector3 Xstart = { x, 0, -kGridHalfWidth };
		Vector3 Xend = { x, 0, kGridHalfWidth };

		Xstart = Transform(Xstart, worldViewProjectionMatrix);
		Xstart = Transform(Xstart, viewportMatrix);
		Xend = Transform(Xend, worldViewProjectionMatrix);
		Xend = Transform(Xend, viewportMatrix);

		Novice::DrawLine(int(Xstart.x), int(Xstart.y), int(Xend.x), int(Xend.y), 0xAAAAAAFF);
		if (xIndex==5) {
			Novice::DrawLine(int(Xstart.x), int(Xstart.y), int(Xend.x), int(Xend.y), 0x000000FF);
	}
	}
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		float z = -kGridHalfWidth + zIndex * kGridEvery;
		Vector3 Zstart = { -kGridHalfWidth, 0, z };
		Vector3 Zend = { kGridHalfWidth, 0, z };

		Zstart = Transform(Zstart, worldViewProjectionMatrix);
		Zstart = Transform(Zstart, viewportMatrix);
		Zend = Transform(Zend, worldViewProjectionMatrix);
		Zend = Transform(Zend, viewportMatrix);

		Novice::DrawLine(int(Zstart.x), int(Zstart.y), int(Zend.x), int(Zend.y), 0xAAAAAAFF);
		if (zIndex == 5) {
			Novice::DrawLine(int(Zstart.x), int(Zstart.y), int(Zend.x), int(Zend.y), 0x000000FF);
	}
}
}

struct AABB {
    Vector3 min;
    Vector3 max;
	uint32_t color;
};

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 vertices[8];
	vertices[0] = { aabb.min.x, aabb.min.y, aabb.min.z };
	vertices[1] = { aabb.max.x, aabb.min.y, aabb.min.z };
	vertices[2] = { aabb.min.x, aabb.max.y, aabb.min.z };
	vertices[3] = { aabb.max.x, aabb.max.y, aabb.min.z };
	vertices[4] = { aabb.min.x, aabb.min.y, aabb.max.z };
	vertices[5] = { aabb.max.x, aabb.min.y, aabb.max.z };
	vertices[6] = { aabb.min.x, aabb.max.y, aabb.max.z };
	vertices[7] = { aabb.max.x, aabb.max.y, aabb.max.z };

	for (int i = 0; i < 8; ++i) {
		vertices[i] = Transform(vertices[i], viewProjectionMatrix);
		vertices[i] = Transform(vertices[i], viewportMatrix);
	}

	Novice::DrawLine(int(vertices[0].x), int(vertices[0].y), int(vertices[1].x), int(vertices[1].y), color);
	Novice::DrawLine(int(vertices[1].x), int(vertices[1].y), int(vertices[3].x), int(vertices[3].y), color);
	Novice::DrawLine(int(vertices[3].x), int(vertices[3].y), int(vertices[2].x), int(vertices[2].y), color);
	Novice::DrawLine(int(vertices[2].x), int(vertices[2].y), int(vertices[0].x), int(vertices[0].y), color);

	Novice::DrawLine(int(vertices[4].x), int(vertices[4].y), int(vertices[5].x), int(vertices[5].y), color);
	Novice::DrawLine(int(vertices[5].x), int(vertices[5].y), int(vertices[7].x), int(vertices[7].y), color);
	Novice::DrawLine(int(vertices[7].x), int(vertices[7].y), int(vertices[6].x), int(vertices[6].y), color);
	Novice::DrawLine(int(vertices[6].x), int(vertices[6].y), int(vertices[4].x), int(vertices[4].y), color);

	Novice::DrawLine(int(vertices[0].x), int(vertices[0].y), int(vertices[4].x), int(vertices[4].y), color);
	Novice::DrawLine(int(vertices[1].x), int(vertices[1].y), int(vertices[5].x), int(vertices[5].y), color);
	Novice::DrawLine(int(vertices[2].x), int(vertices[2].y), int(vertices[6].x), int(vertices[6].y), color);
	Novice::DrawLine(int(vertices[3].x), int(vertices[3].y), int(vertices[7].x), int(vertices[7].y), color);
}


bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	return (aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z);
}

