#ifndef AEROPLANE_H
#define AEROPLANE_H

//*********************************************************************************************
// File:			Aeroplane.h
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Tom - 2018-2019
// Notes:
//*********************************************************************************************

#include "Node.h"

__declspec(align(16)) class Aeroplane : public Node
{
  public:
	Aeroplane(std::string name = "Aeroplane", std::string objName = "Other", float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f, float fRotX = 0.0f, float fRotY = 0.0f, float fRotZ = 0.0f, bool bCamEnabled = false);
	~Aeroplane(void);

	void Update(bool bPlayerControl); // Player only has control of plane when flag is set
	void SetUpHierarchy(void);

  private:

	float m_fSpeed; // Forward speed

	Node* m_pProp;
	Node* m_pTurret;
	Node* m_pGun;

	XMFLOAT4 m_v4CamRot; // Local rotation angles
	XMFLOAT4 m_v4CamOff; // Local offset

	XMVECTOR m_vCamWorldPos; // World position
	XMMATRIX m_mCamWorldMatrix; // Camera's world transformation matrix

	bool m_bGunCam;

  public:
	void SetGunCamera(bool value) { m_bGunCam = value; }

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