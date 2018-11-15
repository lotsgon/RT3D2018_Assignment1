#ifndef NODE_H
#define NODE_H

//*********************************************************************************************
// File:			Node.h
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Tom - 2018-2019
// Notes:
//*********************************************************************************************

#include "Application.h"

__declspec(align(16)) class Node
{
public:
	Node(std::string name = "Node", std::string objName = "Other", bool bIsRoot = false, bool bCamEnabled = false, bool bYFacingCam = false)
		:m_name(name), m_bCamEnabled(bCamEnabled), m_bIsRoot(bIsRoot), m_bYFacingCam(bYFacingCam)
	{};
	Node(std::string name = "Node", std::string objName = "Other", float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f, bool bIsRoot = false, float fRotX = 0.0f, float fRotY = 0.0f, float fRotZ = 0.0f, bool bCamEnabled = false, bool bYFacingCam = false);
	Node(std::string name = "Node", std::string objName = "Other", XMFLOAT4 mPos = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), bool bIsRoot = false, XMFLOAT4 mRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), bool bCamEnabled = false, bool bYFacingCam = false);
	~Node(void);

	void LoadResources(void); // Only load the resources once for all instances
	void ReleaseResources(void); // Only free the resources once for all instances
	void Update(void); // Update every frame for all instances
	void Draw(void);

	void SetWorldPosition(float fX, float fY, float fZ);
	void AddChild(Node* pChild); // Add a child to this node

protected:
	void UpdateMatrices(void);
	void UpdateCameraPosition(XMMATRIX &mRotX, XMMATRIX &mRotY, XMMATRIX &mRotZ, XMMATRIX &mTrans);

	CommonMesh* m_pNodeMesh; // Only one mesh for all instances

	static bool s_bResourcesReady;

	std::string m_name;
	std::string m_gameObjectName;

	XMFLOAT4 m_v4LocalRotation; // Euler rotation angles
	XMFLOAT4 m_v4LocalPosition; // Local position
	XMFLOAT4 m_v4LocalScale; // Local scale

	XMVECTOR m_vForwardVector; // Forward Vector for Node

	XMMATRIX m_mLocalMatrix; // Local transformation matrix
	XMMATRIX m_mWorldMatrix; // World transformation matrix

	XMFLOAT4 m_v4LocalCamRotation; // Local rotation angles
	XMFLOAT4 m_v4LocalCamOffset; // Local offset

	XMVECTOR m_vCamWorldPos; // World position
	XMMATRIX m_mCamWorldMatrix; // Camera's world transformation matrix

	bool m_bCamEnabled, m_bYFacingCam;
	bool m_bIsRoot;

	Node* m_pParent = nullptr;
	Node* m_mCamNodeFocus = nullptr;


	std::vector<Node*> m_children;

public:
	float GetXPosition(void) { return m_v4LocalPosition.x; }
	float GetYPosition(void) { return m_v4LocalPosition.y; }
	float GetZPosition(void) { return m_v4LocalPosition.z; }
	float GetXRotation(void) { return m_v4LocalRotation.x; }
	float GetYRotation(void) { return m_v4LocalRotation.y; }
	float GetZRotation(void) { return m_v4LocalRotation.z; }
	std::string GetName(void) { return m_name; }
	std::string GetGameObjectName(void) { return m_gameObjectName; }
	XMFLOAT4 GetFocusPosition(void) { return GetLocalPosition(); }
	XMFLOAT4 GetCameraPosition(void)
	{
		XMFLOAT4 v4Pos;
		XMStoreFloat4(&v4Pos, m_vCamWorldPos);
		return v4Pos;
	}
	XMFLOAT4 GetLocalPosition(void) { return m_v4LocalPosition; }
	XMFLOAT4 GetLocalRotation(void) { return m_v4LocalRotation; }
	XMVECTOR GetForwardVector(void) { return m_vForwardVector; }
	void SetName(std::string name) { m_name = name; }
	void SetGameObjectName(std::string name) { m_gameObjectName = name; }
	void SetCameraEnabled(bool value) { m_bCamEnabled = value; }
	void SetCameraNodeFocus(Node* focus) { m_mCamNodeFocus = focus; }
	void SetYFacingCamera(bool value) { m_bYFacingCam = value; }
	void SetParent(Node* pParent) { m_pParent = pParent; }
	void SetLocalPosition(XMFLOAT4 mPos) { m_v4LocalPosition = mPos; };
	void SetLocalPosition(float fX, float fY, float fZ) { m_v4LocalPosition = XMFLOAT4(fX, fY, fZ, 0.0f); };
	void SetLocalRotation(XMFLOAT4 mRot) { m_v4LocalRotation = mRot; };
	void SetLocalRotation(float fX, float fY, float fZ) { m_v4LocalRotation = XMFLOAT4(fX, fY, fZ, 0.0f); };
	void UpdateXRotation(float f) { m_v4LocalRotation.x += f; }
	void UpdateYRotation(float f) { m_v4LocalRotation.y += f; }
	void UpdateZRotation(float f) { m_v4LocalRotation.z += f; }

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