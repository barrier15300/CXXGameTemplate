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
	
	json m_SpriteDatas;

public:

	static SpriteManager& GetInstance() {
		static SpriteManager _instance = SpriteManager();
		return _instance;
	}

	inline json GetSpriteDatas() { return m_SpriteDatas; }
};

#define SPRITE SpriteManager::GetInstance()