#include "Config.h"

void ConfigManager::Init() {
	std::fstream fs("config.json");

	if (!fs.is_open()) { return; }

	json data;

	fs >> data;

	fs.close();

	m_WindowSizeWidth = data["WindowSize"]["Width"];
	m_WindowSizeHeight = data["WindowSize"]["Height"];
	m_SpriteDir = data["SpriteDir"];
}
