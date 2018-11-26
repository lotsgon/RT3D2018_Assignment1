//*********************************************************************************************
// File:			Bullet.cpp
// Description:		A very simple class to represent an Bullet as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include "Bullet.h"

// Initialise static class variables.

Bullet::Bullet(std::string name, std::string objName, XMFLOAT4 mPos, bool bIsRoot, XMFLOAT4 mRot, bool mCamEnabled) : Node(name, objName, mPos, bIsRoot, mRot, mCamEnabled)
{
	m_v4LocalScale = XMFLOAT4(0.1f,0.1f,0.1f,0.0f);
}

Bullet::~Bullet(void)
{
	m_v4LocalScale = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
}

void Bullet::InitializeBulletPosition(XMMATRIX mGunWorldMatrix)
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans, mScale;

	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4LocalRotation.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4LocalRotation.y + 105.0f));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4LocalRotation.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4LocalPosition));
	mScale = XMMatrixScalingFromVector(XMLoadFloat4(&m_v4LocalScale));

	m_mWorldMatrix = mRotX * mRotY * mRotZ * mScale * mTrans * mGunWorldMatrix;

	m_vForwardVector = m_mWorldMatrix.r[2];

	XMStoreFloat4(&m_v4LocalPosition, m_mWorldMatrix.r[3]);
}

void Bullet::Update(XMVECTOR mGunForwardVector, float fSpeed)
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans, mScale;

	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4LocalRotation.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4LocalRotation.y + 105.0f));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4LocalRotation.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4LocalPosition));
	mScale = XMMatrixScalingFromVector(XMLoadFloat4(&m_v4LocalScale));

	m_mWorldMatrix = mRotX * mRotZ * mRotY * mScale * mTrans;

	m_fSpeed = fSpeed;
	m_fActiveTime += 1;

	// Move Forward
	XMVECTOR vCurrPos = XMLoadFloat4(&m_v4LocalPosition);
	vCurrPos += m_vForwardVector * m_fSpeed;
	XMStoreFloat4(&m_v4LocalPosition, vCurrPos);
}
