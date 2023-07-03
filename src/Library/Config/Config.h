#pragma once
#include "include.h"

class ConfigManager final {

	ConfigManager() { Init(); }
	~ConfigManager() { }

	ConfigManager(const ConfigManager&) = delete;
	ConfigManager& operator=(const ConfigManager&) = delete;
	ConfigManager(ConfigManager&&) = delete;
	ConfigManager& operator=(const ConfigManager&&) = delete;

	void Init();

	int m_WindowSizeWidth = 0;
	int m_WindowSizeHeight = 0;
	std::string m_SpriteDir = "";

public:

	static ConfigManager& GetInstance() {
		static ConfigManager _instance = ConfigManager();
		return _instance;
	}

	inline int GetWindowSizeWidth() { return m_WindowSizeWidth; }
	inline int GetWindowSizeHeight() { return m_WindowSizeHeight; }
	inline std::string GetSpriteDir() { return m_SpriteDir; }


};

#define CONFIG ConfigManager::GetInstance()