#pragma once

#include <memory>
#include <string>
#include "ECS.h"
#include "Components.hpp"

class MovementSystem
{
public:
	static PositionECS AddPositonComponentToEntitiy(uint32_t EntityID,
		ECS& ecs, float InitialX, float InitialY);
	static VelocityECS AddVelocityComponentToEntitiy(uint32_t EntityID,
		ECS& ecs, float InitialDX, float InitialDY ,
		float Gravity = 1.0f);

	static void UpdatePositions(ECS& ecs);
};

