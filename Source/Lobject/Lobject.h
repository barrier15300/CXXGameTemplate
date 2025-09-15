#pragma once
#include <atomic>
#include <unordered_map>
#include <optional>
#include <tuple>
#include <bitset>
#include <deque>
#include <ranges>

/// Layer Object (Lobject)

class Lobject {
public:

	using Pointer = std::unique_ptr<Lobject>;
	using ChildrenType = std::vector<Pointer>;

	template<void(Lobject::* pfunc)()>
	static void RecusiveInvoke(Pointer& target) {
		thread_local std::deque<Pointer&> queue;

		if (!target) [[unlikely]] {
			throw std::runtime_error("target is nullptr");
		}

		queue.push_back(target);

		while (!queue.empty()) {
			auto&& cur = queue.back();
			queue.pop_back();

			for (auto&& child : std::ranges::reverse_view(cur->m_Children)) {
				queue.push_back(child);
			}

			cur->CommonInvoke<pfunc>();
		}
	}

	template<std::derived_from<Lobject> T>
	static Pointer Make(bool active = true) {
		return Pointer(new T(active));
	}

	template<std::derived_from<Lobject> T>
	static Pointer Make(bool active, std::initializer_list<Pointer&&>&& list) {
		auto ret = new T(active);
		for (auto&& p : list) {
			ret->RegistChild(p);
		}
		return Pointer(ret);
	}
	
	template<std::derived_from<Lobject> T>
	static Pointer Make(std::initializer_list<Pointer&&>&& list) {
		return Make(true, std::move(list));
	}

protected:

	template<void(Lobject::* pfunc)()>
	void CommonInvoke() {
		if (GetFlag<IsActive>()) {
			if (!GetFlag<IsInitialized>()) {
				if (!Init()) [[unlikely]] {
					throw std::runtime_error("Init() has return false");
				}
				_SetFlag<IsInitialized>(true);
			}
			this->*pfunc();
		}
	}

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

	Lobject(bool active = true) {
		_SetFlag<IsActive>(active);
		IDRegister();
	}

public:

	virtual ~Lobject() {
		Left();
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

	template<std::derived_from<Lobject> T>
	T* UpCast() const {
		return static_cast<T*>(this);
	}

	const Lobject* GetByID(size_t id) const {
		auto&& it = AllLobjects.find(id);
		if (it == AllLobjects.end()) {
			return nullptr;
		}
		return it->second;
	}
	const std::vector<std::unique_ptr<Lobject>>& GetChildren() const {
		return m_Children;
	}
	Lobject* GetChild(size_t idx) const {
		return m_Children.at(idx).get();
	}
	Lobject* operator[](size_t idx) const {
		return m_Children[idx].get();
	}
	const Lobject* GetParent() const {
		return m_Parent;
	}

	/// Flag Types 
	enum FlagType : size_t {
		/// private flags
		IsInitialized = 0,
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
		m_Flags[Ty] = f;
	}

	template<size_t Ty>
	bool GetFlag() const {
		return m_Flags[Ty];
	}

private:

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
		child->m_Parent = this;
	}

	std::bitset<64> m_Flags;
	size_t m_ID = 0;
	Lobject* m_Parent = nullptr;
	std::vector<Pointer> m_Children;
	inline static std::atomic<size_t> LastGenID = 0;
	inline static std::unordered_map<size_t, Lobject*> AllLobjects;

	template<size_t Ty>
	void _SetFlag(bool f) {
		m_Flags[Ty] = f;
	}
	
};

