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

	// �^�C���̍쐬
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(TileSize / 2.0f + j * TileSize, StartY + i * TileSize));
		}
	}

	//�ŏ��̃^�[�������ŏ�����
	turnState = TURN_BLACK;

	//�����΂�z�u
	mTiles[3][4]->SetTileState(Tile::EBlack);
	mTiles[4][3]->SetTileState(Tile::EBlack);

	//�����΂�z�u
	mTiles[3][3]->SetTileState(Tile::EWhite);
	mTiles[4][4]->SetTileState(Tile::EWhite);

}

void Grid::SelectTile(size_t row, size_t col)
{
	// �L���ȑI���ł��邱�Ƃ��m�F����
	//Tile::TileState tstate = mTiles[row][col]->GetTileState();

	if (CheckCanPlace(row, col)) {
		// �O�̑I������������
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
		//printf("���̂܂��ɂ͐΂�u���܂���");
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

//�΂�u���邩�ǂ����̔���
bool Grid::CheckCanPlace(size_t row, size_t col, bool turnOver)
{
	//�u���邩�ǂ����̃t���O��錾
	bool canPlace = false;


	//�Ώۂ̍��W�ɂ��łɐ΂��u����Ă��Ȃ����𔻒肷��
	Tile::TileState tstate = mTiles[row][col]->GetTileState();

	//����̐΂̃^�C��
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

	if (tstate == Tile::EBlack || tstate == Tile::EWhite)
	{
		//�u���Ȃ���Ԃ�
		return false;
	}
	Vector2 currentPosition = Vector2(row, col);
	printf("%d\n", turnState);
	printf("�G�̐�:%d\n", opponentTile);
	printf("X: %f, Y: %f\n", currentPosition.y, currentPosition.x);

	//�S�Ă̕����𔽕�����
	for (int i = 0; i < DIRECTION_MAX; i++) 
	{
		//���݃`�F�b�N���̍��W��錾
		Vector2 currentPosition = Vector2(row, col);

		//�ׂ̃}�X�Ɉړ�
		currentPosition = currentPosition + DirectionsState[i];

		printf("X2: %f, Y2: %f\n",currentPosition.y,currentPosition.x);

		//�Ֆʂ̊O���ɏo����X�L�b�v����
		if ((currentPosition.x < 0)
			|| (currentPosition.x >= NumCols)
			|| (currentPosition.y < 0)
			|| (currentPosition.y >= NumRows))
		{
			printf("�Ֆʂ̊O���ɏo���̂ŃX�L�b�v\n");
			continue;
		}


		//����̐΂��ǂ����𔻒�
		if (mTiles[currentPosition.y][currentPosition.x]->GetTileState() != opponentTile)
		{
			//����̐΂łȂ���΁A���̕����̃`�F�b�N���X�L�b�v����
			printf("�ׂ̐΂�����̐΂łȂ��������߃X�L�b�v\n");
			continue;
		}

		//�Ֆʂ͈̔͊O�ɍs���܂Ŗ������[�v
		while (1)
		{
			//�ׂ̃}�X�Ɉړ�
			currentPosition = currentPosition + DirectionsState[i];

			//�`�F�b�N����}�X���Ֆʂ͈͓̔��łȂ������肷��
			if ((currentPosition.x < 0)
				|| (currentPosition.x >= NumCols)
				|| (currentPosition.y < 0)
				|| (currentPosition.y >= NumRows))
			{
				//�Ֆʂ̊O���ɂł���A���݂̕����̃`�F�b�N�𔲂���
				printf("�Ֆʂ̊O���ɏo���̂ŃX�L�b�v\n");
				break;
			}

			//�`�F�b�N����}�X�ɐ΂��Ȃ����ǂ����𔻒�
			if (mTiles[currentPosition.y][currentPosition.x]->GetTileState() == Tile::EDefault)
			{
				//�΂��Ȃ���Ό��݂̃`�F�b�N�𔲂���
				break;
				printf("�ׂ̐΂�����̐΂łȂ��������߃X�L�b�v\n");
			}
			
			//�`�F�b�N���Ă���܂��Ɏ����̐΂������
			if(mTiles[currentPosition.y][currentPosition.x]->GetTileState() == turnTile)
			{
				//�΂��u���邱�Ƃ��m��
				canPlace = true;

				//�Ђ�����Ԃ��t���O�������Ă��邩�ǂ�������
				if (turnOver)
				{
					printf("turnOver\n");
					//�Ђ�����Ԃ����W��錾
					Vector2 reversePosition = Vector2(row, col);

					//�ׂ̃}�X�Ɉړ�����
					reversePosition = reversePosition + DirectionsState[i];

					//�Ֆʂ̊O���ɏo����X�L�b�v����
					if ((reversePosition.x < 0)
						|| (reversePosition.x >= NumCols)
						|| (reversePosition.y < 0)
						|| (reversePosition.y >= NumRows))
					{
						printf("�Ֆʂ̊O���ɏo���̂ŃX�L�b�v\n");
						break;
					}

					//���݂̃^�[���̐΂�������܂Ŕ�������
					do
					{
						//����̐΂��Ђ�����Ԃ�
						mTiles[reversePosition.y][reversePosition.x]->SetTileState(turnTile);

						//�Ђ�����Ԃ����Ƃɗׂ̃}�X�ɂ��ǂ�
						reversePosition = reversePosition + DirectionsState[i];

						//�Ֆʂ̊O���ɏo����X�L�b�v����
						if ((reversePosition.x < 0)
							|| (reversePosition.x >= NumCols)
							|| (reversePosition.y < 0)
							|| (reversePosition.y >= NumRows))
						{
							printf("�Ֆʂ̊O���ɏo���̂ŃX�L�b�v\n");
							break;
						}
						printf("�Ђ�����Ԃ���\n");

					} while (mTiles[reversePosition.y][reversePosition.x]->GetTileState() != turnTile);
				}
			}
			
		}
	}

	//�΂�u���邩�ǂ�����Ԃ�
	return canPlace;
}

//�΂�u������
void Grid::PlaceOthello()
{

	
	//
	if (mSelectedTile->GetTileState() != Tile::EWhite && mSelectedTile->GetTileState() != Tile::EBlack) {
		//�^�[���ɂ���Ēu���΂̔z�u
		if (turnState == TURN_BLACK)
		{
			mSelectedTile->SetTileState(Tile::EBlack);
			turnState = TURN_WHITE;
		}
		else
		{
			mSelectedTile->SetTileState(Tile::EWhite);
			turnState = TURN_BLACK;
		}
	}
}


void Grid::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	//�΂��Ђ�����Ԃ�����
	//�΂��Ђ�����Ԃ��t���O��ݒ肵��CheckCanPlace���Ăяo��
	if (mTiles[selRow][selCol]->GetTileState() == Tile::EBlack || mTiles[selRow][selCol]->GetTileState() == Tile::EWhite) {
		printf("�Ђ�����Ԃ�\n");
		CheckCanPlace(selRow, selCol, true);
	}
}
