#pragma once
#include "Transform.hpp"
#include <vector>
#include "I_ComponentBase.h"
#include <memory>
#include <algorithm>

template<typename T>
concept componentType = std::is_same_v< T, I_ComponentBase >;
class GameObject
{

public:

	void Update();

	Transform transform; // The transform data for the game object

	std::vector<std::shared_ptr<I_ComponentBase>> Components;

	void AddComponent(std::shared_ptr<I_ComponentBase> component);
	void RemoveComponent(std::shared_ptr<I_ComponentBase> component);
	
	template<typename componentType>
	componentType* GetComponentByType()
	{

		auto it = std::find_if(Components.begin(), Components.end(),
			[](const std::shared_ptr<I_ComponentBase>& obj)
			{
				return dynamic_cast<componentType*>(obj.get()) != nullptr;
			}
		);
		if (it != Components.end())
			return dynamic_cast<componentType*> ((*it).get());

		return nullptr;

	}

};


