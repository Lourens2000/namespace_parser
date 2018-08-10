namespace ct_parser {
    namespace variadic {

        template <typename SEQ, char C0, char... Cs>
        struct number_substring_helper
            : std::conditional_t<is_number<C0>::value
                , number_substring_helper<typename S_add<SEQ, C0>::type, Cs...>
                , std::integral_constant<int, cast_to_int<SEQ>::value> >
        {};

        template <char C0, char... Cs> // 'false'
        struct number_substring_helper<void, C0, Cs...>
            : number_substring_helper<
                std::conditional_t<is_number<C0>::value
                    , std::integer_sequence<char, C0>, void>
                , Cs... >
        {};

        template <typename SEQ, char C>
        struct number_substring_helper<SEQ, C>
            : std::integral_constant<int
            , cast_to_int<
                std::conditional_t<
                    is_number<C>::value,
                    typename S_add<SEQ, C>::type,
                    SEQ>>::value>
        {};

        template <char C0, char... Cs>
        using number_substring = number_substring_helper<void, C0, Cs...>;

    } // namespace variadic
} // namespace parser
