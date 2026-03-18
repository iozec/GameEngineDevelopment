#pragma once

#include <vector>
#include <memory>
#include "IGuiWindow.h"
#include "IDerectoryItem.h"
#include "Subscriber.h"

class IEventData;

class EditorGui : public IGuiWindow, public Subscriber
{
private:
    static EditorGui* _instance;
public:
    
    static EditorGui& const INSTANCE();
    // Inherited via IGuiWindow
    void DrawWindow() override;
	IDirectoryItem* AssetMouseDrag = nullptr;
    void Receive(const IEventData* message, const std::string& topic);
};
