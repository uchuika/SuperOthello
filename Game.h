#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddText(class TextComponent* text);
	void RemoveText(class TextComponent* text);

	SDL_Texture* GetTexture(const std::string& fileName);

	class Grid* GetGrid() { return mGrid; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	class Enemy* GetNearestEnemy(const Vector2& pos);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// �ǂݍ��܂ꂽ�e�N�X�`���̃}�b�v
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// �S�ẴA�N�^�[��ۊǂ���z��
	std::vector<class Actor*> mActors;
	// �ҋ@���̃A�N�^�[��ۊǂ���z��
	std::vector<class Actor*> mPendingActors;

	//�S�Ă̕`��p�e�L�X�g��ۊǂ���z��
	std::vector<class TextComponent*> mTexts;

	//�S�Ă̑ҋ@���̕`��p�e�L�X�g��ۊǂ���z��
	//std::vector<

	// �`�悳�ꂽ�S�ẴX�v���C�g�R���|�[�l���g�̔z��
	std::vector<class SpriteComponent*> mSprites;

	//�e�퓮��p�����o�ϐ�
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// ���݃A�N�^�[���X�V���Ă��邩�ǂ���
	bool mUpdatingActors;

	// Game-specific
	std::vector<class Enemy*> mEnemies;
	class Grid* mGrid;
	float mNextEnemy;
};
