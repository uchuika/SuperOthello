#pragma once
#include <cstdint>

class Component
{
public:
	// コンストラクタ
	// (更新順序が低いほど、コンポーネントは早く更新される)
	Component(class Actor* owner, int updateOrder = 100);
	// デストラクタ
	virtual ~Component();
	// このコンポーネントをデルタタイムで更新
	virtual void Update(float deltaTime);
	// このコンポーネントの入力を受付
	virtual void ProcessInput(const uint8_t* keyState) {}

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// 所属しているアクター
	class Actor* mOwner;
	// コンポーネントの順序を更新する
	int mUpdateOrder;
};
