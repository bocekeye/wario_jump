#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//�҂�����
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 120;

	//�Ԃ̑��x
	constexpr float kSpeed = -20.0;
}


Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_waitFrame = 0;
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

	//�����̃o���G�[�V������I��
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
		m_moveType = kMoveTypeRetuen;
	}
	//�����n�߂�܂ł̎��Ԃ�ݒ� 1�b����3�b�҂� 60�t���[������180�t���[��
	m_waitFrame = GetRand(kWaitFrameMax) + kWaitFrameMin;
}

void Car::update()
{
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
	case kMoveTypeRetuen:
		updateReturn();
		break;
	default:
		updateNormal();
		break;
	}

	updateNormal();
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}

//*********
//private *
//*********
//�܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;
}
//�ꎞ��~�t�F�C���g
void Car::updateStop()
{
	updateNormal(); //��
}
//�W�����v����
void Car::updateJump()
{
	updateNormal(); //��
}
//�r���ň����Ԃ�(�K������)
void Car::updateReturn()
{
	updateNormal(); //��
}