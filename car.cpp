#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	//�҂�����
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 60;

	//�Ԃ̑҂�����
	constexpr int kWaitCarFrameMin = 10;
	constexpr int kWaitCarFrameMax = 10;


	//�Ԃ̑��x
	constexpr float kSpeed = -14.0;

	//�Ԃ̃W�����v����ʒu
	constexpr int kJumpPos = 320;

	//�Ԃ̒�~����ʒu
	constexpr int kStopPos = 380;

	//�Ԃ̈����Ԃ��ʒu
	constexpr int kReturnPos = 320;

	//�Ԃ̃W�����v��
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
		m_moveType = kMoveTypeReturn;
	}
	//�f�o�b�N�p�ɋ��������߂�
//	 m_moveType = kMoveTypeStop;
	//�����n�߂�܂ł̎��Ԃ�ݒ� 1�b����3�b�҂� 60�t���[������180�t���[��
	m_waitFrame = GetRand(kWaitFrameMax) + kWaitFrameMin;

	m_waitCar = GetRand(kWaitCarFrameMax) + kWaitCarFrameMin;
}

void Car::update()
{

	DrawFormatString(0, 0, GetColor(255, 255, 255), "�X�s�[�h:%f", kSpeed);
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
//�܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;

}

//�ꎞ��~�t�F�C���g
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
//�W�����v����
void Car::updateJump()
{
	//�n�ʂƂ̃v���C���[�ړ�����
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
//�r���ň����Ԃ�(�K������)
void Car::updateReturn()
{
	m_pos += m_vec;
	if (m_pos.x < kReturnPos)
	{
		m_vec.x *= -1;
	}

}