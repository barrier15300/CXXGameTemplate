#pragma once

#include <type_traits>
#include <utility>
#include <functional>
#include <cstddef>
#include <memory>

class function_ref_unique_func_impl {
protected:
	struct _uniquefunc_base {
		_uniquefunc_base() noexcept = default;
		virtual ~_uniquefunc_base() noexcept = default;
	};

	template<class F>
	struct _uniquefunc : public _uniquefunc_base {
		_uniquefunc(F* f) noexcept : func_ptr(f) {}
		~_uniquefunc() noexcept override { delete func_ptr; func_ptr = nullptr; }
		F* func_ptr;
	};

	static inline std::vector<std::unique_ptr<_uniquefunc_base>> unique_functions;

	template <class F>
	static constexpr F* store_lambda(F&& f) noexcept {
		unique_functions.push_back(std::make_unique<_uniquefunc<F>>(new F(std::forward<F>(f))));
		return static_cast<_uniquefunc<F>*>(unique_functions.back().get())->func_ptr;
	}
};

template <typename>
class function_ref;

template <typename R, typename... Args>
class function_ref<R(Args...)> : function_ref_unique_func_impl {
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
		*this = function_ref([mf, pobj](Args&&... args) noexcept(is_nothrow_callable) -> R {
			return (pobj->*mf)(std::forward<Args>(args)...);
			});
	}

	template <typename T>
	constexpr function_ref(R(T::* mf)(Args...) const, const T& obj) noexcept {
		auto pobj = std::addressof(obj);
		*this = function_ref([mf, pobj](Args&&... args) noexcept(is_nothrow_callable) -> R {
			return (pobj->*mf)(std::forward<Args>(args)...);
			});
	}

	constexpr R operator()(Args... args) const noexcept(is_nothrow_callable) {
		return callback_(obj_, std::forward<Args>(args)...);
	}
};

template <typename R, typename... Args, typename F>
auto make_function_ref(F&& f) -> function_ref<R(Args...)> {
	return function_ref<R(Args...)>(std::forward<F>(f));
}

