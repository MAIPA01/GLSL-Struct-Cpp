#pragma once

namespace glsl::extra {

#pragma region LOGIC_EXPRESIONS
	template<auto A, auto B> constexpr bool is_eq_v = (A == B);
	template<auto A, auto B> constexpr bool is_gteq_v = (A >= B);
	template<auto A, auto B> constexpr bool is_lteq_v = (A <= B);
#pragma endregion

#pragma region IS_IN
	template<class T, class U, class... Us> constexpr bool is_type_in_v = (std::is_same_v<T, U> || (sizeof...(Us) > 0 ? (std::is_same_v<T, Us> || ...) : true));
	
	template<auto A, auto B, auto... Cs> constexpr bool is_in_v = (is_eq_v<A, B> || (sizeof...(Cs) > 0 ? (is_eq_v<A, Cs> || ...) : true));

	template<size_t N1, size_t N2, size_t... Ns> constexpr bool is_num_in_v = is_in_v<N1, N2, Ns...>;
#pragma endregion

#pragma region IS_IN_RANGE
	template<auto A, auto Min, auto Max> constexpr bool is_in_range_v = (is_gteq_v<A, Min> && is_lteq_v<A, Max>);

	template<size_t N, size_t Min, size_t Max> constexpr bool is_num_in_range_v = is_in_range_v<N, Min, Max>;
#pragma endregion
	
#pragma region TESTS
	template<bool Test, class Ta, class Tb> struct type_test {
		using type = Ta;
	};
	template<class Ta, class Tb> struct type_test<false, Ta, Tb> {
		using type = Tb;
	};
	template<bool Test, class Ta, class Tb> using type_test_t = type_test<Test, Ta, Tb>::type;
#pragma endregion
	
#pragma region UNIQUE_TYPES
	template<class... Ts> struct types_holder {
		static constexpr size_t types_num = sizeof...(Ts);
	};

	template<class T, class U> struct unique_impl {	};
	template<class... Ts, class T, class... Us> struct unique_impl<types_holder<Ts...>, types_holder<T, Us...>> {
		using type = type_test_t<is_type_in_v<T, Ts...>,
			unique_impl<types_holder<Ts...>, types_holder<Us...>>,
			unique_impl<types_holder<Ts..., T>, types_holder<Us...>>>;
	};
	template<class... Ts> struct unique_impl<types_holder<Ts...>, types_holder<>> {
		using type = types_holder<Ts...>;
	};
	template<class... Ts> using unique_types = unique_impl<types_holder<>, types_holder<Ts...>>::type;
#pragma endregion

	template<typename T> const T& unmove(T&& x) {
		return x;
	};
}