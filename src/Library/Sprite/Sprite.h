#pragma once
#include "include.h"

class SpriteManager final {

	SpriteManager() { Init(); };
	~SpriteManager() { };

	SpriteManager(const SpriteManager&) = delete;
	SpriteManager& operator=(const SpriteManager&) = delete;
	SpriteManager(SpriteManager&&) = delete;
	SpriteManager& operator=(SpriteManager&&) = delete;

	void Init();
	
	std::vector<json> SpriteDatas;

public:

	static SpriteManager& GetInstance() {
		static SpriteManager _instance = SpriteManager();
		return _instance;
	}

	json operator[](size_t index) { return SpriteDatas[index]; }
};

#define SPRITE SpriteManager::GetInstance()