#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//待ち時間
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 60;

	//車の待ち時間
	constexpr int kWaitCarFrameMin = 10;
	constexpr int kWaitCarFrameMax = 10;


	//車の速度
	constexpr float kSpeed = -14.0;

	//車のジャンプする位置
	constexpr int kJumpPos = 320;

	//車の停止する位置
	constexpr int kStopPos = 380;

	//車の引き返す位置
	constexpr int kReturnPos = 320;

	//車のジャンプ力
	constexpr float kJumpAcc = -18.0f;

	constexpr float kGravity = 0.7f;

}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_waitFrame = 0;
	m_waitCar = 0;
}
void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	//動きのバリエーションを選択
	int randNum = GetRand(99);
	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 38 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}
	//デバック用に挙動を決める
//	 m_moveType = kMoveTypeStop;
	//動き始めるまでの時間を設定 1秒から3秒待つ 60フレームから180フレーム
	m_waitFrame = GetRand(kWaitFrameMax) + kWaitFrameMin;

	m_waitCar = GetRand(kWaitCarFrameMax) + kWaitCarFrameMin;
}

void Car::update()
{

	DrawFormatString(0, 0, GetColor(255, 255, 255), "スピード:%f", kSpeed);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "%d", m_waitCar);

	if (m_waitFrame > 0)
	{
		m_waitFrame-- ;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
		updateStop();
		break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	default:
		updateNormal();
		break;
	}
}

void Car::draw()
{
	if (m_vec.x <= 0.0f)
	{
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	else
	{
		DrawTurnGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
}

//*********
//private *
//*********
//まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;

}

//一時停止フェイント
void Car::updateStop()
{
	m_pos += m_vec;
	if (m_pos.x < kStopPos)
	{
		if (m_waitCar > 0)
		{
			m_waitCar--;
			m_vec.x = 0.0f;	
			return;
		}
		else
		{
			m_vec.x = kSpeed;
			m_pos += m_vec;
		}
	}
}
//ジャンプする
void Car::updateJump()
{
	//地面とのプレイヤー移動制限
	bool isField = false;
	m_pos += m_vec;

	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;

		isField = true;
	}

	if (m_pos.x < kJumpPos)
	{
		if (isField)
		{
			m_vec.y = kJumpAcc;
		}
	}
	m_vec.y += kGravity;
}
//途中で引き返す(必ず成功)
void Car::updateReturn()
{
	m_pos += m_vec;
	if (m_pos.x < kReturnPos)
	{
		m_vec.x *= -1;
	}

}