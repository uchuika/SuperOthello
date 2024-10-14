// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Grid.h"
#include "Tile.h"
//#include "Tower.h"
//#include "Enemy.h"
#include <algorithm>
#include "Math.h"

Grid::Grid(class Game* game)
	:Actor(game)
	, mSelectedTile(nullptr)
{
	// 7 rows, 16 columns
	mTiles.resize(NumRows);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(NumCols);
	}

	// タイルの作成
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(TileSize / 2.0f + j * TileSize, StartY + i * TileSize));
		}
	}

	//最初のターンを黒で初期化
	turnState = TURN_BLACK;

	//黒い石を配置
	mTiles[3][4]->SetTileState(Tile::EBlack);
	mTiles[4][3]->SetTileState(Tile::EBlack);

	//白い石を配置
	mTiles[3][3]->SetTileState(Tile::EWhite);
	mTiles[4][4]->SetTileState(Tile::EWhite);

}

void Grid::SelectTile(size_t row, size_t col)
{
	// 有効な選択であることを確認する
	//Tile::TileState tstate = mTiles[row][col]->GetTileState();

	if (CheckCanPlace(row, col)) {
		// 前の選択を解除する
		if (mSelectedTile)
		{
			mSelectedTile->ToggleSelect();
		}
		selRow = row;
		selCol = col;
		mSelectedTile = mTiles[row][col];
		mSelectedTile->ToggleSelect();

	}
	else {
		//printf("このますには石を置けません");
	}
}

void Grid::ProcessClick(int x, int y)
{
	y -= static_cast<int>(StartY - TileSize / 2);
	if (y >= 0)
	{
		x /= static_cast<int>(TileSize);
		y /= static_cast<int>(TileSize);
		if (x >= 0 && x < static_cast<int>(NumCols) && y >= 0 && y < static_cast<int>(NumRows))
		{
			SelectTile(y, x);
		}
	}
}

//石を置けるかどうかの判定
bool Grid::CheckCanPlace(size_t row, size_t col, bool turnOver)
{
	//置けるかどうかのフラグを宣言
	bool canPlace = false;


	//対象の座標にすでに石が置かれていないかを判定する
	Tile::TileState tstate = mTiles[row][col]->GetTileState();

	//相手の石のタイル
	Tile::TileState opponentTile;
	Tile::TileState turnTile;
	if (turnState == TURN_BLACK)
	{
		opponentTile = Tile::EWhite;
		turnTile = Tile::EBlack;
	}else
	{
		opponentTile = Tile::EBlack;
		turnTile = Tile::EWhite;
	}

	if ((tstate == Tile::EBlack || tstate == Tile::EWhite) && !turnOver)
	{
		//置けないを返す
		printf("すでに置かれているので置けない\n");
		return false;
	}
	Vector2 currentPosition = Vector2(col, row);
	printf("%d\n", turnState);
	printf("敵の石:%d\n", opponentTile);
	printf("X: %f, Y: %f\n", currentPosition.y, currentPosition.x);

	//全ての方向を反復する
	for (int i = 0; i < DIRECTION_MAX; i++) 
	{
		//現在チェック中の座標を宣言
		Vector2 currentPosition = Vector2(col, row);

		//隣のマスに移動
		currentPosition = currentPosition + DirectionsState[i];

		printf("X2: %f, Y2: %f\n",currentPosition.y,currentPosition.x);

		//盤面の外側に出たらスキップする
		if ((currentPosition.x < 0)
			|| (currentPosition.x >= NumCols)
			|| (currentPosition.y < 0)
			|| (currentPosition.y >= NumRows))
		{
			printf("盤面の外側に出たのでスキップ\n");
			continue;
		}


		//相手の石かどうかを判定
		if (mTiles[currentPosition.y][currentPosition.x]->GetTileState() != opponentTile)
		{
			//相手の石でなければ、その方向のチェックをスキップする
			printf("隣の石が相手の石でなかったためスキップ\n");
			continue;
		}

		//盤面の範囲外に行くまで無限ループ
		while (1)
		{
			//隣のマスに移動
			currentPosition = currentPosition + DirectionsState[i];

			//チェックするマスが盤面の範囲内でないか判定する
			if ((currentPosition.x < 0)
				|| (currentPosition.x >= NumCols)
				|| (currentPosition.y < 0)
				|| (currentPosition.y >= NumRows))
			{
				//盤面の外側にでたら、現在の方向のチェックを抜ける
				printf("盤面の外側に出たのでスキップ\n");
				break;
			}

			//チェックするマスに石がないかどうかを判定
			if (mTiles[currentPosition.y][currentPosition.x]->GetTileState() == Tile::EDefault)
			{
				//石がなければ現在のチェックを抜ける
				break;
				printf("隣の石が相手の石でなかったためスキップ\n");
			}
			
			//チェックしているますに自分の石があれば
			if(mTiles[currentPosition.y][currentPosition.x]->GetTileState() == turnTile)
			{
				//石が置けることが確定
				canPlace = true;

				//ひっくり返しフラグが立っているかどうか判定
				if (turnOver)
				{
					printf("turnOver\n");
					//ひっくり返す座標を宣言
					Vector2 reversePosition = Vector2(col, row);

					//隣のマスに移動する
					reversePosition = reversePosition + DirectionsState[i];

					//盤面の外側に出たらスキップする
					if ((reversePosition.x < 0)
						|| (reversePosition.x >= NumCols)
						|| (reversePosition.y < 0)
						|| (reversePosition.y >= NumRows))
					{
						printf("盤面の外側に出たのでスキップ\n");
						break;
					}

					//現在のターンの石が見つかるまで反復する
					do
					{
						//相手の石をひっくり返す
						mTiles[reversePosition.y][reversePosition.x]->SetTileState(turnTile);

						//ひっくり返すごとに隣のマスにいどう
						reversePosition = reversePosition + DirectionsState[i];

						//盤面の外側に出たらスキップする
						if ((reversePosition.x < 0)
							|| (reversePosition.x >= NumCols)
							|| (reversePosition.y < 0)
							|| (reversePosition.y >= NumRows))
						{
							printf("盤面の外側に出たのでスキップ\n");
							break;
						}
						printf("ひっくり返し中\n");

					} while (mTiles[reversePosition.y][reversePosition.x]->GetTileState() != turnTile);
				}
			}
		}
	}

	//石を置けるかどうかを返す
	return canPlace;
}

//盤面上に石を置けるマスがあるかどうかを判定する関数
bool Grid::CheckCanPlaceAll(TurnState turn)
{
	//盤面の全ての行を反復する
	for (int y = 0; y < NumRows; y++)
	{
		//盤面の全ての列を反復する
		for (int x = 0; x < NumCols; x++)
		{
			//判定する座標を宣言する
			Vector2 position = Vector2{ (float)x, (float)y };

			//対象の座標に石を置けるかどうか判定する
			if (CheckCanPlace(position.y, position.x))
			{
				//石を置けるマスがあるという結果を返す
				return true;
			}
		}
	}

	//石を置けるマスがないという結果を返す
	printf("石を置けるマスがないのでスキップします\n");
	return false;
}

//石を置く処理
void Grid::PlaceOthello()
{
	Tile::TileState turnTile;
	if (turnState == TURN_BLACK)
	{
		turnTile = Tile::EBlack;
	}
	else
	{
		turnTile = Tile::EWhite;
	}

	//石を置けるマスがあるか判定
	if (!CheckCanPlaceAll(turnState))
	{
		toggleTurn();
		return;
	}

	if (mSelectedTile->GetTileState() != Tile::EWhite && mSelectedTile->GetTileState() != Tile::EBlack) {
		//ターンによって置く石の配置
		if (turnState == TURN_BLACK)
		{
			mSelectedTile->SetTileState(Tile::EBlack);
			CheckCanPlace(selRow, selCol, true);
			toggleTurn();
		}
		else
		{
			mSelectedTile->SetTileState(Tile::EWhite);
			CheckCanPlace(selRow, selCol, true);
			toggleTurn();
		}
	}
}

//ターンを切り返す関数
void Grid::toggleTurn()
{
	if (turnState == TURN_BLACK)
	{
		turnState = TURN_WHITE;
		printf("白のターンです\n");
	}
	else
	{
		turnState = TURN_BLACK;
		printf("黒のターンです\n");
	}

}

void Grid::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	//石をひっくり返す処理
	//石をひっくり返すフラグを設定してCheckCanPlaceを呼び出し
	/*
	if (mTiles[selRow][selCol]->GetTileState() == Tile::EBlack || mTiles[selRow][selCol]->GetTileState() == Tile::EWhite) {
		//printf("ひっくり返し\n");
		CheckCanPlace(selRow, selCol, true);
	}*/
}
