#ifndef BULLET_H
#define BULLET_H

//*********************************************************************************************
// File:			Bullet.h
// Description:		A very simple class to represent an Bullet as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Tom - 2018-2019
// Notes:
//*********************************************************************************************

#include "Node.h"
#include "Aeroplane.h"

__declspec(align(16)) class Bullet : public Node
{
public:
	Bullet(std::string name = "Bullet", std::string objName = "Bullet", XMFLOAT4 mPos = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), bool bIsRoot = false, XMFLOAT4 mRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), bool bCamEnabled = false);
	~Bullet(void);

	void InitializeBulletPosition(XMMATRIX mGunWorldMatrix);

	void Update(XMVECTOR mGunForwardVector, float fSpeed);

private:
	float m_fSpeed; // Forward speed
	float m_fActiveTime = 0.0f;

public:

	float GetActiveTime(void) { return m_fActiveTime; }

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

#endif