#pragma once
#include "SceneLobject.h"

class SceneManager {
public:

	SceneManager() = default;
	~SceneManager() = default;

	using ScenePointer = SceneLobject::Pointer;
	using LobjectPointer = SceneLobject::LobjectPointer;
	using SceneMaker = function_ref<ScenePointer()>;

	template<std::derived_from<SceneLobject> T>
	void Regist() {
		m_MakeFunctions.emplace(GetTypeHash<T>(), [tp = this]() -> ScenePointer {
			return SceneLobject::Make<T>(tp);
		});
		if (!m_Current) {
			Change<T>();
		}
	}

	template<std::derived_from<SceneLobject> T>
	void Change() {
		auto it = m_MakeFunctions.find(GetTypeHash<T>());
		if (it == m_MakeFunctions.end()) {
			throw std::runtime_error("not register scene type");
		}
		if (m_Current) {
			m_MakeQueue = it->second;
		}
		else {
			m_Current = it->second();
		}
	}

	void Clock() {
		m_Current->Clock();
		if (m_MakeQueue) {
			m_Current = m_MakeQueue.value()();
			m_MakeQueue = std::nullopt;
		}
	}

private:

	template<class T>
	size_t GetTypeHash() {
		return typeid(T).hash_code();
	}

	ScenePointer m_Current = nullptr;
	std::optional<SceneMaker> m_MakeQueue;
	std::unordered_map<size_t, SceneMaker> m_MakeFunctions;
};
