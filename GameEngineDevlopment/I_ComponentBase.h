#pragma once

class GameObject;

class I_ComponentBase
{
public:

	I_ComponentBase(GameObject* parent) : ParentObject(parent)
	{
	}

	virtual ~I_ComponentBase() = 0;
	virtual void Update() = 0;

protected:
	GameObject* ParentObject;
};

