#pragma once
# include <type_traits>
# include <utility>
# include <tuple>

template <typename C, typename V>
auto member_variable_pointer_t_impl(V C::* p) -> std::pair<C, V>;

template <auto P>
using member_variable_pointer_class_t = typename decltype(member_variable_pointer_t_impl(P))::first_type;

template <auto P>
using member_variable_pointer_variable_t = typename decltype(member_variable_pointer_t_impl(P))::second_type;

template <typename C, typename R, typename... Ps>
auto member_function_pointer_t_impl(R(C::* p)(Ps...)) -> std::tuple<C, R, std::tuple<Ps...>>;

template <auto P>
using member_function_pointer_class_t = std::tuple_element_t<0, decltype(member_function_pointer_t_impl(P))>;

template <auto P>
using member_function_pointer_return_t = std::tuple_element_t<1, decltype(member_function_pointer_t_impl(P))>;

template <auto P>
using member_function_pointer_parameters_t = std::tuple_element_t<2, decltype(member_function_pointer_t_impl(P))>;

template <auto P, size_t I>
using member_function_pointer_parameter_t = std::tuple_element_t<I, member_function_pointer_parameters_t<P>>;
