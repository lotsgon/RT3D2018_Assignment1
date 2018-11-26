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

class Bullet;

__declspec(align(16)) class Aeroplane : public Node
{
  public:
	  Aeroplane(std::string name = "Aeroplane", std::string objName = "Aeroplane", float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f, bool bIsRoot = false, float fRotX = 0.0f, float fRotY = 0.0f, float fRotZ = 0.0f, bool bCamEnabled = false, bool bYFacingCam = false);
	~Aeroplane(void);

	void Update(bool bPlayerControl); // Player only has control of plane when flag is set
	void SetUpHierarchy(void);

	void Draw(void);
	void ReleaseResources(void);

  private:

	float m_fSpeed; // Forward speed

	Node* m_pProp;
	Node* m_pTurret;
	Node* m_pGun;
	std::vector< Bullet* > m_pBullets;

	XMFLOAT4 m_v4CamRot; // Local rotation angles
	XMFLOAT4 m_v4CamOff; // Local offset

	XMVECTOR m_vCamWorldPos; // World position
	XMMATRIX m_mCamWorldMatrix; // Camera's world transformation matrix

  public:
	  void SetGunCamera(bool value) {
		  if (value)
		  {
			  this->SetCameraNodeFocus(m_pGun);
		  }
		  else
		  {
			  this->SetCameraNodeFocus(nullptr);
		  }
	  }

	  XMMATRIX GetGunWorldMatrix(void) { return m_pGun->GetWorldMatrix(); }
	  XMVECTOR GetGunForwardVector(void) { return m_pGun->GetForwardVector(); }
	  float GetSpeed(void) { return m_fSpeed; }

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