#pragma once
#include "include.h"

class SceneBase {
public:

	SceneBase() { Init(); }
	~SceneBase() { End(); }

	virtual void Init() { };
	virtual void Update() {
		for (const auto& _ptr : m_Objects) {
			_ptr->Update();
		}
	}
	virtual void Draw() {
		for (const auto& _ptr : m_Objects) {
			_ptr->Draw();
		}
	}
	virtual void End() {}

protected:

	std::vector<std::unique_ptr<ObjectBase>> m_Objects;

};

class SceneManager final {
	
	SceneManager() {};
	~SceneManager() = default;

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;
	
	std::unique_ptr<SceneBase> m_Scene;

public:

	static SceneManager& GetInstance() {
		static SceneManager _instance = SceneManager();
		return _instance;
	}

	SceneBase& Get() {
		return *m_Scene;
	}

	void Set(SceneBase* ptr) {
		m_Scene.reset(ptr);
	}
};

#define SCENE SceneManager::GetInstance()
