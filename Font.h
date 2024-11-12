#pragma once
#include <string>
#include <unordered_map>
#include "SDL_ttf.h"
#include "Math.h"
#include "SDL.h"

class Font
{
public:
	Font(class Game* game,class SDL_Renderer* renderer);
	~Font();

	//�t�@�C���̃��[�h�ƃA�����[�h�̊֐�
	bool Load(const std::string& filename);
	void Unload();

	//��������e�N�X�`���ɕ`��
	class SDL_Texture* RenderText(const std::string& text,
		const Vector3& color = Color::White,
		int pointSize = 30
	);

private:
	//�|�C���g�T�C�Y�ƃt�H���g�f�[�^�̘A�z�z��
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
	class SDL_Renderer* mRenderer;
};