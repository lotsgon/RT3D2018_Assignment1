#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H

#pragma once

#include <tinyxml2.h>
#include <StringUtils.h>
#include "Animation.h"
#include "Node.h"

class AnimationLoader
{
public:

	static void LoadAnimation(const char * fileName, Node * gameObject);

	static std::vector<std::string> GetXMLElementNameAndType(tinyxml2::XMLElement * animationElement);

	static void ParseElement(tinyxml2::XMLElement* animationElement, Animation * animation, std::string animType);
private:
	AnimationLoader();
	~AnimationLoader();

	static std::vector<Node*> GetAllGameObjects(Node* obj)
	{
		std::vector<Node*> objects;

		for (Node* childObj : obj->GetChildren())
		{
			std::vector<Node*> childObjects = GetAllGameObjects(childObj);

			for (Node* child : childObjects)
			{
				objects.push_back(child);
			}
		}
		
		objects.push_back(obj);

		return objects;
	}
};

#endif
