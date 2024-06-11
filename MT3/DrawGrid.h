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

struct Segment {
	Vector3 origin;
	Vector3 diff;
	uint32_t color;
};

struct Plane {
	Vector3 normal;
	float distance;
	uint32_t color;
};

void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 start = Transform(segment.origin, viewProjectionMatrix);
	start = Transform(start, viewportMatrix);

	Vector3 end = Add(segment.origin, segment.diff);
	end = Transform(end, viewProjectionMatrix);
	end = Transform(end, viewportMatrix);

	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 center = Multiply(plane.normal, plane.distance);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(perpendiculars[index], 2.0f);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[0].x), int(points[0].y), color);
}

bool IsCollision(const Segment& segment, const Plane& plane) {
	float d1 = Dot(plane.normal, segment.origin) - plane.distance;
	float d2 = Dot(plane.normal, Add(segment.origin, segment.diff)) - plane.distance;

	return d1 * d2 <= 0.0f;
}