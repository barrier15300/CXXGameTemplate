#pragma once
#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "DataStorage.h"
#include "DxLib_wrapper/DxLib_wrapper.h"

#define OBJECT_INTERFACE_INLINE_H(cls_t)\
class cls_t : public IObjectBase {\
public:\
	\
	IObjectBase* ObjectInit() { return new cls_t(); }\
	\
	virtual bool Init();\
	virtual void Proc();\
	virtual void Draw();\
	virtual void End();\
};

#define OBJECT_INTERFACE_INLINE_CPP(cls_t) \
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

	IObjectBase() = default;
	virtual ~IObjectBase() = default;

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

	std::unique_ptr<ObjectSwitcher> Scene = std::make_unique<ObjectSwitcher>(this);

private:

	Storage::Data<"config.json"> m_Config;
	Storage::Data<"Asset/asset.json"> m_Asset;

protected:

	using Config = decltype(m_Config);
	using Asset = decltype(m_Asset);

	InputDevices Input;

	DxLibSystem DXSystem;

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
	~ObjectSwitcher() { if (m_NowObject != nullptr) { m_NowObject->Invoke_End(); } }

	template<std::derived_from<IObjectBase> T>
	void Regist() {
		IObjectBase* obj = new T();
		std::string name = std::string(typeid(T).name()).substr(6);
		SetParent(obj, m_ParentObject);
		m_RegistObjects[name] = [=] { return obj->ObjectInit(); };
		if (m_NowObject == nullptr) {
			this->Change(name);
		}
	}

	void Change(const std::string& name) {
		if (name.empty()) {
			return;
		}

		auto it = m_RegistObjects.find(name);
		if (it == m_RegistObjects.end()) {
			throw std::runtime_error("Object name not found: " + name);
		}

		if (m_NowObject != nullptr) { m_NowObject->Invoke_End(); }
		
		m_NowObject.reset(it->second());
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
	std::unique_ptr<IObjectBase> m_NowObject = nullptr;
	std::unordered_map<std::string, std::function<IObjectBase*()>> m_RegistObjects;
};