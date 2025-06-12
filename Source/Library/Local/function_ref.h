#pragma once
#include <type_traits>
#include <utility>
#include <functional>

template <typename>
class function_ref;

template <typename R, typename... Args>
class function_ref<R(Args...)> {
public:
    // デフォルト構築禁止
    function_ref() = delete;

    // コピーのみ許可（移動も不要）
    function_ref(const function_ref&) noexcept = default;
    function_ref& operator=(const function_ref&) noexcept = default;

    // 関数ポインタ対応
    constexpr function_ref(R(*func)(Args...)) noexcept
        : obj_(reinterpret_cast<void*>(func)) {
        callback_ = [](void* obj, Args&&... args) -> R {
            return reinterpret_cast<R(*)(Args...)>(obj)(std::forward<Args>(args)...);
            };
    }

    // 左辺値参照呼び出し可能な型（ラムダや関数オブジェクト）
    template <typename F>
        requires std::is_invocable_r_v<R, F&, Args...>&&
    std::is_lvalue_reference_v<F&>
        constexpr function_ref(F& f) noexcept
        : obj_(static_cast<void*>(std::addressof(f))) {
        callback_ = [](void* obj, Args&&... args) -> R {
            return std::invoke(*static_cast<F*>(obj), std::forward<Args>(args)...);
            };
    }

    // 右辺値（ラムダ）にも対応させる static 保持（非constexpr）
    template <typename F>
        requires (!std::is_lvalue_reference_v<F&&>) &&
    std::is_invocable_r_v<R, F, Args...>
        function_ref(F&& f) noexcept
        : obj_(static_cast<void*>(store_lambda(std::forward<F>(f)))) {
        callback_ = [](void* obj, Args&&... args) -> R {
            return std::invoke(*static_cast<F*>(obj), std::forward<Args>(args)...);
            };
    }

    // 呼び出し
    constexpr R operator()(Args... args) const {
        return callback_(obj_, std::forward<Args>(args)...);
    }

private:
    void* obj_;
    R(*callback_)(void*, Args&&...);

    template <typename F>
    static F* store_lambda(F&& f) noexcept {
        static F instance = std::forward<F>(f);
        return &instance;
    }
};
