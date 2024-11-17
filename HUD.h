#pragma once
#include "UIScreen.h"
#include <vector>
#include "SDL.h"
#include <string>

class HUD : public UIScreen
{
public:
	//�h���[���ʂ��Ⴂ�قǌ���Ɉʒu����
	HUD(class Game* game);
	~HUD();

	void Update(float deltaTime) override;
	void Draw(class SDL_Renderer* renderer) override;
	void SetStatusText(const std::string& text);

protected:

	void UpdateStatusText(float deltaTime);

	//�X�e�[�^�X�e�L�X�g���i�[����ϐ�
	std::string mStatusText;

	class Font* mFont;
	class Game* mGame;
};