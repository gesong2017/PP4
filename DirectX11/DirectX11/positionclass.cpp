////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "positionclass.h"

PositionClass::PositionClass()
{
	m_frameTime = 0.0f;
	m_distanceX = 0.0f;
	m_distanceZ = 0.0f;
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_moveSpeed = 0.0f;
	m_upTurnSpeed = 0.0f;
	m_downTurnSpeed = 0.0f;
	m_leftTurnSpeed = 0.0f;
	m_rightTurnSpeed = 0.0f;
}

PositionClass::PositionClass(const PositionClass& other)
{
}

PositionClass::~PositionClass()
{
}

void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}

void PositionClass::GetMoveDistanceX(float& x)
{
	x = m_distanceX;
	return;
}

void PositionClass::GetMoveDistanceZ(float& z)
{
	z = m_distanceZ;
	return;
}

void PositionClass::GetRotationX(float& x)
{
	x = m_rotationX;
	return;
}

void PositionClass::GetRotationY(float& y)
{
	y = m_rotationY;
	return;
}

void PositionClass::MoveForward(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_moveSpeed += m_frameTime * 0.01f;

		if (m_moveSpeed > (m_frameTime * 0.15f))
		{
			m_moveSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_moveSpeed -= m_frameTime* 0.005f;

		if (m_moveSpeed < 0.0f)
		{
			m_moveSpeed = 0.0f;
		}
	}

	// Update the position using the moving speed.
	m_distanceZ += m_moveSpeed ;

	return;
}

void PositionClass::MoveBackward(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_moveSpeed += m_frameTime * 0.01f;

		if (m_moveSpeed > (m_frameTime * 0.15f))
		{
			m_moveSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_moveSpeed -= m_frameTime* 0.005f;

		if (m_moveSpeed < 0.0f)
		{
			m_moveSpeed = 0.0f;
		}
	}

	// Update the position using the moving speed.
	m_distanceZ -= m_moveSpeed ;

	return;
}

void PositionClass::MoveLeftward(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_moveSpeed += m_frameTime * 0.01f;

		if (m_moveSpeed > (m_frameTime * 0.15f))
		{
			m_moveSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_moveSpeed -= m_frameTime* 0.005f;

		if (m_moveSpeed < 0.0f)
		{
			m_moveSpeed = 0.0f;
		}
	}

	// Update the position using the moving speed.
	m_distanceX -= m_moveSpeed ;

	return;
}

void PositionClass::MoveRightward(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_moveSpeed += m_frameTime * 0.01f;

		if (m_moveSpeed > (m_frameTime * 0.15f))
		{
			m_moveSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_moveSpeed -= m_frameTime* 0.005f;

		if (m_moveSpeed < 0.0f)
		{
			m_moveSpeed = 0.0f;
		}
	}

	// Update the position using the moving speed.
	m_distanceX += m_moveSpeed ;

	return;
}

void PositionClass::TurnUp(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_upTurnSpeed += m_frameTime * 0.01f;

		if (m_upTurnSpeed > (m_frameTime * 0.15f))
		{
			m_upTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_upTurnSpeed -= m_frameTime* 0.005f;

		if (m_upTurnSpeed < 0.0f)
		{
			m_upTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX -= m_upTurnSpeed;
	if (m_rotationX < 0.0f)
	{
		m_rotationX += 360.0f;
	}

	return;
}

void PositionClass::TurnDown(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
	if (keydown)
	{
		m_downTurnSpeed += m_frameTime * 0.01f;

		if (m_downTurnSpeed > (m_frameTime * 0.15f))
		{
			m_downTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_downTurnSpeed -= m_frameTime* 0.005f;

		if (m_downTurnSpeed < 0.0f)
		{
			m_downTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationX += m_downTurnSpeed;
	if (m_rotationX > 360.0f)
	{
		m_rotationX -= 360.0f;
	}

	return;
}

void PositionClass::TurnLeft(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
	if (keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if (m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime* 0.005f;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY -= m_leftTurnSpeed;
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}

void PositionClass::TurnRight(bool keydown)
{
	// If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
	if (keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if (m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime* 0.005f;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	m_rotationY += m_rightTurnSpeed;
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;
}