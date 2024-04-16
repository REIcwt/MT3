#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cal.h>

const char kWindowTitle[] = "GC2B_09_シュウ_エイトウ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 v1{ 1.0f,3.0f,-5.0f };
		Matrix4x4 v2{ 4.0f,-1.0f,2.0f };
		float k = { 4.0f };

		Matrix4x4 resultAdd = Add(v1, v2);
		Matrix4x4 resultSubtract = Subtract(v1, v2);
		Matrix4x4 resultMultiply = Multiply(k, v1);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Matrix4x4 resultNormalize = Normalize(v2);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, resultAdd, " : Add");
		VectorScreenPrintf(0, kColumnWidth, resultSubtract, " : Subtract");
		VectorScreenPrintf(0, kColumnWidth * 2, resultMultiply, " : Multiply");
		Novice::ScreenPrintf(0, kColumnWidth * 3, "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(0, kColumnWidth * 4, "%.02f : Length", resultLength);
		VectorScreenPrintf(0, kColumnWidth * 5, resultNormalize, " : Normalize");

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
