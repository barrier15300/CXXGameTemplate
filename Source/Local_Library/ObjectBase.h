#pragma once
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "DataStorage.h"
#include "DxLib_wrapper/DxLib_wrapper.h"

#define INTERFACE_INLINE_H(cls_t)\
class cls_t : public IObjectBase {\
public:\
	cls_t() { Name = __func__; }\
	\
	IObjectBase* ObjectInit() { return new cls_t(); }\
	virtual bool Init();\
	virtual void Proc();\
	virtual void Draw();\
	virtual void End();\
};

#define INTERFACE_INLINE_CPP(cls_t) \
bool cls_t::Init() {\
	return true;\
}\
\
void cls_t::Proc() {\
	return;\
}\
\
void cls_t::Draw() {\
	return;\
}\
\
void cls_t::End() {\
	return;\
}\


class ObjectSwitcher;

class IObjectBase {
public:

	inline IObjectBase();
	inline ~IObjectBase();

	virtual IObjectBase* ObjectInit() = 0;

	virtual bool Invoke_Init() {
		return Init();
	}

	virtual void Invoke_Proc() {
		Input.Update();
		Proc();
	}

	virtual void Invoke_Draw() {
		Draw();
	}

	virtual void Invoke_End() {
		End();
	}

	virtual bool Init() = 0;
	virtual void Proc() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;

	IObjectBase* GetParent() { return m_ParentObject; };

	ObjectSwitcher* Scene;

protected:

	std::string Name = "Base";

	DataStorage<"config.json"> Config;
	DataStorage<"Asset/asset.json"> Asset;

	InputDevices Input;

	DxLibSystem System;

	IObjectBase* m_ParentObject = nullptr;
};

class ObjectSwitcher {
	inline static struct _SetParent final : public IObjectBase {
		IObjectBase* ObjectInit() { return new _SetParent(); };
		bool Init() { return true; };
		void Proc() {};
		void Draw() {};
		void End() {};
		void operator()(IObjectBase* source, IObjectBase* parent) {
			((_SetParent*)source)->m_ParentObject = parent;
		}
	} SetParent{};

public:

	ObjectSwitcher(IObjectBase* parent) { m_ParentObject = parent; }
	~ObjectSwitcher() {}

	void Regist(const std::string& name, IObjectBase* obj) {
		if (obj == nullptr) {
			return;
		}
		SetParent(obj, m_ParentObject);
		m_ObjectList[name] = std::unique_ptr<IObjectBase>(obj);
		if (m_NowObject == nullptr) {
			this->Change(name);
		}
	}

	void Change(const std::string& name, bool objinitflag = true) {
		if (name.empty()) {
			return;
		}
		if (m_NowObject != nullptr) { m_NowObject->Invoke_End(); }
		m_NowObject = m_ObjectList[name].get();
		if (objinitflag) { 
			m_NowObject = m_NowObject->ObjectInit();
			m_ObjectList[name].reset(m_NowObject);
		}
		m_NowObject->Invoke_Init();
	}

	void Proc() {
		m_NowObject->Invoke_Proc();
	}

	void Draw() {
		m_NowObject->Invoke_Draw();
	}

	IObjectBase* GetParent() {
		return m_ParentObject;
	}

private:

	IObjectBase* m_ParentObject = nullptr;
	IObjectBase* m_NowObject = nullptr;
	std::unordered_map<std::string, std::unique_ptr<IObjectBase>> m_ObjectList;
};

inline IObjectBase::IObjectBase() {
	Scene = new ObjectSwitcher(this);
}

inline IObjectBase::~IObjectBase() {
	delete Scene;
	Scene = nullptr;
}