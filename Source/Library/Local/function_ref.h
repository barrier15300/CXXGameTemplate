#pragma once

#include <type_traits>
#include <utility>
#include <functional>
#include <cstddef>
#include <memory>

template <typename>
class function_ref;

template <typename R, typename... Args>
class function_ref<R(Args...)> {
public:
	function_ref() = delete;
	function_ref(const function_ref&) noexcept = default;
	function_ref& operator=(const function_ref&) noexcept = default;

	using Object = void*;
	using CallBack = R(*)(void*, Args&&...);

private:
	
	Object obj_ = nullptr;
	CallBack callback_ = nullptr;

	constexpr static bool is_nothrow_callable =
		std::is_nothrow_invocable_r_v<R, decltype(callback_), void*, Args...>;

	template <typename F>
	constexpr F* store_lambda(F&& f) noexcept {
		std::string s = typeid(typename std::remove_reference<decltype(f)>::type).name();
		//static F instance = std::forward<F>(f);
		//return &instance;
		return new F(std::forward<F>(f));
	}

public:
	
	template <typename F> requires
		std::is_pointer_v<F> &&
		std::is_function_v<std::remove_pointer_t<F>> &&
		std::is_invocable_r_v<R, F, Args...>	
	constexpr function_ref(R(*func)(Args...)) noexcept {
		obj_ = reinterpret_cast<void*>(func);
		callback_ = [](void* obj, Args&&... args) noexcept(is_nothrow_callable) -> R {
			return reinterpret_cast<R(*)(Args...)>(obj)(std::forward<Args>(args)...);
			};
	}

	template <typename F> requires
		(!std::is_same_v<F, function_ref>) &&
		std::is_invocable_r_v<R, F&, Args...> &&
		std::is_lvalue_reference_v<F&>
	constexpr function_ref(F& f) noexcept {
		obj_ = static_cast<void*>(std::addressof(f));
		callback_ = [](void* obj, Args&&... args) noexcept(is_nothrow_callable) -> R {
			return std::invoke(*static_cast<F*>(obj), std::forward<Args>(args)...);
			};
	}

	template <typename F> requires
		(!std::is_same_v<F, function_ref>) &&
		(!std::is_lvalue_reference_v<F&&>) &&
		std::is_invocable_r_v<R, F, Args...>
	constexpr function_ref(F&& f) noexcept {
		obj_ = static_cast<void*>(store_lambda(std::forward<F>(f)));
		callback_ = [](void* obj, Args&&... args) noexcept(is_nothrow_callable) -> R {
			return std::invoke(*static_cast<F*>(obj), std::forward<Args>(args)...);
			};
	}

	template <typename T>
	constexpr function_ref(R(T::* mf)(Args...), T& obj) noexcept {
		auto pobj = std::addressof(obj);
		auto plambda = store_lambda([mf, pobj](Args&&... args) noexcept(is_nothrow_callable) -> R {
			return (pobj->*mf)(std::forward<Args>(args)...);
			});
		obj_ = static_cast<void*>(plambda);
		callback_ = [](void* obj, Args&&... args) noexcept(is_nothrow_callable) -> R {
			return std::invoke(*static_cast<decltype(plambda)>(obj), std::forward<Args>(args)...);
			};
	}

	template <typename T>
	constexpr function_ref(R(T::* mf)(Args...) const, const T& obj) noexcept {
		auto pobj = std::addressof(obj);
		auto plambda = store_lambda([mf, pobj](Args&&... args) noexcept(is_nothrow_callable) -> R {
			return (pobj->*mf)(std::forward<Args>(args)...);
			});
		obj_ = static_cast<void*>(plambda);
		callback_ = [](void* obj, Args&&... args) noexcept(is_nothrow_callable) -> R {
			return std::invoke(*static_cast<decltype(plambda)>(obj), std::forward<Args>(args)...);
			};
	}

	constexpr R operator()(Args... args) const noexcept(is_nothrow_callable) {
		return callback_(obj_, std::forward<Args>(args)...);
	}
};

template <typename R, typename... Args, typename F>
auto make_function_ref(F&& f) -> function_ref<R(Args...)> {
	return function_ref<R(Args...)>(std::forward<F>(f));
}

