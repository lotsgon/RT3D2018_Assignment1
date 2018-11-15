//*******//*********************************************************************************************
// File:			Node.cpp
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Tom - 2018-2019
// Notes:
//*********************************************************************************************

#include "Node.h"
#include <cctype>

bool Node::s_bResourcesReady = false;

Node::Node(std::string name, std::string objName, float fX, float fY, float fZ, bool bIsRoot, float fRotX, float fRotY, float fRotZ, bool bCamEnabled, bool bYFacingCam)
	: m_name(name), m_gameObjectName(objName), m_bCamEnabled(bCamEnabled), m_bIsRoot(bIsRoot), m_bYFacingCam(bYFacingCam)
{
	m_mWorldMatrix = XMMatrixIdentity();
	m_mCamWorldMatrix = XMMatrixIdentity();

	this->SetLocalRotation(fRotX, fRotY, fRotZ);
	this->SetLocalPosition(fX, fY, fZ);

	m_v4LocalCamOffset = XMFLOAT4(0.0f, 4.5f, -15.0f, 0.0f);
	m_v4LocalCamRotation = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_vCamWorldPos = XMVectorZero();
	m_vForwardVector = XMVectorZero();
}

Node::Node(std::string name, std::string objName, XMFLOAT4 mPos, bool bIsRoot, XMFLOAT4 mRot, bool bCamEnabled, bool bYFacingCam)
	: m_name(name), m_gameObjectName(objName), m_bCamEnabled(bCamEnabled), m_bIsRoot(bIsRoot), m_bYFacingCam(bYFacingCam)
{
	m_mWorldMatrix = XMMatrixIdentity();
	m_mCamWorldMatrix = XMMatrixIdentity();

	this->SetLocalRotation(mRot);
	this->SetLocalPosition(mPos);

	m_v4LocalCamOffset = XMFLOAT4(0.0f, 4.5f, -15.0f, 0.0f);
	m_v4LocalCamRotation = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_vCamWorldPos = XMVectorZero();
	m_vForwardVector = XMVectorZero();
}


Node::~Node(void)
{
}

void Node::SetWorldPosition(float fX, float fY, float fZ)
{
	m_v4LocalPosition = XMFLOAT4(fX, fY, fZ, 0.0f);
	UpdateMatrices();
}

void Node::AddChild(Node* pChild)
{
	m_children.push_back(pChild);
	pChild->SetParent(this);
}

void Node::UpdateMatrices(void)
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans;

	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4LocalRotation.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4LocalRotation.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4LocalRotation.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4LocalPosition));

	if (!m_pParent)
	{
		m_mWorldMatrix = mRotX * mRotZ * mRotY * mTrans;
	}
	else
	{
		m_mWorldMatrix = mRotX * mRotY * mRotZ * mTrans * m_pParent->m_mWorldMatrix;
	}

	m_vForwardVector = m_mWorldMatrix.r[2];

	if (m_bCamEnabled)
	{
		this->UpdateCameraPosition(mRotX, mRotY, mRotZ, mTrans);
	}

	for (Node* child : m_children)
	{
		child->UpdateMatrices();
	}
}

void Node::Update()
{
	UpdateMatrices();
}

void Node::LoadResources(void)
{
	if (!m_bIsRoot)
	{
		std::string fileName;

		fileName = "Resources/" + m_gameObjectName + "/" + m_name + ".x";

		m_pNodeMesh = CommonMesh::LoadFromXFile(Application::s_pApp, fileName.c_str());
	}

	for (Node* child : m_children)
	{
		child->LoadResources();
	}
}

void Node::ReleaseResources(void)
{
	delete m_pNodeMesh;

	for (Node* child : m_children)
	{
		child->ReleaseResources();
	}
}

void Node::Draw(void)
{
	if (!m_bIsRoot)
	{
		Application::s_pApp->SetWorldMatrix(m_mWorldMatrix);
		m_pNodeMesh->Draw();
	}

	for (Node* child : m_children)
	{
		child->Draw();
	}
}

void Node::UpdateCameraPosition(XMMATRIX &mRotX, XMMATRIX &mRotY, XMMATRIX &mRotZ, XMMATRIX &mTrans)
{
	XMMATRIX mYCameraRot = mRotY * mTrans;

	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4LocalCamRotation.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4LocalCamRotation.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4LocalCamRotation.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4LocalCamOffset));

	if (m_bYFacingCam)
	{
		m_mCamWorldMatrix = mRotY * mTrans * mYCameraRot;
	}
	else if(!m_pParent && m_mCamNodeFocus)
	{
		m_mCamWorldMatrix = mRotX * mRotY * mRotZ * mTrans * m_mCamNodeFocus->m_mWorldMatrix;
	}
	else
	{
		m_mCamWorldMatrix = mRotX * mRotY * mRotZ * mTrans * m_mWorldMatrix;
	}
	// Get the camera's world position (m_vCamWorldPos) out of m_mCameraWorldMatrix

	m_vCamWorldPos = m_mCamWorldMatrix.r[3];
}
