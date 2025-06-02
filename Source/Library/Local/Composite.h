#pragma once
#include <vector>
#include <memory>
#include <concepts>
#include <functional>

class IComposite {
public:

	IComposite() = default;
	IComposite(IComposite* parent) : m_Parent(parent) {};
	virtual ~IComposite() = default;

	template<std::derived_from<IComposite> T>
	void AddChild() {
		m_Children.push_back(std::make_unique<T>(new T));
	}
	
	virtual const IComposite* GetParent() const {
		return m_Parent;
	}
	
	virtual IComposite* operator[](size_t idx) {
		return m_Children.at(idx).get();
	}
	
	virtual IComposite* Assemble() const = 0;

private:
	IComposite* m_Parent = nullptr;
	std::vector<std::unique_ptr<IComposite>> m_Children{};
};

template<class T>
class Composite : public std::vector<Composite<T>> {
public:

	Composite() = default;
	Composite(const Composite* parent) : m_Parent(parent) {}
	
	Composite& AddChild(const T& init) {
		Composite ret(this);
		ret.m_Object = init;
		this->push_back(std::move(ret));
		return this->back();
	}
	
	Composite& AddChild(T&& init) {
		Composite ret(this);
		ret.m_Object = init;
		this->push_back(std::move(ret));
		return this->back();
	}
	
	const Composite* GetParent() const {
		return m_Parent;
	}
	
	T& Get() {
		return m_Object;
	}

	const T& Get() const {
		return m_Object;
	}
	
	void ForEach(const std::function<T(const T&, T&)>& action) {
		std::stack<std::pair<Composite*, T>> stack;
		stack.push({ this, {} });

		while (!stack.empty()) {
			auto&& [node, parent] = stack.top();
			stack.pop();

			auto&& next = action(parent, node->Get());
			
			for (auto it = node->begin(), end = node->end(); it != end; ++it) {
				auto&& child = *it;
				stack.push({ &child, next});
			}
		}
	}

	static Composite AbsoluteLoop(const Composite* src, const std::function<T(T, T)>& action) {
		const Composite* parent = src->GetParent();
		std::vector<const Composite*> roots{};
		
		while (parent != nullptr) {
			roots.push_back(parent);
			parent = parent->GetParent();
		};

		Composite ret(src->GetParent());
		ret.Get() = src->Get();
		for (auto it = roots.rbegin(), end = roots.rend(); it != end; ++it) {
			ret.Get() = action(ret.Get(), (*it)->Get());
		}

		return ret;
	}

private:
	T m_Object{};
	const Composite* m_Parent = nullptr;
};

