#pragma once
#include "include.h"

class ObjectBase {
public:

	ObjectBase() { Init(); }
	~ObjectBase() { End(); }

	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void End() {}

protected:

	struct IMAGE {
		struct POSITION {
			float x = 0;
			float y = 0;
		} pos;
		std::vector<int> handle;
		float w = 0;
		float h = 0;
		virtual void Load(json data) {
			handle.push_back(LoadGraph((CONFIG.GetSpriteDir() + "/" + (std::string)data["filepath"]).c_str()));
			if (handle[0] == -1) { return; }
			GetGraphSizeF(handle[0], &w, &h);
		}
		virtual void Draw(int index = 0, int transflag = TRUE) {
			if (handle.size() == 0) { return; }
			if (handle[index] == -1) { return; }
			DrawExtendGraphF(
				pos.x - (w / 2),
				pos.y - (h / 2),
				pos.x + (w / 2),
				pos.y + (h / 2),
				handle[index],
				transflag
			);
		}
	} image;


};