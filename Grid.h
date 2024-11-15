#pragma once
#include "Actor.h"
#include <vector>
#include "Math.h"
#include "string"

class Grid : public Actor
{
public:
	Grid(class Game* game);

	//ターンの種類の定義
	enum TurnState
	{
		TURN_BLACK,
		TURN_WHITE,
		TURN_NONE
	};

	//方向の種類を定義
	enum DirState
	{
		DIRECTION_UP,		//上
		DIRECTION_UP_LEFT,	//左上
		DIRECTION_LEFT,		//左
		DIRECTION_DOWN_LEFT,//左下
		DIRECTION_DOWN,		//下
		DIRECTION_DOWN_RIGHT,//右下
		DIRECTION_RIGHT,	//右
		DIRECTION_UP_RIGHT,	//右上
		DIRECTION_MAX		//方向の数
	};

	//DirStateとリンクしたベクトルの方向を保存
	Vector2 DirectionsState[DIRECTION_MAX]
	{
		Vector2 { 0,-1},		//上
		Vector2 {-1,-1},		//左上
		Vector2 {-1, 0},		//左
		Vector2 {-1, 1},		//左下
		Vector2 { 0, 1},		//下
		Vector2 { 1, 1},		//右下
		Vector2 { 1, 0},		//右
		Vector2 { 1,-1}			//右上
	};
	// x/y座標のところでマウスクリックを処理する
	void ProcessClick(int x, int y);

	//石の設置
	void PlaceOthello();

	//ターンの切り替え
	void toggleTurn();

	//石が置けるかどうかを判定する関数
	bool CheckCanPlace(size_t row, size_t col, bool turnOver = false);

	//盤面上に石が置けるかどうかを判定する関数
	bool CheckCanPlaceAll(TurnState turn);

	//任意の石の数を数える関数
	int GetDiskCount(TurnState turn);

	// 開始/終了 のタイルの場所
	//class Tile* GetStartTile();
	//class Tile* GetEndTile();

	void UpdateActor(float deltaTime) override;
private:
	// 特定のタイルを選択
	void SelectTile(size_t row, size_t col);

	//描画するTextを配列についか
	void AddRenderText(const std::string& text);

	// パス上のタイルのテクスチャを更新する
	//void UpdatePathTiles(class Tile* start);

	// 現在選択されているタイル
	class Tile* mSelectedTile;

	//選択されている場所のRowとcol
	size_t selRow;
	size_t selCol;

	// グリッド内のタイルの2Dベクトル
	std::vector<std::vector<class Tile*>> mTiles;

	//ゲーム画面内での文字列
	std::vector<class Text*> mTexts;

	// 次の敵までの時間
	//float mNextEnemy;

	//現在のターンを保存
	TurnState turnState;

	// グリッドの行と列
	const size_t NumRows = 8;
	const size_t NumCols = 8;
	// 左上隅の開始y座標
	const float StartY = 192.0f;
	// 各タイルの幅と高さ
	const float TileSize = 64.0f;
	// 次のオセロを配置できるまでの時間
	//const float EnemyTime = 1.5f;
};
