#include "EditorGui.h"
#include "IEventData.h"
#include "SDL3/SDL.h" 
#include "MouseEventData.h"
#include "Hierarchy.h"
#include <iostream>

void EditorGui::DrawWindow()
{
}


EditorGui& const EditorGui::INSTANCE()
{
    if (!EditorGui::_instance)
        EditorGui::_instance = new EditorGui();

    return *EditorGui::_instance;
}
EditorGui* EditorGui::_instance = nullptr;

void EditorGui::Receive(const IEventData* EventData, const std::string& topic)
{
	const MouseEventData* mouseEventData = static_cast<const MouseEventData*>(EventData);

	if (mouseEventData->mouseButton.button == SDL_BUTTON_LEFT &&
		mouseEventData->mouseButton.type == SDL_EVENT_MOUSE_BUTTON_UP &&
		AssetMouseDrag != nullptr)
	{
		SDL_Point mousePosition = { mouseEventData->mousePositon.x, mouseEventData->mousePositon.y };
		std::cout << "Mouse Button Update at position: ("
			<< mousePosition.x << ", " << mousePosition.y << ")\n";

		Hierarchy::INSTANCE().AddGameObject(
			AssetMouseDrag->GetDirectoryEntry().path().string(),
			mousePosition.x,
			mousePosition.y,
			true);

		AssetMouseDrag = nullptr;
	}
}