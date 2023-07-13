#include "Sprite.h"

void SpriteManager::Init() {
	std::fstream fs(CONFIG.GetSpriteDir() + "/spriteconfig.json");

	if (!fs.is_open()) { return; }

	json data;

	fs >> data;

	fs.close();

	m_SpriteDatas = data["Sample"];
}

