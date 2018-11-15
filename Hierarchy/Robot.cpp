//*********************************************************************************************
// File:			Robot.cpp
// Description:		A very simple class to represent an Robot as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include "Robot.h"

// Initialise static class variables.

Robot::Robot(std::string name, std::string objName, float fX, float fY, float fZ, bool bIsRoot, float fRotX, float fRotY, float fRotZ, bool mCamEnabled) : Node(name, objName, fX, fY, fZ, bIsRoot, fRotX, fRotY, fRotZ, mCamEnabled)
{
}

Robot::~Robot(void)
{
}

void Robot::SetUpHierarchy(void)
{
	m_pPelvis = new Node("Pelvis", this->GetGameObjectName(), -0.0250011f, 1.5250000f, -0.0000005f);
	m_pBody = new Node("Body", this->GetGameObjectName(), 0.0500099f, 4.3749992f, 0.0000003f);
	m_pLHip = new Node("LeftHip", this->GetGameObjectName(), 1.9500000f, -0.7724991f, 0.000000f);
	m_pLKnee = new Node("LeftKnee", this->GetGameObjectName(), 0.0000006f, -2.2200001f, 0.000000f);
	m_pLAnkle = new Node("LeftAnkle", this->GetGameObjectName(), -0.0800152f, -3.6399994f, -0.0000098f);
	m_pRHip = new Node("RightHip", this->GetGameObjectName(), -1.9500000f, -0.7724991f, 0.000000f);
	m_pRKnee = new Node("RightKnee", this->GetGameObjectName(), 0.0000006f, -2.2000000f, 0.000000f);
	m_pRAnkle = new Node("RightAnkle", this->GetGameObjectName(), 0.0199911f, -3.6799995f, 0.0000039f);
	m_pLShoulder = new Node("LeftShoulder", this->GetGameObjectName(), 4.6000000f, 0.000000f, -0.0009992f);
	m_pLElbow = new Node("LeftElbow", this->GetGameObjectName(), 3.4250019f, -0.0499817f, -0.0004262f);
	m_pLWrist = new Node("LeftWrist", this->GetGameObjectName(), 5.5250008f, -0.0999710f, 0.0003968f);
	m_pRShoulder = new Node("RightShoulder", this->GetGameObjectName(), -4.4500023f, 0.0500000f, -0.0000021f);
	m_pRElbow = new Node("RightElbow", this->GetGameObjectName(), -3.3999996f, 0.0250229f, -0.0000194f);
	m_pRWrist = new Node("RightWrist", this->GetGameObjectName(), -6.0000381f, -0.1750183f, 0.0007156f);
	m_pNeck = new Node("Neck", this->GetGameObjectName(), 0.0249983f, 3.6625015f, 2.5999998f);

	// Root Children
	this->AddChild(m_pPelvis);

	// Pelvis Children
	m_pPelvis->AddChild(m_pBody);

	m_pPelvis->AddChild(m_pLHip);
	m_pLHip->AddChild(m_pLKnee);
	m_pLKnee->AddChild(m_pLAnkle);
	
	m_pPelvis->AddChild(m_pRHip);
	m_pRHip->AddChild(m_pRKnee);
	m_pRKnee->AddChild(m_pRAnkle);

	// Body Children
	m_pBody->AddChild(m_pLShoulder);
	m_pLShoulder->AddChild(m_pLElbow);
	m_pLElbow->AddChild(m_pLWrist);
	
	m_pBody->AddChild(m_pRShoulder);
	m_pRShoulder->AddChild(m_pRElbow);
	m_pRElbow->AddChild(m_pRWrist);

	m_pBody->AddChild(m_pNeck);
}
