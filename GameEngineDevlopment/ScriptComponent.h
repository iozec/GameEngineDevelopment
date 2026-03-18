#pragma once

#include "I_ComponentBase.h"

#include "Sol/sol.hpp"
#include <filesystem>
#include "GameObject.h"

class ScriptComponent : public I_ComponentBase
{
private:
	sol:: state lua;
	sol::table luaScriptComponent;
	std::string ScriptPath;

	std::filesystem::file_time_type LastUpdated;
public:

	void Update() override;

	ScriptComponent(GameObject* ParentObject);

	ScriptComponent::ScriptComponent(const std::string FilePath, GameObject* ParentObj)
		:I_ComponentBase(ParentObj)
	{
		ScriptPath = FilePath;
		lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
		LoadScript();
	}

	nlohmann::json Save() const override;
	void Load(nlohmann::json LoadData,
		std::shared_ptr<SDL_Renderer> renderer) override;

	std::string Type() const override { return "ScriptComponent"; }

	

private:
	void reloadIfChanged();

	void LoadScript();
};

