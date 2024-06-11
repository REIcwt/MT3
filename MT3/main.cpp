#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cal.h>
#include <DrawGrid.h>
#include "ImGuiManager.h"

const char kWindowTitle[] = "GC2B_09_シュウ_エイトウ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	float kWindowWidth = 1280;
	float kWindowHeight = 720;

	int mousePosX, mousePosY;
	int preMousePosX, preMousePosY;
	Novice::GetMousePosition(&mousePosX, &mousePosY);
	Novice::GetMousePosition(&preMousePosX, &preMousePosY);
	bool isMousePressed = false;

	///

	AABB aabb1 = {
		{-0.5f, -0.5f, -0.5f},
		{0.5f, 0.5f, 0.5f}
	};
	AABB aabb2 = {
		{0.2f, 0.2f, 0.2f},
		{1.0f, 1.0f, 1.0f}
	};

	
	///
	Vector3 rotate{0,0,0 };
	Vector3 translate{ 0,0,0 };

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

#pragma region Mouse Control Cam

		Novice::GetMousePosition(&mousePosX, &mousePosY);

		if (Novice::IsPressMouse(1)) {
			isMousePressed = true;
		}
		else {
			isMousePressed = false;
		}
		//z-
		if (isMousePressed) {
			float deltaX = float(mousePosX - preMousePosX);
			float deltaY = float(mousePosY - preMousePosY);

			cameraRotate.y += deltaX * 0.005f;
			cameraRotate.x += deltaY * 0.005f;

			if (cameraRotate.x > float(M_PI_2)) {
				cameraRotate.x = float(M_PI_2);
			}
			else if (cameraRotate.x < float(-M_PI_2)) {
				cameraRotate.x = float(-M_PI_2);
			}
		}
		
		//x-y-
		if (keys[DIK_A]) {
			cameraTranslate.x -= 0.05f;
		}
		else if (keys[DIK_D]) {
			cameraTranslate.x += 0.05f;
		}

		if (keys[DIK_W]) {
			cameraTranslate.y += 0.05f;
		}
		else if (keys[DIK_S]) {
			cameraTranslate.y -= 0.05f;
		}

		int scroll = Novice::GetWheel();
		if (scroll != 0) {
			cameraTranslate.z += scroll * 0.001f;
		}

			preMousePosX = mousePosX;
			preMousePosY = mousePosY;
#pragma endregion

		///
		/// ↓更新処理ここから
		///

		ImGui::Begin("Debug");
		ImGui::DragFloat3("CameraTranslate", &translate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &rotate.x, 0.01f);
		ImGui::DragFloat3("AABB1.min", &aabb1.min.x, 0.01f);
		ImGui::DragFloat3("AABB1.max", &aabb1.max.x, 0.01f);
		ImGui::DragFloat3("AABB2.min", &aabb2.min.x, 0.01f);
		ImGui::DragFloat3("AABB2.max", &aabb2.max.x, 0.01f);
		ImGui::End();

		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);

		aabb2.min.x = (std::min)(aabb2.min.x, aabb2.max.x);
		aabb2.max.x = (std::max)(aabb2.min.x, aabb2.max.x);
		aabb2.min.y = (std::min)(aabb2.min.y, aabb2.max.y);
		aabb2.max.y = (std::max)(aabb2.min.y, aabb2.max.y);
		aabb2.min.z = (std::min)(aabb2.min.z, aabb2.max.z);
		aabb2.max.z = (std::max)(aabb2.min.z, aabb2.max.z);

		if (IsCollision(aabb1, aabb2)) {
			aabb1.color = RED;
		}
		else {
			aabb1.color = WHITE;
		}

		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f,1.0f,1.0f}, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, aabb1.color);
		DrawAABB(aabb2, worldViewProjectionMatrix, viewportMatrix, WHITE);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
