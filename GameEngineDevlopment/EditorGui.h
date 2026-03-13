#pragma once

#include <vector>
#include <memory>
#include "IGuiWindow.h"

class EditorGui : public IGuiWindow
{
private:
    static EditorGui* _instance;
public:
    
    static EditorGui& const INSTANCE();
    // Inherited via IGuiWindow
    void DrawWindow() override;
};
