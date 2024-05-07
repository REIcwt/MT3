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

struct Sphere {
	Vector3 center;
	float radius;
};

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	const uint32_t kSubdivision = 20;
	const float kLonEvery = 2.0f *float(M_PI) / kSubdivision;
	const float kLatEvery = float(M_PI) / kSubdivision;

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex; 

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;

			Vector3 a = {
				sphere.center.x + sphere.radius * cosf(lat) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat),
				sphere.center.z + sphere.radius * cosf(lat) * sinf(lon)
			};

			Vector3 b = {
				sphere.center.x + sphere.radius * cosf(lat + kLatEvery) * cosf(lon),
				sphere.center.y + sphere.radius * sinf(lat + kLatEvery),
				sphere.center.z + sphere.radius * cosf(lat + kLatEvery) * sinf(lon)
			};

			Vector3 c = {
			   sphere.center.x + sphere.radius * cosf(lat) * cosf(lon + kLonEvery),
			   sphere.center.y + sphere.radius * sinf(lat),
			   sphere.center.z + sphere.radius * cosf(lat) * sinf(lon + kLonEvery)
			};
	
			a = Transform(a, viewProjectionMatrix);
			b = Transform(b, viewProjectionMatrix);
			c = Transform(c, viewProjectionMatrix);

			a = Transform(a, viewportMatrix);
			b = Transform(b, viewportMatrix);
			c = Transform(c, viewportMatrix);
			
			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y), color);
			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);
		}
	}
};