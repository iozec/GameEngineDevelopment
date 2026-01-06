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

	ecs.velocities[EntityID] = vel;
	ecs.entityIDs[EntityID] |= VelocityKey;
		

	return vel;
}

void MovementSystem::UpdatePositions(ECS& const ecs)
{

	if (ecs.entityIDs[0] & (PositionKey | VelocityKey))
	{
		ecs.velocities[0].dy += ecs.velocities[0].gravity;
		ecs.positions[0] += ecs.velocities[0];
	}
}