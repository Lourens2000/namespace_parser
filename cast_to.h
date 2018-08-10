namespace ct_parser {
    namespace variadic {

        /**
            @brief May be updated => cast_to<typename T, char C0, char... Cs>
                Mainly based on specializations; still use of helper aliases - especially for converting std::integer_sequence<...>
        */

        template <int i, char C0, char... Cs>
        struct to_int
            : std::integral_constant<int, to_int<i + int(C0 - '0')*tmp_pow<10, sizeof... (Cs)>::value, Cs...>::value>
        {
            static_assert(is_number<C0, Cs...>::value && !is_decimal_number<C0, Cs...>::value, "Casting from variadic [CHAR...] to [INT] has failed!");
            // assertion should only occur once...
        };


        template <int i, char C>
        struct to_int<i, C>
            : std::integral_constant<int, i+(int)(C-'0')>
        {};

        template <typename>
        struct cast_to_int;

        template <char... Cs>
        struct cast_to_int<std::integer_sequence<char, Cs...> >
            : to_int<0, Cs...>
        {};
    }
}
