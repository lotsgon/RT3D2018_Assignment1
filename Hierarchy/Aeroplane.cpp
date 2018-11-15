//*********************************************************************************************
// File:			Aeroplane.cpp
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include "Aeroplane.h"

// Initialise static class variables.

Aeroplane::Aeroplane(std::string name, std::string objName, float fX, float fY, float fZ, float fRotX, float fRotY, float fRotZ, bool mCamEnabled) : Node(name, objName, fX, fY, fZ, fRotX, fRotY, fRotZ, mCamEnabled)
{
	m_fSpeed = 0.0f;
}

Aeroplane::~Aeroplane(void)
{
}

void Aeroplane::Update(bool bPlayerControl)
{
	// DON'T DO THIS UNTIL YOu HAVE COMPLETED THE FUNCTION ABOVE
	if (bPlayerControl)
	{
		// Step 1: Make the plane pitch upwards when you press "Q" and return to level when released
		// Maximum pitch = 60 degrees
		if (Application::s_pApp->IsKeyPressed('Q') && this->GetXRotation() <= 60.0f)
		{
			this->UpdateXRotation(2.0f);
		}
		else if (this->GetXRotation() > 0.0f && !Application::s_pApp->IsKeyPressed('Q'))
		{
			this->UpdateXRotation(-2.0f);
		}


		// Step 2: Make the plane pitch downwards when you press "A" and return to level when released
		// You can also impose a take off speed of 0.5 if you like
		// Minimum pitch = -60 degrees
		if (Application::s_pApp->IsKeyPressed('A') && this->GetXRotation() >= -60.0f)
		{
			this->UpdateXRotation(-2.0f);
		}
		else if (this->GetXRotation() < 0.0f && !Application::s_pApp->IsKeyPressed('A'))
		{
			this->UpdateXRotation(2.0f);
		}

		// Step 3: Make the plane yaw and roll left when you press "O" and return to level when released
		// Maximum roll = 20 degrees
		if (Application::s_pApp->IsKeyPressed('O'))
		{
			if (this->GetZRotation() <= 20.0f)
			{
				this->UpdateZRotation(1.0f);
			}

			this->UpdateYRotation(-1.0f);
		}
		else if (this->GetZRotation() > 0.0f && !Application::s_pApp->IsKeyPressed('O'))
		{
			this->UpdateZRotation(-1.0f);
		}

		// Step 4: Make the plane yaw and roll right when you press "P" and return to level when released
		// Minimum roll = -20 degrees
		if (Application::s_pApp->IsKeyPressed('P'))
		{
			if (this->GetZRotation() >= -20.0f)
			{
				this->UpdateZRotation(-1.0f);
			}

			this->UpdateYRotation(1.0f);
		}
		else if (this->GetZRotation() < 0.0f && !Application::s_pApp->IsKeyPressed('P'))
		{
			this->UpdateZRotation(1.0f);
		}

	} // End of if player control

	// Apply a forward thrust and limit to a maximum speed of 1
	m_fSpeed += 0.001f;

	if (m_fSpeed > 1)
		m_fSpeed = 1;

	//// Rotate propeller and turret
	m_pProp->UpdateZRotation(100 * m_fSpeed);
	m_pTurret->UpdateYRotation(0.5f);

	//// Tilt gun up and down as turret rotates
	m_pGun->SetLocalRotation(0.0f, 0.0f, (sin((float)XMConvertToRadians(m_pTurret->GetYRotation() * 4.0f)) * 10.0f) - 10.0f);

	Node::Update();

	// Move Forward
	XMVECTOR vCurrPos = XMLoadFloat4(&m_v4LocalPosition);
	vCurrPos += m_vForwardVector * m_fSpeed;
	XMStoreFloat4(&m_v4LocalPosition, vCurrPos);
}

void Aeroplane::SetUpHierarchy(void)
{
	m_pProp = new Node("Propellor", this->GetGameObjectName(), 0.0f, 0.0f, 1.9f);
	m_pTurret = new Node("Turret", this->GetGameObjectName(), 0.0f, 1.05f, -1.3f);
	m_pGun = new Node("Gun", this->GetGameObjectName(), 0.0f, 0.5f, 0.0f);

	this->AddChild(m_pProp);
	this->AddChild(m_pTurret);
	m_pTurret->AddChild(m_pGun);

}
