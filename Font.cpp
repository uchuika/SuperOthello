#include "Font.h"
#include <vector>
#include "Game.h"
#include "SDL.h"

Font::Font(class Game* game, class SDL_Renderer* renderer)
	:mGame(game)
	,mRenderer(renderer)
{

}

Font::~Font()
{

}

//�K�v�ȃ|�C���g�T�C�Y�̔z����쐬���A
//���ꂼ��̃|�C���g�T�C�Y��TTF_Font��mFontData�ɒǉ�����
bool Font::Load(const std::string& fileName)
{
	//�T�|�[�g����t�H���g�̃T�C�Y
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto& size : fontSizes)
	{
		//.ttf�t�@�C�������[�h���A�w�肵���|�C���g�T�C�Y��TTF_Font�f�[�^�̃|�C���^��Ԃ�
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);

		if (font == nullptr)
		{
			SDL_Log("�t�H���g &s �T�C�Y %d �̃��[�h�Ɏ��s���܂���",
				fileName.c_str(), size);
			return false;
		}
		mFontData.emplace(size, font);
	}
	return true;
}

//�S�Ẵf�[�^���J������
void Font::Unload()
{
	for (auto& font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
}

//��������󂯎��K�؂ȃT�C�Y�̃t�H���g���g���ăe�N�X�`���𐶐�����
SDL_Texture* Font::RenderText(
	const std::string& text,
	const Vector3& color,
	int pointSize)
{
	SDL_Texture* tex = nullptr;

	//�F��SDL_Color�ɕϊ�����
	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 255);
	sdlColor.g = static_cast<Uint8>(color.y * 255);
	sdlColor.b = static_cast<Uint8>(color.z * 255);
	sdlColor.b = 255;

	//�w��T�C�Y�̃t�H���g�f�[�^��T��
	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		//SDL_Surface�ɕ`��(�A���t�@�u�����f�B���O)
		SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(),
			sdlColor);

		if (surf != nullptr)
		{
			//SDL_Surface����e�N�X�`���ɕϊ�
			tex = SDL_CreateTextureFromSurface(mRenderer, surf);
			SDL_FreeSurface(surf);
			if (!tex)
			{
				SDL_Log("�T�[�t�F�X���e�N�X�`���ɕϊ��ł��܂���ł��� %s", text.c_str());
				return nullptr;
			}
		}
	}
	else 
	{
		SDL_Log("�|�C���g�T�C�Y %d �����Ή��ł�", pointSize);
	}
	return tex;
}