////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetFrameTime(float);
	void GetRotationX(float&);
	void GetRotationY(float&);
	void GetMoveDistanceX(float&);
	void GetMoveDistanceZ(float&);

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveLeftward(bool);
	void MoveRightward(bool);
	void TurnUp(bool);
	void TurnDown(bool);
	void TurnLeft(bool);
	void TurnRight(bool);

private:
	float m_frameTime;
	float m_distanceX;
	float m_distanceZ;
	float m_rotationX;
	float m_rotationY;
	float m_moveSpeed, m_upTurnSpeed, m_downTurnSpeed, m_leftTurnSpeed, m_rightTurnSpeed;
};

#endif
