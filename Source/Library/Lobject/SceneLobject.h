#pragma once
#include "Lobject.h"

class SceneManager;

class SceneLobject {
	friend SceneManager;

protected:

	SceneLobject() = default;

public:

	~SceneLobject() = default;

	using Pointer = std::unique_ptr<SceneLobject>;
	using LobjectPointer = Lobject::Pointer;

	virtual void Clock() {
		Lobject::RecusiveInvoke<&Lobject::CommonProc>(m_RootLobject);
		Lobject::RecusiveInvoke<&Lobject::CommonDraw>(m_RootLobject);
	}

	SceneManager* GetManager() const {
		return m_Manager;
	}

private:

	template<std::derived_from<SceneLobject> T>
	static Pointer Make(SceneManager* manager) {
		auto ret = Pointer(new T());
		ret->m_RootLobject->GetInfo().m_Scene = ret.get();
		ret->m_Manager = manager;
		return ret;
	}

	LobjectPointer m_RootLobject = Lobject::Make<RootLobject>();
	SceneManager* m_Manager = nullptr;

};
