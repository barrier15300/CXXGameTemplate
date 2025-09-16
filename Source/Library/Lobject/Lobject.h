#pragma once
#include <atomic>
#include <unordered_map>
#include <optional>
#include <tuple>
#include <bitset>
#include <deque>
#include <ranges>

/// Layer Object (Lobject)

class SceneLobject;
class SceneManager;

class Lobject {
	friend SceneLobject;

public:

	using RawPointer = Lobject*;
	using Pointer = std::unique_ptr<Lobject>;
	using ChildrenType = std::vector<Pointer>;

	template<std::derived_from<Lobject> T>
	static Pointer Make(bool active = true) {
		auto ret = Pointer(new T());
		ret->_SetFlag<IsActive>(active);
		return ret;
	}

	template<std::derived_from<Lobject> T>
	static Pointer Make(bool active, std::initializer_list<Pointer&&>&& list) {
		auto ret = Make<T>(active);
		for (auto&& p : list) {
			ret->RegistChild(std::move(p));
		}
		return Pointer(ret);
	}
	
	template<std::derived_from<Lobject> T>
	static Pointer Make(std::initializer_list<Pointer&&>&& list) {
		return Make(true, std::move(list));
	}

	template<void(Lobject::* pfunc)()>
	static void RecusiveInvoke(Pointer& target) {
		thread_local std::deque<RawPointer> queue;

		if (!target) [[unlikely]] {
			throw std::runtime_error("target is nullptr");
		}

		queue.push_back(target.get());

		while (!queue.empty()) {
			auto&& cur = queue.back();
			queue.pop_back();

			for (auto&& child : std::ranges::reverse_view(cur->m_Children)) {
				queue.push_back(child.get());
			}

			cur->CommonInvoke<pfunc>();
		}
	}

	template<void(Lobject::* pfunc)()>
	void CommonInvoke() {
		if (GetFlag<IsActive>()) {
			if (!GetFlag<IsInitialized>()) {
				if (!Init()) [[unlikely]] {
					throw std::runtime_error("Init() has return false");
				}
				_SetFlag<IsInitialized>(true);
			}
			std::invoke(pfunc, *this);
		}
	}

	/// TODO:
	///		Left()関数の呼び出しを自然に行わなければいけない
	///		または明示的に呼び出せるようにする方法を考える
	/// 

	virtual bool CommonInit() {
		return Init();
	}
	virtual void CommonProc() {
		Proc();
	}
	virtual void CommonDraw() {
		Draw();
	}
	virtual void CommonLeft() {
		Left();
	}

	virtual bool Init() = 0;
	virtual void Proc() = 0;
	virtual void Draw() = 0;
	virtual void Left() = 0;

protected:

	Lobject() {
		IDRegister();
	}

public:

	virtual ~Lobject() {
		IDUnregister();
	}

	template<std::derived_from<Lobject> T>
		requires(std::is_default_constructible_v<T>)
	void RegistChild() {
		RegistChild(Make<T>());
	}
	void RegistChild(Pointer&& child) {
		AttachParent(child);
		m_Children.push_back(std::move(child));
	}

	void DestroyChild(size_t idx) {
		auto&& target = m_Children[idx];
		auto it = std::remove(m_Children.begin(), m_Children.end(), target);
		m_Children.erase(it, m_Children.end());
	}

	template<std::derived_from<Lobject> T>
	T* UpCast() const {
		return static_cast<T*>(this);
	}

	const RawPointer GetByID(size_t id) const {
		auto&& it = AllLobjects.find(id);
		if (it == AllLobjects.end()) {
			return nullptr;
		}
		return it->second.m_This;
	}
	const ChildrenType& GetChildren() const {
		return m_Children;
	}
	RawPointer GetChild(size_t idx) const {
		return m_Children.at(idx).get();
	}
	RawPointer operator[](size_t idx) const {
		return m_Children[idx].get();
	}
	const RawPointer GetParent() const {
		return GetInfo().m_Parent;
	}

	SceneLobject* GetScene() const {
		return GetInfo().m_Scene;
	}

	/// Flag Types 
	enum FlagType : size_t {
		/// private flags
		IsInitialized = 0,
		DestroyQueue,
		PrivateFlagEnd,

		/// public flags
		IsActive = 32,
		PublicFlagEnd,
	};

	template<size_t Ty>
	void SetFlag(bool f) {
		if constexpr (Ty < IsActive) {
			throw std::runtime_error("private flag accessed");
		}
		GetInfo().m_Flags[Ty] = f;
	}
	template<size_t Ty>
	bool GetFlag() const {
		return GetInfo().m_Flags[Ty];
	}
	template<size_t Ty>
	auto GetFlagRef() const {
		if constexpr (Ty < IsActive) {
			throw std::runtime_error("private flag accessed");
		}
		return GetInfo().m_Flags[Ty];
	}

private:

	template<size_t Ty>
	void _SetFlag(bool f) {
		GetInfo().m_Flags[Ty] = f;
	}

	void IDRegister() {
		while (true) {
			++LastGenID;
			if (LastGenID == 0) { continue; }
			if (AllLobjects.find(LastGenID) != AllLobjects.end()) { continue; }
			m_ID = LastGenID;
			break;
		}
		AllLobjects[m_ID] = this;
	}
	void IDUnregister() {
		auto&& it = AllLobjects.find(m_ID);
		if (it != AllLobjects.end()) {
			AllLobjects.erase(it);
		}
	}

	void AttachParent(Pointer& child) {
		child->GetInfo().m_Parent = this;
	}

	struct _Info {
		_Info() {}
		_Info(RawPointer _this) : m_This(_this) {}
		
		std::bitset<64> m_Flags;
		RawPointer m_Parent = nullptr;
		RawPointer m_This = nullptr;
		SceneLobject* m_Scene = nullptr;
	};

	_Info& GetInfo() const {
		return AllLobjects[m_ID];
	}

	size_t m_ID = 0;
	ChildrenType m_Children;
	inline static std::atomic<size_t> LastGenID = 0;
	inline static std::unordered_map<size_t, _Info> AllLobjects;
};

class RootLobject : public Lobject {

	virtual bool Init() { return true; };
	virtual void Proc() { std::cout << __FUNCTION__ << std::endl; };
	virtual void Draw() { std::cout << __FUNCTION__ << std::endl; };
	virtual void Left() { std::cout << __FUNCTION__ << std::endl; };

};