#pragma once
#include "Math.h"
#include <cstdint>
#include <string>
#include <functional>
#include <vector>
#include "SDL.h"

class Button
{
public:
	Button(const std::string& name, class Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	~Button();

	// �{�^���̖��O��ݒ肷��
	void SetName(const std::string& name);

	// �Q�b�^�[�ƃZ�b�^�[
	class SDL_Texture* GetNameTex() { return mNameTex; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetHighlighted(bool sel) { mHighlighted = sel; }
	bool GetHighlighted() const { return mHighlighted; }

	// �|�C���^�[���{�^���͈̔͂Ȃ��ɂ���ꍇtrue��Ԃ�
	bool ContainsPoint(const Vector2& pt) const;
	// �{�^�����N���b�N���ꂽ�Ƃ��ɌĂяo��
	void OnClick();
private:
	std::function<void()> mOnClick;
	std::string mName;
	class SDL_Texture* mNameTex;
	class Font* mFont;
	Vector2 mPosition;
	Vector2 mDimensions;
	bool mHighlighted;
};

class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();
	//UIScreen�̔h���N���X�͈ȏ���I�[�o�[���C�h�ł���
	virtual void Update(float deltaTime);
	virtual void Draw(class SDL_Renderer* renderer);
	virtual void ProcessInput(const uint8_t* kyes);
	virtual void HandleKeyPress(int key);
	//��Ԃ��N���[�W���O�ɂ���
	void Close();
	//��Ԃ��A�N�e�B�u���N���[�W���O�����Ǘ�
	enum UIState { 
		EActive, 
		EClosing 
	};

	//��Ԃ��擾
	UIState GetState() const { return mState; }

	// �^�C�g����ύX����֐�
	void SetTitle(const std::string& text,
		const Vector3& color = Color::White,
		int pointSize = 40);
	// �{�^�����X�N���[���ɂ���
	void AddButton(const std::string& name, std::function<void()> onClick);
protected:
	//�e�N�X�`����`�悷��w���p�[�֐�
	void DrawTexture(class SDL_Renderer* renderer, class SDL_Texture* texture,
		const Vector2& offset = Vector2::Zero,
		float scale = 1.0f);

	// �}�E�X���[�h�𑊑΃��[�h�ɂ��邩�ǂ�����ݒ肷��
	void SetRelativeMouseMode(bool relative);
	class Game* mGame;
	
	//UI��ʂ̃^�C�g��������p
	class Font* mFont;
	class SDL_Texture* mTitle;

	class SDL_Texture* mBackground;
	class SDL_Texture* mButtonOn;
	class SDL_Texture* mButtonOff;

	Vector2 mTitlePos;
	Vector2 mNextButtonPos;
	Vector2 mBGPos;
	//���
	UIState mState;
	// �{�^���̃��X�g
	std::vector<Button*> mButtons;
};
