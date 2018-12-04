#include "AnimationLoader.h"



AnimationLoader::AnimationLoader()
{
}


AnimationLoader::~AnimationLoader()
{
}

void AnimationLoader::LoadAnimation(const char* fileName, Node* gameObject)
{
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName);

	tinyxml2::XMLNode* rootElement = xmlDoc.FirstChildElement();

	std::vector<Node*> gameObjects = GetAllGameObjects(gameObject);

	for (Node* component : gameObjects)
	{
		Animation animation;

		for (tinyxml2::XMLElement* animationElement = rootElement->FirstChildElement("animation"); animationElement != NULL; animationElement = animationElement->NextSiblingElement("animation"))
		{
			std::vector<std::string> elementNameAndType = GetXMLElementNameAndType(animationElement);

			if (component->GetName() == elementNameAndType[0])
			{
				ParseElement(animationElement, &animation, elementNameAndType[1]);
			}
			else if ("root" == elementNameAndType[0] && component->IsRoot())
			{
				ParseElement(animationElement, &animation, elementNameAndType[1]);
			}
		}

		component->AddAnimation(animation);
	}
}

std::vector<std::string> AnimationLoader::GetXMLElementNameAndType(tinyxml2::XMLElement* animationElement)
{
	std::string idAttribute = animationElement->Attribute("id");

	std::vector<std::string> elementNameAndType = StringUtils::split(idAttribute, '.');

	return elementNameAndType;
}

void AnimationLoader::ParseElement(tinyxml2::XMLElement* animationElement, Animation* animation, std::string animType)
{
	tinyxml2::XMLElement* sourceElement = animationElement->FirstChildElement("source");
	tinyxml2::XMLElement* inputArray = sourceElement->FirstChildElement("float_array");

	std::vector<std::string> inputValues = StringUtils::split(inputArray->GetText(), ' ');

	tinyxml2::XMLElement* sourceElement2 = sourceElement->NextSiblingElement("source");
	tinyxml2::XMLElement* outputArray = sourceElement2->FirstChildElement("float_array");

	std::vector<std::string> outputValues = StringUtils::split(outputArray->GetText(), ' ');

	int count = std::stoi(inputArray->Attribute("count"));

	for (int i = 0; i < count; i++)
	{
		Keyframe keyframe;
		bool frameExists = false;
		std::vector<Keyframe> keyframes = animation->mKeyframes;

		if (keyframes.size() > i)
		{
			keyframe = animation->mKeyframes[i];
			frameExists = true;
		}

		keyframe.m_KeyframeTime = std::stof(inputValues[i]);

		if (animType == "translate")
		{
			keyframe.m_v4LocalPosition.x = std::stof(outputValues[i]) / 10;
			keyframe.m_v4LocalPosition.y = std::stof(outputValues[i + 1]) / 10;
			keyframe.m_v4LocalPosition.z = std::stof(outputValues[i + 2]) / 10;
		}
		else if (animType == "rotateX")
		{
			keyframe.m_v4LocalRotation.x = std::stof(outputValues[i]);
		}
		else if (animType == "rotateY")
		{
			keyframe.m_v4LocalRotation.y = std::stof(outputValues[i]);
		}
		else if (animType == "rotateZ")
		{
			keyframe.m_v4LocalRotation.z = std::stof(outputValues[i]);
		}

		if (!frameExists)
		{
			animation->mKeyframes.push_back(keyframe);
		}
		else
		{
			animation->mKeyframes[i] = keyframe;
		}
	}

}
