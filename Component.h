// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <cstdint>

class Component
{
public:
	// �R���X�g���N�^
	// (�X�V�������Ⴂ�قǁA�R���|�[�l���g�͑����X�V�����)
	Component(class Actor* owner, int updateOrder = 100);
	// �f�X�g���N�^
	virtual ~Component();
	// ���̃R���|�[�l���g���f���^�^�C���ōX�V
	virtual void Update(float deltaTime);
	// ���̃R���|�[�l���g�̓��͂���t
	virtual void ProcessInput(const uint8_t* keyState) {}

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// �������Ă���A�N�^�[
	class Actor* mOwner;
	// �R���|�[�l���g�̏������X�V����
	int mUpdateOrder;
};
