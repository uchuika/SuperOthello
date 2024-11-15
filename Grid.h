#pragma once
#include "Actor.h"
#include <vector>
#include "Math.h"
#include "string"

class Grid : public Actor
{
public:
	Grid(class Game* game);

	//�^�[���̎�ނ̒�`
	enum TurnState
	{
		TURN_BLACK,
		TURN_WHITE,
		TURN_NONE
	};

	//�����̎�ނ��`
	enum DirState
	{
		DIRECTION_UP,		//��
		DIRECTION_UP_LEFT,	//����
		DIRECTION_LEFT,		//��
		DIRECTION_DOWN_LEFT,//����
		DIRECTION_DOWN,		//��
		DIRECTION_DOWN_RIGHT,//�E��
		DIRECTION_RIGHT,	//�E
		DIRECTION_UP_RIGHT,	//�E��
		DIRECTION_MAX		//�����̐�
	};

	//DirState�ƃ����N�����x�N�g���̕�����ۑ�
	Vector2 DirectionsState[DIRECTION_MAX]
	{
		Vector2 { 0,-1},		//��
		Vector2 {-1,-1},		//����
		Vector2 {-1, 0},		//��
		Vector2 {-1, 1},		//����
		Vector2 { 0, 1},		//��
		Vector2 { 1, 1},		//�E��
		Vector2 { 1, 0},		//�E
		Vector2 { 1,-1}			//�E��
	};
	// x/y���W�̂Ƃ���Ń}�E�X�N���b�N����������
	void ProcessClick(int x, int y);

	//�΂̐ݒu
	void PlaceOthello();

	//�^�[���̐؂�ւ�
	void toggleTurn();

	//�΂��u���邩�ǂ����𔻒肷��֐�
	bool CheckCanPlace(size_t row, size_t col, bool turnOver = false);

	//�Ֆʏ�ɐ΂��u���邩�ǂ����𔻒肷��֐�
	bool CheckCanPlaceAll(TurnState turn);

	//�C�ӂ̐΂̐��𐔂���֐�
	int GetDiskCount(TurnState turn);

	// �J�n/�I�� �̃^�C���̏ꏊ
	//class Tile* GetStartTile();
	//class Tile* GetEndTile();

	void UpdateActor(float deltaTime) override;
private:
	// ����̃^�C����I��
	void SelectTile(size_t row, size_t col);

	//�`�悷��Text��z��ɂ���
	void AddRenderText(const std::string& text);

	// �p�X��̃^�C���̃e�N�X�`�����X�V����
	//void UpdatePathTiles(class Tile* start);

	// ���ݑI������Ă���^�C��
	class Tile* mSelectedTile;

	//�I������Ă���ꏊ��Row��col
	size_t selRow;
	size_t selCol;

	// �O���b�h���̃^�C����2D�x�N�g��
	std::vector<std::vector<class Tile*>> mTiles;

	//�Q�[����ʓ��ł̕�����
	std::vector<class Text*> mTexts;

	// ���̓G�܂ł̎���
	//float mNextEnemy;

	//���݂̃^�[����ۑ�
	TurnState turnState;

	// �O���b�h�̍s�Ɨ�
	const size_t NumRows = 8;
	const size_t NumCols = 8;
	// ������̊J�ny���W
	const float StartY = 192.0f;
	// �e�^�C���̕��ƍ���
	const float TileSize = 64.0f;
	// ���̃I�Z����z�u�ł���܂ł̎���
	//const float EnemyTime = 1.5f;
};
