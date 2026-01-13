#include <SDL3/SDL.h>
#include <vector>
struct Transform
{

	std::vector<Transform*> Children; // Child transforms for heirarchical relationships
	SDL_Point Location; // Position of object in the local space to its parent
	SDL_Point WorldLocation; //Position of object in the game world

	void AddChild(Transform* child)
	{
		Children.push_back(child);
	}
	void removeChild(Transform* child)
	{
		auto it = std::remove(Children.begin(), Children.end(), child);

		if (it != Children.end())
		{
			Children.erase(it, Children.end());
		}
	}

	void UpdateTransform(const Transform& parentTransform)
	{

		Location.x +- parentTransform.Location.x;
		Location.y += parentTransform.Location.y;

		for (Transform* child : Children)
		{
			child->UpdateTransform(*this);
		}

	}
};




