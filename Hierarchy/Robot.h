#ifndef ROBOT_H
#define ROBOT_H

//*********************************************************************************************
// File:			Robot.h
// Description:		A very simple class to represent an Robot as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Tom - 2018-2019
// Notes:
//*********************************************************************************************

#include "Node.h"

__declspec(align(16)) class Robot : public Node
{
public:
	Robot(std::string name = "Robot", std::string objName = "Robot", float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f, bool bIsRoot = false, float fRotX = 0.0f, float fRotY = 0.0f, float fRotZ = 0.0f, bool bCamEnabled = false);
	~Robot(void);

	void SetUpHierarchy(void);

private:

	Node* m_pPelvis;
	Node* m_pBody;
	Node* m_pLHip;
	Node* m_pLKnee;
	Node* m_pLAnkle;
	Node* m_pRHip;
	Node* m_pRKnee;
	Node* m_pRAnkle;
	Node* m_pLShoulder;
	Node* m_pLElbow;
	Node* m_pLWrist;
	Node* m_pRShoulder;
	Node* m_pRElbow;
	Node* m_pRWrist;
	Node* m_pNeck;

public:

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