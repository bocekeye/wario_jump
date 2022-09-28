#include "DxLib.h"
#include "game.h"
#include "player.h"

namespace
{	
	//キャラクターのサイズ
	constexpr float kSizeX = 128.0f;
	constexpr float kSizeY = 128.0f;

	//ジャンプ力
	constexpr float kJumpAcc = -16.0f;
	//重力
	constexpr float kGravity = 0.5f;
}

Player::Player()
{
	m_handle = -1;
	m_fieldY = 0.0f;

//	m_isJumpUp = false;
//	m_isJumpDown = false;

	m_isDead = false;
}

void Player::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle ,&m_graphSize.x, &m_graphSize.y);
	m_colSize = m_graphSize;
}

void Player:: setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = 64.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
}

void Player::update()//1秒間に60回呼ばれている
{
	
	m_pos += m_vec;

	//地面とのプレイヤー移動制限
	bool isField = false; //地面と当たっていない

	if (m_pos.y > m_fieldY - m_graphSize.y)
	{
		m_pos.y = m_fieldY - m_graphSize.y;
		isField = true;
	}

	if (m_isDead) return;
	// キー入力処理
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		if (isField) //地面に当たったらジャンプができる
		{
			m_vec.y = kJumpAcc; //ジャンプ開始
		}
		
	}
	m_vec.y += kGravity;



	//if (padState & PAD_INPUT_1)
	//{
	//	m_isJumpUp = true;
	//}
	//if (m_isJumpUp)
	//{
	//	m_pos.y -= 4.0f;
	//	if (m_pos.y <= 64.0f)
	//	{
	//		m_isJumpUp = false;
	//		m_isJumpDown = true;
	//	}
	//}
	//else if (m_isJumpDown)
	//{
	//	m_pos.y += 4.0f;
	//	if (m_pos.y >= m_fieldY - m_graphSize.y)
	//	{
	//		m_pos.y = m_fieldY - m_graphSize.y;
	//	}
	//}

}

void Player::draw()
{
	if (m_isDead)
	{
		DrawRectGraph(m_pos.x, m_pos.y, m_graphSize.x / 2, 0, m_graphSize.x / 2, m_graphSize.y, m_handle, true, false);
	}
	else
	{
		DrawRectGraph(m_pos.x, m_pos.y, 0, 0, m_graphSize.x / 2, m_graphSize.y, m_handle, true, false);
	}
}

bool Player::isCol(Car& car)
{
	float playerLeft = getPos().x;
	float playerRight = getPos().x + kSizeX;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + kSizeY;

	float carLeft = car.getPos().x;
	float carRight = car.getPos().x + car.getSize().x;
	float carTop = car.getPos().y;
	float carBottom = car.getPos().y + car.getSize().y;

	if (playerLeft > carRight)	return false;
	if (playerRight < carLeft)	return false;
	if (playerTop > carBottom)	return false;
	if (playerBottom < carTop)	return false;

	return true;
}
