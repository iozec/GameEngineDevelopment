#pragma once
#include "ISaveLoadable.h"
class GameObject;

class I_ComponentBase : public ISaveLoadable
{
public:

	I_ComponentBase(GameObject* parent) : ParentObject(parent)
	{
	}

	virtual ~I_ComponentBase() = 0;
	virtual void Update() = 0;

	//inherited via ISaveLoadable
	virtual nlohmann::json Save() const = 0;
	virtual void Load(nlohmann::json LoadData,
		std::shared_ptr<SDL_Renderer> renderer) = 0;

	virtual std::string Type() const = 0;

protected:
	GameObject* ParentObject;
};

