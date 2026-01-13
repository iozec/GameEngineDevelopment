#include "MovementSystem.h"
PositionECS MovementSystem::AddPositonComponentToEntitiy(uint32_t EntityID,
	ECS& const ecs, float InitialX, float InitialY)
{
	PositionECS pos;
	pos.X = InitialX;
	pos.Y = InitialY;

	ecs.positions[EntityID] = pos;
	ecs.entityIDs[EntityID] |= PositionKey;

	return pos;
}

VelocityECS MovementSystem::AddVelocityComponentToEntitiy(uint32_t EntityID,
	ECS& const ecs, float InitialDX, float InitialDY, float Gravity)
{
	VelocityECS vel;
	vel.dx = InitialDX;
	vel.dy = InitialDY;
	vel.gravity = Gravity;

	ecs.velocities[EntityID] = vel;
	ecs.entityIDs[EntityID] |= VelocityKey;
		

	return vel;
}

void MovementSystem::UpdatePositions(ECS& const ecs)
{
	for (int entityID = 0; entityID < MAX_ENTITIES; entityID++)
	{
		if (ecs.entityIDs[entityID] & (PositionKey | VelocityKey))
		{
			ecs.velocities[entityID].dy += ecs.velocities[entityID].gravity;
			ecs.positions[entityID] += ecs.velocities[entityID];
		}
	}
}