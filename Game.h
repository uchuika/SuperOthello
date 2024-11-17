#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "Font.h"

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

	SDL_Texture* GetTexture(const std::string& fileName);

	//�X�N���[������Ԃ�
	float GetScreenWidth() const { return mScreenWidth; }

	//�X�N���[��������Ԃ�
	float GetScreenHeight() const { return mScreenHeight; }

	//�e�L�X�g�t�@�C������e�L�X�g��ǂݍ��ފ֐�
	const std::string& GetText(const std::string& key);
	
	//�t�H���g�擾�֐�
	Font* GetFont(const std::string& fileName);

	//UI�X�^�b�N�̊Ǘ�
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	//�w���UIScreen���X�^�b�N�Ƀv�b�V������
	void PushUI(class UIScreen* screen);

	class Grid* GetGrid() { return mGrid; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	class Enemy* GetNearestEnemy(const Vector2& pos);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	//�e�L�X�g�̃��[�J���C�Y�p�}�b�v
	std::unordered_map<std::string, std::string> mText;

	// �ǂݍ��܂ꂽ�e�N�X�`���̃}�b�v
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// �S�ẴA�N�^�[��ۊǂ���z��
	std::vector<class Actor*> mActors;
	//�Q�[���p��UI�X�^�b�N
	std::vector<class UIScreen*> mUIStack;
	std::unordered_map<std::string, class Font*> mFonts;

	// �ҋ@���̃A�N�^�[��ۊǂ���z��
	std::vector<class Actor*> mPendingActors;

	// �`�悳�ꂽ�S�ẴX�v���C�g�R���|�[�l���g�̔z��
	std::vector<class SpriteComponent*> mSprites;

	//�e�퓮��p�����o�ϐ�
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// ���݃A�N�^�[���X�V���Ă��邩�ǂ���
	bool mUpdatingActors;

	//�X�N���[���̍����ƕ�
	int mScreenWidth;
	int mScreenHeight;

	// Game-specific
	std::vector<class Enemy*> mEnemies;
	class Grid* mGrid;
	float mNextEnemy;
};
